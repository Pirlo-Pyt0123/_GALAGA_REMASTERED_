// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "CJ_Aurora_Dagger.generated.h"

/**
 * 
 */
UCLASS()
class GALAGA_REMASTERED_API ACJ_Aurora_Dagger : public AC_Projectile
{
	GENERATED_BODY()


public:

	ACJ_Aurora_Dagger();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//componente de movimiento del proyectil
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;


	/** Returns ProjectileMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	

	virtual void Tick(float DeltaTime) override;	

protected:
	virtual void BeginPlay() override;

private:
	FVector CurrentDirection;
	
};
