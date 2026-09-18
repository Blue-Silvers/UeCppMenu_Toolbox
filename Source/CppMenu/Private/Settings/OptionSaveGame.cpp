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
