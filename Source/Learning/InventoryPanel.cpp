// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemDragDropOperation.h"
#include "GridCell.h"
#include "MyCharacter.h"
#include "InventoryPanel.h"

void UInventoryPanel::CreateInventory(int32 AmmountOfRows, int32 AmmountOfColumns)
{
	if (Label)
	{
		Label->SetText(FText::FromString("Inventory"));
	}

	if (Grid && ItemWidgetClass)
	{
		APlayerController* Player = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
		if (Player) 
		{
			for (int32 y = 0; y < Rows; ++y)
				{
				for (int32 x = 0; x < Columns; ++x)
				{
					UUserWidget* Widget = CreateWidget<UUserWidget>(Player, ItemWidgetClass);
					if (Widget)
					{
						Grid->AddChildToUniformGrid(Widget, y, x);
					}
				}
			}
		}
	}
}

void UInventoryPanel::SetSize(int32 AmmountOfRows, int32 AmmountOfColumns)
{
	Rows = AmmountOfRows;
	Columns = AmmountOfColumns;
}

void UInventoryPanel::PutInItem(UItemInformation* ItemInfo)
{
	TArray<UWidget*> AllCells = Grid->GetAllChildren();
	int32 AmmountOfChildren = Grid->GetChildrenCount();
	int32 i = 1;
	for (auto& Cell : AllCells)
	{
		UGridCell* GridCell = Cast<UGridCell>(Cell);
		if (GridCell)
		{
			if (GridCell->ItemInfo == nullptr)
			{
				GridCell->FillCell(ItemInfo);
				GridCell->Owner = this;
				return;
			}
		}
	}
}

void UInventoryPanel::UpdateInformation()
{
	TArray<UWidget*> AllCells = Grid->GetAllChildren();
	for (auto& Cell : AllCells)
	{
		UGridCell* GridCell = Cast<UGridCell>(Cell);
		if (GridCell)
		{
			if (GridCell->ItemInfo != nullptr)
			{
				GridCell->UpdateInfo();
			}
		}
	}
}

void UInventoryPanel::SwapCells(UGridCell* FirstCell, UGridCell* SecondCell)
{
	UItemInformation* InfoCopy = SecondCell->ItemInfo;
	
	if (FirstCell->ItemInfo)
	{
		UE_LOG(LogTemp, Warning, TEXT("Added to second slot"));
		SecondCell->Cell->OnClicked.Clear();
		SecondCell->Owner = this;
		SecondCell->FillCell(FirstCell->ItemInfo);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Second slot cleared"));
		SecondCell->ClearCell();
	}
	if (InfoCopy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Added to first slot"));
		FirstCell->Cell->OnClicked.Clear();
		FirstCell->Owner = this;
		FirstCell->FillCell(InfoCopy);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("First slot cleared"));
		FirstCell->ClearCell();
	}
}

void UInventoryPanel::SendInfoToPanel(UItemInformation* ItemInfo)
{
	if (InfoPanel)
	{
		InfoPanel->SetPropertys(ItemInfo);
	}
}

void UInventoryPanel::ClearInfoPanel()
{
	if (InfoPanel)
	{
		InfoPanel->ClearPanel();
	}
}

void UInventoryPanel::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Drag is entaring"));
	OutOfScreen = false;
}

void UInventoryPanel::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//UE_LOG(LogTemp, Warning, TEXT("Drag is leving"));
	OutOfScreen = true;
}

bool UInventoryPanel::CheckDrop(UItemDragDropOperation* DropOperation)
{
	UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(DropOperation);
	if(ItemDragDrop){
		if (OutOfScreen)
		{
			AMyCharacter* Player = GetOwningPlayerPawn<AMyCharacter>();
			if (Player) 
			{
				UGridCell* Cell = Cast<UGridCell>(ItemDragDrop->Payload);
				if (Cell)
				{
					return Player->RemoveItem(Cell->ItemInfo);
				}
			}
		}
	}
	return false;
}

UGridCell* UInventoryPanel::CreatePointer()
{
	UGridCell* Pointer = nullptr;
	APlayerController* Player = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (Player)
	{
		Pointer = CreateWidget<UGridCell>(Player, ItemWidgetClass);
	}
	return Pointer;
}