
#pragma once

#include "CoreMinimal.h"
#include "C_Projectile.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "CJ_Astro_Bean.generated.h"



UCLASS()
class GALAGA_REMASTERED_API ACJ_Astro_Bean : public AC_Projectile
{
    GENERATED_BODY()

public:

	ACJ_Astro_Bean();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//componente de movimiento del proyectil
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;


	/** Returns ProjectileMesh subobject **/
	FORCEINLINE UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	void UpdateProjectileDirection(const FVector& NewDirection);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


private:
	FVector CurrentDirection;



};
