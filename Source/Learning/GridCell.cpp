// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCell.h"
#include "ItemDragDropOperation.h"
#include "InventoryPanel.h"

void UGridCell::FillCell(UItemInformation* InfoAboutItem)
{
	if (InfoAboutItem)
	{
		ItemInfo = InfoAboutItem;
		if (ItemInfo->Image && ItemImage) {
			ItemImage->SetBrushFromTexture(ItemInfo->Image);
		}
		ItemName->SetText(FText::FromString(ItemInfo->Name));
		AmmountOfItems->SetText(FText::AsNumber(ItemInfo->Ammount));
		Cell->OnClicked.AddDynamic(this, &UGridCell::SendInfoToItemPanel);
	}
}

void UGridCell::ClearCell()
{
	ItemImage->Brush = FSlateBrush();
	ItemName->SetText(FText::GetEmpty());
	AmmountOfItems->SetText(FText::GetEmpty());
	ItemInfo = nullptr;
	Owner = nullptr;
	Cell->OnClicked.Clear();
}

void UGridCell::SendInfoToItemPanel()
{
	if (Owner)
	{
		Owner->SendInfoToPanel(ItemInfo);
	}
}

void UGridCell::UpdateInfo()
{
	if (ItemInfo)
	{
		AmmountOfItems->SetText(FText::AsNumber(ItemInfo->Ammount));
	}
}

FReply UGridCell::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		Reply.DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
		return Reply;
	}
	return Reply;
}

void UGridCell::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (Owner && Owner->ItemWidgetClass)
	{
		UGridCell* Pointer = Owner->CreatePointer();

		if (Pointer)
		{
			if (ItemInfo) {
				Pointer->FillCell(ItemInfo);
			}
			
			Pointer->SetDesiredSizeInViewport(GetDesiredSize());
			Pointer->ColorAndOpacity = FLinearColor(this->ColorAndOpacity.R, this->ColorAndOpacity.G, this->ColorAndOpacity.B, 0.5);
			this->ColorAndOpacity = Pointer->ColorAndOpacity;

			UItemDragDropOperation* DragOperation = NewObject<UItemDragDropOperation>();
			DragOperation->Payload = this;
			DragOperation->DefaultDragVisual = Pointer;
			DragOperation->Pivot = EDragPivot::CenterCenter;

			OutOperation = DragOperation;
		}
	}
}

void UGridCell::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (Owner)
	{
		UItemDragDropOperation* ItemDrag = Cast<UItemDragDropOperation>(InOperation);
		if (ItemDrag) 
		{
			if (Owner->CheckDrop(ItemDrag))
			{
				this->ClearCell();
			}
		}
	}
}

bool UGridCell::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UItemDragDropOperation* ItemOperation = Cast<UItemDragDropOperation>(InOperation);
	if (ItemOperation)
	{
		UGridCell* AnotherCell = Cast<UGridCell>(ItemOperation->Payload);
		if (AnotherCell)
		{
			if (this->ItemInfo != AnotherCell->ItemInfo)
			{	
				if(Owner)
				{
					Owner->SwapCells(this, AnotherCell);
				}
				if (AnotherCell->Owner)
				{
					AnotherCell->Owner->SwapCells(this, AnotherCell);
				}
				return true;
			}
		}
	}
	return false;
}

void UGridCell::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		//
	}
}