// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainCommonButtonBase.h"
#include "CommonTextBlock.h"

void UMainCommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (BIND_ButtonButtonText)
	{
		BIND_ButtonButtonText->SetText(ButtonText);
	}

}

void UMainCommonButtonBase::NativeOnClicked()
{
	Super::NativeOnClicked();
	OnButtonClicked.Broadcast();
}
