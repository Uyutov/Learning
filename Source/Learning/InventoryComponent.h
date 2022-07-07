// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AMyCharacter;
class UItemInformation;
class APickUp;
class UInventoryPanel;
class UEquipmentPart;
class UAccessibleArmorTypes;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNING_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInventoryComponent();

	UPROPERTY()
		int32 ArraySize;
	UPROPERTY()
		TArray<UItemInformation*> Items;
	UPROPERTY()
		UInventoryPanel* InventoryPanelWidget;

	UPROPERTY()
		UEquipmentPart* Equipment;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UAccessibleArmorTypes> AccessibleArmor;

	UFUNCTION()
		bool Add(APickUp* Item);
	UFUNCTION()
		bool Remove(UItemInformation* RemovedItem);
	UFUNCTION()
		void SetInventorySize(int32 Rows, int32 Columns);

	virtual void BeginPlay() override;

protected:
	/*int32 PutIn(UArmorInfo* ArmorInfo);
	int32 PutIn(UConsumablesInfo* ConsumablesInfo);*/
	int32 PutIn(UItemInformation* ItemInfo);

};
