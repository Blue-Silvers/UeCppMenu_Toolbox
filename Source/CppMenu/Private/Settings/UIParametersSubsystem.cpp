// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/UIParametersSubsystem.h"
#include "UI/MenuNavigationDataAsset.h"
#include "Settings/UiParameters.h"

UMenuNavigationDataAsset* UUIParametersSubsystem::GetMenuNavigationInfo()
{
	//If reference wasn't load, try to load it
	if(!MenuNavigationInfo)
	{
		UUiParameters* UIParameters = Cast<UUiParameters>(UUiParameters::StaticClass()->GetDefaultObject());
		if (UIParameters)
		{
			MenuNavigationInfo = Cast<UMenuNavigationDataAsset>(UIParameters->MenuNavigationInfoPath.TryLoad());
		}
	}

	return MenuNavigationInfo;
}

