// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "PickUpInterface.h"
#include "ArmorItem.h"
#include "ConsumableItem.h"
#include "CommonItem.h"
#include "InventoryPanel.h"
#include "InventoryComponent.h"
#include "PlayerHUD.h"
#include "UseInterface.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LastInput = FVector2D::ZeroVector;
	CorrentInteraction = EInteractEnum::NONE;
	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();	
	Inventory = Cast<UInventoryComponent>(this->GetComponentByClass(UInventoryComponent::StaticClass()));
	SetInventorySizes();
}

AActor* AMyCharacter::CheckForVievingActor() {

	APlayerController* MyController = Cast<APlayerController>(Controller);
	APlayerCameraManager* MyCamera = MyController->PlayerCameraManager;

	FHitResult ObjectHited;
	FVector StartLocation = MyCamera->GetCameraLocation();
	FVector EndLocation = MyCamera->GetCameraLocation() + (MyCamera->GetActorForwardVector()* 300);

	GetWorld()->SweepSingleByObjectType(ObjectHited, StartLocation, EndLocation, FQuat::Identity,
		FCollisionObjectQueryParams(FCollisionObjectQueryParams::AllObjects), 
		FCollisionShape::MakeSphere(25), FCollisionQueryParams(FName("Interaction"), true, this));

	if (ObjectHited.Actor != nullptr) {
		
		if (ObjectHited.Actor->GetClass()->ImplementsInterface(UPickUpInterface::StaticClass())) {

			CorrentInteraction = EInteractEnum::PICKUP;
			return ObjectHited.Actor.Get();

		}

		if (ObjectHited.Actor->GetClass()->ImplementsInterface(UUseInterface::StaticClass())) {

			CorrentInteraction = EInteractEnum::USE;
			return ObjectHited.Actor.Get();

		}

	}

	CorrentInteraction = EInteractEnum::NONE;
	return nullptr;
	

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (LastInput.Size() > 1) {

		LastInput /= LastInput.Size();

	}

	AddMovementInput(GetActorForwardVector(), LastInput.X);
	AddMovementInput(GetActorRightVector(), LastInput.Y);

	LastInput = FVector2D::ZeroVector;

	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString("X: " + FString::SanitizeFloat(GetActorRotation().Vector().X) + "    " + "Y: " + FString::SanitizeFloat(GetActorRotation().Vector().Y)));

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AMyCharacter::LookRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Interact);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AMyCharacter::OpenInventory);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);

}

void AMyCharacter::MoveForward(float amount) {

	LastInput.X += amount;

}

void AMyCharacter::MoveRight(float amount) {

	LastInput.Y += amount;

}

void AMyCharacter::LookUp(float amount) {

	AddControllerPitchInput(-amount);

}

void AMyCharacter::LookRight(float amount) {

	AddControllerYawInput(amount);
	AddActorLocalRotation(FQuat(GetActorUpVector(), amount / PI));

}

void AMyCharacter::StopLooking(float amount)
{

}

void AMyCharacter::Jump() {

	//Super::Jump();

}

void AMyCharacter::Interact() {

	AActor* VievingActor = CheckForVievingActor();

	switch (CorrentInteraction) 
	{
		
		case EInteractEnum::PICKUP:
			{
				
				PickUp(VievingActor);
				break;

			}

		case EInteractEnum::USE:
			{
					
				Use(VievingActor);
				break;

			}

		case EInteractEnum::NONE:
			{

				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, TEXT("There nothhing to do?!?!?!"));
				break;

			}
	}

}

void AMyCharacter::PickUp(AActor* MyPickUp) {

	IPickUpInterface::Execute_PickUp(MyPickUp,this);

}

bool AMyCharacter::RemoveItem(UItemInformation* RemovedItem)
{
	if (RemovedItem)
	{
		FVector ScaledVector = this->GetActorLocation() + this->GetActorForwardVector()*100;
		
		const FVector ItemVector = ScaledVector;
		const FRotator ItemRotation = this->GetActorRotation();
		UArmorInfo* ArmorInfo = Cast<UArmorInfo>(RemovedItem);
		if (ArmorInfo)
		{
			UE_LOG(LogTemp, Warning, TEXT("Info exists"));
			AArmorItem* Armor = GetWorld()->SpawnActor<AArmorItem>(AArmorItem::StaticClass(), ItemVector, ItemRotation);
			Armor->SetPropertys(ArmorInfo);
			if (this->Inventory->Remove(ArmorInfo))
			{
				UE_LOG(LogTemp, Warning, TEXT("Item removed succsesfuly"));
				return true;
			}
		}
		UConsumablesInfo* ConsumablesInfo = Cast<UConsumablesInfo>(RemovedItem);
		if (ConsumablesInfo)
		{
			AConsumableItem* Consumable = GetWorld()->SpawnActor<AConsumableItem>(ItemVector, ItemRotation);
			Consumable->SetPropertys(ConsumablesInfo);
			if (this->Inventory->Remove(ConsumablesInfo))
			{
				return true;
			}
		}
		UItemInformation* ItemInfo = Cast<UItemInformation>(RemovedItem);
		if (ItemInfo)
		{
			ACommonItem* CommonItem = GetWorld()->SpawnActor<ACommonItem>(ItemVector, ItemRotation);
			CommonItem->SetPropertys(ItemInfo);
			if (this->Inventory->Remove(ItemInfo))
			{
				UE_LOG(LogTemp, Warning, TEXT("Item deleated"));
				return true;
			}
		}
	}
	return false;
}

void AMyCharacter::Use(AActor* UsedItem) {

	if (IUseInterface::Execute_CanBeUsed(UsedItem)) {
		
		APlayerController* MyController = Cast<APlayerController>(Controller);
		APlayerCameraManager* MyCamera = MyController->PlayerCameraManager;

		IUseInterface::Execute_Use(UsedItem, GetActorForwardVector());

	}

}


void AMyCharacter::OpenInventory() 
{

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
	if (PC) 
	{
		APlayerHUD* PlayerHUD = PC->GetHUD<APlayerHUD>();
		if (PlayerHUD)
		{
			PlayerHUD->UseInventory();
		}
	}
}

void AMyCharacter::SetInventorySizes()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		APlayerHUD* PlayerHUD = PC->GetHUD<APlayerHUD>();
		if (PlayerHUD)
		{
			PlayerHUD->SetSize(InventoryRows, InventoryColumns);
		}
	}
	if (Inventory) {
		Inventory->SetInventorySize(InventoryRows, InventoryColumns);
	}
}
