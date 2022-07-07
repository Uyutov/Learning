// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableItem.h"

AConsumableItem::AConsumableItem()
{
	ConsumableInfo = CreateDefaultSubobject<UConsumablesInfo>("ConsumablesInfo");
}

void AConsumableItem::BeginPlay()
{
	Super::BeginPlay();
}

void AConsumableItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if (DataAsset)
	{
		UConsumablesDataAsset* ConsumableDataAsset = Cast<UConsumablesDataAsset>(DataAsset);

		if (ConsumableDataAsset)
		{
			ConsumableDataAsset->ChangeAll.AddUObject(this, &AConsumableItem::ApplyChange);
			ApplyChange(ConsumableDataAsset->ConsumableInfoArray);
		}
	}
}

void AConsumableItem::ApplyChange(TArray<FConsumablesInfoStruct> ConsumablesArray)
{
	for (auto& ConsumableRow : ConsumablesArray)
	{
		if (ConsumableRow.ItemVariation == ItemVariation && ConsumableInfo)
		{
			ConsumableInfo->ItemType = ConsumableRow.ItemType;
			ConsumableInfo->ItemVariation = ConsumableRow.ItemVariation;
			ConsumableInfo->Coast = ConsumableRow.Coast;
			ConsumableInfo->Ammount = ConsumableRow.Ammount;
			ConsumableInfo->MaxAmmount = ConsumableRow.MaxAmmount;
			ConsumableInfo->Name = ConsumableRow.Name;
			ConsumableInfo->Weight = ConsumableRow.Weight;
			ConsumableInfo->Image = ConsumableRow.Image;
			ConsumableInfo->Mesh = ConsumableRow.Mesh;

			ConsumableInfo->Duration = ConsumableRow.Duration;
			ConsumableInfo->Rate = ConsumableRow.Rate;

			Mesh->SetStaticMesh(ConsumableInfo->Mesh);

			break;
		}
	}
}

UItemInformation* AConsumableItem::GetItemInformation()
{
	return ConsumableInfo;
}

void AConsumableItem::PickUp_Implementation(AActor* LiftingActor)
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

void AConsumableItem::TakeInfoFromItem(APickUp* ItemToTakeInfoFrom)
{
	AConsumableItem* ConsumableInfoSource = Cast<AConsumableItem>(ItemToTakeInfoFrom);
	if (ConsumableInfoSource && ConsumableInfo)
	{
		ConsumableInfo->Copy(ConsumableInfoSource->ConsumableInfo);
	}
}

void AConsumableItem::SetPropertys(UConsumablesInfo* InfoAboutConsumable)
{
	ConsumableInfo->Copy(InfoAboutConsumable);
	Mesh->SetStaticMesh(ConsumableInfo->Mesh);
}