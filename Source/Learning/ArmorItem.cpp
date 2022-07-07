// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorItem.h"

AArmorItem::AArmorItem()
{
	ArmorInfo = CreateDefaultSubobject<UArmorInfo>("ItemInfo");
}

void AArmorItem::BeginPlay()
{
	Super::BeginPlay();
}

void AArmorItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if(DataAsset)
	{
		UArmorDataAsset* ArmorDataAsset = Cast<UArmorDataAsset>(DataAsset);

		if (ArmorDataAsset)
		{
			ArmorDataAsset->ChangeAll.AddUObject(this, &AArmorItem::ApplyChange);
			ApplyChange(ArmorDataAsset->ArmorInfoArray);
		}
	}
}

void AArmorItem::ApplyChange(TArray<FArmorInfoStruct> ArmorArray)
{
	for (auto& ArmorRow : ArmorArray)
	{
		if (ArmorRow.ItemVariation == ItemVariation && ArmorInfo)
		{
			ArmorInfo->ItemType = ArmorRow.ItemType;
			ArmorInfo->ItemVariation = ArmorRow.ItemVariation;
			ArmorInfo->Coast = ArmorRow.Coast;
			ArmorInfo->Ammount = ArmorRow.Ammount;
			UE_LOG(LogTemp, Warning, TEXT("Ammount of items: %d"), ArmorInfo->Ammount);
			ArmorInfo->MaxAmmount = ArmorRow.MaxAmmount;
			ArmorInfo->Name = ArmorRow.Name;
			ArmorInfo->Weight = ArmorRow.Weight;
			ArmorInfo->Image = ArmorRow.Image;
			ArmorInfo->Mesh = ArmorRow.Mesh;

			
			ArmorInfo->Armor = ArmorRow.Armor;
			ArmorInfo->ArmorType = ArmorRow.ArmorType;

			Mesh->SetStaticMesh(ArmorInfo->Mesh);

			break;
		}
	}
}

void AArmorItem::SetPropertys(UArmorInfo* InfoAboutArmor)
{
	ArmorInfo->Copy(InfoAboutArmor);
	Mesh->SetStaticMesh(ArmorInfo->Mesh);
}

UItemInformation* AArmorItem::GetItemInformation()
{
	return ArmorInfo;
}

void AArmorItem::PickUp_Implementation(AActor* LiftingActor)
{
	UInventoryComponent* CharacterInventory = Cast<UInventoryComponent>(LiftingActor->FindComponentByClass(UInventoryComponent::StaticClass()));
	if (CharacterInventory)
	{
		if (CharacterInventory->Add(this))
		{
			this->Destroy();
		}
	}
}

void AArmorItem::TakeInfoFromItem(APickUp* ItemToTakeInfoFrom)
{
	AArmorItem* ArmorInfoSource = Cast<AArmorItem>(ItemToTakeInfoFrom);
	if(ArmorInfoSource && ArmorInfo)
	{
		ArmorInfo->Copy(ArmorInfoSource->ArmorInfo);
	}
}
