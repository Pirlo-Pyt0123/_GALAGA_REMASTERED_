// Fill out your copyright notice in the Description page of Project Settings.


#include "CJ_Nova_Pulse.h"
#include "Z_Enemy_Ship_P.h"
#include "X_Master_Ship_P.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Engine.h"

ACJ_Nova_Pulse::ACJ_Nova_Pulse()
{
    PrimaryActorTick.bCanEverTick = true;
    // Creando la malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/Space_Creator/Star_Creator/Star_Creator_Original/Meshes/Sphere_2_Plane.Sphere_2_Plane'"));
    if (ProjectileMeshAsset.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
        // Ajustar la rotación de la malla sin afectar el movimiento
        ProjectileMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

        // Escala de la malla
        ProjectileMesh->SetWorldScale3D(FVector(5.5f, 5.5f, 5.5f));
    }
    //=======================================================
    //Habilitar visibilidad de la malla
    ProjectileMesh->SetVisibility(true);

    //=======================================================
    //Configurar el componente de movimiento del proyectil
    ProjectileMesh->OnComponentHit.AddDynamic(this, &ACJ_Nova_Pulse::OnHit);
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
    ProjectileMovement->UpdatedComponent = ProjectileMesh;

    //Determinando la velocidad inicial de la bala
    ProjectileMovement->InitialSpeed = 150000.f; // Ajusta según tus necesidades

    //Determinando la velocidad máxima de la bala
    ProjectileMovement->MaxSpeed = 150000.f; // Ajusta según tus necesidades

    //Determinando si la rotación sigue la velocidad
    ProjectileMovement->bRotationFollowsVelocity = true;

    //Determinando si la bala rebota
    ProjectileMovement->bShouldBounce = false;

    //Habilitar la gravedad para el movimiento parabólico
    ProjectileMovement->ProjectileGravityScale = 0.f; // Ajusta según tus necesidades

    //muere después de 3 segundos por defecto
    InitialLifeSpan = 5.0f;

    // Configurando el campo de colisión de este actor
    ProjectileCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollision"));
    ProjectileCollision->SetBoxExtent(FVector(250.0f, 250.0f, 250.0f));
    ProjectileCollision->SetupAttachment(ProjectileMesh);

    // Crear el componente de partículas y adjuntarlo a la malla del proyectil
    Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
    Proye->SetupAttachment(ProjectileMesh);
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/P_Projectile_Orb06_Purple.P_Projectile_Orb06_Purple'"));
    if (ParticleAsset2.Succeeded())
    {
        Proye->SetTemplate(ParticleAsset2.Object);
        Proye->bAutoActivate = false;
        // Girar hacia adelante

		Proye->SetWorldScale3D(FVector(18.5f, 18.5f, 18.5f));
    }
	
}

void ACJ_Nova_Pulse::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();


	//=======================================================
	//Daño a la nave enemiga
	AZ_Enemy_Ship_P* Nave_Padre = Cast<AZ_Enemy_Ship_P>(OtherActor);

	if (Nave_Padre)
	{
		Nave_Padre->Recibir_Danio(100);

	}


	//=======================================================
	//Daño la master ship
	AX_Master_Ship_P* Nave_Padre_2 = Cast<AX_Master_Ship_P>(OtherActor);

	if (Nave_Padre_2)
	{

		Nave_Padre_2->Recibir_Danio(300);

	}
}

void ACJ_Nova_Pulse::UpdateProjectileDirection(const FVector& NewDirection)
{
    // Actualizar la dirección del proyectil
    CurrentDirection = NewDirection.GetSafeNormal();
    ProjectileMovement->Velocity = CurrentDirection * ProjectileMovement->InitialSpeed;

    // Actualizar la rotación del proyectil basada en la dirección
    FRotator NewRotation = CurrentDirection.Rotation();
    NewRotation.Yaw += 90.0f; // Ajustar según necesidades específicas

}

void ACJ_Nova_Pulse::BeginPlay()
{
    Super::BeginPlay();


    // Ajustar la dirección inicial hacia adelante con un ángulo hacia arriba
    FVector InitialDirection = FVector(1.f, 0.f, 0.5f); // Adelante y un poco hacia arriba
    UpdateProjectileDirection(InitialDirection);
}