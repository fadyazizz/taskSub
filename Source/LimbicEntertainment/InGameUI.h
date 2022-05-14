// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class LIMBICENTERTAINMENT_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
public:
	static inline   bool isBuilding=false;
	UPROPERTY(meta= (BindWidget))
	class  UButton* addLargeBuilding;
protected:
	UFUNCTION(BlueprintCallable)
	void addSmallBuilding();
	//UPROPERTY(meta= (BindWidget))
	//class UTextBlock* buildingType;
	
	void NativeConstruct() override;
	

	
};
