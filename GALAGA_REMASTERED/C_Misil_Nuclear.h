#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "C_Misil_Nuclear.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AC_Misil_Nuclear : public AC_Projectile
{
    GENERATED_BODY()

public:
    AC_Misil_Nuclear();

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    // Componente de movimiento del proyectil
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
    UProjectileMovementComponent* ProjectileMovement;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
    class UNiagaraComponent* NiagaraComponent;
};
