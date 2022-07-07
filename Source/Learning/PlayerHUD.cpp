// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* Player = Cast<APlayerController>(GetOwner());
	if (Player) 
	{
		AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Player->GetPawn());
		if(PlayerCharacter)
		{
			AmmountOfRows = PlayerCharacter->InventoryRows;
			AmmountOfColumns = PlayerCharacter->InventoryColumns;
		}
		InventoryWidget = CreateWidget<UUserWidget>(Player, InventoryClass);
		UInventoryPanel* Inventory = Cast<UInventoryPanel>(InventoryWidget);
		if (Inventory) 
		{
			Inventory->CreateInventory(AmmountOfRows, AmmountOfColumns);
		}
	}
}

void APlayerHUD::UseInventory()
{
	if (IsInventoryOpend == true)
	{
		CloseInventory();
	}
	else
	{
		OpenInventory();
	}
}
void APlayerHUD::OpenInventory()
{
	InventoryWidget->AddToViewport();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
	UInventoryPanel* Inventory = Cast<UInventoryPanel>(InventoryWidget);
	if (Inventory)
	{
		Inventory->UpdateInformation();
	}
	IsInventoryOpend = true;
}

void APlayerHUD::CloseInventory()
{
	UInventoryPanel* Inventory = Cast<UInventoryPanel>(InventoryWidget);
	if (Inventory) 
	{
		Inventory->ClearInfoPanel();
	}
	InventoryWidget->RemoveFromViewport();
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
	IsInventoryOpend = false;
}

void APlayerHUD::AddItem(UItemInformation* ItemInfo)
{
}

void APlayerHUD::RemoveItem(int32 Row, int32 Column)
{
}

void APlayerHUD::SetSize(int32 RowsAmmount, int32 ColumnsAmmount)
{
	if (InventoryWidget)
	{
		UInventoryPanel* Inventory = Cast<UInventoryPanel>(InventoryWidget);
		if (Inventory)
		{
			Inventory->SetSize(AmmountOfRows, AmmountOfColumns);
		}
	}
}
