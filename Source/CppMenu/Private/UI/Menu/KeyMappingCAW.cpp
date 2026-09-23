// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/Menu/KeyMappingCAW.h"
#include "Components/TextBlock.h"
#include "Framework/Commands/InputChord.h"
#include "Components/InputKeySelector.h"
#include "Ui/MainCommonButtonBase.h"

//Controller
#include "CppMenuPlayerController.h"

//Setrtings
#include "Kismet/Gameplaystatics.h"

void UKeyMappingCAW::NativeConstruct()
{
	Super::NativeConstruct();

	if (BIND_Reset_Button)
	{
		BIND_Reset_Button->OnButtonClicked.AddUniqueDynamic(this, &UKeyMappingCAW::OnResetKeyMapping);
	}
	//Bind key selctor
	if (BIND_InputSelector)
	{
		BIND_InputSelector->OnKeySelected.AddUniqueDynamic(this, &UKeyMappingCAW::OnKeySelected);
	}
}

void UKeyMappingCAW::SetInputName(FName InName)
{
	InputName = InName;
}

void UKeyMappingCAW::SetInputDisplayName(FText InName)
{
	if (BIND_InputDisplayName_Text)
	{
		BIND_InputDisplayName_Text->SetText(InName);
	}
}

void UKeyMappingCAW::SetInputSelector(FEnhancedActionKeyMapping& GivenKey)
{
	if (BIND_InputSelector)
	{
		BIND_InputSelector->SetSelectedKey(GivenKey.Key);
		DisplayKey = GivenKey;
	}
}

void UKeyMappingCAW::OnKeySelected(FInputChord SelectedKey)
{
	//Send Selected key to the player controller
	ACppMenuPlayerController* PlayerController = Cast<ACppMenuPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		//PlayerController->OnUpdateMappableKey(InputName, SelectedKey.Key);
	}
}

void UKeyMappingCAW::OnResetKeyMapping()
{
	//Send reset key to the player controller
	ACppMenuPlayerController* PlayerController = Cast<ACppMenuPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController)
	{
		//PlayerController->ResetKey(InputName, DisplayKey, this);
	}
}

FText UKeyMappingCAW::GetKeyName_Implementation() const
{
	return KeyName;
}
