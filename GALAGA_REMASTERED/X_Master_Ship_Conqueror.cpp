// Fill out your copyright notice in the Description page of Project Settings.


#include "X_Master_Ship_Conqueror.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "CB_Asteroid_Sword.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AX_Master_Ship_Conqueror::AX_Master_Ship_Conqueror()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/assetsGENIE/NEWJHK/c18429120998_Zerg_Metroid_Prime_.c18429120998_Zerg_Metroid_Prime_'"));
	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(40.5f, 40.5f, 40.5f));
		Nave_Mesh->SetupAttachment(RootComponent);
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


	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Explode/A_Explode_08.A_Explode_08'"));
	if (AssetShotSound.Succeeded())
	{
		Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
	}

	Au_Con = CreateDefaultSubobject<UAudioComponent>(TEXT("Au_Con"));
	Au_Con->SetupAttachment(Nave_Mesh);
	Au_Con->bAutoActivate = false;
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound2(TEXT("SoundWave'/Game/BOSS_SOUNDS/Nagata.Nagata'"));
	if (AssetExplosionSound2.Succeeded())
	{
		Au_Con->SetSound(AssetExplosionSound2.Object);
	}


	Spawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Spawn"));
	Spawn->SetupAttachment(Nave_Mesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MagicProjectilesVol2/Particles/Hits/P_Hit_Waterball01_Blue.P_Hit_Waterball01_Blue'"));
	if (ParticleAsset2.Succeeded())
	{
		Spawn->SetTemplate(ParticleAsset2.Object);
		Spawn->bAutoActivate = true;
		Spawn->SetWorldScale3D(FVector(25.5f, 25.5f, 25.5f));
	}

	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(Nave_Mesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset3(TEXT("PParticleSystem'/Game/VFXSeries1/Particles/Tails/P_LaserTrail.P_LaserTrail'"));
	if (ParticleAsset3.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset3.Object);
		Proye->bAutoActivate = true;
		Proye->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
	}

	Nia_Con = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia_Con"));
	Nia_Con->SetupAttachment(Nave_Mesh);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/NS_BubbleGex.NS_BubbleGex'"));
	if (NiagaraAsset.Succeeded())
	{
		Nia_Con->SetAsset(NiagaraAsset.Object);
		Nia_Con->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
	}


	// Añadir todos los movimientos al array
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDePulso);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeReboteTridimensional);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeTornado);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeSerpiente);


	

	Colision_Nave->SetupAttachment(Nave_Mesh);

}


void AX_Master_Ship_Conqueror::BeginPlay()
{
	Super::BeginPlay();
	// Reproducir el sonido de apertura de la nave
	
	Au_Con->Play();
	
}

void AX_Master_Ship_Conqueror::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	Disparo_Nave(DeltaTime);

	Movimiento_Nave(DeltaTime);

	if (Life <= 0)
	{
		Au_Con->Stop();
	}

}

void AX_Master_Ship_Conqueror::Recibir_Danio(float Danio)
{
	Life -= Danio;

}

void AX_Master_Ship_Conqueror::Disparo_Nave(float DeltaTime)
{
    // Actualizar el temporizador
    TiempoTotal += DeltaTime;

    // Verificar si es tiempo de disparar
    if (TiempoTotal >= IntervaloActual)
    {
        // Reiniciar el temporizador
        TiempoTotal = 0.0f;

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
            const float DisparoOffset = 6000.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
            FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

            // Alternar entre diferentes tipos de disparos
            switch (DisparoActual)
            {
            case 0:
                // Disparo individual
                World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), SpawnLocation, FireRotation);
                break;

            case 1:
                // Disparo triple
                for (int i = -1; i <= 1; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 10.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                }
                break;

            case 2:
                // Disparo creativo: disparo en espiral alrededor del jugador
                for (int i = 0; i < 12; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 30.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                }
                break;
            }

            // Reproducir el sonido del disparo
            if (Shot_Sound != nullptr)
            {
                UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
            }

            // Cambiar al siguiente disparo
            DisparoActual = (DisparoActual + 1) % 3;
        }
    }
	
}

void AX_Master_Ship_Conqueror::Movimiento_Nave(float DeltaTime)
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









