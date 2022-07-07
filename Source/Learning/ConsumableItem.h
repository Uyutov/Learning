// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "InventoryComponent.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API AConsumableItem : public APickUp
{
	GENERATED_BODY()
public:
	
	AConsumableItem();

	UPROPERTY()
		UConsumablesInfo* ConsumableInfo;
	UPROPERTY(EditAnywhere, Category = "Item Info")
		UDataAsset* DataAsset;
	UPROPERTY(EditAnywhere, Category = "Item Info")
		EItemsVariety ItemVariation;
	UPROPERTY(EditAnywhere, Category = "Item Info")
		bool Change;

	UFUNCTION()
		void SetPropertys(UConsumablesInfo* InfoAboutConsumable);
	UFUNCTION()
		void ApplyChange(TArray<FConsumablesInfoStruct> ConsumablesArray);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual UItemInformation* GetItemInformation() override;
	virtual void BeginPlay() override;
	virtual void PickUp_Implementation(AActor* LiftingActor) override;
	virtual void TakeInfoFromItem(APickUp* ItemToTakeInfoFrom) override;

};
