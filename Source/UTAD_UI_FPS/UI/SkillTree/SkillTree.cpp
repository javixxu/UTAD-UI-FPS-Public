// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTree.h"
#include "Kismet/GameplayStatics.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"

void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}
