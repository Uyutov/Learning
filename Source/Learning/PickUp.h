// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpInterface.h"
#include "ItemLibrary.h"
#include "PickUp.generated.h"

UCLASS()
class LEARNING_API APickUp : public AActor, public IPickUpInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

public:	

	UPROPERTY()
	UStaticMeshComponent* Mesh;

	UFUNCTION()
		virtual UItemInformation* GetItemInformation();
	UFUNCTION()
		virtual void PickUp_Implementation(AActor* LiftingActor) override;
	UFUNCTION()
		virtual void TakeInfoFromItem(APickUp* ItemToTakeInfoFrom);	

};
