#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "C_Projectile.generated.h"
UCLASS()
class GALAGA_REMASTERED_API AC_Projectile : public AActor
{
    GENERATED_BODY()

public:
	// Constructor
	AC_Projectile();

	// propiedades de proyectil
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	class UStaticMeshComponent* ProjectileMesh; // malla
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	class UBoxComponent* ProjectileCollision; // colision

	UPROPERTY(EditAnywhere, Category = "Componentes")
	class UParticleSystemComponent* Proye;


	

};
