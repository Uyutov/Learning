// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ItemLibrary.h"
#include "MyCharacter.h"
#include "InventoryPanel.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		bool IsInventoryOpend = false;
	UFUNCTION()
		void OpenInventory();
	UFUNCTION()
		void CloseInventory();

public:
	

	UPROPERTY()
		int32 AmmountOfRows;
	UPROPERTY()
		int32 AmmountOfColumns;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> InventoryClass;
	UPROPERTY()
		class UUserWidget* InventoryWidget;

	UFUNCTION()
		void UseInventory();
	UFUNCTION()
		void AddItem(UItemInformation* ItemInfo);
	UFUNCTION()
		void RemoveItem(int32 Row, int32 Column);
	UFUNCTION()
		void SetSize(int32 RowsAmmount, int32 ColumnsAmmount);

	virtual void BeginPlay() override;

};
