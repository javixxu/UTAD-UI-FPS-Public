// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillSubsystem.h"

#include "UTAD_UI_FPSCharacter.h"
#include "DataAsset/GenericSkillNodeData.h"
#include "Kismet/GameplayStatics.h"

void USkillSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// Initialize skills at level 1 instead of 0
	SkillLevels.Add(ESkillEffect::IncreaseSpeed,1);
	SkillLevels.Add(ESkillEffect::IncreaseHealth,1); 
	SkillLevels.Add(ESkillEffect::IncreaseDamage,1);
	
	UE_LOG(LogTemp, Log, TEXT("SkillSubsystem Initialized."));
}

void USkillSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("SkillSubsystem Destroyed."));
	Super::Deinitialize();
}

ESkillUnlockResult USkillSubsystem::UnlockOrUpgradeSkill(UGenericSkillNodeData* SkillData)
{
	AUTAD_UI_FPSCharacter* MainCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!MainCharacter)return ESkillUnlockResult::InvalidSkillData;

	ESkillUnlockResult Result = CanSkillUnlocked(SkillData);
	if ( Result != ESkillUnlockResult::CanUnlock)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot unlock skill: %d"), (uint8)Result);
		return Result;
	}
	
	int32& Level = SkillLevels.FindOrAdd(SkillData->SkillEffectData.SkillEffect);
	Level++;
	
	MainCharacter->OnSkillUpdate.ExecuteIfBound(SkillData->SkillEffectData);
	
	MainCharacter->AddPoints(-SkillData->Cost);
	
	UE_LOG(LogTemp, Log, TEXT("Skill '%s' has been levelled up %d"), *SkillData->SkillName.ToString(), Level);
	
	return Result;
}

ESkillUnlockResult USkillSubsystem::CanSkillUnlocked(UGenericSkillNodeData* SkillData) const
{
	const AUTAD_UI_FPSCharacter* MainCharacter = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if (!SkillData || !MainCharacter)
		return ESkillUnlockResult::InvalidSkillData;

	if (MainCharacter->CurrentPoints < SkillData->Cost)
		return ESkillUnlockResult::NoEnoughPoints;

	const int32* CurrentLevelPtr = SkillLevels.Find(SkillData->SkillEffectData.SkillEffect);

	// Skill no desbloqueada aún
	if (!CurrentLevelPtr)
	{
		return (SkillData->SkillEffectData.LevelEffect == 1) 
			? ESkillUnlockResult::CanUnlock 
			: ESkillUnlockResult::LevelTooLow;
	}

	const int32 CurrentLevel = *CurrentLevelPtr;

	if (CurrentLevel >= SkillData->SkillEffectData.LevelEffect)
		return ESkillUnlockResult::AlreadyMaxLevel;

	if (CurrentLevel == SkillData->SkillEffectData.LevelEffect - 1)
		return ESkillUnlockResult::CanUnlock;

	return ESkillUnlockResult::LevelTooLow;
}

int32 USkillSubsystem::GetSkillLevel(const UGenericSkillNodeData* SkillData) const
{
	if (!SkillData)
		return -1;

	const int32* Found = SkillLevels.Find(SkillData->SkillEffectData.SkillEffect);
	return Found ? *Found : -1;
}
