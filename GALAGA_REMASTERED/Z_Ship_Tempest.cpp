// Fill out your copyright notice in the Description page of Project Settings.


#include "Z_Ship_Tempest.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Basic_Laser.h"



AZ_Ship_Tempest::AZ_Ship_Tempest()
{
	PrimaryActorTick.bCanEverTick = true;
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/tru/textures/tempes.tempes'"));
	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
	}

	//|*| COMPONENTE DE PARTICULA DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MFK/Particles/Umbrella/Par_FW_Umbr_02_Rain.Par_FW_Umbr_02_Rain'"));

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


	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Nuke/NukeMissle_CartoonyShoot.NukeMissle_CartoonyShoot'"));
	if (AssetShotSound.Succeeded())
	{
		Shot_Sound = Cast<USoundBase>(AssetShotSound.Object);
	}
	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(Nave_Mesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/VFXSeries1/Particles/Tails/P_Plasmatrail01.P_Plasmatrail01'"));
	if (ParticleAsset2.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset2.Object);
		Proye->bAutoActivate = true;
		Proye->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));			
	}
	

	//|*| COMPONENTE DE COLISION DE LA NAVE |*|
	
	Colision_Nave->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	Colision_Nave->SetupAttachment(Nave_Mesh);


	DistanciaRecorrida = 0.0f;
	Velocidad_Nave = 20000.0f;
	DistanciaMovimiento = 8000.0f;
	IntervaloCambioDireccion = 20.0f;  // Cada 20 segundos
	IntervaloGiroAleatorio = 7.0f;  // Cada 8 segundos
	bPersiguiendoPawn = false;
	bPlayerDetected = false;
	FireRate = 1.5f; // Ajusta la tasa de disparo
	TimeSinceLastShot = 0.0f;
}


void AZ_Ship_Tempest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Life <= 0)
	{
		Componente_Destruccion();
	}
}

void AZ_Ship_Tempest::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_CambioDireccion, this, &AZ_Ship_Tempest::GirarNaveAleatorio, IntervaloCambioDireccion, true);
	GetWorldTimerManager().SetTimer(TimerHandle_GiroAleatorio, this, &AZ_Ship_Tempest::GirarLigeramente, IntervaloGiroAleatorio, true);
}


void AZ_Ship_Tempest::Recibir_Danio(float Danio)
{
	Super::Recibir_Danio(Danio);
}

void AZ_Ship_Tempest::Disparo_Nave(UWorld* World, FVector Location, FRotator Rotation)
{
	if (World != nullptr)
	{
		// Obtener la posición y la rotación actuales de la nave enemiga
		FVector EnemyLocation = GetActorLocation() + 500;
		FRotator EnemyRotation = GetActorRotation();

		// Obtener la posición del jugador (suponiendo que el jugador es de tipo APawn)
		if (Player)
		{
			FVector PlayerLocation = Player->GetActorLocation();

			// Calcular la dirección del disparo hacia el jugador
			FVector DisparoDirection = (PlayerLocation - EnemyLocation).GetSafeNormal();
			FRotator FireRotation = DisparoDirection.Rotation();

			// Configurar la distancia de disparo directamente en la función
			const float DisparoOffset = 4600.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
			FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

			// Spawn del proyectil
			AC_Basic_Laser* Proyectil = World->SpawnActor<AC_Basic_Laser>(AC_Basic_Laser::StaticClass(), SpawnLocation, FireRotation);

			// Reproducir el sonido del disparo
			UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
		}
	}

}


