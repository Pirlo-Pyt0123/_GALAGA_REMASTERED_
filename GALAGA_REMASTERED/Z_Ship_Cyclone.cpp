// Fill out your copyright notice in the Description page of Project Settings.


#include "Z_Ship_Cyclone.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Fire_Ball.h"

AZ_Ship_Cyclone::AZ_Ship_Cyclone()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/red/source/Final.Final'"));
	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(30.5f, 25.5f, 25.5f));
	}
	
	//|*| COMPONENTE DE PARTICULA DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MFK/Particles_Tiny/Palms/Par_FW_Palm_01_Rain_Tiny.Par_FW_Palm_01_Rain_Tiny'"));

	if (ParticleAsset.Succeeded())
	{
		Explosion_Nave = Cast<UParticleSystem>(ParticleAsset.Object);
	}

	//|*| COMPONENTE DE SONIDO DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Mystic/MysticMissle_FireExplosion.MysticMissle_FireExplosion'"));
	if (AssetExplosionSound.Succeeded())
	{
		Sonido_Nave = Cast<USoundBase>(AssetExplosionSound.Object);
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Bullet/BulletSmall_Cartoony_Explosion.BulletSmall_Cartoony_Explosion'"));
	if (AssetShotSound.Succeeded())
	{
		Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
	}

	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(Nave_Mesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MegaSci-FiParticleFXBundle3in1/Particles/P_WeldingTrail.P_WeldingTrail'"));
	if (ParticleAsset2.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset2.Object);
		Proye->bAutoActivate = true;
		Proye->SetWorldScale3D(FVector(2.5f, 2.5f, 2.5f));
		Proye->SetRelativeLocation(FVector(0.f, -70.f, 0.f));


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

void AZ_Ship_Cyclone::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_CambioDireccion, this, &AZ_Ship_Cyclone::GirarNaveAleatorio, IntervaloCambioDireccion, true);
	GetWorldTimerManager().SetTimer(TimerHandle_GiroAleatorio, this, &AZ_Ship_Cyclone::GirarLigeramente, IntervaloGiroAleatorio, true);
}

void AZ_Ship_Cyclone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Life <= 0) 
	{
		Componente_Destruccion();
	}

}

void AZ_Ship_Cyclone::Recibir_Danio(float Danio)
{
	Life -= Danio;
}

void AZ_Ship_Cyclone::Disparo_Nave(UWorld* World, FVector Location, FRotator Rotation)
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
			const float DisparoOffset = 400.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
			FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

			// Spawn del proyectil
			AC_Fire_Ball* Proyectil = World->SpawnActor<AC_Fire_Ball>(AC_Fire_Ball::StaticClass(), SpawnLocation, FireRotation);

			// Reproducir el sonido del disparo
			UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
		}
	}
}


