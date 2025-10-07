// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillSubsystem.h"
#include "DataAsset/GenericSkillNodeData.h"

void USkillSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	SkillLevels.Add(ESkillEffect::IncreaseSpeed,0);
	SkillLevels.Add(ESkillEffect::IncreaseHealth,0);
	SkillLevels.Add(ESkillEffect::IncreaseDamage,0);
	
	UE_LOG(LogTemp, Log, TEXT("SkillSubsystem Initialized."));
}

void USkillSubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("SkillSubsystem Destroyed."));
	Super::Deinitialize();
}

bool USkillSubsystem::UnlockOrUpgradeSkill(UGenericSkillNodeData* SkillData)
{
	if (IsSkillUnlocked(SkillData))return false;
	
	int32& Level = SkillLevels.FindOrAdd(SkillData->SkillEffectData.SkillEffect);
	Level++;

	UE_LOG(LogTemp, Log, TEXT("Skill '%s' has been levelled up %d"), *SkillData->SkillName.ToString(), Level);
	
	return true;
}

bool USkillSubsystem::IsSkillUnlocked(UGenericSkillNodeData* SkillData) const
{
	if (!SkillData)
		return false;

	const int32* Found = SkillLevels.Find(SkillData->SkillEffectData.SkillEffect);
	return Found && *Found > -1;
}

int32 USkillSubsystem::GetSkillLevel(const UGenericSkillNodeData* SkillData) const
{
	if (!SkillData)
		return -1;

	const int32* Found = SkillLevels.Find(SkillData->SkillEffectData.SkillEffect);
	return Found ? *Found : -1;
}