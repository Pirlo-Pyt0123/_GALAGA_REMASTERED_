// Fill out your copyright notice in the Description page of Project Settings.


#include "X_Master_Ship_Titan.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "PF_Level_Difficulty_Base_P.h"
#include "CB_Asteroid_Sword.h"
#include "CB_Ice_Sword.h"
#include "CB_Space_Sword.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


AX_Master_Ship_Titan::AX_Master_Ship_Titan()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/v6/source/DoomScythe.DoomScythe'"));
	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
	}


    Nia_Tit = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Expo"));
    Nia_Tit->SetupAttachment(Nave_Mesh);

    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/NS_BubbleGex.NS_BubbleGex'"));
    if (NiagaraAsset.Succeeded())
    {
        Nia_Tit->SetAsset(NiagaraAsset.Object);
        
        Nia_Tit->SetAutoActivate(true);
        
    }


	//|*| COMPONENTE DE PARTICULA DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MFK/Particles_Tiny/Crysantums/Clusters/Par_FW_Crys_01_Small_CL1_Tiny.Par_FW_Crys_01_Small_CL1_Tiny'"));

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


	

	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Laser/LaserMissle3_Explosion.LaserMissle3_Explosion'"));
	if (AssetShotSound.Succeeded())
	{
		Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
	}

    Au_Tit = CreateDefaultSubobject<UAudioComponent>(TEXT("Au_Ove"));
    Au_Tit->SetupAttachment(Nave_Mesh);
    Au_Tit->bAutoActivate = false;
    static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound2(TEXT("SoundWave'/Game/BOSS_SOUNDS/PROBLEM.PROBLEM'"));
    if (AssetExplosionSound2.Succeeded())
    {
        Au_Tit->SetSound(AssetExplosionSound2.Object);
    }



	Spawn = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Spawn"));
	Spawn->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MFK/Particles_Tiny/Crysantums/Clusters/Par_FW_Crys_01_Small_CL1_Tiny.Par_FW_Crys_01_Small_CL1_Tiny'"));
	if (ParticleAsset2.Succeeded())
	{
		Spawn->SetTemplate(ParticleAsset2.Object);
		Spawn->bAutoActivate = true;
		Spawn->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(Nave_Mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset3(TEXT("ParticleSystem'/Game/VFXSeries1/Particles/Tails/P_LaserTrail.P_LaserTrail'"));
	if (ParticleAsset3.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset3.Object);
		Proye->bAutoActivate = true;
		Proye->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
		Proye->SetRelativeLocation(FVector(500.f, 0.f, 0.f));
	}
    

   

	// Añadir todos los movimientos al array
	Movimientos.Add(&UAC_MOVEMENT_EPIC::CircularMovement);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeSerpiente);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDePulso);
	Movimientos.Add(&UAC_MOVEMENT_EPIC::MovimientoDeTornado);


	//Colision_Nave->SetBoxExtent(FVector(250.f, 300.f, 300.f));
	Colision_Nave->SetupAttachment(Nave_Mesh);
	


}

void AX_Master_Ship_Titan::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

	Movimiento_Nave(DeltaTime);

	Disparo_Nave(DeltaTime);

   
}

void AX_Master_Ship_Titan::BeginPlay()
{
	Super::BeginPlay();

    Au_Tit->Play();

}

void AX_Master_Ship_Titan::Recibir_Danio(float Danio)
{
	Life -= Danio;

    if (Life <= 0)
    {

        Au_Tit->Stop();
    }
}

void AX_Master_Ship_Titan::Disparo_Nave(float DeltaTime)
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
            const float DisparoOffset = 5600.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
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
                    Proyectil->ProjectileMovement->InitialSpeed = 10000.f;
                    Proyectil->ProjectileMovement->MaxSpeed = 10000.f;
                }
            }
            break;

            case 1:
                // Disparo triple en abanico con zigzag
                for (int i = -1; i <= 1; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 20.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    AdjustedLocation.X += (i % 2 == 0) ? 200.0f : -200.0f; // Zigzag en X
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->SetHomingTarget(PY);
                        Proyectil->ProjectileMovement->InitialSpeed = 12000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 12000.f;
                    }
                }
                break;

            case 2:
                // Disparo en espiral con variación de altura
                for (int i = 0; i < 12; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 30.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    AdjustedLocation.Z += FMath::Sin(FMath::DegreesToRadians(i * 30.0f)) * 200.0f; // Variación en altura sinusoidal
                    ACB_Ice_Sword* Proyectil = World->SpawnActor<ACB_Ice_Sword>(ACB_Ice_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->SetHomingTarget(PY);
                        Proyectil->ProjectileMovement->InitialSpeed = 8000.f + FMath::Sin(i * 30.0f) * 4000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 8000.f + FMath::Sin(i * 30.0f) * 4000.f;
                    }
                }
                break;

            case 3:
                // Disparo en abanico con variación de velocidad
                for (int i = 0; i < 5; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += (i - 2) * 15.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * (DisparoOffset + i * 100.0f);
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->SetHomingTarget(PY);
                        Proyectil->ProjectileMovement->InitialSpeed = 15000.f - i * 2000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 15000.f - i * 2000.f;
                    }
                }
                break;

            case 4:
                // Disparo que se divide en múltiples proyectiles
            {
                ACB_Space_Sword* Proyectil = World->SpawnActor<ACB_Space_Sword>(ACB_Space_Sword::StaticClass(), SpawnLocation, FireRotation);
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
            DisparoActual = (DisparoActual + 1) % 5;

            // Reproducir el sonido del disparo
            UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
        }
    }
}

void AX_Master_Ship_Titan::Movimiento_Nave(float DeltaTime)
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




