// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CppMenuPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract, config="Game")
class CPPMENU_API ACppMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	ACppMenuPlayerController();

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;
	
	// Inputs
protected:
	TWeakObjectPtr<class UEnhancedInputLocalPlayerSubsystem> InputSubsystem = nullptr;
	TWeakObjectPtr<class UEnhancedInputUserSettings> InputUserSettings = nullptr;
	//End Inputs
	//
	//Pause menu
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input");
	TObjectPtr<class UInputAction> InputActionPause = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pause");
	FString PauseMenuBackgroundWidgetName = FString();
	UPROPERTY(EditAnywhere, Category = "Pause");
	FString PauseMenuActivatableWidgetName = FString();

	TWeakObjectPtr<class UMenuNavigationDataAsset> MenuNavigationDataAsset = nullptr;

protected:
	void OnPauseInputPress();

	//end of Pause menu
};
