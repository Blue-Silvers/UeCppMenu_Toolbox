// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/PauseMenuCAW.h"
#include "Ui/MainCommonButtonBase.h"

//Controller
#include "CppMenuPlayerController.h"

//Settings
#include "Kismet/Gameplaystatics.h"

void UPauseMenuCAW::NativeConstruct()
{
	Super::NativeConstruct();

	//Bind all Buttons
	if (BIND_Resume_Button)
	{
		BIND_Resume_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::CloseMenu);
	}
	if (BIND_Restart_Button)
	{
		BIND_Restart_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::OnRestartButtonClicked);
	}
	if (BIND_MainMenu_Button)
	{
		BIND_MainMenu_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::OnMainMenuClicked);
	}
	if (BIND_Options_Button)
	{
		BIND_Options_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::OnOptionButtonClicked);
	}
	if (BIND_Quit_Button)
	{
		BIND_Quit_Button->OnButtonClicked.AddUniqueDynamic(this, &UPauseMenuCAW::OnQuitButtonClicked);
	}
}

void UPauseMenuCAW::OpenMenu()
{
	Super::OpenMenu();

	//Show the mouse cursor
	if (PlayerController.IsValid())
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeUIOnly{});
	}

	//Pause game
	UGameplayStatics::SetGamePaused(this, true);

}

void UPauseMenuCAW::CloseMenu()
{
	//Hide the mouse cursor
	if (PlayerController.IsValid()) 
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly{});
	}

	//Unpause game
	UGameplayStatics::SetGamePaused(this, false);

	Super::CloseMenu();
}

void UPauseMenuCAW::OnRestartButtonClicked()
{
	//Restart current level
	FName LevelName = FName(*UGameplayStatics::GetCurrentLevelName(this));
	UGameplayStatics::OpenLevel(this, LevelName);

	if (!PlayerController.IsValid()) 
	{
		/*Controller*/
		PlayerController = Cast<ACppMenuPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	}
	//Go back to game mode
	if (PlayerController.IsValid())
	{
		PlayerController->SetInputMode(FInputModeGameOnly{});
	}
}

void UPauseMenuCAW::OnQuitButtonClicked()
{
	if(PlayerController.IsValid())
	{
		UKismetSystemLibrary::QuitGame(this, PlayerController.Get(), EQuitPreference::Quit, true);
	}
}

void UPauseMenuCAW::OnOptionButtonClicked()
{
	AddWidgetFromSubsytem(BIND_Options_Button->GetName());

}

void UPauseMenuCAW::OnMainMenuClicked()
{
	if (MainMenuWorldMapName.IsNone() || !PlayerController.IsValid())
	{
		return;
	}

	if (PlayerController.IsValid())
	{
		//Unpause game
		UGameplayStatics::SetGamePaused(this, false);
		Super::CloseMenu();
	}

	UGameplayStatics::OpenLevel(this, MainMenuWorldMapName);
}