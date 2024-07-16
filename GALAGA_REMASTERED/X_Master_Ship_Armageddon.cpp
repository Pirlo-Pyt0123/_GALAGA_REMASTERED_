// Fill out your copyright notice in the Description page of Project Settings.


#include "X_Master_Ship_Armageddon.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "CB_Asteroid_Sword.h"
#include "CB_Lava_Sword.h"
#include "CB_Ice_Sword.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"



AX_Master_Ship_Armageddon::AX_Master_Ship_Armageddon()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/sipo/source/Spcae_ship.Spcae_ship'"));

	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
	}

	//|*| COMPONENTE DE PARTICULA DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MFK/Particles/SawSpark/Par_FW_Saw_01_Rain.Par_FW_Saw_01_Rain'"));

	if (ParticleAsset.Succeeded())
	{
		Explosion_Nave = Cast<UParticleSystemComponent>(ParticleAsset.Object);
	}

	//|*| COMPONENTE DE SONIDO DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/BOSS_SOUNDS/BOSS02_EXPLO.BOSS02_EXPLO'"));
	if (AssetExplosionSound.Succeeded())
	{
		Sonido_Nave = Cast<USoundBase>(AssetExplosionSound.Object);
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion02.Explosion02'"));
	if (AssetShotSound.Succeeded())
	{
		Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
	}

	Au_Arm = CreateDefaultSubobject<UAudioComponent>(TEXT("Au_Arm"));
	Au_Arm->SetupAttachment(Nave_Mesh);
	Au_Arm->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound2(TEXT("SoundWave'/Game/BOSS_SOUNDS/FLUX.FLUX'"));
	if (AssetExplosionSound2.Succeeded())
	{
		Au_Arm->SetSound(AssetExplosionSound2.Object);
	}


	Spawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Spawn"));
	Spawn->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MFK/Particles/Expanders/Par_ExpFire_01_Rain.Par_ExpFire_01_Rain'"));
	if (ParticleAsset2.Succeeded())
	{
		Spawn->SetTemplate(ParticleAsset2.Object);
		Spawn->bAutoActivate = true;
		Spawn->SetWorldScale3D(FVector(50.5f, 50.5f, 50.5f));
	}

	Nia_Arm = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia_Arm"));
	Nia_Arm->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/NS_BubbleWind.NS_BubbleWind'"));
	if (NiagaraAsset.Succeeded())
	{
		Nia_Arm->SetAsset(NiagaraAsset.Object);
		Nia_Arm->SetWorldScale3D(FVector(2.5f, 2.5f, 2.5f));
	}


	// Añadir todos los movimientos al array
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeTornado);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDePulso);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoFiguraOcho);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::CircularMovement);


	Colision_Nave->SetupAttachment(Nave_Mesh);

}

void AX_Master_Ship_Armageddon::BeginPlay()
{
		Super::BeginPlay();

		// Reproducir el sonido de la nave
		Au_Arm->Play();
		
}

void AX_Master_Ship_Armageddon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Movimiento_Nave(DeltaTime);
	Disparo_Nave(DeltaTime);

	if (Life <= 0)
	{
		Au_Arm->Stop();
	}
}

void AX_Master_Ship_Armageddon::Recibir_Danio(float Danio)
{
	Life -= Danio;
}

void AX_Master_Ship_Armageddon::Disparo_Nave(float DeltaTime)
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
            const float DisparoOffset = 10500.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
            FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

            // Alternar entre diferentes tipos de disparos con variaciones
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
                    ACB_Ice_Sword* Proyectil = World->SpawnActor<ACB_Ice_Sword>(ACB_Ice_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
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
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
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

void AX_Master_Ship_Armageddon::Movimiento_Nave(float DeltaTime)
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
