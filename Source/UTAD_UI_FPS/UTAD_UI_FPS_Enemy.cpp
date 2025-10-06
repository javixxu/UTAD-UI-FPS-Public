// Fill out your copyright notice in the Description page of Project Settings.

#include "UTAD_UI_FPS_Enemy.h"

#include "UTAD_UI_FPSCharacter.h"
#include "UI/EnemyHealthBar.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

void AUTAD_UI_FPS_Enemy::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = false;

	Super::BeginPlay();
	
	UWidgetComponent* WidgetComp = FindComponentByClass<UWidgetComponent>();
	if (!WidgetComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("No se encontró UWidgetComponent en el enemigo"));
		return;
	}
	
	UEnemyHealthBar* HealthBar = Cast<UEnemyHealthBar>(WidgetComp->GetUserWidgetObject());
	if (!HealthBar)
	{
		UE_LOG(LogTemp, Warning, TEXT("No se encontró UEnemyHealthBar en el componente"));
		return;
	}
	
	OnEnemyHealthChanged.BindUObject(HealthBar,&UEnemyHealthBar::UpdateEnemyHealthBarValue);
	HealthBar->UpdateEnemyHealthBarValue(Health, MaxHealth);
	
}
void AUTAD_UI_FPS_Enemy::SetHealth(int NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0, MaxHealth);
	if (Health == 0)
	{
		if (AUTAD_UI_FPSCharacter* Player = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
		{
			// Add points to player
			Player->AddPoints(PointsOnKill);
		}
		
		Destroy();
	}
	OnEnemyHealthChanged.ExecuteIfBound(NewHealth,MaxHealth);
}

int AUTAD_UI_FPS_Enemy::GetHealth()
{
	return Health;
}

void AUTAD_UI_FPS_Enemy::SetMaxHealth(int NewMaxHealth)
{
	MaxHealth = FMath::Max(0, NewMaxHealth);
}

int AUTAD_UI_FPS_Enemy::GetMaxHealth()
{
	return MaxHealth;
}