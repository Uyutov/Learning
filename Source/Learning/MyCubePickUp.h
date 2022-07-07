// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpInterface.h"
#include "Components/Image.h"
#include "ItemLibrary.h"
#include "MyCubePickUp.generated.h"

UCLASS()
class LEARNING_API AMyCubePickUp : public AActor, public IPickUpInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCubePickUp();

	UPROPERTY()
		UStaticMeshComponent* CubeMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Item information")
		UDataTable* ItemDataTable;
	UPROPERTY(EditAnywhere, Category = "Item information")
		EItemType TypeOfItem;

	UFUNCTION()
		virtual void PickUp_Implementation(AActor* LiftingActor) override;

};
