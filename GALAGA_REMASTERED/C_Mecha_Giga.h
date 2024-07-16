// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "C_Mecha_Giga.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AC_Mecha_Giga : public AC_Projectile
{
	GENERATED_BODY()


public:
	AC_Mecha_Giga();

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    // Componente de movimiento del proyectil
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
    UProjectileMovementComponent* ProjectileMovement;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
    class UNiagaraComponent* NiagaraComponent;
	
};
