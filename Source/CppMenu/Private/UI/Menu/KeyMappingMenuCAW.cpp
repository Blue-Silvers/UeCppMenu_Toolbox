// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/KeyMappingMenuCAW.h"
#include "Ui/MainCommonButtonBase.h"
#include "Ui/Menu/KeyMappingCAW.h"

//Input
#include "CommonAnimatedSwitcher.h"
#include "CommonHierarchicalScrollBox.h"
#include "EnhancedInputSubsystems.h"
#include "UI/Menu/KeyMappingCategoryCAW.h"
#include "UI/RebindKeyInterface.h"
#include "CoreTypes.h"
#include "UserSettings/EnhancedInputUserSettings.h"

void UKeyMappingMenuCAW::NativeConstruct()
{
	Super::NativeConstruct();


	//Bind button
	if (BIND_KeyboardPage_Button)
	{
		BIND_KeyboardPage_Button->OnButtonClicked.AddUniqueDynamic(this, &UKeyMappingMenuCAW::OnKeyboardPageButtonClicked);
	}
	if (BIND_GamepadPage_Button)
	{
		BIND_GamepadPage_Button->OnButtonClicked.AddUniqueDynamic(this, &UKeyMappingMenuCAW::OnGamepadPageButtonClicked);
	}
	if (BIND_ResetAllControls_Button)
	{
		BIND_ResetAllControls_Button->OnButtonClicked.AddUniqueDynamic(this, &UKeyMappingMenuCAW::OnResetAllControlsClicked);
	}
	
	Controls_Button = BIND_KeyboardPage_Button;

	APlayerController* localPlayerController = GetOwningPlayer();
	if (!localPlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not found"));
		return;
	}

	ULocalPlayer* localPlayer = localPlayerController->GetLocalPlayer();
	if (!localPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("Local Player not found"));

		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(localPlayer);

	if (!EnhancedInputSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputSubsystem not found"));

		return;
	}

	InputUserSettings = EnhancedInputSubsystem->GetUserSettings();
	//Display mappable Key
	OnKeyboardPageButtonClicked();
}

void UKeyMappingMenuCAW::OnResetAllControlsClicked()
{
	TArray<UKeyMappingCAW*> InputListCopy = InputList;
	for (UKeyMappingCAW* eachKey : InputListCopy)
	{
		if (IsValid(eachKey) && eachKey->Implements<URebindKeyInterface>())
		{
			IRebindKeyInterface::Execute_ResetKey(eachKey); // reset individuel (sans se soucier du rebuild répété)
		}
	}

	// Un seul rebuild propre à la fin, sur l'état final
	FindKeys(bRebindGamepad);
}

void UKeyMappingMenuCAW::OnKeyboardPageButtonClicked()
{
	FindKeys(false);
	BIND_KeyMappingContainer_Switcher->SetActiveWidgetIndex(0);
}

void UKeyMappingMenuCAW::OnGamepadPageButtonClicked()
{
	FindKeys(true);
	BIND_KeyMappingContainer_Switcher->SetActiveWidgetIndex(1);
}

void UKeyMappingMenuCAW::FindKeys(bool bIsGamepad)
{
	CleanInput(bIsGamepad);
	if (InputUserSettings)
	{
		bRebindGamepad = bIsGamepad;
		TArray<FKeyMappingRow> keyMappingRows;
		InputUserSettings->GetActiveKeyProfile()->GetPlayerMappingRows().GenerateValueArray(keyMappingRows);
		for (FKeyMappingRow eachKeyMappingRow : keyMappingRows)
		{
			for (FPlayerKeyMapping eachKeyMapping : eachKeyMappingRow.Mappings.Array())
			{

				if (eachKeyMapping.GetSlot() == EPlayerMappableKeySlot::First)
				{
					if (eachKeyMapping.GetDefaultKey().GetDisplayName().ToString().Contains(TEXT("Gamepad")))
					{
						AllKeysGamepadMap.Add(eachKeyMapping.GetAssociatedInputAction(), eachKeyMapping);
						AllKeys.Add(eachKeyMapping.GetCurrentKey());
					}
					else
					{
						AllKeysKeyboardMap.Add(eachKeyMapping.GetAssociatedInputAction(), eachKeyMapping);
						AllKeys.Add(eachKeyMapping.GetCurrentKey());
					}
				}
			}
			AddKeyToScrollBox();
		}
		CheckSimilarKey();
	}
}

