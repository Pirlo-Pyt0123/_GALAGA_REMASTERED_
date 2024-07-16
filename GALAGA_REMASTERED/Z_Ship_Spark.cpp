#include "Z_Ship_Spark.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Bombur_Stronger.h"

AZ_Ship_Spark::AZ_Ship_Spark()
{
    PrimaryActorTick.bCanEverTick = true;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/vehicle/source/sabre.sabre'"));
    if (MeshAsset.Succeeded())
    {
        Nave_Mesh->SetStaticMesh(MeshAsset.Object);
        Nave_Mesh->SetWorldScale3D(FVector(30.5f, 30.5f, 30.5f));
        Nave_Mesh->SetRelativeRotation(FRotator(0.0f, 180.0f, 90.0f));
    }

    //|*| COMPONENTE DE PARTICULA DE LA NAVE |*|
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_ThunderBallHit.P_ky_ThunderBallHit'"));
    if (ParticleAsset.Succeeded())
    {
        Explosion_Nave = Cast<UParticleSystem>(ParticleAsset.Object);
    }

    //|*| COMPONENTE DE SONIDO DE LA NAVE |*|
    static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion02.Explosion02'"));
    if (AssetExplosionSound.Succeeded())
    {
        Sonido_Nave = Cast<USoundBase>(AssetExplosionSound.Object);
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Soul/SoulMissile2_Shoot.SoulMissile2_Shoot'"));
    if (AssetShotSound.Succeeded())
    {
        Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
    }

    Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
    Proye->SetupAttachment(Nave_Mesh);
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/VFXSeries1/Particles/Tails/P_LaserTrail.P_LaserTrail'"));
    if (ParticleAsset2.Succeeded())
    {
        Proye->SetTemplate(ParticleAsset2.Object);
        Proye->bAutoActivate = true;
        Proye->SetWorldScale3D(FVector(2.5f, 2.5f, 2.5f));
    }

    //|*| PARA AJUSTAR LOS LIMITES DE COLISION DE LA NAVE |*|
    Colision_Nave->SetBoxExtent(FVector(150.f, 150.f, 150.f));
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
}

void AZ_Ship_Spark::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(TimerHandle_CambioDireccion, this, &AZ_Ship_Spark::GirarNaveAleatorio, IntervaloCambioDireccion, true);
    GetWorldTimerManager().SetTimer(TimerHandle_GiroAleatorio, this, &AZ_Ship_Spark::GirarLigeramente, IntervaloGiroAleatorio, true);
}

void AZ_Ship_Spark::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Life <= 0)
    {
        Componente_Destruccion();
    }

}

void AZ_Ship_Spark::Recibir_Danio(float Danio)
{
    Super::Recibir_Danio(Danio);
}

void AZ_Ship_Spark::Disparo_Nave(UWorld* World, FVector Location, FRotator Rotation)
{
    if (World != nullptr && Player != nullptr)  // Verificar que World y Player no sean nullptr
    {
        // Obtener la posición y la rotación actuales de la nave enemiga
        FVector EnemyLocation = GetActorLocation();
        FRotator EnemyRotation = GetActorRotation();

        // Obtener la posición del jugador
        FVector PlayerLocation = Player->GetActorLocation();

        // Calcular la dirección del disparo hacia el jugador
        FVector DisparoDirection = (PlayerLocation - EnemyLocation).GetSafeNormal();
        FRotator FireRotation = DisparoDirection.Rotation();

        // Configurar la distancia de disparo directamente en la función
        const float DisparoOffset = 4500.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
        FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

        // Spawn del proyectil
        AC_Bombur_Stronger* Proyectil = World->SpawnActor<AC_Bombur_Stronger>(AC_Bombur_Stronger::StaticClass(), SpawnLocation, FireRotation);

        // Reproducir el sonido del disparo
        UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
    }
}

void AZ_Ship_Spark::Movimiento_Nave(float DeltaTime)
{
    FVector ForwardDirection = GetActorForwardVector();
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

//void AZ_Ship_Spark::PerseguirPawn(float DeltaTime)
//{
//    if (Player)
//    {
//        FVector Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
//        FVector NewLocation = GetActorLocation() + (Direction * Velocidad_Nave * DeltaTime);
//        SetActorLocation(NewLocation);
//
//        FRotator NewRotation = Direction.Rotation();
//        SetActorRotation(NewRotation);
//    }
//}
