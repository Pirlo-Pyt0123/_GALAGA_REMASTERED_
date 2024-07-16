// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PS_ChangeWeapon.h"
#include "PS_TypeOfWeapon.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APS_TypeOfWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	APS_TypeOfWeapon();

	virtual void Tick(float DeltaTime) override;

private:
	class IPS_ChangeWeapon* ChangeWeapon;

public:
	//====================================================================================================
	//Metodo que usaremos para cambiar el tipo de disparo
	void AlterShootingType(AActor* MyChanceWeapon);

	//====================================================================================================
	//Metodo arma que se usara

	void UseWeapon(FVector _LocationPlayer, bool Activate);

protected:
	virtual void BeginPlay() override;

};
