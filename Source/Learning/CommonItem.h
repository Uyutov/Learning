// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemLibrary.h"
#include "InventoryComponent.h"
#include "PickUp.h"
#include "CommonItem.generated.h"


/**
 * 
 */
UCLASS()
class LEARNING_API ACommonItem : public APickUp
{
	GENERATED_BODY()
	
public:

	ACommonItem();

	UPROPERTY()
		UItemInformation* ItemInfo;
	UPROPERTY(EditAnywhere, Category = "Item Info")
		UDataAsset* DataAsset;
	UPROPERTY(EditAnywhere, Category = "Item Info")
		EItemsVariety ItemVariation;
	UPROPERTY(EditAnywhere, Category = "Item Info")
		bool Change;

	UFUNCTION()
		void SetPropertys(UItemInformation* InfoAboutItem);
	UFUNCTION()
		void ApplyChange(TArray<FItemInfoStruct> ItemsArray);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual UItemInformation* GetItemInformation() override;
	virtual void BeginPlay() override;
	virtual void PickUp_Implementation(AActor* LiftingActor) override;
	virtual void TakeInfoFromItem(APickUp* ItemToTakeInfoFrom) override;

};
