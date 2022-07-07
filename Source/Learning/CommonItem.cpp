// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonItem.h"

ACommonItem::ACommonItem()
{
	ItemInfo = CreateDefaultSubobject<UItemInformation>("ItemInfo");
}

void ACommonItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (DataAsset)
	{
		UItemDataAsset* ItemDataAsset = Cast<UItemDataAsset>(DataAsset);

		if (ItemDataAsset)
		{
			ItemDataAsset->ChangeAll.AddUObject(this, &ACommonItem::ApplyChange);
			ApplyChange(ItemDataAsset->ItemInfoArray);
		}
	}
}

void ACommonItem::ApplyChange(TArray<FItemInfoStruct> ItemsArray)
{
	for (auto& ItemRow : ItemsArray)
	{
		if (ItemRow.ItemVariation == ItemVariation && ItemInfo)
		{
			ItemInfo->ItemType = ItemRow.ItemType;
			ItemInfo->ItemVariation = ItemRow.ItemVariation;
			ItemInfo->Coast = ItemRow.Coast;
			ItemInfo->Ammount = ItemRow.Ammount;
			ItemInfo->MaxAmmount = ItemRow.MaxAmmount;
			ItemInfo->Name = ItemRow.Name;
			ItemInfo->Weight = ItemRow.Weight;
			ItemInfo->Image = ItemRow.Image;
			ItemInfo->Mesh = ItemRow.Mesh;

			Mesh->SetStaticMesh(ItemInfo->Mesh);

			break;
		}
	}
}

UItemInformation* ACommonItem::GetItemInformation()
{
	return ItemInfo;
}

void ACommonItem::BeginPlay()
{
	Super::BeginPlay();
}

void ACommonItem::PickUp_Implementation(AActor* LiftingActor)
{
	UInventoryComponent* CharacterInventory = Cast<UInventoryComponent>(LiftingActor->FindComponentByClass(UInventoryComponent::StaticClass()));

	if (CharacterInventory)
	{
		if (CharacterInventory->Add(this))
		{
			UE_LOG(LogTemp, Warning, TEXT("Deleting"));
			this->Destroy();
		}
	}
}

void ACommonItem::TakeInfoFromItem(APickUp* ItemToTakeInfoFrom)
{
	ACommonItem* ItemInfoSource = Cast<ACommonItem>(ItemToTakeInfoFrom);
	if (ItemInfoSource && ItemInfo)
	{
		ItemInfo->Copy(ItemInfoSource->ItemInfo);
	}
}

void ACommonItem::SetPropertys(UItemInformation* InfoAboutItem)
{
	ItemInfo->Copy(InfoAboutItem);
	Mesh->SetStaticMesh(ItemInfo->Mesh);
}
