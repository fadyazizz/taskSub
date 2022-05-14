// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	startAnimation=false;
	timer=0;
	PrimaryActorTick.bCanEverTick = true;
	
	buildingMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("buildingMesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Engine/BasicShapes/Cube.Cube"));
	buildingMesh->SetStaticMesh(MeshObj.Object);
	//this->SetActorEnableCollision(true);
	//buildingMesh->SetSimulatePhysics(true);
	
	selectedMaterial=CreateDefaultSubobject<UMaterial>(TEXT("Selected material"));
	deSelectedMaterial=CreateDefaultSubobject<UMaterial>(TEXT("deselected material"));
	
	buildingMesh->SetMaterial(0,selectedMaterial);

}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timer+=DeltaTime;
	if(startAnimation)
	{
		if(timer<=2)
		{
			FRotator NewRotation = FRotator(0, 10, 0);
	
			FQuat QuatRotation = FQuat(NewRotation);
	
			AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
		}else
		{
			startAnimation=false;
		}
	}

}

