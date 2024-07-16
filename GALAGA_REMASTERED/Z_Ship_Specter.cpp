#include "Z_Ship_Specter.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Ametralladora_plasma.h"

AZ_Ship_Specter::AZ_Ship_Specter()
{
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Mehes/NavesEnemigas/Fighter_01.Fighter_01'"));
    if (MeshAsset.Succeeded())
    {
        Nave_Mesh->SetStaticMesh(MeshAsset.Object);
        Nave_Mesh->SetWorldScale3D(FVector(23.5f, 23.5f, 23.5f));
    }

    //|| COMPONENTE DE PARTICULA DE LA NAVE ||
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MFK/Particles/Expanders/Halfs/Par_ExpFire_02_H_Rain.Par_ExpFire_02_H_Rain'"));
    if (ParticleAsset.Succeeded())
    {
        Explosion_Nave = Cast<UParticleSystem>(ParticleAsset.Object);
    }

    //|| COMPONENTE DE SONIDO DE LA NAVE ||
    static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Magic/MagicMissle_EnergyExplosion.MagicMissle_EnergyExplosion'"));
    if (AssetExplosionSound.Succeeded())
    {
        Sonido_Nave = Cast<USoundBase>(AssetExplosionSound.Object);
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Nova/NovaMissleSmall_NormalShoot.NovaMissleSmall_NormalShoot'"));
    if (AssetShotSound.Succeeded())
    {
        Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
    }

    Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
    Proye->SetupAttachment(Nave_Mesh);
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MegaSci-FiParticleFXBundle3in1/Particles/P_ConstantSparks_Blue.P_ConstantSparks_Blue'"));
    if (ParticleAsset2.Succeeded())
    {
        Proye->SetTemplate(ParticleAsset2.Object);
        Proye->bAutoActivate = true;
        Proye->SetWorldScale3D(FVector(2.5f, 2.5f, 2.5f));
        Proye->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
        Proye->SetRelativeLocation(FVector(-70.0f, 0.0f, 40.0f));
    }

    //|| COMPONENTE DE COLISION DE LA NAVE ||
    Colision_Nave->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
    Colision_Nave->SetupAttachment(Nave_Mesh);

    DistanciaRecorrida = 0.0f;
    Velocidad_Nave = 20000.0f;
    DistanciaMovimiento = 8000.0f;
    IntervaloCambioDireccion = 20.0f;  // Cada 20 segundos
    IntervaloGiroAleatorio = 7.0f;  // Cada 8 segundos
    bPersiguiendoPawn = false;
    bPlayerDetected = false;
    FireRate = 2.5f; // Ajusta la tasa de disparo
    TimeSinceLastShot = 0.0f;
    bKamikazeMode = false;
}

void AZ_Ship_Specter::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(TimerHandle_CambioDireccion, this, &AZ_Ship_Specter::GirarNaveAleatorio, IntervaloCambioDireccion, true);
    GetWorldTimerManager().SetTimer(TimerHandle_GiroAleatorio, this, &AZ_Ship_Specter::GirarLigeramente, IntervaloGiroAleatorio, true);
}

void AZ_Ship_Specter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Life <= 0)
    {
        Componente_Destruccion();
    }

    if (bKamikazeMode)
    {
        Kamikaze(DeltaTime);
    }
    else
    {
        DetectarPawn();

        if (bPersiguiendoPawn)
        {
            PerseguirPawn(DeltaTime);
        }
        else
        {
            Movimiento_Nave(DeltaTime);
        }
    }
}

void AZ_Ship_Specter::Recibir_Danio(float Danio)
{
    Super::Recibir_Danio(Danio);
    if (Life <= 100 && !bKamikazeMode)
    {
        bKamikazeMode = true;
        GetWorldTimerManager().ClearTimer(TimerHandle_CambioDireccion);
        GetWorldTimerManager().ClearTimer(TimerHandle_GiroAleatorio);
    }
}

void AZ_Ship_Specter::Disparo_Nave(UWorld* World, FVector Location, FRotator Rotation)
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
            const float DisparoOffset = 3500.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
            FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

            // Spawn del proyectil
            AC_Ametralladora_plasma* Proyectil = World->SpawnActor<AC_Ametralladora_plasma>(AC_Ametralladora_plasma::StaticClass(), SpawnLocation, FireRotation);

            // Reproducir el sonido del disparo
            UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
        }
    }
}

void AZ_Ship_Specter::Movimiento_Nave(float DeltaTime)
{
    FVector ForwardDirection = GetActorRightVector();
    float DistanceToMove = Velocidad_Nave * DeltaTime;

    if (DistanciaRecorrida + DistanceToMove > DistanciaMovimiento)
    {
        DistanceToMove = DistanciaMovimiento - DistanciaRecorrida;
    }

    FVector NewLocation = GetActorLocation() + (ForwardDirection * DistanceToMove);
    SetActorLocation(NewLocation);

    DistanciaRecorrida += DistanceToMove;

    if (DistanciaRecorrida >= DistanciaMovimiento)
    {
        // Resetear la distancia recorrida
        DistanciaRecorrida = 0.0f;
    }

    VerificarLimitesYRebotar();
}

void AZ_Ship_Specter::Kamikaze(float DeltaTime)
{
    if (Player)
    {
        FVector Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        FVector NewLocation = GetActorLocation() + (Direction * Velocidad_Nave * DeltaTime);
        SetActorLocation(NewLocation);

        FRotator NewRotation = Direction.Rotation();
        SetActorRotation(NewRotation);
    }
}
