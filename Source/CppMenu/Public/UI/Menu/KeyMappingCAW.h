// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "UI/RebindKeyInterface.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "KeyMappingCAW.generated.h"

DECLARE_MULTICAST_DELEGATE(FUpdateKeyBindSignature);

UCLASS()
class CPPMENU_API UKeyMappingCAW : public UCommonActivatableWidget, public IRebindKeyInterface
{
	GENERATED_BODY()

public:
	void InitKeyMapping(FText pKeyName, FPlayerKeyMapping pKey, bool pRebindGamepadKey, UEnhancedInputUserSettings* pUserSettings);
	
protected:
	virtual void NativeConstruct() override;

//Keybinding
protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Rebind Key")
	void UpdateKey( FKey pNewKey);
	FKey MultidirectionInputFunction( FKey pTempKey);
	UFUNCTION()
	void OnKeySelected(FInputChord pKey);
	void ApplyNewKey();

protected:
	//Binding
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<class UInputKeySelector> BIND_InputSelector = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonTextBlock> BIND_InputDisplayName_Text = nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<class UImage> BIND_KeyPicture_Image = nullptr;
	//End of Binding
	
	//Initialize variables
	UPROPERTY(EditAnywhere, Category = "Key Mapping Settings")
	FText KeyName;
	UPROPERTY(EditAnywhere, Category = "Key Mapping Settings")
	FPlayerKeyMapping Key;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Key Mapping Settings")
	bool RebindGamepadKey = false;
	UPROPERTY(EditAnywhere, Category = "Key Mapping Settings")
	UEnhancedInputUserSettings* UserSettings;
	//End of Initialize variables
	
	//Other variables
	FKey newKey;
	int iSameKeyCount = 0;
	bool bMultidirectionalInput = false;
	//End of Other variables
	
//End of Keybinding
	
	//IRebindKeyInterface
public:
	virtual FText GetKeyName_Implementation() const override;
	virtual void ResetKey_Implementation() override;
	virtual void UpdateAllKey_Implementation(const TArray<FKey>& AllKey) override;
	virtual UInputKeySelector* GetKeySelector_Implementation() override;
	virtual UKeyMappingCAW* GetKeyMappingWidget_Implementation() override;
	//End of IRebindKeyInterface
	
	//Event dispatchers
	FUpdateKeyBindSignature OnUpdateKeyBindSignature;
	//End of Event dispatchers
};
