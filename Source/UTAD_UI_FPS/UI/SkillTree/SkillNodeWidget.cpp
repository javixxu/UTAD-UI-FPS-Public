// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNodeWidget.h"

#include "DescriptionSkill.h"
#include "SkillTree.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"
#include "UTAD_UI_FPS/UI/PlayerHUD.h"


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
	bWasClicked = false;

	MyHUD = Character->GetPlayerHUDInstance();
}

void USkillNodeWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	DescriptionWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (bWasClicked || bIsCompleted)return; // iF WAS CLICKED WE WANT TO KEEP THE COLOR
	Border->SetBrushColor(OnHoverColor);
}

void USkillNodeWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	DescriptionWidget->SetVisibility(ESlateVisibility::Collapsed);

	if (bWasClicked || bIsCompleted)return; // iF WAS CLICKED WE WANT TO KEEP THE COLOR
	Border->SetBrushColor(OnNormalColor);
}

FReply USkillNodeWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsCompleted)return FReply::Handled();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("On Click"));
	
	bWasClicked = !bWasClicked;
	
	Border->SetBrushColor(bWasClicked ? OnPressedColor: OnNormalColor);

	//ADD THIS NODE_DATA TO THE SKILL on the NODE CLICKED event
	MyHUD->SkillTree->OnSkillNodeClicked.ExecuteIfBound(this);
	
	return FReply::Handled();
}

void USkillNodeWidget::ResetNode(bool bSuccess)
{
	bWasClicked = false;
	bIsCompleted = bSuccess;
	
	Border->SetBrushColor(bSuccess ? OnCompletedColor: OnNormalColor);
}

UGenericSkillNodeData* USkillNodeWidget::GetSkillData() const
{
	return SkillData;
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
