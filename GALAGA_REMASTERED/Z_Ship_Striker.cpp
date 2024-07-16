#include "Z_Ship_Striker.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Fire_Ball.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "C_Misil_Nuclear.h"

AZ_Ship_Striker::AZ_Ship_Striker()
{
    PrimaryActorTick.bCanEverTick = true;

    Nave_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NaveMesh"));
    RootComponent = Nave_Mesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/infp/source/spaceship_3_Cube_003.spaceship_3_Cube_003'"));
    if (MeshAsset.Succeeded())
    {
        Nave_Mesh->SetStaticMesh(MeshAsset.Object);
        Nave_Mesh->SetWorldScale3D(FVector(9.5f, 9.5f, 9.5f));
    }

    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MFK/Particles/Umbrella/Par_FW_Umbr_02_Rain.Par_FW_Umbr_02_Rain'"));
    if (ParticleAsset.Succeeded())
    {
        Explosion_Nave = Cast<UParticleSystem>(ParticleAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion02.Explosion02'"));
    if (AssetExplosionSound.Succeeded())
    {
        Sonido_Nave = Cast<USoundBase>(AssetExplosionSound.Object);
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Importaciones/Sonidos_Armas/Sounds/Wavs/S_Spfire01.S_Spfire01'"));
    if (AssetShotSound.Succeeded())
    {
        Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
    }

    Colision_Nave = CreateDefaultSubobject<UBoxComponent>(TEXT("ColisionNave"));
    Colision_Nave->SetBoxExtent(FVector(350.0f, 350.0f, 350.0f));
    Colision_Nave->SetupAttachment(Nave_Mesh);

    Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
    Proye->SetupAttachment(Nave_Mesh);

    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MegaSci-FiParticleFXBundle3in1/Particles/P_WeldingTrail.P_WeldingTrail'"));
    if (ParticleAsset2.Succeeded())
    {
        Proye->SetTemplate(ParticleAsset2.Object);
        Proye->bAutoActivate = true;
        Proye->SetRelativeLocation(FVector(0.0f, 30.0f, 50.0f));
        Proye->SetWorldScale3D(FVector(10.5f, 10.5f, 30.5f));
    }

    DistanciaRecorrida = 0.0f;
    Velocidad_Nave = 30000.0f;
    DistanciaMovimiento = 18000.0f;
    IntervaloCambioDireccion = 20.0f;  // Cada 20 segundos
    IntervaloGiroAleatorio = 7.0f;  // Cada 8 segundos
    bPersiguiendoPawn = false;
    bPlayerDetected = false;
    FireRate = 2.5f; // Ajusta la tasa de disparo
    TimeSinceLastShot = 0.0f;
    Life = 6000.0f; // Vida de la nave
}

void AZ_Ship_Striker::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(TimerHandle_CambioDireccion, this, &AZ_Ship_Striker::GirarNaveAleatorio, IntervaloCambioDireccion, true);
    GetWorldTimerManager().SetTimer(TimerHandle_GiroAleatorio, this, &AZ_Ship_Striker::GirarLigeramente, IntervaloGiroAleatorio, true);
}

void AZ_Ship_Striker::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Life <= 0)
	{
		Componente_Destruccion();
	}

    // La detección y el manejo de disparo se realiza en la clase padre
}

void AZ_Ship_Striker::Recibir_Danio(float Danio)
{
    Super::Recibir_Danio(Danio);
}

void AZ_Ship_Striker::Disparo_Nave(UWorld* World, FVector Location, FRotator Rotation)
{
    if (World != nullptr)
    {
        // Obtener la posición y la rotación actuales de la nave enemiga
        FVector EnemyLocation = GetActorLocation();
        FRotator EnemyRotation = GetActorRotation();

        // Obtener la posición del jugador (suponiendo que el jugador es de tipo APawn)
        if (Player)
        {
            FVector PlayerLocation = Player->GetActorLocation();

            // Calcular la dirección del disparo hacia el jugador
            FVector DisparoDirection = (PlayerLocation - EnemyLocation).GetSafeNormal();
            FRotator FireRotation = DisparoDirection.Rotation();

            // Configurar la distancia de disparo directamente en la función
            const float DisparoOffset = 1000.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
            FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

            // Spawn del proyectil
            AC_Misil_Nuclear* Proyectil = World->SpawnActor<AC_Misil_Nuclear>(AC_Misil_Nuclear::StaticClass(), SpawnLocation, FireRotation);

            // Aumentar la velocidad del proyectil
            if (Proyectil)
            {
                UProjectileMovementComponent* ProjectileMovement = Proyectil->FindComponentByClass<UProjectileMovementComponent>();
                if (ProjectileMovement)
                {
                    ProjectileMovement->InitialSpeed = 60000.f; // Nueva velocidad inicial
                    ProjectileMovement->MaxSpeed = 60000.f;     // Nueva velocidad máxima
                }
            }

            // Reproducir el sonido del disparo
            UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
        }
    }
}