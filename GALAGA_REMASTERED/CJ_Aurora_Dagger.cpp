#include "CJ_Aurora_Dagger.h"
#include "Z_Enemy_Ship_P.h"
#include "X_Master_Ship_P.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACJ_Aurora_Dagger::ACJ_Aurora_Dagger()
{
    PrimaryActorTick.bCanEverTick = true;

    // Crear y configurar la malla del proyectil
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/assetsGENIE/DAGGER/DAGGER.DAGGER'"));
    if (MeshAsset.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(MeshAsset.Object);
        // Ajustar la rotación de la malla sin afectar el movimiento
        ProjectileMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

        // Escala de la malla
        ProjectileMesh->SetWorldScale3D(FVector(4.5f, 4.5f, 4.5f));
    }

    // Invisibilidad de la malla
    ProjectileMesh->SetVisibility(false);
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ACJ_Aurora_Dagger::OnHit);

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

    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/P_Projectile_Trail04_Orange.P_Projectile_Trail04_Orange'"));
    if (ParticleAsset.Succeeded())
    {
        Proye->SetTemplate(ParticleAsset.Object);
        Proye->bAutoActivate = true;
		Proye->SetWorldScale3D(FVector(7.5f, 7.5f, 7.5f));
    }

    // Configurar colisión
    ProjectileCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollision"));
	ProjectileCollision->SetBoxExtent(FVector(150.0f, 150.0f, 150.0f));
    ProjectileCollision->SetupAttachment(ProjectileMesh);
}

void ACJ_Aurora_Dagger::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
   

    Destroy();

    AZ_Enemy_Ship_P* Nave_Padre = Cast<AZ_Enemy_Ship_P>(OtherActor);

    if (Nave_Padre)
    {
        Nave_Padre->Recibir_Danio(100);

    }

    AX_Master_Ship_P* Nave_Padre_2 = Cast<AX_Master_Ship_P>(OtherActor);

    if (Nave_Padre_2)
    {
        Nave_Padre_2->Recibir_Danio(200);

    }


}



void ACJ_Aurora_Dagger::BeginPlay()
{
	Super::BeginPlay();
   
}



void ACJ_Aurora_Dagger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
