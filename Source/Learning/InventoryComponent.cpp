// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "PlayerHUD.h"
#include "MyCharacter.h"
#include "PickUp.h"
#include "ItemLibrary.h"
#include "EquipmentPart.h"
#include "InventoryPanel.h"
#include "AccessibleArmorTypes.h"

UInventoryComponent::UInventoryComponent()
{
	Equipment = CreateDefaultSubobject<UEquipmentPart>("Equipment");
}

void UInventoryComponent::BeginPlay()
{
	if (AccessibleArmor)
	{
		if (Equipment) {
			Equipment->AccessibleArmor = NewObject<UAccessibleArmorTypes>(this, AccessibleArmor);
		}
	}
}

bool UInventoryComponent::Add(APickUp* Item)
{
	UItemInformation* ItemInfo = Item->GetItemInformation();
	if (ItemInfo) {
		switch (ItemInfo->ItemType)
		{
		case EItemType::ARMOR: {

			UArmorInfo* ArmorInfo = NewObject<UArmorInfo>();
			ArmorInfo->Copy(ItemInfo);
			for (auto& armor : Items)
			{
				if (armor->Name == ArmorInfo->Name)
				{
					if (armor->MaxAmmount >= armor->Ammount + ArmorInfo->Ammount)
					{
						armor->Ammount += ArmorInfo->Ammount;
						return true;
					}
					if (armor->MaxAmmount != armor->Ammount)
					{
						ArmorInfo->Ammount = ArmorInfo->Ammount + armor->Ammount - ArmorInfo->MaxAmmount;
						ItemInfo->Ammount = ArmorInfo->Ammount;
						armor->Ammount = armor->MaxAmmount;
					}

				}
			}
			if (Items.Num() < ArraySize)
			{
				if (PutIn(ArmorInfo) == 0)
				{
					ItemInfo->Ammount = 0;
					return true;
				}
				else
				{
					ItemInfo->Ammount = ArmorInfo->Ammount;
					return false;
				}
			}
			break;
		}
		case EItemType::CONSUMABLE: {
			UConsumablesInfo* ConsumablesInfo = NewObject<UConsumablesInfo>();
			ConsumablesInfo->Copy(ItemInfo);

			for (auto& consumable : Items)
			{
				if (consumable->Name == ConsumablesInfo->Name)
				{
					if (consumable->MaxAmmount >= consumable->Ammount + ConsumablesInfo->Ammount)
					{
						consumable->Ammount += ConsumablesInfo->Ammount;
						return true;
					}
					else
					{
						if (consumable->MaxAmmount != consumable->Ammount)
						{
							ConsumablesInfo->Ammount = ConsumablesInfo->Ammount + consumable->Ammount - ConsumablesInfo->MaxAmmount;
							ItemInfo->Ammount = ConsumablesInfo->Ammount;
							consumable->Ammount = consumable->MaxAmmount;
						}
					}
				}
			}
			if (Items.Num() < ArraySize)
			{
				if (PutIn(ConsumablesInfo) == 0)
				{
					ItemInfo->Ammount = 0;
					return true;
				}
				else
				{
					ItemInfo->Ammount = ConsumablesInfo->Ammount;
					return false;
				}
			}
			break;
		}
		case EItemType::ITEM: {

			UItemInformation* ItemInformation = NewObject<UItemInformation>();
			ItemInformation->Copy(ItemInfo);

			for (auto& item : Items)
			{
				if (item->Name == ItemInformation->Name)
				{
					if (item->MaxAmmount >= item->Ammount + ItemInformation->Ammount)
					{
						item->Ammount += ItemInformation->Ammount;
						return true;
					}
					else
					{
						if (item->MaxAmmount != item->Ammount)
						{
							ItemInformation->Ammount = ItemInformation->Ammount + item->Ammount - ItemInformation->MaxAmmount;
							ItemInfo->Ammount = ItemInformation->Ammount;
							item->Ammount = item->MaxAmmount;
						}
					}
				}
			}

			if (Items.Num() < ArraySize)
			{
				if (PutIn(ItemInformation) == 0)
				{
					ItemInfo->Ammount = 0;
					return true;
				}
				else
				{
					ItemInfo->Ammount = ItemInformation->Ammount;
					return false;
				}
			}
			break;
		}
		}
	}
	return false;
}

