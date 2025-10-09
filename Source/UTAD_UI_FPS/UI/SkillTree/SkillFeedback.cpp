// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillFeedback.h"
#include "Components/TextBlock.h"

void USkillFeedback::SetFeedback(const FText InText, const float ShowTime)
{
	TextBlock->SetText(InText);
	
	SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}, ShowTime, false);
}