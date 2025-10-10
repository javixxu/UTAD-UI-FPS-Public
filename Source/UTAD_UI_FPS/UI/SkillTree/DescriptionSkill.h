// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DescriptionSkill.generated.h"


class UTextBlock;

/**
 * Display the skill description
 */
UCLASS()
class UTAD_UI_FPS_API UDescriptionSkill : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CostText{nullptr};
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DescriptionText{nullptr};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* NameText{nullptr};
};
