// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorItemInfoPanel.h"
#include "ItemLibrary.h"

void UArmorItemInfoPanel::SetProperties(UArmorInfo* ArmorInfo)
{
	if (ArmorInfo)
	{
		ArmorType->SetText(UEnum::GetDisplayValueAsText(ArmorInfo->ArmorType));
		Armor->SetText(FText::AsNumber(ArmorInfo->Armor));
	}
}