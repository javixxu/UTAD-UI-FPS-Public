// Fill out your copyright notice in the Description page of Project Settings.

#include "PointsCounter.h"

#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"


void UPointsCounter::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UPointsCounter::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UPointsCounter::NativeConstruct()
{
	Super::NativeConstruct();
	AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (!Character)return;

	Character->OnPointsChanged.AddDynamic(this,&UPointsCounter::UpdatePoints);
	Character->AddPoints(0);
}

void UPointsCounter::UpdatePoints(int NewPoints)
{
	TextPoints->SetText(FText::FromString("Current Points: "+FString::FromInt(NewPoints)));
}