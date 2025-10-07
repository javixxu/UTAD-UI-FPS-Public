// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillNodeWidget.generated.h"

class UDescriptionSkill;
class UTextBlock;
class AUTAD_UI_FPSCharacter;
class UGenericSkillNodeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillUnlocked, UGenericSkillNodeData*, Skill);

UCLASS()
class UTAD_UI_FPS_API USkillNodeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	// Data Asset que representa la habilidad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	UGenericSkillNodeData* SkillData{nullptr};
	
	// Evento que se dispara al desbloquear
	UPROPERTY(BlueprintAssignable, Category = "Skill")
	FOnSkillUnlocked OnSkillUnlocked;
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	void TryUnlockSkill();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UDescriptionSkill* DescriptionWidget{nullptr};

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
private:
	UPROPERTY()
	AUTAD_UI_FPSCharacter* Character{nullptr};
};
