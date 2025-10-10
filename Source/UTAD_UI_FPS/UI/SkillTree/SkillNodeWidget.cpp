// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillNodeWidget.h"

#include "DescriptionSkill.h"
#include "SkillTree.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "UTAD_UI_FPS/SkillSubsystem.h"
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

	DescriptionWidget->SetVisibility(ESlateVisibility::Hidden);
	bWasClicked = false;

	MyHUD = Character->GetPlayerHUDInstance();

	if (GetGameInstance()->GetSubsystem<USkillSubsystem>()->GetSkillLevel(SkillData) == SkillData->SkillEffectData.LevelEffect)
	{
		ResetNode(true);
	}
}
void USkillNodeWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	DescriptionWidget->SetVisibility(ESlateVisibility::Visible);
	
	if (bWasClicked || bIsCompleted)return; // iF WAS CLICKED WE WANT TO KEEP THE COLOR
	Border->SetBrushColor(HoverColor);
}

void USkillNodeWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	DescriptionWidget->SetVisibility(ESlateVisibility::Hidden);

	if (bWasClicked || bIsCompleted)return; // iF WAS CLICKED WE WANT TO KEEP THE COLOR
	Border->SetBrushColor(NormalColor);
}

FReply USkillNodeWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsCompleted)
	{
		Border->SetBrushColor(DeniedColor);

		return FReply::Handled();
	}
	
	bWasClicked = !bWasClicked;
	
	Border->SetBrushColor(bWasClicked ? PressedColor: NormalColor);

	//ADD THIS NODE_DATA TO THE SKILL on the NODE CLICKED event
	MyHUD->SkillTree->OnSkillNodeClicked.ExecuteIfBound(this);
	
	return FReply::Handled();
}

FReply USkillNodeWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsCompleted)
	{
		Border->SetBrushColor(CompletedColor);
	}
	
	return FReply::Handled();
}

void USkillNodeWidget::ResetNode(bool bSuccess)
{
	bWasClicked = false;
	bIsCompleted = bSuccess;
	
	Border->SetBrushColor(bSuccess ? CompletedColor: NormalColor);
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
	
	IconImage->SetBrush(Brush);
}

void USkillNodeWidget::UpdateDescription() const
{
	if (!DescriptionWidget || !SkillData)
		return;

	DescriptionWidget->CostText->SetText(FText::FromString(FString::Printf(TEXT("Cost: %d"), SkillData->Cost)));
	DescriptionWidget->DescriptionText->SetText(SkillData->Description);	
	DescriptionWidget->NameText->SetText(SkillData->SkillName);	
}
