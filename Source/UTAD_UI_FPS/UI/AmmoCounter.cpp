// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCounter.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "../TP_WeaponComponent.h"
#include "Components/TextBlock.h"

void UAmmoCounter::Show()
{
	AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter());
	if (Character) {
		Character->OnTotalNumBulletsChanged.BindUObject(this, &UAmmoCounter::UpdateTotalAmmo);
		UTP_WeaponComponent* weaponComponent = Character->GetAttachedWeaponComponent();
		if (weaponComponent) {
			weaponComponent->OnCurrentNumBulletsChanged.BindUObject(this, &UAmmoCounter::UpdateCurrentAmmo);
		}
	}
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UAmmoCounter::Hide()
{
	AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayer()->GetCharacter());
	if (Character) {
		Character->OnTotalNumBulletsChanged.Unbind();
		UTP_WeaponComponent* weaponComponent = Character->GetAttachedWeaponComponent();
		if (weaponComponent) {
			weaponComponent->OnCurrentNumBulletsChanged.Unbind();
		}
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UAmmoCounter::UpdateCurrentAmmo(int NewCurrentAmmo)
{
	CurrentAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"),NewCurrentAmmo)));
}

void UAmmoCounter::UpdateTotalAmmo(int NewTotalAmmo)
{
	TotalAmmo->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewTotalAmmo)));
}
