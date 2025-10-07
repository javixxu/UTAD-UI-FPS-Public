// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/GenericSkillNodeData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SkillSubsystem.generated.h"

UCLASS()
class UTAD_UI_FPS_API USkillSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	// Inicialización del subsistema
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Desinicialización
	virtual void Deinitialize() override;
	
	// Función para desbloquear una habilidad
	UFUNCTION(BlueprintCallable, Category = "Skill System")
	bool UnlockOrUpgradeSkill(UGenericSkillNodeData* SkillData);
	
	// Comprueba si una habilidad ya está desbloqueada
	UFUNCTION(BlueprintCallable, Category = "Skill System")
	bool IsSkillUnlocked(UGenericSkillNodeData* SkillData) const;

	// Get SkillLevel
	int32 GetSkillLevel(const UGenericSkillNodeData* SkillData) const;

private:
	// Nivel de las habilitates desbloqueadas
	UPROPERTY()
	TMap<ESkillEffect, int32> SkillLevels;
};
