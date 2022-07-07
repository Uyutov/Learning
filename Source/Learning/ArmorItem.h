// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUp.h"
#include "InventoryComponent.h"
#include "ArmorItem.generated.h"

/**
 * 
 */
UCLASS()
class LEARNING_API AArmorItem : public APickUp
{
	GENERATED_BODY()
	
public:
	AArmorItem();

	UPROPERTY(EditAnywhere)
		UArmorInfo* ArmorInfo;
	UPROPERTY(EditAnywhere, Category = "Item Info")
		UDataAsset* DataAsset;
	UPROPERTY(EditAnywhere, Category = "Item Info")
		EItemsVariety ItemVariation;
	UPROPERTY(EditAnywhere, Category = "Item Info")
		bool Change;

	UFUNCTION()
		void SetPropertys(UArmorInfo* InfoAboutArmor);
	UFUNCTION()
		void ApplyChange(TArray<FArmorInfoStruct> ArmorArray);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual UItemInformation* GetItemInformation() override;
	virtual void BeginPlay() override;
	virtual void PickUp_Implementation(AActor* LiftingActor) override;
	virtual void TakeInfoFromItem(APickUp* ItemToTakeInfoFrom) override;
};
