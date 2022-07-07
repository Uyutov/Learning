// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UInventoryComponent;
class APlayerHUD;
class UInventoryPanel;

UENUM()
enum class EInteractEnum : uint8
{

	NONE = 0 UMETA(ScriptName = "Value if nothing in the way"),

	PICKUP = 1 UMETA(ScriptName = "Value for pickingup items"),

	USE = 2 UMETA(ScriptName = "value for using items")

};

UCLASS()
class LEARNING_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	

	void MoveForward(float amount);
	void MoveRight(float amount);
	void LookUp(float amount);
	void LookRight(float amount);
	void StopLooking(float amount);

	AActor* CheckForVievingActor();

	void Use(AActor* UsedItem);
	void PickUp(AActor* MyPickUp);
	void Interact();
	
	void OpenInventory();
	void SetInventorySizes();

	EInteractEnum CorrentInteraction;
	
	
	UPROPERTY()
		UInventoryComponent* Inventory;

public:	

	UFUNCTION()
	bool RemoveItem(UItemInformation* RemovedItem);

	UPROPERTY(EditAnywhere)
		int32 InventoryRows;
	UPROPERTY(EditAnywhere)
		int32 InventoryColumns;

	FVector2D LastInput;

	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

};
