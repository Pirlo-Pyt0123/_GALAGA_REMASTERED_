// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PS_ChangeWeapon.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "PS_Electric_Ray.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APS_Electric_Ray : public AActor, public IPS_ChangeWeapon
{
	GENERATED_BODY()
	

public:

	APS_Electric_Ray();

	virtual void Tick(float DeltaTime) override;

	void ShotFire(FVector LocationPlayer, bool WeaponPower);

	void SetPlayerPawn(AGALAGA_REMASTEREDPawn* NewPlayerPawn);

protected:
	virtual void BeginPlay() override;

private:
	AGALAGA_REMASTEREDPawn* myPlayerPawn;

};