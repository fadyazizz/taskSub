// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class LIMBICENTERTAINMENT_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();
	UPROPERTY(EditAnywhere)
	UMaterial* deSelectedMaterial;
	UPROPERTY(EditAnywhere)
	UMaterial* selectedMaterial;
	float timer=0;
	bool startAnimation=false;
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* buildingMesh;
	

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
