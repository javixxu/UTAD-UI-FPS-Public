// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadBar.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "../TP_WeaponComponent.h"
#include "Components/ProgressBar.h"

void UReloadBar::Show()
{
	if (const AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter())) {
		if (UTP_WeaponComponent* WeaponComponent = Character->GetAttachedWeaponComponent()) {
			WeaponComponent->OnReloadChanged.BindUObject(this, &UReloadBar::UpdateReloadBarValue);
			WeaponComponent->OnReloadChanged.ExecuteIfBound(0.0f);
		}
	}
	
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UReloadBar::Hide()
{
	if (const AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter())) {
		if (UTP_WeaponComponent* WeaponComponent = Character->GetAttachedWeaponComponent()) {
			WeaponComponent->OnReloadChanged.Unbind();
		}
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UReloadBar::UpdateReloadBarValue(float NewValue)
{
	ReloadBar->SetPercent(NewValue);
}
