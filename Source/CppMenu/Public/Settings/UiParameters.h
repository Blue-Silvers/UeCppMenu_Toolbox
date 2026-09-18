// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UiParameters.generated.h"

/**
 * 
 */
UCLASS(Config = Engine, BlueprintType, Blueprintable, defaultconfig, meta = (DisplayName = "UI  Parameters"))
class CPPMENU_API UUiParameters : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(config, EditAnywhere, Category = Settings, meta = (AllowedClasses = "/Script/Engine.DataAsset"))
	FSoftObjectPath MenuNavigationInfoPath;
};
