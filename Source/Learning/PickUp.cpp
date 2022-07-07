// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

UItemInformation* APickUp::GetItemInformation()
{
	return nullptr;
}

void APickUp::PickUp_Implementation(AActor* LiftingActor)
{

	UE_LOG(LogTemp, Warning, TEXT("The implementation of PickUp shouldn't be called from APickUp"));

}

void APickUp::TakeInfoFromItem(APickUp* ItemToTakeInfoFrom)
{

	UE_LOG(LogTemp, Warning, TEXT("The implementation of TakeInfoFromItem shouldn't be called from APickUp"));

}

