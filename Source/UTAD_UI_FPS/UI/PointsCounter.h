// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PointsCounter.generated.h"

class UTextBlock;

UCLASS()
class UTAD_UI_FPS_API UPointsCounter : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();
	
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdatePoints(int32 NewPoints);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextPoints;
};
