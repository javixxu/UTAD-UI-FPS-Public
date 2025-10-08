// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillFeedback.generated.h"

class UBorder;
class UTextBlock;

UCLASS()
class UTAD_UI_FPS_API USkillFeedback : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* Border;
};
