// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "C_Basic_Laser.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AC_Basic_Laser : public AC_Projectile
{
	GENERATED_BODY()

public:
	AC_Basic_Laser();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//componente de movimiento del proyectil
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	class UNiagaraComponent* NiagaraComponent;


protected:

	virtual void BeginPlay() override;
	
public:

	virtual void Tick(float DeltaTime) override;


};
