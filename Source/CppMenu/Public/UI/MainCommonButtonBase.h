// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "MainCommonButtonBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

UCLASS()
class CPPMENU_API UMainCommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;

	//text
protected:
	UPROPERTY(EditAnywhere, Category = "Main Button")
	FText ButtonText = FText();
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UCommonTextBlock> BIND_ButtonButtonText = nullptr;

	//End of text

	//Events
protected:
	virtual void NativeOnClicked() override;

public:
	FOnButtonClicked OnButtonClicked;

	//End of Events
};
