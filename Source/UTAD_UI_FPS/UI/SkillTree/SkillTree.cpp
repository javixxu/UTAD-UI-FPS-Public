// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTree.h"

#include "SkillNodeWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	SkillNodes.Empty();
	// Get All Nodes
	TArray<UWidget*> AllWidgets;
	WidgetTree->GetAllWidgets(AllWidgets);

	for (UWidget* Widget : AllWidgets)
	{
		if (USkillNodeWidget* SkillNode = Cast<USkillNodeWidget>(Widget))
		{
			SkillNodes.Add(SkillNode);
		}
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
