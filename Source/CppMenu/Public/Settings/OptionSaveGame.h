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
	//Mouse Sensitivity Functions
		/* Sets mouse sensitivity */
	void SetMouseSensitivityX(float NewSensitivity);
	void SetMouseSensitivityY(float NewSensitivity);
		/* Get mouse sensitivity */
	float GetMouseSensitivityX() const;
	float GetMouseSensitivityY() const;
	//End Mouse Sensitivity Functions
	
	//Audio Functions
		/* Sets audio volume */
	void SetGeneralVolume(float NewVolume);
	void SetMusicVolume(float NewVolume);
	void SetSoundVolume(float NewVolume);
		/* Get audio volume */
	float GetGeneralVolume() const;
	float GetMusicVolume() const;
	float GetSoundVolume() const;
	//End Audio Functions
	
protected:
	//Mouse Sensitivity
	UPROPERTY(SaveGame)
	float MouseSensitivityX = 1.f;
	UPROPERTY(SaveGame)
	float MouseSensitivityY = 1.f;	
	//End Mouse Sensitivity
	
	//Audio
	UPROPERTY(SaveGame)
	float GeneralVolume = 100.f;	
	UPROPERTY(SaveGame)
	float MusicVolume = 100.f;	
	UPROPERTY(SaveGame)
	float SoundVolume = 100.f;
	//End Audio
};
