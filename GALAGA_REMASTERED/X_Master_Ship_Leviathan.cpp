// Fill out your copyright notice in the Description page of Project Settings.


#include "X_Master_Ship_Leviathan.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "CB_Ice_Sword.h"
#include "CB_Asteroid_Sword.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


AX_Master_Ship_Leviathan::AX_Master_Ship_Leviathan()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/tru/textures/fast_texturing_output.fast_texturing_output'"));
	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(15.5f, 15.5f, 15.5f));
		
	}
	

	//|*| COMPONENTE DE PARTICULA DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/TypeAStarFighter/Particles/PS_BlasterHit.PS_BlasterHit'"));

	if (ParticleAsset.Succeeded())
	{
		Explosion_Nave = Cast<UParticleSystemComponent>(ParticleAsset.Object);
	}

	Nia_Lev = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia_Lev"));
	Nia_Lev->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/NS_BubbleTech.NS_BubbleTech'"));
	if (NiagaraAsset.Succeeded())
	{
		Nia_Lev->SetAsset(NiagaraAsset.Object);
		Nia_Lev->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
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

	Au_Lev = CreateDefaultSubobject<UAudioComponent>(TEXT("Au_Lev"));
	Au_Lev->SetupAttachment(Nave_Mesh);
	Au_Lev->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound2(TEXT("SoundWave'/Game/BOSS_SOUNDS/CyberPhonk.CyberPhonk'"));
	if (AssetExplosionSound2.Succeeded())
	{
		Au_Lev->SetSound(AssetExplosionSound2.Object);
		
	}
	
	
	Spawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Spawn"));
	Spawn->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MFK/Particles_Tiny/Crysantums/Clusters/Par_FW_Crys_01_Small_CL1_Tiny.Par_FW_Crys_01_Small_CL1_Tiny'"));
	if (ParticleAsset2.Succeeded())
	{
		Spawn->SetTemplate(ParticleAsset2.Object);
		Spawn->bAutoActivate = false;
		Spawn->SetWorldScale3D(FVector(5.5f, 5.5f, 5.5f));
	
	}


	// Añadir todos los movimientos al array
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MoveTowardsPlayer);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeTornado);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::CircularMovement);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDePulso);
}

void AX_Master_Ship_Leviathan::BeginPlay()
{
	Super::BeginPlay();
	Au_Lev->Play();
}

void AX_Master_Ship_Leviathan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Disparo_Nave(DeltaTime);

	Movimiento_Nave(DeltaTime);

	if (Life <= 0)
	{
		Au_Lev->Stop();
		
	}
}

void AX_Master_Ship_Leviathan::Recibir_Danio(float Danio)
{
	Life -= Danio;
}

void AX_Master_Ship_Leviathan::Disparo_Nave(float DeltaTime)
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
                // Disparo individual con velocidad aumentada
            {
                ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), SpawnLocation, FireRotation);
                if (Proyectil)
                {
                    Proyectil->ProjectileMovement->InitialSpeed = 20000.f;
                    Proyectil->ProjectileMovement->MaxSpeed = 20000.f;
                }
            }
            break;

            case 1:
                // Disparo triple con un ángulo más amplio
                for (int i = -1; i <= 1; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 15.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    World->SpawnActor<ACB_Ice_Sword>(ACB_Ice_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                }
                break;

            case 2:
                // Disparo creativo: disparo en espiral con variación en altura
                for (int i = 0; i < 12; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 30.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    AdjustedLocation.Z += FMath::Sin(FMath::DegreesToRadians(i * 30.0f)) * 200.0f; // Variación en altura
                    World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                }
                break;

            case 3:
                // Disparo en ráfaga de cinco proyectiles
                for (int i = 0; i < 5; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    FVector AdjustedLocation = EnemyLocation + FireRotation.Vector() * (DisparoOffset + i * 100.0f);
                    World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                }
                break;

            case 4:
                // Disparo en todas las direcciones
                for (int i = 0; i < 360; i += 45)
                {
                    FRotator AdjustedRotation = FRotator(0, i, 0);
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    World->SpawnActor<ACB_Ice_Sword>(ACB_Ice_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                }
                break;
            }

            // Reproducir el sonido del disparo
            if (Shot_Sound != nullptr)
            {
                UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
            }

            // Cambiar al siguiente disparo
            DisparoActual = (DisparoActual + 1) % 5; // Ajustado para cinco tipos de disparos
        }
    }
}

void AX_Master_Ship_Leviathan::Movimiento_Nave(float DeltaTime)
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
