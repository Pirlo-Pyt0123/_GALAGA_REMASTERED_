// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PS_ChangeWeapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPS_ChangeWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GALAGA_REMASTERED_API IPS_ChangeWeapon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void ShotFire(FVector LocationPlayer, bool WeaponPower) = 0;
};
