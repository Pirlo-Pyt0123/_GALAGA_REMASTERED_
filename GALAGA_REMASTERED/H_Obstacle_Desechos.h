// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Objects_P.h"
#include "H_Obstacle_Desechos.generated.h"




UCLASS()
class GALAGA_REMASTERED_API AH_Obstacle_Desechos : public AInteractable_Objects_P
{
	GENERATED_BODY()

public:

	AH_Obstacle_Desechos();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	void MoveObstacle(float DeltaTime);

	void NotifyActorBeginOverlap(AActor* OtherActor) override;	
	
	
};
