// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "CJ_Nova_Pulse.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_REMASTERED_API ACJ_Nova_Pulse : public AC_Projectile
{
	GENERATED_BODY()
public:

	//constructor
	ACJ_Nova_Pulse();

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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
