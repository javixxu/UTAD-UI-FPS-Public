// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillFeedback.generated.h"

class UBorder;
class UTextBlock;

/**
 * Visual feedback system for the user when attempting/unlocking skills
 */
UCLASS()
class UTAD_UI_FPS_API USkillFeedback : public UUserWidget
{
	GENERATED_BODY()
public:
	/**Set feedback messages for a period of time */
	UFUNCTION(BlueprintCallable, Category = "SkillFeedback")
	void SetFeedback(FText InText, float ShowTime);

protected:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock;
private:
	FTimerHandle TimerHandle;
};
