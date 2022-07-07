// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLibrary.h"

UConsumablesInfo::UConsumablesInfo()
{
	
	ItemType = EItemType::CONSUMABLE;
}

UArmorInfo::UArmorInfo()
{
	ItemType = EItemType::ARMOR;
}

void UItemInformation::Copy(UItemInformation* OtherItem)
{
	if (OtherItem) {
		this->Coast = OtherItem->Coast;
		this->Ammount = OtherItem->Ammount;
		this->MaxAmmount = OtherItem->MaxAmmount;
		this->Name = OtherItem->Name;
		this->Weight = OtherItem->Weight;
		this->Image = OtherItem->Image;
		this->Mesh = OtherItem->Mesh;
	}
}

UItemInformation* UItemInformation::CreateDeepCopy()
{
	UItemInformation* NewItemInfo = NewObject<UItemInformation>();
	NewItemInfo->Copy(this);
	return NewItemInfo;
}

void UArmorInfo::Copy(UItemInformation* OtherItem)
{
	if (OtherItem) {
		
		UArmorInfo* info = Cast<UArmorInfo>(OtherItem);
		
		if (info) {

			this->ItemVariation = info->ItemVariation;
			this->ItemType = info->ItemType;
			this->Coast = info->Coast;
			this->Ammount = info->Ammount;
			this->MaxAmmount = info->MaxAmmount;
			this->Name = info->Name;
			this->Weight = info->Weight;
			this->Image = info->Image;
			this->Mesh = info->Mesh;
			this->Armor = info->Armor;
			this->ArmorType = info->ArmorType;
		}
	}
}

UItemInformation* UArmorInfo::CreateDeepCopy()
{
	UArmorInfo* NewArmorInfo = NewObject<UArmorInfo>();
	NewArmorInfo->Copy(this);
	return NewArmorInfo;
}

void UConsumablesInfo::Copy(UItemInformation* OtherItem)
{
	if (OtherItem) {

		UConsumablesInfo* info = Cast<UConsumablesInfo>(OtherItem);

		this->Coast = info->Coast;
		this->Ammount = info->Ammount;
		this->MaxAmmount = info->MaxAmmount;
		this->Name = info->Name;
		this->Weight = info->Weight;
		this->Image = info->Image;
		this->Mesh = info->Mesh;
		this->Duration = info->Duration;
		this->Rate = info->Rate;
	}

}

UItemInformation* UConsumablesInfo::CreateDeepCopy()
{
	UConsumablesInfo* NewConsumableInfo = NewObject<UConsumablesInfo>();
	NewConsumableInfo->Copy(this);
	return NewConsumableInfo;
}

void UItemDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ChangeAll.Broadcast(ItemInfoArray);
}

void UArmorDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ChangeAll.Broadcast(ArmorInfoArray);
}

void UConsumablesDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	ChangeAll.Broadcast(ConsumableInfoArray);
}