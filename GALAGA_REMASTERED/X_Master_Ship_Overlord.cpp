// Fill out your copyright notice in the Description page of Project Settings.


#include "X_Master_Ship_Overlord.h"
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
#include "CB_Lava_Sword.h"
#include "CB_Space_Sword.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AX_Master_Ship_Overlord::AX_Master_Ship_Overlord()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Assets/Meshes/SciFi_Ship_Escort-FBX.SciFi_Ship_Escort-FBX'"));
	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	//|*| COMPONENTE DE PARTICULA DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MFK/Particles_Tiny/FlatRings/Par_FW_FlatRing_03_Tiny.Par_FW_FlatRing_03_Tiny'"));

	if (ParticleAsset.Succeeded())
	{
		Explosion_Nave = Cast<UParticleSystemComponent>(ParticleAsset.Object);
	}

	//|*| COMPONENTE DE SONIDO DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/BOSS_SOUNDS/EXPLO_BOSS.EXPLO_BOSS'"));
	if (AssetExplosionSound.Succeeded())
	{
		Sonido_Nave = Cast<USoundBase>(AssetExplosionSound.Object);
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MagicCombatAudio/Magic/MagicEnchant_Normal.MagicEnchant_Normal'"));
	if (AssetShotSound.Succeeded())
	{
		Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
	}

	Au_Ove = CreateDefaultSubobject<UAudioComponent>(TEXT("Au_Ove"));
	Au_Ove->SetupAttachment(Nave_Mesh);
	Au_Ove->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound2(TEXT("SoundWave'/Game/BOSS_SOUNDS/Roi.Roi'"));
	if (AssetExplosionSound2.Succeeded())
	{
		Au_Ove->SetSound(AssetExplosionSound2.Object);
	}

	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(Nave_Mesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MFK/Particles/Expanders/Par_ExpFire_02_Rain.Par_ExpFire_02_Rain'"));
	if (ParticleAsset2.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset2.Object);
        Proye->SetWorldScale3D(FVector(30.5f, 30.5f, 30.5f));

	}

	Nia_Ove = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia_Ove"));
	Nia_Ove->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/NS_BubbleMagic.NS_BubbleMagic'"));
	if (NiagaraAsset.Succeeded())
	{
		Nia_Ove->SetAsset(NiagaraAsset.Object);
		Nia_Ove->SetWorldScale3D(FVector(7.5f, 7.5f, 7.5f));
	
		
	}

	Spawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Spawn"));
	Spawn->SetupAttachment(Nave_Mesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset4(TEXT("ParticleSystem'/Game/MFK/Particles_Tiny/FlatRings/Par_FW_FlatRing_03_Tiny.Par_FW_FlatRing_03_Tiny'"));
	if (ParticleAsset4.Succeeded())
	{
		Spawn->SetTemplate(ParticleAsset4.Object);
		Spawn->bAutoActivate = true;
		Spawn->SetWorldScale3D(FVector(30.5f, 30.5f, 30.5f));
		

		Spawn->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		Spawn->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	}

	// Añadir todos los movimientos al array
	Movimientos.Add(&UAC_MOVEMENT_EPIC::CircularMovement);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoEspiralExpansiva);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeReboteTridimensional);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDePulso);



	//|*| PARA AJUSTAR LOS LIMITES DE COLISION DE LA NAVE |*|
	Colision_Nave->SetBoxExtent(FVector(150.f, 150.f, 150.f));
	//atachamiento

	Colision_Nave->SetupAttachment(Nave_Mesh);
}

void AX_Master_Ship_Overlord::BeginPlay()
{
	Super::BeginPlay();

	Au_Ove->Play();

		
}

void AX_Master_Ship_Overlord::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Disparo_Nave(DeltaTime);

	Movimiento_Nave(DeltaTime);

	
	if (Life <= 0)
	{
		
		Au_Ove->Stop();
	}
	
}

void AX_Master_Ship_Overlord::Recibir_Danio(float Danio)
{
	Life -= Danio;
}

void AX_Master_Ship_Overlord::Disparo_Nave(float DeltaTime)
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
            const float DisparoOffset = 3600.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
            FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

            // Alternar entre diferentes tipos de disparos con variaciones
            switch (DisparoActual)
            {
            case 0:
                // Disparo individual con efecto de rastreo
            {
                ACB_Lava_Sword* Proyectil = World->SpawnActor<ACB_Lava_Sword>(ACB_Lava_Sword::StaticClass(), SpawnLocation, FireRotation);
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
                    ACB_Lava_Sword* Proyectil = World->SpawnActor<ACB_Lava_Sword>(ACB_Lava_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
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
                    ACB_Space_Sword* Proyectil = World->SpawnActor<ACB_Space_Sword>(ACB_Space_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 10000.f + FMath::RandRange(-2000.f, 2000.f);
                        Proyectil->ProjectileMovement->MaxSpeed = 10000.f + FMath::RandRange(-2000.f, 2000.f);
                        
                    }
                }
                break;
            }

            // Reproducir el sonido del disparo
            if (Shot_Sound != nullptr)
            {
                UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
            }

            // Cambiar al siguiente disparo
            DisparoActual = (DisparoActual + 1) % 5; 
        }
    }

}


void AX_Master_Ship_Overlord::Movimiento_Nave(float DeltaTime)
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


