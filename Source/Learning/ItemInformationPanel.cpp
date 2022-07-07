// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInformationPanel.h"
#include "ItemLibrary.h"
#include "CommonItemInfoPanel.h"
#include "ArmorItemInfoPanel.h"
#include "ConsumableItemInfoPanel.h"

void UItemInformationPanel::SetPropertys(UItemInformation* ItemInfo)
{
	this->ClearPanel();
	if (ItemInfo) {
		if (ItemInfo->ItemType == EItemType::ITEM)
		{
			if (CommonItemPanelClass)
			{
				UCommonItemInfoPanel* CommonItemPanel = CreateWidget<UCommonItemInfoPanel>(this, CommonItemPanelClass);
				CommonItemPanel->SetProperties(ItemInfo);
				Panels->AddChildToVerticalBox(CommonItemPanel);
			}
		}
		if (ItemInfo->ItemType == EItemType::ARMOR)
		{
			UE_LOG(LogTemp, Warning, TEXT("If type of info is ARMOR"));
			if (ArmorPanelClass && CommonItemPanelClass)
			{
				UE_LOG(LogTemp, Warning, TEXT("If Armor class exists"));
				UCommonItemInfoPanel* CommonItemPanel = CreateWidget<UCommonItemInfoPanel>(this, CommonItemPanelClass);
				CommonItemPanel->SetProperties(ItemInfo);
				UArmorItemInfoPanel* ArmorItemPanel = CreateWidget<UArmorItemInfoPanel>(this, ArmorPanelClass);
				UArmorInfo* ArmorInfo = Cast<UArmorInfo>(ItemInfo);
				if (ArmorInfo) {
					UE_LOG(LogTemp, Warning, TEXT("Before setting propertys"));
					ArmorItemPanel->SetProperties(ArmorInfo);
				}
				Panels->AddChildToVerticalBox(CommonItemPanel);
				Panels->AddChildToVerticalBox(ArmorItemPanel);
			}
		}
		if (ItemInfo->ItemType == EItemType::CONSUMABLE)
		{
			if (ConsumablePanelClass && CommonItemPanelClass)
			{
				UCommonItemInfoPanel* CommonItemPanel = CreateWidget<UCommonItemInfoPanel>(this, CommonItemPanelClass);
				CommonItemPanel->SetProperties(ItemInfo);
				UConsumableItemInfoPanel* ConsumablePanel = CreateWidget<UConsumableItemInfoPanel>(this, ConsumablePanelClass);
				UConsumablesInfo* ConsumableInfo = Cast<UConsumablesInfo>(ItemInfo);
				if (ConsumableInfo)
				{
					ConsumablePanel->SetProperties(ConsumableInfo);
				}
				Panels->AddChildToVerticalBox(CommonItemPanel);
				Panels->AddChildToVerticalBox(ConsumablePanel);
			}
		}
	}
}

void UItemInformationPanel::ClearPanel()
{
	Panels->ClearChildren();
}