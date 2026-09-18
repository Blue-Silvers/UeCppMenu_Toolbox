// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/BaseMenuCommonUserWidget.h"

#include "Ui/Menu/BaseCommonActivatableWidget.h"
#include "Ui/MenuNavigationDataAsset.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UBaseMenuCommonUserWidget::AddWidgetOnStack(TSubclassOf<class UCommonActivatableWidget> DesireWidget)
{
	//Check pointer
	if (!BIND_PauseMenuWidgetStack || !DesireWidget)
	{
		return;
	}

	//GetCurrent displayed widget
	UCommonActivatableWidget* PrevoiousWidget = BIND_PauseMenuWidgetStack->GetActiveWidget();

	//Create or get new Widget to dislpay
	UCommonActivatableWidget* NewWidget = BIND_PauseMenuWidgetStack->AddWidget(DesireWidget);

	//Update pointer for our Activatable Widget
	UBaseCommonActivatableWidget* BaseWidget = Cast<UBaseCommonActivatableWidget>(NewWidget);
	if (BaseWidget) 
	{
		BaseWidget->SetBaseMenuCommonUserWidget(this);
		BaseWidget->SetPreviousCommonUserWidget(PrevoiousWidget);
	}
}

void UBaseMenuCommonUserWidget::RemoveWidgetFromStack(UBaseCommonActivatableWidget& InWidget)
{
	//Check pointer
	if(!BIND_PauseMenuWidgetStack)
	{
		return;
	}

	//Remove widget from stack
	BIND_PauseMenuWidgetStack->RemoveWidget(InWidget);

	//When we call RemoveWidget, we don't necesseraly remove the item form the WidgetList
	//We just Deactivate it and hide it
	//We need to Use a  for loop to make sure that alla items are closed

	//If there's no widget, we can close it
	if(BIND_PauseMenuWidgetStack->GetNumWidgets() == 0)
	{
		CloseBaseMenu();
	}
	else 
	{
		bool bIsDeactivated = true;
		const TArray<UCommonActivatableWidget*>& WidgetList = BIND_PauseMenuWidgetStack->GetWidgetList();

		for(UCommonActivatableWidget* Widget : WidgetList)
		{
			if(Widget && Widget->IsActivated())
			{
				bIsDeactivated = false;
				break;
			}
		}

		if(bIsDeactivated)
		{
			CloseBaseMenu();
		}
	}
}


void UBaseMenuCommonUserWidget::CloseBaseMenu()
{
	SetVisibility(ESlateVisibility::Collapsed);
	RemoveFromParent();
}

