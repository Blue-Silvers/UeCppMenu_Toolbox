// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/SettingsMenuCAW.h"

#include "GameFramework/PlayerController.h"
#include "Ui/Menu/BaseCommonActivatableWidget.h"
#include "Ui/MainCommonButtonBase.h"
#include "UI/MenuNavigationDataAsset.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void USettingsMenuCAW::NativeConstruct()
{
	Super::NativeConstruct();

	//Bind all Buttons
	if (BIND_Audio_Button)
	{
		BIND_Audio_Button->OnButtonClicked.AddUniqueDynamic(this, &USettingsMenuCAW::OnAudioButtonClicked);
	}
	if (BIND_Graphics_Button)
	{
		BIND_Graphics_Button->OnButtonClicked.AddUniqueDynamic(this, &USettingsMenuCAW::OnGraphicsClicked);
	}
	if (BIND_Controls_Button)
	{
		BIND_Controls_Button->OnButtonClicked.AddUniqueDynamic(this, &USettingsMenuCAW::OnControlsButtonClicked);
	}
	if (BIND_Quit_Button)
	{
		BIND_Quit_Button->OnButtonClicked.AddUniqueDynamic(this, &USettingsMenuCAW::CloseMenu);
		//USettingsMenuCAW::CloseMenu();
	}
}

void USettingsMenuCAW::OnAudioButtonClicked()
{
	//BIND_Settings_Switcher->SetActiveWidgetIndex(0);
	TSubclassOf <UCommonActivatableWidget> DesireWidget = *MenuNavigationDataAsset->MenuNavigationSubWidgetMap.Find(BIND_Audio_Button->GetName());
	if(DesireWidget)
	{
		BIND_CommonActivatableWidgetStack->AddWidget(DesireWidget);
		//BIND_CommonActivatableWidgetStack->SetFocus();
	}
}

void USettingsMenuCAW::OnGraphicsClicked()
{
	//BIND_Settings_Switcher->SetActiveWidgetIndex(1);
	TSubclassOf <UCommonActivatableWidget> DesireWidget = *MenuNavigationDataAsset->MenuNavigationSubWidgetMap.Find(BIND_Graphics_Button->GetName());
	if(DesireWidget)
	{
		BIND_CommonActivatableWidgetStack->AddWidget(DesireWidget);
		//BIND_CommonActivatableWidgetStack->SetFocus();

	}
}

void USettingsMenuCAW::OnControlsButtonClicked()
{
	//BIND_Settings_Switcher->SetActiveWidgetIndex(2);
	TSubclassOf <UCommonActivatableWidget> DesireWidget = *MenuNavigationDataAsset->MenuNavigationSubWidgetMap.Find(BIND_Controls_Button->GetName());
	if(DesireWidget)
	{
		BIND_CommonActivatableWidgetStack->AddWidget(DesireWidget);
		//BIND_CommonActivatableWidgetStack->SetFocus();
	}
	
}
