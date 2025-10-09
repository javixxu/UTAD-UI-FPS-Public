// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UPointsCounter;
class USkillTree;
class UAmmoCounter;
class UCrosshair;
class UPlayerHealthBar;
class UReloadBar;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UAmmoCounter* AmmoCounterWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPlayerHealthBar* PlayerHealthBarWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UReloadBar* ReloadBarWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	USkillTree* SkillTree;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UPointsCounter* PointsCounter;
	
	/** Show the Minimap and the PlayerHealthBar */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void ShowNoWeapon();

	/** Show all the widgets */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void ShowAll();

	/** Hide all the widgets */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void ShowSkillTree();
	
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void HideSkillTree();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void HandleSkillTree(bool bIsActive, bool bHasRifle);

};
