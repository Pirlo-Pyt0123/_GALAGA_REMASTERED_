// Fill out your copyright notice in the Description page of Project Settings.


#include "CJ_Galactic_Ray.h"
#include "Z_Enemy_Ship_P.h"
#include "X_Master_Ship_P.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Engine.h"

ACJ_Galactic_Ray::ACJ_Galactic_Ray()
{
	PrimaryActorTick.bCanEverTick = true;
    // Creando la malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/assetsGENIE/ARROW/ARROW.ARROW'"));
    if (ProjectileMeshAsset.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
        ProjectileMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
        // Escala de la malla
        ProjectileMesh->SetWorldScale3D(FVector(4.5f, 4.5f, 10.5f));

		ProjectileMesh->SetVisibility(false);
    }

    ProjectileMesh->OnComponentHit.AddDynamic(this, &ACJ_Galactic_Ray::OnHit);

 

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
    ProjectileMovement->UpdatedComponent = ProjectileMesh;
    ProjectileMovement->InitialSpeed = 150000.f;
    ProjectileMovement->MaxSpeed = 150000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

    // Die after 3 seconds by default
    InitialLifeSpan = 5.0f;

    // Configurando el campo de colisión de este actor
    ProjectileCollision->SetBoxExtent(FVector(250.0f, 250.0f, 250.0f));
    ProjectileCollision->AttachToComponent(ProjectileMesh, FAttachmentTransformRules::KeepRelativeTransform);

    Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
    Proye->SetupAttachment(ProjectileMesh);
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/P_Projectile_Firefrost01_Orange.P_Projectile_Firefrost01_Orange'"));
    if (ParticleAsset2.Succeeded())
    {
        Proye->SetTemplate(ParticleAsset2.Object);
        Proye->bAutoActivate = true;
		Proye->SetWorldScale3D(FVector(7.5f, 7.5f, 7.5f));
    }
}

void ACJ_Galactic_Ray::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Destroy();

    AZ_Enemy_Ship_P* Nave_Padre = Cast<AZ_Enemy_Ship_P>(OtherActor);

    if (Nave_Padre)
    {
        Nave_Padre->Recibir_Danio(200);
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ship Colision [Enemy]"));
    }



    AX_Master_Ship_P* Nave_Padre_2 = Cast<AX_Master_Ship_P>(OtherActor);

    if (Nave_Padre_2)
    {
        Nave_Padre_2->Recibir_Danio(300);
    }
}

void ACJ_Galactic_Ray::UpdateProjectileDirection(const FVector& NewDirection)
{
    //=======================================================
    //Actualizar la dirección del proyectil
    CurrentDirection = NewDirection.GetSafeNormal();
    ProjectileMovement->Velocity = CurrentDirection * ProjectileMovement->InitialSpeed;

    // Actualizar la rotación del proyectil basada en la dirección
    FRotator NewRotation = CurrentDirection.Rotation();
    NewRotation.Yaw += 90.0f; // Ajustar según necesidades específicas

}


