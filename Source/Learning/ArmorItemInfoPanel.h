// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components\TextBlock.h"
#include "ArmorItemInfoPanel.generated.h"

class UArmorInfo;

/**
 * 
 */
UCLASS()
class LEARNING_API UArmorItemInfoPanel : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* Armor;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ArmorType;
public:
	UFUNCTION()
	void SetProperties(UArmorInfo* ArmorInfo);
};
