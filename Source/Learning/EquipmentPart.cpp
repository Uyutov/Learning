// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentPart.h"
#include "ItemLibrary.h"
#include "AccessibleArmorTypes.h"

UEquipmentPart::UEquipmentPart()
{
	AccessibleArmor = CreateDefaultSubobject<UAccessibleArmorTypes>("AccessibleArmor");
	if (AccessibleArmor)
	{
		UE_LOG(LogTemp, Warning, TEXT("AccecibleArmor made"));
	}
}

UArmorInfo* UEquipmentPart::EquipArmor(UArmorInfo* ArmorPiece)
{

	if (ArmorPiece) {
		bool IsEquipeble = false;
		for (auto& type : AccessibleArmor->ArmorTypesList)
		{
			if (ArmorPiece->ArmorType == type)
			{
				IsEquipeble = true;
				break;
			}
		}
		if (IsEquipeble == false)
		{
			return ArmorPiece;
		}

		for (auto& unit : Equipment)
		{
			if (unit->ArmorType == ArmorPiece->ArmorType)
			{
				if (ArmorPiece->Ammount == 1)
				{
					UArmorInfo* Copy = unit;
					unit = ArmorPiece;
					return Copy;
				}
				else
				{
					UArmorInfo* NewSplitedArmor = Cast<UArmorInfo>(ArmorPiece->CreateDeepCopy());
					NewSplitedArmor->Ammount = 1;
					ArmorPiece->Ammount -= 1;
					UArmorInfo* Copy = unit;
					unit = NewSplitedArmor;
					return Copy;
				}
			}
		}
		UArmorInfo* NewArmor = Cast<UArmorInfo>(ArmorPiece->CreateDeepCopy());
		Equipment.Add(NewArmor);
		ArmorPiece = nullptr;
		return ArmorPiece;
	}
	return nullptr;
}

UArmorInfo* UEquipmentPart::TakeOffArmor(UArmorInfo* ArmorPiece)
{
	if (ArmorPiece)
	{
		if (Equipment.Remove(ArmorPiece) >= 0)
		{
			return ArmorPiece;
		}
	}
	return nullptr;
}