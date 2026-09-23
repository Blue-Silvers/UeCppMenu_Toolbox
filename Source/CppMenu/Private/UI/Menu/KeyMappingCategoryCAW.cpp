// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/KeyMappingCategoryCAW.h"

#include "UI/RebindKeyInterface.h"
#include "Components/VerticalBox.h"

UKeyMappingCategoryCAW::UKeyMappingCategoryCAW()
{
	// UKeyMappingCategoryCAW* CategoryWidget = CreateWidget<UKeyMappingCategoryCAW>(this, CategoryWidgetClass);
	//
	// if (CategoryWidget)
	// {
	// 	CategoryWidget->InitKeyMappingCategory(CategoryName, LastWidget);
	// }
}

void UKeyMappingCategoryCAW::InitKeyMappingCategory(FText pKeyCategoryName, UWidget* pLastWidgetNav)
{
	KeyCategoryName = pKeyCategoryName;
	LastWidgetNav = pLastWidgetNav;
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
		const TArray<UWidget*>& widgets = BIND_InputList_VB->GetAllChildren();
		if (widgets[widgets.Num() - 2])
		{
			NewKeyMapping->SetNavigationRuleExplicit(EUINavigation::Up, widgets[widgets.Num() - 2]);
			widgets[widgets.Num() - 2]->SetNavigationRuleExplicit(EUINavigation::Down, NewKeyMapping);
		}
		else
		{
			if (widgets.Num() - 2 == 0)
			{
				UKeyMappingCategoryCAW* categoryWidget = Cast<UKeyMappingCategoryCAW>(LastWidgetNav);
				UWidget* lastIndewWidget = categoryWidget->BIND_InputList_VB->GetAllChildren()[BIND_InputList_VB->GetAllChildren().Num() - 1];
				NewKeyMapping->SetNavigationRuleExplicit(EUINavigation::Up, lastIndewWidget);
				
				//Double check (NEED REWORK)
				if (lastIndewWidget->Implements<URebindKeyInterface>())
				{
					NewKeyMapping->SetNavigationRuleExplicit(EUINavigation::Up, IRebindKeyInterface::Execute_GetKeySelector(lastIndewWidget));
				}
			}
		}
	}
}

void UKeyMappingCategoryCAW::CanAddNewKeyMapping()
{
	bGateOpen = true;
}

void UKeyMappingCategoryCAW::InputRebinderAlreadyHere()
{
	bGateOpen = false;
}
