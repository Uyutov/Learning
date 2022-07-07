// Fill out your copyright notice in the Description page of Project Settings.


//#include "ItemsRow.h"
//
//void UItemsRow::SetSize(int32 SizeOfArray)
//{
//	ArraySize = SizeOfArray;
//}
//
//int32 UItemsRow::AddIn(UItemInformation* ItemInfo)
//{
//	switch (ItemInfo->ItemType)
//	{
//	case EItemType::ARMOR: {
//
//		UArmorInfo* ArmorInfo = NewObject<UArmorInfo>();
//		ArmorInfo->Copy(ItemInfo);
//		UE_LOG(LogTemp, Warning, TEXT("Item ammount: %d"), ItemInfo->Ammount);
//		for (auto& armor : Items)
//		{
//			if (armor->Name == ArmorInfo->Name)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("tryind to add items to simelar once"));
//				if (armor->MaxAmmount >= armor->Ammount + ArmorInfo->Ammount)
//				{
//					armor->Ammount += ArmorInfo->Ammount;
//					return 0;
//				}
//				UE_LOG(LogTemp, Warning, TEXT("adding ostatok"));
//				if (armor->MaxAmmount != armor->Ammount)
//				{	
//					ArmorInfo->Ammount = ArmorInfo->Ammount + armor->Ammount - ArmorInfo->MaxAmmount;
//					ItemInfo->Ammount = ArmorInfo->Ammount;
//					armor->Ammount = armor->MaxAmmount;
//				}
//				
//			}
//		}
//		if (Items.Num() < ArraySize)
//		{
//			if (PutIn(ArmorInfo) == 0)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("All ites are added"));
//				ItemInfo->Ammount = 0;
//				return 0;
//			}
//			else
//			{
//				ItemInfo->Ammount = ArmorInfo->Ammount;
//				return ItemInfo->Ammount;
//			}
//		}
//		break;
//	}
//	case EItemType::CONSUMABLE: {
//		UConsumablesInfo* ConsumablesInfo = NewObject<UConsumablesInfo>();
//		ConsumablesInfo->Copy(ItemInfo);
//
//		for (auto& consumable : Items)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("tryind to add items to simelar once"));
//			if (consumable->Name == ConsumablesInfo->Name)
//			{
//				if (consumable->MaxAmmount >= consumable->Ammount + ConsumablesInfo->Ammount)
//				{
//					consumable->Ammount += ConsumablesInfo->Ammount;
//					return 0;
//				}
//				else
//				{
//					if (consumable->MaxAmmount != consumable->Ammount)
//					{
//						ConsumablesInfo->Ammount = ConsumablesInfo->Ammount + consumable->Ammount - ConsumablesInfo->MaxAmmount;
//						ItemInfo->Ammount = ConsumablesInfo->Ammount;
//						consumable->Ammount = consumable->MaxAmmount;
//					}
//				}
//			}
//		}
//		if (Items.Num() < ArraySize)
//		{
//			if (PutIn(ConsumablesInfo) == 0)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("All ites are added"));
//				ItemInfo->Ammount = 0;
//				return 0;
//			}
//			else
//			{
//				ItemInfo->Ammount = ConsumablesInfo->Ammount;
//				return ItemInfo->Ammount;
//			}
//		}
//		break;
//	}
//	case EItemType::ITEM: {
//
//		UItemInformation* ItemInformation = NewObject<UItemInformation>();
//		ItemInformation->Copy(ItemInfo);
//	
//		for (auto& item : Items)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("tryind to add items to simelar once"));
//			if (item->Name == ItemInformation->Name)
//			{
//				if (item->MaxAmmount >= item->Ammount + ItemInformation->Ammount)
//				{
//					item->Ammount += ItemInformation->Ammount;
//					return 0;
//				}
//				else
//				{
//					if (item->MaxAmmount != item->Ammount)
//					{
//						ItemInformation->Ammount = ItemInformation->Ammount + item->Ammount - ItemInformation->MaxAmmount;
//						ItemInfo->Ammount = ItemInformation->Ammount;
//						item->Ammount = item->MaxAmmount;
//					}
//				}
//			}
//		}
//
//		if (Items.Num() < ArraySize)
//		{
//			if (PutIn(ItemInformation) == 0)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("All ites are added"));
//				ItemInfo->Ammount = 0;
//				return 0;
//			}
//			else
//			{
//				ItemInfo->Ammount = ItemInformation->Ammount;
//				return ItemInfo->Ammount;
//			}
//		}
//		break;
//	}
//	}
//	return ItemInfo->Ammount;
//}
//
//bool UItemsRow::RemoveItem(UItemInformation* ItemInfo)
//{
//	return false;
//}
//
//int32 UItemsRow::PutIn(UItemInformation* ItemInfo)
//{
//	int32 rest = ItemInfo->Ammount;
//	UE_LOG(LogTemp, Warning, TEXT("Adding armor to inventory"));
//	if (Items.Num() <= ArraySize) {
//		if (ItemInfo->MaxAmmount >= ItemInfo->Ammount)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Item gets enough spaece"));
//			Items.Add(ItemInfo);
//			return 0;
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Item ammount more than max ammount"));
//			UArmorInfo* SplitedItem = NewObject<UArmorInfo>();
//			SplitedItem->Copy(ItemInfo);
//			SplitedItem->Ammount = SplitedItem->MaxAmmount;
//			Items.Add(SplitedItem);
//			ItemInfo->Ammount -= ItemInfo->MaxAmmount;
//			rest = this->PutIn(ItemInfo);
//		}
//	}
//
//	return rest;
//}
//
//int32 UItemsRow::PutIn(UArmorInfo* ArmorInfo)
//{
//	int32 rest = ArmorInfo->Ammount;
//	UE_LOG(LogTemp, Warning, TEXT("Adding armor to inventory"));
//	if (Items.Num() < ArraySize) {
//		if (ArmorInfo->MaxAmmount >= ArmorInfo->Ammount)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Item gets enough spaece"));
//			Items.Add(ArmorInfo);
//			return 0;
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Item ammount more than max ammount"));
//			UArmorInfo* SplitedArmor = NewObject<UArmorInfo>();
//			SplitedArmor->Copy(ArmorInfo);
//			SplitedArmor->Ammount = SplitedArmor->MaxAmmount;
//			Items.Add(SplitedArmor);
//			ArmorInfo->Ammount -= ArmorInfo->MaxAmmount;
//			rest = this->PutIn(ArmorInfo);
//		}
//	}
//	return rest;
//}
//
//int32 UItemsRow::PutIn(UConsumablesInfo* ConsumablesInfo)
//{
//	int32 rest = ConsumablesInfo->Ammount;
//	UE_LOG(LogTemp, Warning, TEXT("Adding armor to inventory"));
//	if (Items.Num() <= ArraySize) {
//		UE_LOG(LogTemp, Warning, TEXT("Trying to put in consumable"));
//		if (ConsumablesInfo->MaxAmmount >= ConsumablesInfo->Ammount)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Item gets enough spaece"));
//			Items.Add(ConsumablesInfo);
//			return 0;
//		}
//		else
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Item ammount more than max ammount"));
//			UArmorInfo* SplitedConsumable = NewObject<UArmorInfo>();
//			SplitedConsumable->Copy(ConsumablesInfo);
//			SplitedConsumable->Ammount = SplitedConsumable->MaxAmmount;
//			Items.Add(SplitedConsumable);
//			ConsumablesInfo->Ammount -= ConsumablesInfo->MaxAmmount;
//			rest = this->PutIn(ConsumablesInfo);
//		}
//	}
//
//	return rest;
//}