// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GridCell.generated.h"


class UInventoryPanel;

/**
 * 
 */
UCLASS()
class LEARNING_API UGridCell : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
		UInventoryPanel* Owner;
	UPROPERTY()
		UItemInformation* ItemInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* Cell;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* AmmountOfItems;
	
	UFUNCTION()
		void FillCell(UItemInformation* InfoAboutItem);
	UFUNCTION()
		void ClearCell();
	UFUNCTION()
		void UpdateInfo();
	UFUNCTION()
		void SendInfoToItemPanel();

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	//virtual void NativeConstruct() override;
	
};
