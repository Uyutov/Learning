// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components\TextBlock.h"
#include "CommonItemInfoPanel.generated.h"

class UItemInformation;

/**
 * 
 */
UCLASS()
class LEARNING_API UCommonItemInfoPanel : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemName;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemMaxAmmount;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemAmmount;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemWeight;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UTextBlock* ItemCoast;
public:
	UFUNCTION()
	void SetProperties(UItemInformation* CommoInfo);
};
