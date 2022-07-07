// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EquipmentPart.generated.h"

class UArmorInfo;
class UAccessibleArmorTypes;

/**
 * 
 */
UCLASS()
class LEARNING_API UEquipmentPart : public UObject
{
	GENERATED_BODY()
public:
	UEquipmentPart();

	UPROPERTY()
		UAccessibleArmorTypes* AccessibleArmor;

	UFUNCTION()
		UArmorInfo* EquipArmor(UArmorInfo* ArmorPiece);
	UFUNCTION()
		UArmorInfo* TakeOffArmor(UArmorInfo* ArmorPiece);
protected:

	UPROPERTY()
		TArray<UArmorInfo*> Equipment;
	/*UPROPERTY()
		TArray<UInstrumentInfo> Instruments;*/
};
