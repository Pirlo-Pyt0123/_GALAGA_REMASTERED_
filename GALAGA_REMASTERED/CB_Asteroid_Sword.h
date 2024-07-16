// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "CB_Asteroid_Sword.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_REMASTERED_API ACB_Asteroid_Sword : public AC_Projectile
{
	GENERATED_BODY()

public:

	ACB_Asteroid_Sword();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//componente de movimiento del proyectil
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing")
	float HomingAccelerationMagnitude;

	void SetHomingTarget(AActor* Target);
	
	

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
