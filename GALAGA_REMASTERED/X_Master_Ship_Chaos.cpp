// Fill out your copyright notice in the Description page of Project Settings.


#include "X_Master_Ship_Chaos.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "CB_Asteroid_Sword.h"
#include "CB_Ice_Sword.h"
#include "CB_Space_Sword.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AX_Master_Ship_Chaos::AX_Master_Ship_Chaos()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/saki/source/SM_SkyFly_v07.SM_SkyFly_v07'"));
	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
	}

	//|*| COMPONENTE DE PARTICULA DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/TypeAStarFighter/Particles/PS_BlasterHit.PS_BlasterHit'"));

	if (ParticleAsset.Succeeded())
	{
		Explosion_Nave = Cast<UParticleSystemComponent>(ParticleAsset.Object);
	}

	//|*| COMPONENTE DE SONIDO DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/Explode/A_Explode_08.A_Explode_08'"));
	if (AssetExplosionSound.Succeeded())
	{
		Sonido_Nave = Cast<USoundBase>(AssetExplosionSound.Object);
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Magic/MagicMissle_FireEnergyShoot.MagicMissle_FireEnergyShoot'"));
	if (AssetShotSound.Succeeded())
	{
		Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
	}

	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MegaSci-FiParticleFXBundle3in1/Particles/OVERLORD_ADVANCE.OVERLORD_ADVANCE'"));

	if (ParticleAsset2.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset2.Object);

		Proye->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));

		Proye->SetRelativeLocation(FVector(0.f, 0.f, -120.f));
		//tamano
		Proye->SetRelativeScale3D(FVector(2.5f, 2.5f, 2.5f));
		Proye->bAutoActivate = true;
	}

	Nia_Cha = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia_Chao"));
	Nia_Cha->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/NS_BubbleMagic_02.NS_BubbleMagic_02'"));
	if (NiagaraAsset.Succeeded())
	{
		Nia_Cha->SetAsset(NiagaraAsset.Object);
		Nia_Cha->bAutoActivate = true;
		Nia_Cha->SetWorldScale3D(FVector(0.85f, 0.85f, 0.85f));
	}

    // Creación del AudioComponent
    Au_Cha = CreateDefaultSubobject<UAudioComponent>(TEXT("AccelerationAudioComponent"));
    Au_Cha->SetupAttachment(RootComponent);
    Au_Cha->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound2(TEXT("SoundWave'/Game/BOSS_SOUNDS/DVRST.DVRST'"));
	if (AssetExplosionSound2.Succeeded())
	{
		Au_Cha->SetSound(AssetExplosionSound2.Object);
	}



	Spawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Spawn"));
	Spawn->SetupAttachment(Nave_Mesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset3(TEXT("ParticleSystem'/Game/MFK/Particles_Tiny/Crysantums/Clusters/Par_FW_Crys_01_Small_CL1_Tiny.Par_FW_Crys_01_Small_CL1_Tiny'"));
	if (ParticleAsset3.Succeeded())
	{
		Spawn->SetTemplate(ParticleAsset3.Object);
		Spawn->bAutoActivate = true;
		Spawn->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	// Añadir todos los movimientos al array
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeTornado);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeSerpiente);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoFiguraOcho);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDePulso);


	Colision_Nave->SetupAttachment(Nave_Mesh);

 
}

void AX_Master_Ship_Chaos::BeginPlay()
{
	Super::BeginPlay();

	// Reproducir el sonido de la nave
	Au_Cha->Play();


}

void AX_Master_Ship_Chaos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Disparo_Nave(DeltaTime);

	Movimiento_Nave(DeltaTime);

	if (Life <= 0)
	{
		Au_Cha->Stop();
	}
}

void AX_Master_Ship_Chaos::Recibir_Danio(float Danio)
{
	Life -= Danio;

}

