// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "BaseMenuCommonUserWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CPPMENU_API UBaseMenuCommonUserWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Base Menu Common User Widget")
	void AddWidgetOnStack(TSubclassOf <class UCommonActivatableWidget> DesireWidget);
	void RemoveWidgetFromStack(class UBaseCommonActivatableWidget& InWidget);

protected:
	void CloseBaseMenu();

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonActivatableWidgetStack> BIND_PauseMenuWidgetStack = nullptr;
};
