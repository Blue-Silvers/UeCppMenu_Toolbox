// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BaseCommonActivatableWidget.generated.h"


UCLASS(Abstract)
class CPPMENU_API UBaseCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()


protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OpenMenu();
	UFUNCTION()
	virtual void CloseMenu();

	void AddWidgetFromSubsytem(FString WidgetName);
	void CloseActivatableWidget();

public:
	void SetBaseMenuCommonUserWidget(class UBaseMenuCommonUserWidget* BaseMenuCommonUserWidget);
	void SetPreviousCommonUserWidget(class UCommonActivatableWidget* PreviousCommonUserWidget);

protected:
	/*Player controller*/
	TWeakObjectPtr<class ACppMenuPlayerController> PlayerController = nullptr;

	//Background Widget that contains the Activatable Widget Stack
	TWeakObjectPtr<class UBaseMenuCommonUserWidget> BaseMenuCommonUserWidget = nullptr;
	//Previous Display Widget on the BaseMenuCommonUserWidget
	TWeakObjectPtr<class UCommonActivatableWidget> PreviousCommonUserWidget = nullptr;
	// navigation data asset
	TWeakObjectPtr<class UMenuNavigationDataAsset> MenuNavigationDataAsset = nullptr;

};
