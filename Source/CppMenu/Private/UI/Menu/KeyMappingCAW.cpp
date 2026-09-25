// Fill out your copyright notice in the Description page of Project Settings.


#include "Ui/Menu/KeyMappingCAW.h"
#include "Framework/Commands/InputChord.h"
#include "Components/InputKeySelector.h"
#include "Ui/MainCommonButtonBase.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateColor.h"

//Setrtings
#include "CommonTextBlock.h"
#include "Components/Image.h"

void UKeyMappingCAW::InitKeyMapping(FText pKeyName, FPlayerKeyMapping* pKey, bool pRebindGamepadKey, UEnhancedInputUserSettings* pUserSettings)
{
	KeyName = pKeyName;
	KeyRef = pKey;
	RebindGamepadKey = pRebindGamepadKey;
	UserSettings = pUserSettings;
	BIND_InputDisplayName_Text->SetText(KeyName);
}

void UKeyMappingCAW::NativeConstruct()
{
	Super::NativeConstruct();
	
	//Bind key selector
	if (BIND_InputSelector)
	{
		
		BIND_InputSelector->OnKeySelected.AddUniqueDynamic(this, &UKeyMappingCAW::OnKeySelected);
	}
	
	UpdateKey(KeyRef->GetCurrentKey());
	BIND_InputSelector->SetAllowGamepadKeys(RebindGamepadKey);
	if (KeyRef->GetAssociatedInputAction())
	{
		bMultidirectionalInput = KeyRef->GetAssociatedInputAction()->ValueType == EInputActionValueType::Axis2D;
	}
}

void UKeyMappingCAW::UpdateKey_Implementation(FKey pNewKey)
{
	FInputChord newChord = pNewKey;
	BIND_InputSelector->SetSelectedKey(newChord);
}

FKey UKeyMappingCAW::MultidirectionInputFunction(FKey pTempKey)
{
	if (RebindGamepadKey && pTempKey == FKey(EKeys::LeftMouseButton))
	{
		return FKey(EKeys::Gamepad_FaceButton_Bottom);
	}
	if (bMultidirectionalInput)
	{
		if (pTempKey == FKey(EKeys::Gamepad_LeftStick_Up) ||
			pTempKey == FKey(EKeys::Gamepad_LeftStick_Down) ||
			pTempKey == FKey(EKeys::Gamepad_LeftStick_Left) ||
			pTempKey == FKey(EKeys::Gamepad_LeftStick_Right) ||
			pTempKey == FKey(EKeys::Gamepad_RightStick_Up) ||
			pTempKey == FKey(EKeys::Gamepad_RightStick_Down) ||
			pTempKey == FKey(EKeys::Gamepad_RightStick_Left) ||
			pTempKey == FKey(EKeys::Gamepad_RightStick_Right))
		{
			return pTempKey == FKey(EKeys::Gamepad_LeftStick_Up) || 
					pTempKey == FKey(EKeys::Gamepad_LeftStick_Down) || 
					pTempKey == FKey(EKeys::Gamepad_LeftStick_Left) || 
					pTempKey == FKey(EKeys::Gamepad_LeftStick_Right) 
					? FKey(EKeys::Gamepad_Left2D) : FKey(EKeys::Gamepad_Right2D);
		}
	}
	return pTempKey;
}


void UKeyMappingCAW::OnKeySelected(FInputChord SelectedKey)
{
	FKey verifiedKey = MultidirectionInputFunction(SelectedKey.Key);
	if ((RebindGamepadKey && verifiedKey.GetDisplayName().ToString().Contains(TEXT("Gamepad"))) || !RebindGamepadKey)
	{
		newKey = verifiedKey;
		ApplyNewKey();
	}
	else
	{
		UpdateKey(KeyRef->GetCurrentKey());
	}
}

void UKeyMappingCAW::ApplyNewKey()
{
	UpdateKey(newKey);
	FMapPlayerKeyArgs KeyArgs;
	KeyArgs.MappingName = KeyRef->GetMappingName();
	KeyRef->SetCurrentKey(newKey);
	KeyArgs.NewKey = KeyRef->GetCurrentKey();
	FGameplayTagContainer FailureReason;
	UserSettings->MapPlayerKey(KeyArgs, FailureReason);
	UserSettings->ApplySettings();
	UserSettings->SaveSettings();
	OnUpdateKeyBindSignature.Broadcast();
}


FText UKeyMappingCAW::GetKeyName_Implementation() const
{
	return KeyName;
}

void UKeyMappingCAW::ResetKey_Implementation()
{
	newKey = KeyRef->GetDefaultKey();
	//ApplyNewKey();
}

void UKeyMappingCAW::UpdateAllKey_Implementation(const TArray<FKey>& AllKey)
{
	iSameKeyCount = 0;
	for (FKey eachKey : AllKey)
	{
		if (eachKey == KeyRef->GetCurrentKey())
		{
			++iSameKeyCount;
		}
	}
	
	FTextBlockStyle blockStyle;
	FLinearColor newColorAndOpacity = iSameKeyCount > 1 ? FLinearColor(1,0,0,BIND_InputSelector->GetTextStyle().ColorAndOpacity.GetSpecifiedColor().A) : 
															FLinearColor(1,1,1,BIND_InputSelector->GetTextStyle().ColorAndOpacity.GetSpecifiedColor().A);
	blockStyle = BIND_InputSelector->GetTextStyle();
	blockStyle.Font.OutlineSettings.OutlineColor.A = blockStyle.ColorAndOpacity.GetSpecifiedColor().A;
	blockStyle.ColorAndOpacity = newColorAndOpacity;
	BIND_InputSelector->SetTextStyle(blockStyle);
	
	FSlateBrush brush = BIND_KeyPicture_Image->GetBrush();
	brush.TintColor = iSameKeyCount > 1 ? FLinearColor::Red : FLinearColor::White;
	BIND_KeyPicture_Image->SetBrush(brush);
}

UInputKeySelector* UKeyMappingCAW::GetKeySelector_Implementation()
{
	return BIND_InputSelector;
}

UKeyMappingCAW* UKeyMappingCAW::GetKeyMappingWidget_Implementation()
{
	return this;
}
