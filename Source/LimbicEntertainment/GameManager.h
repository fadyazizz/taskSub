// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <stdbool.h>

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Building.h"
#include "InGameUI.h"
#include "GameManager.generated.h"


UCLASS()
class LIMBICENTERTAINMENT_API AGameManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameManager();
	void spawn();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABuilding> toSpawn;
	ABuilding* spawnedBuildingObject;
	bool spawnedBuilding=false;
	AActor* selectedActor;
	float timer;
	
	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void onLeftMouseClick();
	void followCursor();
	//main pawn camera
	UPROPERTY(EditAnywhere)
	UCameraComponent* camera;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* cameraMesh;
UPROPERTY(EditAnywhere,Category="character settings")
	float movementSpeed;
	TSubclassOf<class  UInGameUI> hud;
void insertBuilding();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
