#include "CJ_Astro_Bean.h"
#include "Z_Enemy_Ship_P.h"
#include "X_Master_Ship_P.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Engine.h"

ACJ_Astro_Bean::ACJ_Astro_Bean()
{
    PrimaryActorTick.bCanEverTick = true;

    // Crear y configurar la malla del proyectil
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Laser_Bean.Laser_Bean'"));
    if (MeshAsset.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(MeshAsset.Object);

        // Escala de la malla
        ProjectileMesh->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
    }

    // Invisibilidad de la malla
    ProjectileMesh->SetVisibility(false);
	
    ProjectileMesh->OnComponentHit.AddDynamic(this, &ACJ_Astro_Bean::OnHit);

    // Configurar el componente de movimiento del proyectil
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
    ProjectileMovement->InitialSpeed = 150000.f;
    ProjectileMovement->MaxSpeed = 150000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.f; // Sin gravedad

    // Duración de vida del proyectil
    InitialLifeSpan = 5.0f;

    // Crear el componente de partículas y adjuntarlo a la malla del proyectil
    Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileParticles"));
    Proye->SetupAttachment(ProjectileMesh);

    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/P_Projectile_Trail02_Red.P_Projectile_Trail02_Red'"));
    if (ParticleAsset.Succeeded())
    {
        Proye->SetTemplate(ParticleAsset.Object);
        Proye->bAutoActivate = true;
        // Rotar hacia atrás del mesh
        Proye->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		// Escala de la partícula
		Proye->SetWorldScale3D(FVector(5.5f, 5.5f, 5.5f));
    }

    // Configurando el campo de colisión de este actor
    ProjectileCollision->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
    ProjectileCollision->AttachToComponent(ProjectileMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

void ACJ_Astro_Bean::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Destroy();

    //=======================================================
    //Daño a la nave enemiga
    AZ_Enemy_Ship_P* Nave_Padre = Cast<AZ_Enemy_Ship_P>(OtherActor);

    if (Nave_Padre)
    {
        Nave_Padre->Recibir_Danio(70);

    }


    //=======================================================
    //Daño la master ship
    AX_Master_Ship_P* Nave_Padre_2 = Cast<AX_Master_Ship_P>(OtherActor);

    if (Nave_Padre_2)
    {

        Nave_Padre_2->Recibir_Danio(100);

    }
}


void ACJ_Astro_Bean::UpdateProjectileDirection(const FVector& NewDirection)
{
    CurrentDirection = NewDirection.GetSafeNormal();
    ProjectileMovement->Velocity = CurrentDirection * ProjectileMovement->InitialSpeed;

}

void ACJ_Astro_Bean::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACJ_Astro_Bean::BeginPlay()
{
	Super::BeginPlay();
}
