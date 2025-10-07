// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GenericSkillNodeData.generated.h"

// Enum para clasificar la habilidad
UENUM(BlueprintType)
enum class ESkillEffect : uint8
{
	None        UMETA(DisplayName = "None"),
	IncreaseSpeed UMETA(DisplayName = "Increase Speed"),
	IncreaseHealth UMETA(DisplayName = "Increase Health"),
	IncreaseDamage UMETA(DisplayName = "Increase Damage"),
};

USTRUCT(BlueprintType)
struct FSkillEffectData
{
	GENERATED_BODY()

	// Tipo de efecto de la habilidad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	ESkillEffect SkillEffect = ESkillEffect::None;

	// Nivel del efecto
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 LevelEffect = 0;

	// Constructor por defecto
	FSkillEffectData()
		: SkillEffect(ESkillEffect::None)
		, LevelEffect(0)
	{}
};

UCLASS(BlueprintType)
class UTAD_UI_FPS_API UGenericSkillNodeData : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	
	// Nombre de la habilidad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	FText SkillName= FText::FromString("DefaultName");

	// Descripción para mostrar en la UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	FText Description = FText::FromString("DefaultDescription");

	// Icono para la UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	UTexture2D* Icon{nullptr};

	// Puntos necesarios para desbloquear
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 Cost = 25;

	//LEVEL TO SKILL UP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	FSkillEffectData SkillEffectData;
};
