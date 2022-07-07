// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "RunTime/UMG/Public/UMG.h"
#include "ItemLibrary.h"
#include "ItemInformationPanel.h"
#include "InventoryPanel.generated.h"

class UGridCell;
class UItemDragDropOperation;
/**
 * 
 */
UCLASS()
class LEARNING_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()
protected:
	bool OutOfScreen;
public:
	UPROPERTY(EditAnywhere, Category = "Inventory Panel")
		TSubclassOf<UGridCell> ItemWidgetClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Inventory Panel")
		int32 Columns = 4;
	UPROPERTY(EditAnywhere, Category = "Inventory Panel")
		int32 Rows = 3;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory Panel", meta = (BindWidget))
		UTextBlock* Label = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Panel", meta = (BindWidget))
		UUniformGridPanel* Grid = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = "Inventory Panel", meta = (BindWidget))
		UItemInformationPanel* InfoPanel;


	UFUNCTION()
		void SetSize(int32 AmmountOfRows, int32 AmmountOfColumns);
	UFUNCTION()
		void PutInItem(UItemInformation* ItemInfo);
	UFUNCTION()
		void CreateInventory(int32 AmmountOfRows, int32 AmmountOfColumns);
	UFUNCTION()
		void UpdateInformation();
	UFUNCTION()
		void SwapCells(UGridCell* FirstCell, UGridCell* SecondCell);
	UFUNCTION()
		void SendInfoToPanel(UItemInformation* ItemInfo);
	UFUNCTION()
		void ClearInfoPanel();
	UFUNCTION()
		bool CheckDrop(UItemDragDropOperation* DropOperation);
	UFUNCTION()
		UGridCell* CreatePointer();

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	
};
