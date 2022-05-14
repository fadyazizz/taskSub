// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "Building.h"
#include "InGameUI.h"
#include "GameManager.h"



// Sets default values
AGameManager::AGameManager()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//create components
	camera=CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	cameraMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("camera nd"));
	//cameraMesh->SetStaticMesh(TEXT("Engine/BasicShape/Cube"));
	//set up the Camera
	camera->FieldOfView=120.0f;
	camera->SetupAttachment(cameraMesh);
	camera->AddRelativeLocation(FVector(-100.0f,0.0f,50.0f));
	
	

}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	
	if(UInGameUI::isBuilding)
	{
		//UE_LOG(LogTemp, Warning, TEXT("state has changed"));
		
		
		if(!spawnedBuilding)
		{
			spawn();
			spawnedBuilding=true;
			
		}
		 followCursor();
	}
	

}
void AGameManager::followCursor()
{
	float mouseX, mouseY;
	APlayerController* controller = Cast<APlayerController>(GetController());
	controller->GetMousePosition(mouseX, mouseY);

	FHitResult Hit(ForceInit);
	

	FVector2D* screenPos = new FVector2D(mouseX, mouseY);
	controller->GetHitResultAtScreenPosition(*screenPos, ECC_Visibility, false, Hit);
	Hit.Location.Z=100;
	
	
	if(Hit.GetComponent()!=nullptr)
	{
		
		FString name=Hit.GetComponent()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s"),*name);
		if(name=="buildingMesh")
		{
			if(spawnedBuilding)
			{
				spawnedBuildingObject->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0,spawnedBuildingObject->deSelectedMaterial);
			}
		}else
		{
			if(spawnedBuilding)
			{
				
				spawnedBuildingObject->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0,spawnedBuildingObject->selectedMaterial);
			}	
		}
	}
	
	spawnedBuildingObject->SetActorLocation(Hit.Location);
}

void AGameManager::spawn()
{
	if(toSpawn)
	{
		UWorld* world=GetWorld();
		if(world)
		{
			FActorSpawnParameters spawnParameters;
			spawnParameters.Owner=this;
			FRotator rotator;
			FVector spawnLocation=FVector(0.0f);
			spawnLocation.X=840;
			spawnLocation.Z=100;
			spawnedBuildingObject=world->SpawnActor<ABuilding>(toSpawn,spawnLocation,rotator,spawnParameters);
			spawnedBuildingObject->FindComponentByClass<UStaticMeshComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
		}
	}
}

void AGameManager::insertBuilding()
{
	float mouseX, mouseY;
	APlayerController* controller = Cast<APlayerController>(GetController());
	controller->GetMousePosition(mouseX, mouseY);
	FVector2D* screenPos = new FVector2D(mouseX, mouseY);
	
	
}
void AGameManager::onLeftMouseClick()
{
	float mouseX, mouseY;
	APlayerController* controller = Cast<APlayerController>(GetController());
	controller->GetMousePosition(mouseX, mouseY);

	FHitResult Hit(ForceInit);
	

	FVector2D* screenPos = new FVector2D(mouseX, mouseY);
	controller->GetHitResultAtScreenPosition(*screenPos, ECC_Visibility, false, Hit);
	
	if(spawnedBuilding)
	{
		if(Hit.GetComponent()!=nullptr)
		{
			FString name=Hit.GetComponent()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("%s"),*name);
			if(name!="buildingMesh")
			{
				spawnedBuilding=false;
				UInGameUI::isBuilding=false;
				spawnedBuildingObject->FindComponentByClass<UStaticMeshComponent>()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				spawnedBuildingObject->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
			}
		}
	}else
	{
		if(Hit.GetComponent()!=nullptr)
		{
			FString name=Hit.GetComponent()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("%s"),*name);
			if(name=="buildingMesh")
			{
				if(selectedActor!=nullptr)
				{
					selectedActor->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0,spawnedBuildingObject->selectedMaterial);
				}
				selectedActor=Hit.GetActor();
				selectedActor->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0,spawnedBuildingObject->deSelectedMaterial);
				static_cast<ABuilding*>(selectedActor)->timer=0;
				static_cast<ABuilding*>(selectedActor)->startAnimation=true;
				
			}else
			{
				if(selectedActor!=nullptr)
				{
					selectedActor->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0,spawnedBuildingObject->selectedMaterial);
					selectedActor=nullptr;
				}
			}
		}	
	}

}


// Called to bind functionality to input
void AGameManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("mouse",IE_Pressed,this,&AGameManager::onLeftMouseClick);
	

}

