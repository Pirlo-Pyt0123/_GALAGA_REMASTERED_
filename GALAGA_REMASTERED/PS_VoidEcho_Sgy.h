// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PS_ChangeWeapon.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "PS_VoidEcho_Sgy.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APS_VoidEcho_Sgy : public AActor, public IPS_ChangeWeapon
{
	GENERATED_BODY()

public:

	APS_VoidEcho_Sgy();

	virtual void Tick(float DeltaTime) override;

	void ShotFire(FVector LocationPlayer, bool WeaponPower);

	void SetPlayerPawn(AGALAGA_REMASTEREDPawn* NewPlayerPawn);

protected:
	virtual void BeginPlay() override;

private:
	AGALAGA_REMASTEREDPawn* myPlayerPawn;

};