// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCubePickUp.h"

// Sets default values
AMyCubePickUp::AMyCubePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");

	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	
	if (MeshAsset.Object != nullptr) {

		CubeMesh->SetStaticMesh(MeshAsset.Object);

	}

	RootComponent = CubeMesh;

}

void AMyCubePickUp::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{

	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(ItemDataTable)
	{

		

	}

}

// Called when the game starts or when spawned
void AMyCubePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCubePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCubePickUp::PickUp_Implementation(AActor* LiftingActor) {

	

}
