// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RebindKeyInterface.h"
#include "Components/InputKeySelector.h"

FText IRebindKeyInterface::GetKeyName()
{
	return FText::GetEmpty();
}

void IRebindKeyInterface::ResetKey()
{
}

void IRebindKeyInterface::UpdateAllKey(TArray<FKey> allKey)
{
}

UInputKeySelector* IRebindKeyInterface::GetKeySelector()
{
	return nullptr;
}
