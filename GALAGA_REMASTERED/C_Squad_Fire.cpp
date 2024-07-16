// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Squad_Fire.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AC_Squad_Fire::AC_Squad_Fire()
{
    PrimaryActorTick.bCanEverTick = true;

    // Creando la malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/VFXSeries1/Meshes/Projectile/SM_Missile.SM_Missile'"));
    if (ProjectileMeshAsset.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);

        ProjectileMesh->SetVisibility(false);
    }

    ProjectileMesh->OnComponentHit.AddDynamic(this, &AC_Squad_Fire::OnHit);

    // Determinando la velocidad del proyectil
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
    ProjectileMovement->UpdatedComponent = ProjectileMesh;
    ProjectileMovement->InitialSpeed = 60000.f;
    ProjectileMovement->MaxSpeed = 60000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.f; // Sin gravedad

    // Tiempo de vida del proyectil
    InitialLifeSpan = 15.0f;

    // Configurando el campo de colisión del proyectil
    ProjectileCollision->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f)); // Incrementa el tamaño de la colisión
    ProjectileCollision->SetupAttachment(ProjectileMesh);

    // Creando el componente de Niagara
    NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    NiagaraComponent->SetupAttachment(ProjectileMesh);
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/NS_EnergySphere.NS_EnergySphere'"));
    if (NiagaraSystemAsset.Succeeded())
    {
        NiagaraComponent->SetAsset(NiagaraSystemAsset.Object);
        NiagaraComponent->bAutoActivate = true;
        NiagaraComponent->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
        // Girar hacia adelante
        NiagaraComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
    }
}

void AC_Squad_Fire::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Solo proceder si el misil golpea algo
    if (OtherActor && OtherActor != this && OtherComp)
    {
        // Verificar si el actor golpeado es la nave del jugador
        AGALAGA_REMASTEREDPawn* Nave_Padre = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);
        if (Nave_Padre)
        {
            // Solo agregar impulso y destruir el proyectil si golpeamos un componente con física habilitada de la nave del jugador
            if (OtherComp->IsSimulatingPhysics())
            {
                OtherComp->AddImpulseAtLocation(GetVelocity() * 10000.0f, GetActorLocation());
            }
            Nave_Padre->Damage_received(350.f); // Daño a la nave del jugador
            // Destruir el misil después de la colisión
            Destroy();
        }
    }
}
