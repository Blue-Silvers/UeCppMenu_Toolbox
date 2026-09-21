// Copyright Epic Games, Inc. All Rights Reserved.


#include "CppMenuPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "CppMenuCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "CppMenu.h"
#include "Widgets/Input/SVirtualJoystick.h"

//UI
#include "Ui/Menu/BaseMenuCommonUserWidget.h"
#include "Ui/MenuNavigationDataAsset.h"
#include "CommonActivatableWidget.h"

// Inputs
#include "InputAction.h"
#include "EnhancedInputComponent.h"

//System
#include "Settings/UIParametersSubsystem.h"

ACppMenuPlayerController::ACppMenuPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ACppMenuCameraManager::StaticClass();
}

void ACppMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Load subsystem
	UUIParametersSubsystem* UIParametersSubsystem = GEngine->GetEngineSubsystem<UUIParametersSubsystem>();
	if (UIParametersSubsystem)
	{
		MenuNavigationDataAsset = UIParametersSubsystem->GetMenuNavigationInfo();
	}
	
	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogCppMenu, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void ACppMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
	InputSubsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!InputSubsystem.IsValid()) 
	{
		return;
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent) 
	{
		return;
	}

	if (InputActionPause)
	{
		EnhancedInputComponent->BindAction(InputActionPause, ETriggerEvent::Triggered, this, &ACppMenuPlayerController::OnPauseInputPress);
	}
	
}

bool ACppMenuPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void ACppMenuPlayerController::OnPauseInputPress()
{
	if (MenuNavigationDataAsset.IsValid()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("MenuNavigationDataAsset if valid"));

	}
	if (!MenuNavigationDataAsset.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("isn't MenuNavigationDataAsset"));
	}
	if (!MenuNavigationDataAsset.IsValid() || PauseMenuBackgroundWidgetName.IsEmpty() || PauseMenuActivatableWidgetName.IsEmpty()) 
	{
		return;
	}

	TSubclassOf<UUserWidget> MenuWidgetTemplate = *MenuNavigationDataAsset->MenuNavigationMap.Find(PauseMenuBackgroundWidgetName);
	UE_LOG(LogTemp, Warning, TEXT("Pause Press"));

	if (!MenuWidgetTemplate)
	{
		return;
	}

	//Spawn background widget
	UBaseMenuCommonUserWidget* MenuWidget = CreateWidget<UBaseMenuCommonUserWidget>(this, MenuWidgetTemplate);
	if (MenuWidget)
	{
		MenuWidget->AddToViewport(0);

		TSubclassOf<UCommonActivatableWidget> MenuActivatableWidgetTemplate = *MenuNavigationDataAsset->MenuNavigationWidgetMap.Find(PauseMenuActivatableWidgetName);

		if (MenuActivatableWidgetTemplate)
		{
			MenuWidget->AddWidgetOnStack(MenuActivatableWidgetTemplate);
		}
	}
}