// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/BaseCommonActivatableWidget.h"
#include "PauseMenuCAW.generated.h"


UCLASS()
class CPPMENU_API UPauseMenuCAW : public UBaseCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void OpenMenu() override;
	virtual void CloseMenu() override;


	//Button
protected:
	UFUNCTION()
	void OnRestartButtonClicked();
	UFUNCTION()
	void OnQuitButtonClicked();
	UFUNCTION()
	void OnOptionButtonClicked();
	UFUNCTION()
	void OnMainMenuClicked();

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_Resume_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_Restart_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_MainMenu_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_Options_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_Quit_Button = nullptr;


	UPROPERTY(EditAnywhere, Category = "Main Menu")
	FName MainMenuWorldMapName = "MainMenuWorld";
	//End of Button
};
