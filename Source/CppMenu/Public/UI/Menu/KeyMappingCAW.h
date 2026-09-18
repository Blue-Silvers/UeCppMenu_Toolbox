// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "EnhancedActionKeyMapping.h"
#include "KeyMappingCAW.generated.h"

/**
 * 
 */
UCLASS()
class CPPMENU_API UKeyMappingCAW : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	//Keybinding
public:
	void SetInputName(FName InName);
	void SetInputDisplayName(FText InName);
	void SetInputSelector(FEnhancedActionKeyMapping& GivenKey);

protected:
	UFUNCTION()
	void OnKeySelected(struct FInputChord SelectedKey);
	UFUNCTION()
	void OnResetKeyMapping();

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_Reset_Button = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UInputKeySelector> BIND_InputSelector = nullptr;
	FName InputName;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> BIND_InputDisplayName_Text = nullptr;
	FEnhancedActionKeyMapping DisplayKey;

	//End of Keybinding
};
