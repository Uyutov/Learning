// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonItemInfoPanel.h"
#include "ItemLibrary.h"

void UCommonItemInfoPanel::SetProperties(UItemInformation* CommonInfo)
{
	if (CommonInfo) 
	{
		ItemName->SetText(FText::FromString(CommonInfo->Name));
		ItemMaxAmmount->SetText(FText::AsNumber(CommonInfo->MaxAmmount));
		ItemAmmount->SetText(FText::AsNumber(CommonInfo->Ammount));
		ItemWeight->SetText(FText::AsNumber(CommonInfo->Weight));
		ItemCoast->SetText(FText::AsNumber(CommonInfo->Coast));
	}
}