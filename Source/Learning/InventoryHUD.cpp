// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHUD.h"

void AInventoryHUD::BeginPlay() 
{
	
	Super::BeginPlay();

	if(InventoryWidgetClass)
	{
		
		InventoryWidget = CreateWidget<UInventoryPanel>(GetWorld(), InventoryWidgetClass);

		if (InventoryWidget) {

			InventoryWidget->AddToViewport();
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

void AInventoryHUD::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

}

void AInventoryHUD::DrawHUD()
{

	Super::DrawHUD();

}

void AInventoryHUD::OpenInventory()
{

	if (InventoryWidget)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}

}

void AInventoryHUD::CloseInventoy()
{

	if (InventoryWidget)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}

}