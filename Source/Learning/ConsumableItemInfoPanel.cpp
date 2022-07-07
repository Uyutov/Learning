// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumableItemInfoPanel.h"
#include "ItemLibrary.h"

void UConsumableItemInfoPanel::SetProperties(UConsumablesInfo* ConsumableInfo)
{
	if (ConsumableInfo)
	{
		Duration->SetText(FText::AsNumber(ConsumableInfo->Duration));
		Rate->SetText(FText::AsNumber(ConsumableInfo->Rate));
	}
}