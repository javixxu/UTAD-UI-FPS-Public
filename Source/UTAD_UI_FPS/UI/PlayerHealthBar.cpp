// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthBar.h"

#include "AmmoCounter.h"
#include "Kismet/GameplayStatics.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "Components/ProgressBar.h"
#include "Math/Color.h"
#include "Styling/SlateColor.h"

#define BLINK_ANIMATION_TIME 1.f
#define BLINK_THRESHOLD 0.25f

void UPlayerHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsLowHealth && PlayerHealthBar)
	{
		BlinkTimer += InDeltaTime / BLINK_ANIMATION_TIME;

		LowHealthBlink();
	}
}

void UPlayerHealthBar::Show()
{
	AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter());
	if (Character) {
		
		Character->OnHealthChanged.Unbind();
		
		Character->OnHealthChanged.BindUObject(this, &UPlayerHealthBar::UpdatePlayerHealthBar);
		UpdatePlayerHealthBar(Character->Health, Character->MaxHealth);
	}
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UPlayerHealthBar::Hide()
{
	AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter());
	if (Character) {
		Character->OnHealthChanged.Unbind();
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHealthBar::UpdatePlayerHealthBar(int NewHealth, int MaxHealth)
{
	if (!PlayerHealthBar || MaxHealth <= 0) return;

	CurrentHealthPercent = static_cast<float>(NewHealth) / static_cast<float>(MaxHealth);
	PlayerHealthBar->SetPercent(CurrentHealthPercent);
	
	if (CurrentHealthPercent <= 0.3f)
	{
		if (!bIsLowHealth)
		{
			bIsLowHealth = true;
			BlinkTimer = 0.f;
		}
	}
	else
	{
		bIsLowHealth = false;
		
		FLinearColor NormalColor = (CurrentHealthPercent > 0.6f)
			? FLinearColor::Green
			: FLinearColor::Yellow;

		PlayerHealthBar->SetFillColorAndOpacity(NormalColor);
	}
}

void UPlayerHealthBar::LowHealthBlink()
{
	// Calcula una interpolación de color entre rojo y blanco
	float Alpha = FMath::Abs(FMath::Sin(BlinkTimer * PI));
	FLinearColor BlinkColor = FLinearColor::LerpUsingHSV(
		FLinearColor::Red,
		FLinearColor::White,
		Alpha
	);

	PlayerHealthBar->SetFillColorAndOpacity(BlinkColor);
}
