// Fill out your copyright notice in the Description page of Project Settings.

#include "HoldButtonWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/ProgressBar.h"

void UHoldButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HoldButton)
	{
		HoldButton->OnPressed.AddDynamic(this, &UHoldButtonWidget::OnButtonPressed);
		HoldButton->OnReleased.AddDynamic(this, &UHoldButtonWidget::OnButtonReleased);
	}

	if (HoldProgressBar)
	{
		HoldProgressBar->SetPercent(0.0f);
		HoldProgressBar->SetRenderOpacity(0.0f);
	}
}

void UHoldButtonWidget::OnButtonPressed()
{
	bIsHolding = true;
	HoldElapsed = 0.0f;

	if (HoldProgressBar)
	{
		HoldProgressBar->SetPercent(0.0f);
		HoldProgressBar->SetRenderOpacity(1.0f);
	}
}

void UHoldButtonWidget::OnButtonReleased()
{
	if (bIsHolding)
	{
		ResetHold();
	}
}

void UHoldButtonWidget::ResetHold()
{
	bIsHolding = false;
	HoldElapsed = 0.0f;

	if (HoldProgressBar)
	{
		HoldProgressBar->SetPercent(0.0f);
		HoldProgressBar->SetRenderOpacity(0.0f);
	}
}

void UHoldButtonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsHolding)
	{
		HoldElapsed += InDeltaTime;
		float Progress = FMath::Clamp(HoldElapsed / HoldDuration, 0.0f, 1.0f);

		if (HoldProgressBar)
			HoldProgressBar->SetPercent(Progress);

		if (Progress >= 1.0f)
		{
			bIsHolding = false;
			OnHoldCompleted.Broadcast();
			ResetHold();
		}
	}
}