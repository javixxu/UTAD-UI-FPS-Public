// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNodeWidget.h"

#include "DescriptionSkill.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void USkillNodeWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	PutIconDataOnImage();
	UpdateDescription();
}

void USkillNodeWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	Character = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	DescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void USkillNodeWidget::TryUnlockSkill()
{
	if (!SkillData)
		return;
}

void USkillNodeWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	DescriptionWidget->SetVisibility(ESlateVisibility::Visible);
}

void USkillNodeWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	DescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void USkillNodeWidget::PutIconDataOnImage() const
{
	if (!IconImage || !SkillData->Icon)
	{
		return;
	}
	
	FSlateBrush Brush;
	Brush.SetResourceObject(SkillData->Icon);
	/*
	Brush.ImageSize = FVector2D(
		SkillData->Icon->GetSizeX(),
		SkillData->Icon->GetSizeY()
	);*/
	
	IconImage->SetBrush(Brush);
}

void USkillNodeWidget::UpdateDescription() const
{
	if (!DescriptionWidget || !SkillData)
		return;
	
	DescriptionWidget->DescriptionText->SetText(SkillData->Description);	
	DescriptionWidget->NameText->SetText(SkillData->SkillName);	
}
