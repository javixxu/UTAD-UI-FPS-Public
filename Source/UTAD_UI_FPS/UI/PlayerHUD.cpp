// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "AmmoCounter.h"
#include "PlayerHealthBar.h"
#include "ReloadBar.h"
#include "SkillTree/SkillTree.h"

void UPlayerHUD::ShowNoWeapon()
{
	AmmoCounterWidget->Hide();
	ReloadBarWidget->Hide();
	PlayerHealthBarWidget->Show();
}

void UPlayerHUD::ShowAll()
{
	AmmoCounterWidget->Show();
	PlayerHealthBarWidget->Show();
	ReloadBarWidget->Show();
}

void UPlayerHUD::Hide()
{
	AmmoCounterWidget->Hide();
	PlayerHealthBarWidget->Hide();
	ReloadBarWidget->Hide();
}

void UPlayerHUD::ShowSkillTree()
{
	SkillTree->Show();
}

void UPlayerHUD::HideSkillTree()
{
	SkillTree->Hide();
}

void UPlayerHUD::HandleSkillTree(bool bIsActive, bool bHasRifle)
{
	if (bIsActive)
	{
		ShowSkillTree(); 
		Hide();
	}
	else
	{
		HideSkillTree();
		if (bHasRifle)ShowAll();
		else ShowNoWeapon();
	}
}