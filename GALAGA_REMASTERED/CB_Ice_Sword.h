// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "CB_Ice_Sword.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_REMASTERED_API ACB_Ice_Sword : public AC_Projectile
{
	GENERATED_BODY()

public:

	ACB_Ice_Sword();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//componente de movimiento del proyectil
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	class UNiagaraComponent* NiagaraComponent;

	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing")
	float HomingAccelerationMagnitude;

	void SetHomingTarget(AActor* Target);

public:

	virtual void Tick(float DeltaTime) override;

	
};
