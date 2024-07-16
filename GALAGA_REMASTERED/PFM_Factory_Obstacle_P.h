// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFM_Object_Interact_P.h"
#include "PFM_Factory_Obstacle_P.generated.h"


UCLASS()
class GALAGA_REMASTERED_API APFM_Factory_Obstacle_P : public APFM_Object_Interact_P
{
	GENERATED_BODY()


public:
    // Sets default values for this actor's properties
    APFM_Factory_Obstacle_P();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Factory")
    AInteractable_Objects_P* Create_Interactable_Object(FString Identificador);

private:
    TArray<FVector> SpawnedLocations;
};