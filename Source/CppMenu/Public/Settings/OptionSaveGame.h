// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "OptionSaveGame.generated.h"


UCLASS()
class CPPMENU_API UOptionSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	void SetMouseSensitivityX(float NewSensitivity);
	void SetMouseSensitivityY(float NewSensitivity);
	float GetMouseSensitivityX() const;
	float GetMouseSensitivityY() const;
	
protected:
	UPROPERTY(SaveGame)
	float MouseSensitivityX = 1.f;
	UPROPERTY(SaveGame)
	float MouseSensitivityY = 1.f;
};
