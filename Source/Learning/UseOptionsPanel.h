// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "UseOptionsPanel.generated.h"

class UItemInformation;

/**
 * 
 */
UCLASS()
class LEARNING_API UUseOptionsPanel : public UUserWidget
{
	GENERATED_BODY()
private:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		UVerticalBox* Panels;
public:

	UFUNCTION()
		void CreateUseOptions(UItemInformation* ItemInfo);
	UFUNCTION()
		void ClearPanel();

};
