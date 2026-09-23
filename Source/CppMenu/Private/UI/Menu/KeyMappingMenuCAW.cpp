// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/KeyMappingMenuCAW.h"
#include "Ui/MainCommonButtonBase.h"
#include "Ui/Menu/KeyMappingCAW.h"
#include "Ui/MenuNavigationDataAsset.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

//Controller
#include "CppMenuPlayerController.h"

//Input
#include "EnhancedInputSubsystems.h"

void UKeyMappingMenuCAW::NativeConstruct()
{
	Super::NativeConstruct();


	//Bind button
	if (BIND_ExistMenu_Button)
	{
		BIND_ExistMenu_Button->OnButtonClicked.AddUniqueDynamic(this, &UKeyMappingMenuCAW::CloseMenu);
	}

	//Display mappable Key
	DisplayKeys();
}

void UKeyMappingMenuCAW::DisplayKeys()
{
	/*Player controller*/
	if (!BIND_KeyMappingsMovement_VB || !BIND_KeyMappingsAction_VB || KeyMappingWidgetName.IsEmpty() || !PlayerController.IsValid())
	{
		return;
	}

	if (BIND_KeyMappingsMovement_VB->GetChildrenCount() != 1)
	{
		return;
	}

	if (BIND_KeyMappingsAction_VB->GetChildrenCount() != 1)
	{
		return;
	}
	/*Player controller*/
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!InputSubsystem)
	{
		return;
	}

	//Get Widget template
	TSubclassOf<UCommonActivatableWidget> KeybindingWidgetTemplate = *MenuNavigationDataAsset->MenuNavigationWidgetMap.Find(KeyMappingWidgetName);
	if (!KeybindingWidgetTemplate)
	{
		return;
	}

	//Get all mappable keys
	TArray<FEnhancedActionKeyMapping> MappableKeys = InputSubsystem->GetAllPlayerMappableActionKeyMappings();
	if (MappableKeys.IsEmpty())
	{
		return;
	}

	//For all mappable keys
	for (FEnhancedActionKeyMapping& Key : MappableKeys)
	{
		//WIP
	}		
}

