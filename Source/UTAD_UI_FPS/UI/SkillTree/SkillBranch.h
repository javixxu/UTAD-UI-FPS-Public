// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillBranch.generated.h"

class USkillNodeWidget;
class UVerticalBox;

USTRUCT()
struct FSkillConnection
{
	GENERATED_BODY()

	UPROPERTY()
	USkillNodeWidget* From;

	UPROPERTY()
	USkillNodeWidget* To;
};

UCLASS()
class UTAD_UI_FPS_API USkillBranch : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;
};
