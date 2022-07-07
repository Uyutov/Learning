// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components\VerticalBox.h"
#include "ItemInformationPanel.generated.h"

class UCommonItemInfoPanel;
class UArmorItemInfoPanel;
class UConsumableItemInfoPanel;
/**
 * 
 */
UCLASS()
class LEARNING_API UItemInformationPanel : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UVerticalBox* Panels;

public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<UCommonItemInfoPanel> CommonItemPanelClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UArmorItemInfoPanel> ArmorPanelClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UConsumableItemInfoPanel> ConsumablePanelClass;

	UFUNCTION()
		void SetPropertys(UItemInformation* ItemInfo);
	UFUNCTION()
		void ClearPanel();

};
