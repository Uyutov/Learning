// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPanel.h"
#include "InventoryHUD.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API AInventoryHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUserWidget> InventoryWidgetClass;
	
	UFUNCTION()
		void OpenInventory();
	UFUNCTION()
		void CloseInventoy();

private:

	UInventoryPanel* InventoryWidget;

};
