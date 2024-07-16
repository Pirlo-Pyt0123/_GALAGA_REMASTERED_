// Fill out your copyright notice in the Description page of Project Settings.


#include "X_Master_Ship_Colossus.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "CB_Lava_Sword.h"
#include "CB_Asteroid_Sword.h"
#include "CB_Ice_Sword.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


AX_Master_Ship_Colossus::AX_Master_Ship_Colossus()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Assets/Meshes/levia.levia'"));
	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
		
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


	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/BOSS_SOUNDS/AMETRALLADORA.AMETRALLADORA'"));
	if (AssetShotSound.Succeeded())
	{
		Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
	}

	Au_Col = CreateDefaultSubobject<UAudioComponent>(TEXT("Au_Col"));
	Au_Col->SetupAttachment(Nave_Mesh);
	Au_Col->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound2(TEXT("SoundWave'/Game/BOSS_SOUNDS/EveryTime.EveryTime'"));
	if (AssetExplosionSound2.Succeeded())
	{
		Au_Col->SetSound(AssetExplosionSound2.Object);
	}


	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(Nave_Mesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/VFXSeries1/Particles/Kinetic/P_BulletTracer.P_BulletTracer'"));
	if (ParticleAsset2.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset2.Object);
		Proye->bAutoActivate = true;
		Proye->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));

		Proye->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		Proye->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
		

	}

	Spawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Spawn"));
	Spawn->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset3(TEXT("ParticleSystem'/Game/MFK/Particles/Expanders/Par_ExpFire_01_Rain.Par_ExpFire_01_Rain'"));
	if (ParticleAsset3.Succeeded())
	{
		Spawn->SetTemplate(ParticleAsset3.Object);
		Spawn->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	Nia_Col = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia_Col"));
	Nia_Col->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/Colossus_X.Colossus_X'"));
	if (NiagaraAsset.Succeeded())
	{
		Nia_Col->SetAsset(NiagaraAsset.Object);
		Nia_Col->SetWorldScale3D(FVector(7.5f, 7.5f, 7.5f));
	}

	// Añadir todos los movimientos al array
	Movimientos.Add(&UAC_MOVEMENT_EPIC::CircularMovement);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeSerpiente);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDePulso);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeTornado);

	Colision_Nave->SetupAttachment(Nave_Mesh);

	
}

void AX_Master_Ship_Colossus::BeginPlay()
{
	Super::BeginPlay();

	// Reproducir el sonido de la nave
	Au_Col->Play();
}

void AX_Master_Ship_Colossus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Disparo_Nave(DeltaTime);

	Movimiento_Nave(DeltaTime);

	if (Life <= 0)
	{
		// Detener el sonido de la nave
		Au_Col->Stop();
	}
}

void AX_Master_Ship_Colossus::Recibir_Danio(float Danio)
{
	Life -= Danio;
}

void AX_Master_Ship_Colossus::Disparo_Nave(float DeltaTime)
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
            const float DisparoOffset = 2600.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
            FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

            switch (DisparoActual)
            {
            case 0:
                // Disparo individual con efecto de rastreo
            {
                ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), SpawnLocation, FireRotation);
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
                    ACB_Lava_Sword* Proyectil = World->SpawnActor<ACB_Lava_Sword>(ACB_Lava_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
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
                    ACB_Lava_Sword* Proyectil = World->SpawnActor<ACB_Lava_Sword>(ACB_Lava_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
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
                    ACB_Ice_Sword* Proyectil = World->SpawnActor<ACB_Ice_Sword>(ACB_Ice_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
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
                    ACB_Ice_Sword* Proyectil = World->SpawnActor<ACB_Ice_Sword>(ACB_Ice_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
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
                ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), SpawnLocation, FireRotation);
                if (Proyectil)
                {
                    Proyectil->SetHomingTarget(PY);

                    // Configurar una función lambda para dividir el proyectil después de cierto tiempo
                    FTimerHandle TimerHandle;
                    World->GetTimerManager().SetTimer(TimerHandle, [Proyectil, World, this]()
                        {
                            FVector DivisionLocation = Proyectil->GetActorLocation();
                            for (int i = 0; i < 6; i++)
                            {
                                FRotator AdjustedRotation = Proyectil->GetActorRotation();
                                AdjustedRotation.Yaw += i * 60.0f; // 360 grados dividido por 6 proyectiles
                                FVector AdjustedLocation = DivisionLocation + AdjustedRotation.Vector() * 100.0f;
                                ACB_Asteroid_Sword* SubProyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                                if (SubProyectil)
                                {
                                    SubProyectil->ProjectileMovement->InitialSpeed = 8000.f;
                                    SubProyectil->ProjectileMovement->MaxSpeed = 8000.f;
                                    SubProyectil->SetHomingTarget(PY);
                                }
                            }
                            Proyectil->Destroy();
                        }, 2.0f, false); // Se divide después de 2 segundos
                }
            }
            break;
            }

            // Alternar al siguiente tipo de disparo
            DisparoActual = (DisparoActual + 1) % 8;

            // Reproducir el sonido del disparo
            UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
        }
    }
}

void AX_Master_Ship_Colossus::Movimiento_Nave(float DeltaTime)
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