bool UInventoryComponent::Remove(UItemInformation* RemovedItem)
{
	if(Items.RemoveSingle(RemovedItem) != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item removed succsesfuly"));
		return true;
	}
	return false;
}

void UInventoryComponent::SetInventorySize(int32 Rows, int32 Columns)
{
	ArraySize = Rows * Columns;
}

int32 UInventoryComponent::PutIn(UItemInformation* ItemInfo)
{
	int32 rest = ItemInfo->Ammount;
	if (Items.Num() <= ArraySize) {
		if (ItemInfo->MaxAmmount >= ItemInfo->Ammount)
		{
			Items.Add(ItemInfo);
			if (InventoryPanelWidget)
			{
				InventoryPanelWidget->PutInItem(ItemInfo);
			}
			return 0;
		}
		else
		{
			UArmorInfo* SplitedItem = NewObject<UArmorInfo>();
			SplitedItem->Copy(ItemInfo);
			SplitedItem->Ammount = SplitedItem->MaxAmmount;
			Items.Add(SplitedItem);
			if (InventoryPanelWidget)
			{
				InventoryPanelWidget->PutInItem(SplitedItem);
			}
			ItemInfo->Ammount -= ItemInfo->MaxAmmount;
			rest = this->PutIn(ItemInfo);
		}
	}

	return rest;
}

//int32 UInventoryComponent::PutIn(UArmorInfo* ArmorInfo)
//{
//	
//	int32 rest = ArmorInfo->Ammount;
//	if (Items.Num() < ArraySize) {
//		if (ArmorInfo->MaxAmmount >= ArmorInfo->Ammount)
//		{
//			Items.Add(ArmorInfo);
//			if (InventoryPanelWidget)
//			{
//				InventoryPanelWidget->PutInItem(ArmorInfo);
//			}
//			return 0;
//		}
//		else
//		{
//			UArmorInfo* SplitedArmor = NewObject<UArmorInfo>();
//			SplitedArmor->Copy(ArmorInfo);
//			SplitedArmor->Ammount = SplitedArmor->MaxAmmount;
//			Items.Add(SplitedArmor);
//			if (InventoryPanelWidget)
//			{
//				InventoryPanelWidget->PutInItem(SplitedArmor);
//			}
//			ArmorInfo->Ammount -= ArmorInfo->MaxAmmount;
//			rest = this->PutIn(ArmorInfo);
//		}
//	}
//	return rest;
//}

//int32 UInventoryComponent::PutIn(UConsumablesInfo* ConsumablesInfo)
//{
//	int32 rest = ConsumablesInfo->Ammount;
//	if (Items.Num() <= ArraySize) {
//		if (ConsumablesInfo->MaxAmmount >= ConsumablesInfo->Ammount)
//		{
//			Items.Add(ConsumablesInfo);
//			if (InventoryPanelWidget)
//			{
//				InventoryPanelWidget->PutInItem(ConsumablesInfo);
//			}
//			return 0;
//		}
//		else
//		{
//			UArmorInfo* SplitedConsumable = NewObject<UArmorInfo>();
//			SplitedConsumable->Copy(ConsumablesInfo);
//			SplitedConsumable->Ammount = SplitedConsumable->MaxAmmount;
//			Items.Add(SplitedConsumable);
//			if (InventoryPanelWidget)
//			{
//				InventoryPanelWidget->PutInItem(SplitedConsumable);
//			}
//			ConsumablesInfo->Ammount -= ConsumablesInfo->MaxAmmount;
//			rest = this->PutIn(ConsumablesInfo);
//		}
//	}
//
//	return rest;
//}


