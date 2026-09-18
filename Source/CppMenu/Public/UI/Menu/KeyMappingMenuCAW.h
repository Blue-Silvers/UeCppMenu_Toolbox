// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ui/Menu/BaseCommonActivatableWidget.h"
#include "KeyMappingMenuCAW.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CPPMENU_API UKeyMappingMenuCAW : public UBaseCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	//Button
protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_ExistMenu_Button = nullptr;

	//End of Button


	//Key Mappings
protected:
	void DisplayKeys();

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UVerticalBox> BIND_KeyMappingsMovement_VB = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UVerticalBox> BIND_KeyMappingsAction_VB = nullptr;
	UPROPERTY(EditAnywhere, Category = "Key Mapping User Widget")
	FString KeyMappingWidgetName = FString();

	UPROPERTY(EditAnywhere, Category = "Key Mapping User Widget")
	FString MovementCategoryName = "Movement";
	UPROPERTY(EditAnywhere, Category = "Key Mapping User Widget")
	FString ActionCategoryName = "Action";

	//End of Key Mappings
};
