// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTree.generated.h"


class UButton;
class USkillNodeWidget;
class UGenericSkillNodeData;
class AUTAD_UI_FPSCharacter;

UCLASS()
class UTAD_UI_FPS_API USkillTree : public UUserWidget
{
	GENERATED_BODY()
public:
	/** Actualiza la interfaz cuando una habilidad ha sido desbloqueada. */
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillTree")
	void OnSkillUnlocked(UGenericSkillNodeData* SkillData);

	/** Actualiza el estado visual de todos los nodos (habilitados/desbloqueados/bloqueados). */
	UFUNCTION(BlueprintImplementableEvent, Category = "SkillTree")
	void RefreshTree();

	UFUNCTION(BlueprintCallable, Category = "SkillTree")
	void Show();

	UFUNCTION(BlueprintCallable, Category = "SkillTree")
	void Hide();
	
protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* UpdateSkillsButton;
	
	virtual void NativeConstruct() override;
	
	/** Lista de nodos de habilidad que forman parte del árbol. */
	UPROPERTY(meta = (BindWidgetOptional), BlueprintReadWrite, Category = "SkillTree")
	TArray<USkillNodeWidget*> SkillNodes;
	
private:
	
	UPROPERTY()
	AUTAD_UI_FPSCharacter* Character{nullptr};
};
