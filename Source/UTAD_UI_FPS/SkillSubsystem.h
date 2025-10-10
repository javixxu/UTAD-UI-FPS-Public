// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "DataAsset/GenericSkillNodeData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SkillSubsystem.generated.h"

UENUM(BlueprintType)
enum class ESkillUnlockResult : uint8
{
	CanUnlock        UMETA(DisplayName = "Can Unlock"),
	AlreadyUnlocked  UMETA(DisplayName = "Already Unlocked"),
	NoEnoughPoints   UMETA(DisplayName = "No Enough Points"),
	AlreadyMaxLevel  UMETA(DisplayName = "Already Max Level"),
	LevelTooLow      UMETA(DisplayName = "Level Too Low"),
	InvalidSkillData UMETA(DisplayName = "Invalid Skill Data")
};

UCLASS()
class UTAD_UI_FPS_API USkillSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Deinitialize() override;
	
	// Function to unlock a skill
	UFUNCTION(BlueprintCallable, Category = "Skill System")
	ESkillUnlockResult UnlockOrUpgradeSkill(UGenericSkillNodeData* SkillData);
	
	// Check whether a skill is already unlocked
	UFUNCTION(BlueprintCallable, Category = "Skill System")
	ESkillUnlockResult CanSkillUnlocked(UGenericSkillNodeData* SkillData) const;

	// Get SkillLevel
	int32 GetSkillLevel(const UGenericSkillNodeData* SkillData) const;

	static FString GetSkillUnlockResultMessage(ESkillUnlockResult Result);

private:
	// Level of unlocked skills
	UPROPERTY()
	TMap<ESkillEffect, int32> SkillLevels;
};
