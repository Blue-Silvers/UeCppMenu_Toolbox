// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Ui/Menu/KeyMappingCAW.h"
#include "KeyMappingCategoryCAW.generated.h"

UCLASS()
class CPPMENU_API UKeyMappingCategoryCAW : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	UKeyMappingCategoryCAW();
	void InitKeyMappingCategory(FText pKeyCategoryName, UWidget* pLastWidgetNav);

protected:
	virtual void NativeConstruct() override;
	
	void AddNewKeyMapping(UKeyMappingCAW* NewKeyMapping);
	void CanAddNewKeyMapping();
	void InputRebinderAlreadyHere();
	
protected:
	//Binding
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UVerticalBox> BIND_RebindInputCategory_VB = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UVerticalBox> BIND_InputList_VB = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonTextBlock> BIND_Category_Text = nullptr;
	//End of Binding

	UPROPERTY(EditAnywhere, Category = "Key Mapping Settings")
	FText KeyCategoryName = FText();
	UPROPERTY(EditAnywhere, Category = "Key Mapping Settings")
	UWidget* LastWidgetNav = nullptr;
	
	bool bGateOpen = false;
};
