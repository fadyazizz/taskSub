// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/Button.h"
#include "GameManager.h"

#include "InGameUI.h"




void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	UInGameUI::isBuilding=false;
	addLargeBuilding->OnClicked.AddUniqueDynamic(this,&UInGameUI::addSmallBuilding);
	
}
void UInGameUI::addSmallBuilding()
{
	isBuilding=true;
	UE_LOG(LogTemp, Warning, TEXT("pressed add building"));
}