void AX_Master_Ship_Chaos::Disparo_Nave(float DeltaTime)
{
    // Actualizar el temporizador
    Tiempo_Disparo += DeltaTime;

    // Verificar si es tiempo de disparar
    if (Tiempo_Disparo >= IntervaloActual_Disparo)
    {
        // Reiniciar el temporizador
        Tiempo_Disparo = 0.0f;

        // Obtener el mundo y la referencia al jugador
        UWorld* World = GetWorld();
        PY = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(World, 0));

        if (World != nullptr && PY != nullptr)
        {
            // Obtener la posición y la rotación actuales de la nave enemiga
            FVector EnemyLocation = GetActorLocation();
            FRotator EnemyRotation = GetActorRotation();

            // Obtener la posición del jugador
            FVector PlayerLocation = PY->GetActorLocation();

            // Calcular la dirección del disparo hacia el jugador
            FVector DisparoDirection = (PlayerLocation - EnemyLocation).GetSafeNormal();
            FRotator FireRotation = DisparoDirection.Rotation();

            // Configurar la distancia de disparo
            const float DisparoOffset = 3800.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
            FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

            // Alternar entre diferentes tipos de disparos con variaciones
            switch (DisparoActual)
            {
            case 0:
                // Disparo individual con efecto de rastreo
            {
                ACB_Space_Sword* Proyectil = World->SpawnActor<ACB_Space_Sword>(ACB_Space_Sword::StaticClass(), SpawnLocation, FireRotation);
                if (Proyectil)
                {
                    Proyectil->SetHomingTarget(PY);
                }
            }
            break;

            case 1:
                // Disparo triple en arco
                for (int i = -1; i <= 1; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 20.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->SetHomingTarget(PY);
                    }
                }
                break;

            case 2:
                // Disparo en espiral con velocidad oscilante
                for (int i = 0; i < 12; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 30.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    AdjustedLocation.Z += FMath::Sin(FMath::DegreesToRadians(i * 30.0f)) * 200.0f; // Variación en altura
                    ACB_Space_Sword* Proyectil = World->SpawnActor<ACB_Space_Sword>(ACB_Space_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 8000.f + FMath::Sin(i * 30.0f) * 4000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 8000.f + FMath::Sin(i * 30.0f) * 4000.f;
                        Proyectil->SetHomingTarget(PY);
                    }
                }
                break;

            case 3:
                // Disparo en ráfaga con proyectiles explosivos
                for (int i = 0; i < 5; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    FVector AdjustedLocation = EnemyLocation + FireRotation.Vector() * (DisparoOffset + i * 100.0f);
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 15000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 15000.f;
                        Proyectil->SetHomingTarget(PY);
                    }
                }
                break;

            case 4:
                // Disparo en todas las direcciones con velocidad variable
                for (int i = 0; i < 360; i += 45)
                {
                    FRotator AdjustedRotation = FRotator(0, i, 0);
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 10000.f + FMath::RandRange(-2000.f, 2000.f);
                        Proyectil->ProjectileMovement->MaxSpeed = 10000.f + FMath::RandRange(-2000.f, 2000.f);
                        Proyectil->SetHomingTarget(PY);
                    }
                }
                break;

            case 5:
                // Disparo en línea recta con zigzag
                for (int i = 0; i < 3; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    FVector AdjustedLocation = EnemyLocation + FireRotation.Vector() * (DisparoOffset + i * 200.0f);
                    AdjustedLocation.X += (i % 2 == 0) ? 200.0f : -200.0f; // Zigzag
                    ACB_Space_Sword* Proyectil = World->SpawnActor<ACB_Space_Sword>(ACB_Space_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 12000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 12000.f;
                        Proyectil->SetHomingTarget(PY);
                    }
                }
                break;

            case 6:
                // Disparo en forma de estrella
                for (int i = 0; i < 5; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 72.0f; // 360 grados dividido por 5 puntas de estrella
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 10000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 10000.f;
                        Proyectil->SetHomingTarget(PY);
                    }
                }
                break;

            case 7:
                // Disparo que se divide en múltiples proyectiles
            {
                ACB_Ice_Sword* Proyectil = World->SpawnActor<ACB_Ice_Sword>(ACB_Ice_Sword::StaticClass(), SpawnLocation, FireRotation);
                if (Proyectil)
                {
                    Proyectil->SetHomingTarget(PY);

                    // Configurar un evento para dividir el proyectil
                    FTimerHandle TimerHandle;
                    FTimerDelegate TimerDelegate = FTimerDelegate::CreateLambda([=]()
                        {
                            FVector SplitLocation = Proyectil->GetActorLocation();
                            FRotator SplitRotation = Proyectil->GetActorRotation();
                            for (int j = 0; j < 5; j++)
                            {
                                FRotator AdjustedRotation = SplitRotation;
                                AdjustedRotation.Yaw += j * 72.0f;
                                FVector AdjustedLocation = SplitLocation + AdjustedRotation.Vector() * 200.0f;
                                ACB_Ice_Sword* SplitProjectile = World->SpawnActor<ACB_Ice_Sword>(ACB_Ice_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                                if (SplitProjectile)
                                {
                                    SplitProjectile->ProjectileMovement->InitialSpeed = 6000.f;
                                    SplitProjectile->ProjectileMovement->MaxSpeed = 6000.f;
                                    SplitProjectile->SetHomingTarget(PY);
                                }
                            }
                            Proyectil->Destroy();
                        });

                    // Configurar el temporizador para dividir el proyectil después de 1 segundo
                    World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.0f, false);
                }
            }
            break;

            default:
                break;
            }

            // Alternar al siguiente tipo de disparo
            DisparoActual = (DisparoActual + 1) % 8;
        }

        // Reproducir el sonido del disparo
        UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
    }
}

void AX_Master_Ship_Chaos::Movimiento_Nave(float DeltaTime)
{
	// Actualizar el temporizador
	TiempoTotal += DeltaTime;

	// Comprobar si es momento de cambiar el movimiento
	if (TiempoTotal >= IntervaloActual)
	{
		// Reiniciar el temporizador
		TiempoTotal = 0.0f;

		// Cambiar al siguiente movimiento
		MovimientoActual = (MovimientoActual + 1) % Movimientos.Num();
	}

	// Ejecutar el movimiento actual
	if (Move && Movimientos.IsValidIndex(MovimientoActual))
	{
		(Move->*Movimientos[MovimientoActual])(DeltaTime);
	}
}
