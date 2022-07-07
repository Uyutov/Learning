// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components\TextBlock.h"
#include "ConsumableItemInfoPanel.generated.h"

class UConsumablesInfo;

/**
 * 
 */
UCLASS()
class LEARNING_API UConsumableItemInfoPanel : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* Duration;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* Rate;
public:
	UFUNCTION()
		void SetProperties(UConsumablesInfo* ConsumableInfo);
};
