// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Objects_P.h"
#include "H_Obstacle_Cometa.generated.h"



UCLASS()
class GALAGA_REMASTERED_API AH_Obstacle_Cometa : public AInteractable_Objects_P
{
	GENERATED_BODY()


public:

	AH_Obstacle_Cometa();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
