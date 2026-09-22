// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MenuNavigationDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CPPMENU_API UMenuNavigationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Menu Navigation")
	TMap<FString, TSubclassOf<class UUserWidget>> MenuNavigationMap;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Menu Navigation")
	TMap<FString, TSubclassOf<class UCommonActivatableWidget>> MenuNavigationWidgetMap;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Menu Navigation")
	TMap<FString, TSubclassOf<class UCommonActivatableWidget>> MenuNavigationSubWidgetMap;
};
