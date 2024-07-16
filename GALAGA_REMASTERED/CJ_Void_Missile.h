// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "CJ_Void_Missile.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_REMASTERED_API ACJ_Void_Missile : public AC_Projectile
{
	GENERATED_BODY()

public:
	ACJ_Void_Missile();

	//funcion de colision
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//====================================================================================================
	//componente de movimiento del proyectil
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;

	//====================================================================================================
	//getter de la malla del proyectil
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }

	//getter del componente de movimiento del proyectil
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	//funcion para actualizar la direccion del proyectil
	void UpdateProjectileDirection(const FVector& NewDirection);


private:
	//direccion actual del proyectil
	FVector CurrentDirection;
	
};
