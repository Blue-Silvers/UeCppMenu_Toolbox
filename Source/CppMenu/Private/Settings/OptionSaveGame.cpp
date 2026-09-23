// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/OptionSaveGame.h"

void UOptionSaveGame::SetMouseSensitivityX(float NewSensitivity)
{
	MouseSensitivityX = NewSensitivity;
}

void UOptionSaveGame::SetMouseSensitivityY(float NewSensitivity)
{
	MouseSensitivityY = NewSensitivity;
}

float UOptionSaveGame::GetMouseSensitivityX() const 
{
	return  MouseSensitivityX;
}

float UOptionSaveGame::GetMouseSensitivityY() const 
{
	return MouseSensitivityY;
}

void UOptionSaveGame::SetGeneralVolume(float NewVolume)
{
	GeneralVolume = NewVolume;
}

void UOptionSaveGame::SetMusicVolume(float NewVolume)
{
	MusicVolume = NewVolume;
}

void UOptionSaveGame::SetSoundVolume(float NewVolume)
{
	SoundVolume = NewVolume;
}

float UOptionSaveGame::GetGeneralVolume() const
{
	return GeneralVolume; 
}

float UOptionSaveGame::GetMusicVolume() const
{
	return MusicVolume; 
}

float UOptionSaveGame::GetSoundVolume() const
{
	return SoundVolume;
}
