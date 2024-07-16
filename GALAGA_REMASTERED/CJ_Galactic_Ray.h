// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "CJ_Galactic_Ray.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_REMASTERED_API ACJ_Galactic_Ray : public AC_Projectile
{
	GENERATED_BODY()


public:
	ACJ_Galactic_Ray();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	//componente de movimiento del proyectil
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;

	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	void UpdateProjectileDirection(const FVector& NewDirection);


private:

	FVector CurrentDirection;
	
};
