// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "UTAD_UI_FPSCharacter.h"
#include "UTAD_UI_FPSProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Blueprint/UserWidget.h"

#define RELOAD_TIME 1.f

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
	: ReloadTimer(0.f)
	, bIsReloading(false)
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UTP_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (bIsReloading)
	{
		ReloadTimer += DeltaTime;
		// To test ReloadTimer
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), ReloadTimer));
	}
}

void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	if (CurrentNumBullets <= 0)
	{
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<AUTAD_UI_FPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	--CurrentNumBullets;

	OnCurrentNumBulletsChanged.ExecuteIfBound(CurrentNumBullets);
}

void UTP_WeaponComponent::StartReload()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("START RELOADING 2"));
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	//UE_LOG(LogTemp, Error, TEXT("eNTRAAA"));
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("START RELOADING 1"));

	int playerBullets = Character->GetTotalBullets();
	playerBullets += CurrentNumBullets;

	if (playerBullets <= CurrentNumBullets || CurrentNumBullets == MagazineSize)
	{
		return;
	}

	bIsReloading = true;
	ReloadTimer = 0.f;
}

void UTP_WeaponComponent::CompleteReload()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	bIsReloading = false;

	int playerBullets = Character->GetTotalBullets();
	playerBullets += CurrentNumBullets;

	CurrentNumBullets = __min(MagazineSize, playerBullets);

	Character->SetTotalBullets(playerBullets - CurrentNumBullets);

	OnCurrentNumBulletsChanged.ExecuteIfBound(CurrentNumBullets);
}

void UTP_WeaponComponent::CancelReload()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("cancel"));
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	bIsReloading = false;
}

int UTP_WeaponComponent::GetMagazineSize()
{
	return MagazineSize;
}

void UTP_WeaponComponent::SetMagazineSize(int NewMagazineSize)
{
	MagazineSize = NewMagazineSize;
}

int UTP_WeaponComponent::GetCurrentNumBullets()
{
	return CurrentNumBullets;
}

void UTP_WeaponComponent::SetCurrentNumBullets(int NewCurrentNumBullets)
{
	CurrentNumBullets = NewCurrentNumBullets;
}

void UTP_WeaponComponent::AttachWeapon(AUTAD_UI_FPSCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr || Character->GetHasRifle())
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	Character->SetAttachedWeaponComponent(this);
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("LINK INPUT"));
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("1"));
			// StartReload
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &UTP_WeaponComponent::StartReload);
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("2"));
			// CompleteReload
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Completed, this, &UTP_WeaponComponent::CompleteReload);
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("3"));
			// CancelReload
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Canceled, this, &UTP_WeaponComponent::CancelReload);
		}
	}
	OnCurrentNumBulletsChanged.ExecuteIfBound(CurrentNumBullets);
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("ATTACH WEAPON"));
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}