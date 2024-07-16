// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Objects_P.h"
#include "G_Capsule_Health_Total.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AG_Capsule_Health_Total : public AInteractable_Objects_P
{
	GENERATED_BODY()

public:
	AG_Capsule_Health_Total();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
