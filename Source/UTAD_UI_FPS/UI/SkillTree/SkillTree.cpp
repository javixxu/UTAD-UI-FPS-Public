// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTree.h"

#include "SkillNodeWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/SkillSubsystem.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	UpdateSkillsButton->OnClicked.AddDynamic(this, &USkillTree::UpdateSkillTree);
	
	OnSkillNodeClicked.BindUObject(this, &USkillTree::HandleSkillClicked);
}

void USkillTree::UpdateSkillTree()
{
	USkillSubsystem* SkillSubsystem = GetGameInstance()->GetSubsystem<USkillSubsystem>();
	for (USkillNodeWidget* Node: SkillNodesClicked)
	{
		bool bSuccess = SkillSubsystem->UnlockOrUpgradeSkill(Node->GetSkillData());

		Node->ResetNode(bSuccess);
	}
	
	//reset
	SkillNodesClicked.Empty();
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
	SkillNodesClicked.Add(Node);
}
