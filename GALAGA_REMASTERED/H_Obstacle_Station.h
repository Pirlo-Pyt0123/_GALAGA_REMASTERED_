// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Objects_P.h"
#include "H_Obstacle_Station.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AH_Obstacle_Station : public AInteractable_Objects_P
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	AH_Obstacle_Station();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	virtual void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;


};
