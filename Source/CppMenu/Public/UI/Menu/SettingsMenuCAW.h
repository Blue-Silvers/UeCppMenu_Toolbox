#pragma once

#include "CoreMinimal.h"
#include "UI/Menu/BaseCommonActivatableWidget.h"
#include "SettingsMenuCAW.generated.h"

UCLASS(Abstract)
class CPPMENU_API USettingsMenuCAW : public UBaseCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	//Button
protected:
	UFUNCTION()
	void OnAudioButtonClicked();
	UFUNCTION()
	void OnGraphicsClicked();
	UFUNCTION()
	void OnControlsButtonClicked();


protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_Audio_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_Graphics_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_Controls_Button = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UMainCommonButtonBase> BIND_Quit_Button = nullptr;

	//End of Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	TObjectPtr<class UWidgetSwitcher> BIND_Settings_Switcher = nullptr;
	//BIND_Settings_Switcher
};
