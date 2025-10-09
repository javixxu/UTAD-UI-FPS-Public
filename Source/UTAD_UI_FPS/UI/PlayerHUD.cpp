// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "AmmoCounter.h"
#include "PlayerHealthBar.h"
#include "PointsCounter.h"
#include "ReloadBar.h"
#include "SkillTree/SkillTree.h"

void UPlayerHUD::ShowNoWeapon()
{
	AmmoCounterWidget->Hide();
	ReloadBarWidget->Hide();
	PlayerHealthBarWidget->Show();
	PointsCounter->Show();
}

void UPlayerHUD::ShowAll()
{
	AmmoCounterWidget->Show();
	PlayerHealthBarWidget->Show();
	ReloadBarWidget->Show();
	PointsCounter->Show();
}

void UPlayerHUD::Hide()
{
	AmmoCounterWidget->Hide();
	PlayerHealthBarWidget->Hide();
	ReloadBarWidget->Hide();
	PointsCounter->Hide();
}

void UPlayerHUD::ShowSkillTree()
{
	SkillTree->Show();
	PointsCounter->Show();
}

void UPlayerHUD::HideSkillTree()
{
	SkillTree->Hide();
}

void UPlayerHUD::HandleSkillTree(bool bIsActive, bool bHasRifle)
{
	if (bIsActive)
	{
		Hide();
		ShowSkillTree(); 
	}
	else
	{
		if (bHasRifle)ShowAll();
		else ShowNoWeapon();
		
		HideSkillTree();
	}
}