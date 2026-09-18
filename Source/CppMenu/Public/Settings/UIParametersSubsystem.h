// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "UIParametersSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CPPMENU_API UUIParametersSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	class UMenuNavigationDataAsset* GetMenuNavigationInfo();

protected:
	UPROPERTY(BlueprintReadOnly, transient, EditAnywhere, Category = "UI Parameters")
	TObjectPtr<class UMenuNavigationDataAsset> MenuNavigationInfo;
};
