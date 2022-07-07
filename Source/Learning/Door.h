// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UseInterface.h"
#include "Door.generated.h"

UCLASS()
class LEARNING_API ADoor : public AActor, public IUseInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
		bool IsUseble;
	
	UPROPERTY()
	float OpenValue;

	FRotator OpenPosishon;
	FRotator ClosedPosition;

	bool IsOpend;

	UPROPERTY()
		UStaticMeshComponent* ThisDoor;

	UFUNCTION()
		virtual bool CanBeUsed_Implementation() override;

	UFUNCTION()
		virtual void Use_Implementation(FVector UserVector) override;

};
