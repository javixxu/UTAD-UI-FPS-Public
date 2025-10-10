// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTree.h"

#include "SkillFeedback.h"
#include "SkillNodeWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/SkillSubsystem.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"
#include "UTAD_UI_FPS/UI/HoldButtonWidget.h"

void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	UpdateSkillsButton->OnHoldCompleted.AddDynamic(this, &USkillTree::UpdateSkillTree);
	
	OnSkillNodeClicked.BindUObject(this, &USkillTree::HandleSkillClicked);
}

void USkillTree::UpdateSkillTree()
{
	if (SkillNodesClicked.IsEmpty())
	{
		Feedback->SetFeedback(FText::FromString("No skills selected"),ShowFeedbackTime);
		return;
	}
	
	USkillSubsystem* SkillSubsystem = GetGameInstance()->GetSubsystem<USkillSubsystem>();
	
	// Sort SkillNodesClicked array by level effect
	SkillNodesClicked.Sort([](const USkillNodeWidget& A, const USkillNodeWidget& B) {
		return A.GetSkillData()->SkillEffectData.LevelEffect < B.GetSkillData()->SkillEffectData.LevelEffect;
	});

	//Keep feedback messages
	TArray<FString> FeedbackMessages;

	//Try Unlock Skills
	for (USkillNodeWidget* Node: SkillNodesClicked)
	{
		const ESkillUnlockResult Success = SkillSubsystem->UnlockOrUpgradeSkill(Node->GetSkillData());
		Node->ResetNode(Success == ESkillUnlockResult::CanUnlock);

		FString FeedbackMessage = USkillSubsystem::GetSkillUnlockResultMessage(Success);
		FeedbackMessages.Add(FString::Printf(TEXT("%s: %s"), 
			*Node->GetSkillData()->SkillName.ToString(), 
			*FeedbackMessage));
	}

	//Send Messages
	Feedback->SetFeedback(FText::FromString(FString::Join(FeedbackMessages, TEXT("\n"))),ShowFeedbackTime);
	
	//reset
	SkillNodesClicked.Empty();
}

FString USkillSubsystem::GetSkillUnlockResultMessage(ESkillUnlockResult Result)
{
	switch (Result)
	{
	case ESkillUnlockResult::CanUnlock:
		return TEXT("The skill has been unlocked.!");
		
	case ESkillUnlockResult::AlreadyUnlocked:
		return TEXT("This skill is already unlocked.");
		
	case ESkillUnlockResult::NoEnoughPoints:
		return TEXT("You don't have enough skill points to unlock this skill.");
		
	case ESkillUnlockResult::AlreadyMaxLevel:
		return TEXT("This skill is already at maximum level.");
		
	case ESkillUnlockResult::LevelTooLow:
		return TEXT("Your level is too low to unlock this skill.");
		
	case ESkillUnlockResult::InvalidSkillData:
		return TEXT("Invalid skill data detected.");

	default:
		return TEXT("Unknown skill unlock result.");
	}
}

void USkillTree::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void USkillTree::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void USkillTree::HandleSkillClicked(USkillNodeWidget* Node)
{
	if (SkillNodesClicked.Contains(Node))SkillNodesClicked.Remove(Node);
	else SkillNodesClicked.Add(Node);
}