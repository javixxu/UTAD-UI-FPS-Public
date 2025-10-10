// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillNodeWidget.generated.h"

class UPlayerHUD;
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

	UFUNCTION(BlueprintCallable, Category = "Skill")
	void ResetNode(bool bSuccess = false);

	UFUNCTION(BlueprintCallable, Category = "SkillData")
	UGenericSkillNodeData* GetSkillData() const;
	
protected:
	// Data Asset que representa la habilidad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	UGenericSkillNodeData* SkillData{nullptr};
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UDescriptionSkill* DescriptionWidget{nullptr};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* IconImage{nullptr};

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* Border{nullptr};

	UPROPERTY(EditDefaultsOnly,Category = "Skill|FeedBack")
	FColor HoverColor;
	UPROPERTY(EditDefaultsOnly,Category = "Skill|FeedBack")
	FColor PressedColor;
	UPROPERTY(EditDefaultsOnly,Category = "Skill|FeedBack")
	FColor NormalColor;
	UPROPERTY(EditDefaultsOnly,Category = "Skill|FeedBack")
	FColor CompletedColor;
	UPROPERTY(EditDefaultsOnly,Category = "Skill|FeedBack")
	FColor DeniedColor = FColor::Red;
	
	virtual  void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:

	bool bWasClicked{false};
	bool bIsCompleted{false};
	
	UPROPERTY()
	AUTAD_UI_FPSCharacter* Character{nullptr};
	
	UPROPERTY()
	UPlayerHUD* MyHUD{nullptr}; 
	
	void PutIconDataOnImage() const;

	void UpdateDescription() const;
	
};
