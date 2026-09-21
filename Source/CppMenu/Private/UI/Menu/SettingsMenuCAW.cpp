// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/SettingsMenuCAW.h"
#include "Ui/MainCommonButtonBase.h"

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
	}
}

void USettingsMenuCAW::OnAudioButtonClicked()
{
	AddWidgetFromSubsytem(BIND_Audio_Button->GetName());
}

void USettingsMenuCAW::OnGraphicsClicked()
{
	AddWidgetFromSubsytem(BIND_Graphics_Button->GetName());
}

void USettingsMenuCAW::OnControlsButtonClicked()
{
	AddWidgetFromSubsytem(BIND_Controls_Button->GetName());
}