// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "UTAD_UI_FPS_Enemy.generated.h"

DECLARE_DELEGATE_TwoParams(FOnEnemyHealthChanged, int /*NewHealth*/, int /*MaxHealth*/);

UCLASS()
class UTAD_UI_FPS_API AUTAD_UI_FPS_Enemy : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	
	FOnEnemyHealthChanged OnEnemyHealthChanged;
	
	/** Current Health */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int Health = 100;

	/** Max Health */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int MaxHealth = 100;

	/**Points On Death*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats)
	int PointsOnKill = 50;
	
	/** Setter to set the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetHealth(int NewHealth);

	/** Getter for the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	int GetHealth();

	/** Setter to set the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetMaxHealth(int NewMaxHealth);

	/** Getter for the int */
	UFUNCTION(BlueprintCallable, Category = Stats)
	int GetMaxHealth();

protected:
	
	virtual void BeginPlay() override;

};
