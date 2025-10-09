// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTree.generated.h"


class UHoldButtonWidget;
class USkillFeedback;
class USkillNodeWidget;
class UGenericSkillNodeData;
class AUTAD_UI_FPSCharacter;

DECLARE_DELEGATE_OneParam(FOnSkillNodeClicked, USkillNodeWidget*);

UCLASS()
class UTAD_UI_FPS_API USkillTree : public UUserWidget
{
	GENERATED_BODY()
public:

	FOnSkillNodeClicked OnSkillNodeClicked;
	float ShowFeedbackTime = 3.0f;

	UFUNCTION(BlueprintCallable, Category = "SkillTree")
	void UpdateSkillTree();

	UFUNCTION(BlueprintCallable, Category = "SkillTree")
	void Show();

	UFUNCTION(BlueprintCallable, Category = "SkillTree")
	void Hide();
	
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UHoldButtonWidget* UpdateSkillsButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillFeedback* Feedback;
	
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "SkillTree")
	void HandleSkillClicked(USkillNodeWidget* Node);
	
private:
	
	UPROPERTY()
	AUTAD_UI_FPSCharacter* Character{nullptr};
	
	//Clicked Nodes
	UPROPERTY()
	TArray<USkillNodeWidget*> SkillNodesClicked;
};
