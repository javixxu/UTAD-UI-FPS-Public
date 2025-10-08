// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillNodeWidget.generated.h"

class UBorder;
class UImage;
class UDescriptionSkill;
class UTextBlock;
class AUTAD_UI_FPSCharacter;
class UGenericSkillNodeData;

UCLASS()
class UTAD_UI_FPS_API USkillNodeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	// Data Asset que representa la habilidad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	UGenericSkillNodeData* SkillData{nullptr};
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UDescriptionSkill* DescriptionWidget{nullptr};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* IconImage{nullptr};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* Border{nullptr};

	UPROPERTY(EditDefaultsOnly,Category = "FeedBack|Color")
	FColor OnHoverColor;
	UPROPERTY(EditDefaultsOnly,Category = "FeedBack|Color")
	FColor OnPressedColor;
	UPROPERTY(EditDefaultsOnly,Category = "FeedBack|Color")
	FColor OnNormalColor;
	UPROPERTY(EditDefaultsOnly,Category = "FeedBack|Color")
	FColor OnCompletedColor;
	
	virtual  void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Skill")
	void TryUnlockSkill();
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
private:
	UPROPERTY()
	AUTAD_UI_FPSCharacter* Character{nullptr};

	void PutIconDataOnImage() const;

	void UpdateDescription() const;
	
};