void UKeyMappingMenuCAW::CleanInput(bool bIsGamepad)
{
	if (bIsGamepad)
	{
		BIND_Gamepad_SB->ClearChildren();
	}
	else
	{
		BIND_Keyboard_SB->ClearChildren();
	}
	AllKeysGamepadMap.Empty();
	AllKeysKeyboardMap.Empty();
	AllKeys.Empty();
	CategoryMap.Empty();
	InputList.Empty();
}

void UKeyMappingMenuCAW::CheckSimilarKey()
{
	for (UKeyMappingCAW* eachKey : InputList)
	{
		if (eachKey->Implements<URebindKeyInterface>())
		{
			IRebindKeyInterface::Execute_UpdateAllKey(eachKey, AllKeys);
		}
	}
}

void UKeyMappingMenuCAW::AddKeyToScrollBox()
{
	AllKeysFounded.Empty();
	TArray<const UInputAction*> keyMappingInputAction;
	bRebindGamepad ? AllKeysGamepadMap.GetKeys(keyMappingInputAction) : AllKeysKeyboardMap.GetKeys(keyMappingInputAction);
	for (const UInputAction* eachKey : keyMappingInputAction)
	{
		if (bRebindGamepad ? AllKeysGamepadMap.Find(eachKey) : AllKeysKeyboardMap.Find(eachKey))
		{
			AllKeysFounded.Add(bRebindGamepad ? AllKeysGamepadMap.Find(eachKey) : AllKeysKeyboardMap.Find(eachKey));
		}
	}
	for (FPlayerKeyMapping* keyFounded : AllKeysFounded)
	{
		UWidget* newInputWidget = CreateWidget(GetOwningPlayer(), WidgetKey);
		if (newInputWidget->Implements<URebindKeyInterface>())
		{
			UKeyMappingCAW* newInputWidgetRef = IRebindKeyInterface::Execute_GetKeyMappingWidget(newInputWidget);
			newInputWidgetRef->InitKeyMapping(FText::FromString((keyFounded->GetMappingName().ToString()
																			.Replace(TEXT("Kb"), TEXT("")))
																			.Replace(TEXT("Gp"), TEXT(""))), 
																			keyFounded, bRebindGamepad, InputUserSettings);
			if (!CategoryMap.Find(keyFounded->GetDisplayCategory().ToString()))
			{
				UKeyMappingCategoryCAW* newCategoryWidget = Cast<UKeyMappingCategoryCAW>(CreateWidget(GetOwningPlayer(), WidgetCategory));
				newCategoryWidget->InitKeyMappingCategory(keyFounded->GetDisplayCategory(), Controls_Button);
				CategoryMap.Add(keyFounded->GetDisplayCategory().ToString(), newCategoryWidget);
				bRebindGamepad ? BIND_Gamepad_SB->AddChild(newCategoryWidget) : BIND_Keyboard_SB->AddChild(newCategoryWidget);
				int32 index = bRebindGamepad ? BIND_Gamepad_SB->GetAllChildren().Find(newCategoryWidget): 
									BIND_Keyboard_SB->GetAllChildren().Find(newCategoryWidget);
				if (index > 0)
				{
					newCategoryWidget->SetLastWidget(bRebindGamepad ? BIND_Gamepad_SB->GetAllChildren()[index-1] : 
				 														BIND_Keyboard_SB->GetAllChildren()[index-1]);
				}
				UE_LOG(LogTemp, Warning, TEXT("Create New category"));
			}
			UKeyMappingCategoryCAW** tempCategoryWidget = CategoryMap.Find(keyFounded->GetDisplayCategory().ToString());
			(*tempCategoryWidget)->AddNewKeyMapping(newInputWidgetRef);
			InputList.Add(newInputWidgetRef);
			newInputWidgetRef->OnUpdateKeyBindSignature.AddUObject(this, &UKeyMappingMenuCAW::ReloadKeyMapping);
		}
	}
}

void UKeyMappingMenuCAW::ReloadKeyMapping()
{
	FindKeys(bRebindGamepad);
}


