// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ui/Menu/BaseCommonActivatableWidget.h"
#include "CoreTypes.h"
#include "KeyMappingMenuCAW.generated.h"

UCLASS(Abstract)
class CPPMENU_API UKeyMappingMenuCAW : public UBaseCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;


//Key Mappings
protected:	
	//Button functions
	UFUNCTION()
	void OnResetAllControlsClicked();
	UFUNCTION()
	void OnKeyboardPageButtonClicked();
	UFUNCTION()
	void OnGamepadPageButtonClicked();
	//End of Button functions
	
	//Populate scrollbox functions
	void FindKeys(bool bIsGamepad);
	void CleanInput(bool bIsGamepad);
	void CheckSimilarKey();
	void AddKeyToScrollBox();
	void ReloadKeyMapping();
	//End of Populate scrollbox functions

	

protected:
	//Binding
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_KeyboardPage_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_GamepadPage_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_ResetAllControls_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonAnimatedSwitcher> BIND_KeyMappingContainer_Switcher = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonHierarchicalScrollBox> BIND_Keyboard_SB = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonHierarchicalScrollBox> BIND_Gamepad_SB = nullptr;
	//End of Binding
	
	//Other variables
	UEnhancedInputUserSettings* InputUserSettings = nullptr;
	TArray<UKeyMappingCAW*> InputList;
	TMap<FString, UKeyMappingCategoryCAW*> CategoryMap;
	TMap<const UInputAction*, FPlayerKeyMapping> AllKeysKeyboardMap;
	TMap<const UInputAction*, FPlayerKeyMapping> AllKeysGamepadMap;
	TArray<FKey> AllKeys;
	TArray<FPlayerKeyMapping*> AllKeysFounded;
	bool bRebindGamepad = false;
	UMainCommonButtonBase* Controls_Button = nullptr;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widget")
	TSubclassOf<class UKeyMappingCategoryCAW> WidgetCategory = nullptr;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widget")
	TSubclassOf<class UKeyMappingCAW> WidgetKey = nullptr;
	//End of Other variables
	
	
//End of Key Mappings
};
