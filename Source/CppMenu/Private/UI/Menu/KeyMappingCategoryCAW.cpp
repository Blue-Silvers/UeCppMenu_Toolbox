// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/KeyMappingCategoryCAW.h"

#include "CommonTextBlock.h"
#include "UI/RebindKeyInterface.h"
#include "Components/VerticalBox.h"

void UKeyMappingCategoryCAW::InitKeyMappingCategory(FText pKeyCategoryName, UWidget* pLastWidgetNav)
{
	KeyCategoryName = pKeyCategoryName;
	LastWidgetNav = pLastWidgetNav;
	if (KeyCategoryName.IsEmpty())
	{
		BIND_RebindInputCategory_VB->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		BIND_RebindInputCategory_VB->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	BIND_Category_Text->SetText(KeyCategoryName);
}


void UKeyMappingCategoryCAW::NativeConstruct()
{
	Super::NativeConstruct();
	if (KeyCategoryName.IsEmpty())
	{
		BIND_RebindInputCategory_VB->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UKeyMappingCategoryCAW::AddNewKeyMapping(UKeyMappingCAW* NewKeyMapping)
{
	CanAddNewKeyMapping();
	for (UWidget* widget : BIND_InputList_VB->GetAllChildren())
	{
		if (widget->Implements<URebindKeyInterface>())
		{
			if (NewKeyMapping->Implements<URebindKeyInterface>())
			{
				if (IRebindKeyInterface::Execute_GetKeyName(widget).EqualTo(IRebindKeyInterface::Execute_GetKeyName(NewKeyMapping)))
				{
					InputRebinderAlreadyHere();
					return;
				}
			}
		}
	}
	if (bGateOpen)
	{
		BIND_InputList_VB->AddChild(NewKeyMapping);
	}
}

void UKeyMappingCategoryCAW::SetLastWidget(UWidget* pLastWidget)
{
	LastWidgetNav = pLastWidget;
}

void UKeyMappingCategoryCAW::CanAddNewKeyMapping()
{
	bGateOpen = true;
}

void UKeyMappingCategoryCAW::InputRebinderAlreadyHere()
{
	bGateOpen = false;
}
