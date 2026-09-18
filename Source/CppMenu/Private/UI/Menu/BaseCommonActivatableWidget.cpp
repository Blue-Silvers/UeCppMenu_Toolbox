// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/BaseCommonActivatableWidget.h"
#include "Ui/Menu/BaseMenuCommonUserWidget.h"
#include "Ui/MenuNavigationDataAsset.h"

//Setrtings
#include "Settings/UIParametersSubsystem.h"
#include "Kismet/Gameplaystatics.h"

//Controller
#include "CppMenuPlayerController.h"

void UBaseCommonActivatableWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	//Load data asset
	UUIParametersSubsystem* UIParametersSubsystem = GEngine->GetEngineSubsystem<UUIParametersSubsystem>();
	if (UIParametersSubsystem)
	{
		MenuNavigationDataAsset = UIParametersSubsystem->GetMenuNavigationInfo();
	}
}


void UBaseCommonActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	/*Player controller*/
	PlayerController = Cast<ACppMenuPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	OpenMenu();
}

void UBaseCommonActivatableWidget::OpenMenu()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UBaseCommonActivatableWidget::CloseMenu()
{
	CloseActivatableWidget();
}

void UBaseCommonActivatableWidget::AddWidgetFromSubsytem(FString WidgetName)
{
	if (!BaseMenuCommonUserWidget.IsValid() || !MenuNavigationDataAsset.IsValid()) 
	{
		return;
	}

	TSubclassOf <UCommonActivatableWidget> DesireWidget = *MenuNavigationDataAsset->MenuNavigationWidgetMap.Find(WidgetName);
	
	if(DesireWidget)
	{
		BaseMenuCommonUserWidget->AddWidgetOnStack(DesireWidget);
	}
}

void UBaseCommonActivatableWidget::CloseActivatableWidget()
{
	// Turn back on the previous Activatable Widget if valid
	if (PreviousCommonUserWidget.IsValid())
	{
		PreviousCommonUserWidget->ActivateWidget();
	}

	//Desactivate and hide this one
	DeactivateWidget();
	SetVisibility(ESlateVisibility::Collapsed);
	if(BaseMenuCommonUserWidget.IsValid())
	{
		BaseMenuCommonUserWidget->RemoveWidgetFromStack(*this);
	}
}

void UBaseCommonActivatableWidget::SetBaseMenuCommonUserWidget(UBaseMenuCommonUserWidget* InBaseMenuCommonUserWidget)
{
	BaseMenuCommonUserWidget = InBaseMenuCommonUserWidget;
}

void UBaseCommonActivatableWidget::SetPreviousCommonUserWidget(UCommonActivatableWidget* InBaseMenuCommonUserWidget)
{
	PreviousCommonUserWidget = InBaseMenuCommonUserWidget;
}
