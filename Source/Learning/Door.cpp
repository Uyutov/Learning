// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "math.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsUseble = true;
	IsOpend = false;

	OpenValue = 0.f;

	ThisDoor = CreateDefaultSubobject<UStaticMeshComponent>("Door");

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Door.SM_Door'"));

	if (MeshAsset.Object != nullptr) {

		ThisDoor->SetStaticMesh(MeshAsset.Object);

	}

	RootComponent = ThisDoor;

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	OpenPosishon = GetActorRotation();
	ClosedPosition = GetActorRotation();

}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsUseble) {

		if (IsOpend) {

			OpenValue += 0.05;
			SetActorRelativeRotation(FMath::Lerp(OpenPosishon, ClosedPosition, OpenValue));
			
		}
		else {

			OpenValue += 0.05;
			SetActorRelativeRotation(FMath::Lerp(ClosedPosition, OpenPosishon, OpenValue));

		}

	}
	

	if (OpenValue > 1) {

		OpenValue = 0;
		IsUseble = true;

		if (IsOpend == false) {

			IsOpend = true;
			

		}
		else {

			IsOpend = false;
			OpenPosishon = ClosedPosition;
			

		}
	}

}

bool ADoor::CanBeUsed_Implementation()
{

	return IsUseble;

}

void ADoor::Use_Implementation(FVector UserVector)
{
	
	if (!IsOpend) {
		
		IsUseble = false;
		float Angel = 110;

		if (UserVector.CosineAngle2D(GetActorForwardVector()) < 0) {

			OpenPosishon.Add(0, -Angel, 0);

		}
		else {

			OpenPosishon.Add(0, Angel, 0);

		}

	}
	else {

		IsUseble = false;

	}

}

