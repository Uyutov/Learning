// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemLibrary.h"
#include "AccessibleArmorTypes.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LEARNING_API UAccessibleArmorTypes : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
		TArray<EArmorType> ArmorTypesList;

};
