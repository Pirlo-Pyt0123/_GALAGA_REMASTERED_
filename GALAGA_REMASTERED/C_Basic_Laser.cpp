#include "C_Basic_Laser.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AC_Basic_Laser::AC_Basic_Laser()
{

    // Creando la malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/Mehes/CajaArmas/Bomb550.Bomb550'"));
    if (ProjectileMeshAsset.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
        ProjectileMesh->SetVisibility(false);
    }

    ProjectileMesh->OnComponentHit.AddDynamic(this, &AC_Basic_Laser::OnHit);

    // Determinando la velocidad de la bala
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
    ProjectileMovement->UpdatedComponent = ProjectileMesh;
    ProjectileMovement->InitialSpeed = 80000.f;
    ProjectileMovement->MaxSpeed = 80000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->ProjectileGravityScale = 0.f; // Sin gravedad

    // Tiempo de vida de la bala
    InitialLifeSpan = 15.0f;

    // Configurando el campo de colisión del proyectil
    ProjectileCollision->SetBoxExtent(FVector(450.0f, 450.0f, 450.0f));
    ProjectileCollision->AttachToComponent(ProjectileMesh, FAttachmentTransformRules::KeepRelativeTransform);

    // Crear e inicializar el componente Niagara
    NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    NiagaraComponent->SetupAttachment(ProjectileMesh);

    // Establecer el sistema Niagara
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("NiagaraSystem'/Game/3D_Lasers/Effects/NS_LaserHit_8.NS_LaserHit_8'"));
    if (NiagaraSystemAsset.Succeeded())
    {
        NiagaraComponent->SetAsset(NiagaraSystemAsset.Object);
    }
}

void AC_Basic_Laser::BeginPlay()
{
    Super::BeginPlay();
}

void AC_Basic_Laser::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AC_Basic_Laser::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Solo agregar impulso y destruir el proyectil si golpeamos algo con física
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        OtherComp->AddImpulseAtLocation(GetVelocity() * 15000.0f, GetActorLocation());
    }

    AGALAGA_REMASTEREDPawn* Player = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);
    if (Player)
    {
        Player->Damage_received(200.f);
    }


    this->Destroy();
}
