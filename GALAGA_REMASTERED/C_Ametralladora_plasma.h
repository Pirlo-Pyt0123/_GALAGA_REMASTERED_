#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "C_Ametralladora_plasma.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AC_Ametralladora_plasma : public AC_Projectile
{
    GENERATED_BODY()

public:
    AC_Ametralladora_plasma();

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
