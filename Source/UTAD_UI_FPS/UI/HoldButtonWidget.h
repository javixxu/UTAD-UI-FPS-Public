// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HoldButtonWidget.generated.h"

class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHoldCompleted);

UCLASS()
class UTAD_UI_FPS_API UHoldButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//The time the button must be pressed for the completed event to be called
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Hold Button")
	float HoldDuration = 1.0f;
	
	UPROPERTY(meta = (BindWidget))
	UButton* HoldButton;
	
	UPROPERTY(meta = (BindWidgetOptional))
	class UProgressBar* HoldProgressBar;
	
	UPROPERTY(BlueprintAssignable, Category="Hold Button")
	FOnHoldCompleted OnHoldCompleted;

protected:
	UFUNCTION()
	void OnButtonPressed();

	UFUNCTION()
	void OnButtonReleased();

	void ResetHold();

private:
	bool bIsHolding = false;
	float HoldElapsed = 0.0f;
};
