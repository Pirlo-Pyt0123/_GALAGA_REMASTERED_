


#include "C_Ametralladora_plasma.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Engine.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AC_Ametralladora_plasma::AC_Ametralladora_plasma()
{
    PrimaryActorTick.bCanEverTick = true;


    // Creando la malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/Mehes/CajaArmas/Bomb550.Bomb550'"));
    if (ProjectileMeshAsset.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
        ProjectileMesh->SetVisibility(false);
    }

    ProjectileMesh->OnComponentHit.AddDynamic(this, &AC_Ametralladora_plasma::OnHit);

    // Determinando la velocidad de la bala
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
    ProjectileMovement->UpdatedComponent = ProjectileMesh;
    ProjectileMovement->InitialSpeed = 60000.f;
    ProjectileMovement->MaxSpeed = 60000.f;
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
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAsset(TEXT("NiagaraSystem'/Game/3D_Lasers/Effects/NS_LaserHit_4.NS_LaserHit_4'"));
    if (NiagaraSystemAsset.Succeeded())
    {
        NiagaraComponent->SetAsset(NiagaraSystemAsset.Object);
    }
}

void AC_Ametralladora_plasma::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Solo agregar impulso y destruir el proyectil si golpeamos un objeto físico
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
    {
        // Solo agregar impulso y destruir el proyectil si golpeamos un componente con física habilitada de la nave del jugador
        if (OtherComp->IsSimulatingPhysics())
        {
            OtherComp->AddImpulseAtLocation(GetVelocity() * 10000.0f, GetActorLocation());
        }
    }

    AGALAGA_REMASTEREDPawn* Player = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);

    if (Player)
    {
        Player->Damage_received(300);
    }


    this -> Destroy();
}

void AC_Ametralladora_plasma::BeginPlay()
{
    Super::BeginPlay();
}

void AC_Ametralladora_plasma::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
