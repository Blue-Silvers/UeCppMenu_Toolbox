// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/InputKeySelector.h"
#include "RebindKeyInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class URebindKeyInterface : public UInterface
{
	GENERATED_BODY()
	
};


class CPPMENU_API IRebindKeyInterface
{
	GENERATED_BODY()

	//This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Rebind Key")
	FText GetKeyName() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Rebind Key")
	void ResetKey();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Rebind Key")
	void UpdateAllKey(const TArray<FKey>& AllKey);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Rebind Key")
	UInputKeySelector* GetKeySelector();
 
	//UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Interface")
};