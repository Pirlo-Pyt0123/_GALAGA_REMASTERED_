#include "Z_Ship_Bomber.h"
#include "Sound/SoundBase.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Misil_Nuclear.h"

AZ_Ship_Bomber::AZ_Ship_Bomber()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Mehes/NavesEnemigas/Spaceships_4.Spaceships_4'"));
	if (MeshAsset.Succeeded())
	{
		Nave_Mesh->SetStaticMesh(MeshAsset.Object);
		Nave_Mesh->SetWorldScale3D(FVector(23.5f, 28.5f, 18.5f));
	}

	//|*| COMPONENTE DE PARTICULA DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MFK/Particles/Expanders/Halfs/Par_ExpFire_02_H_Rain.Par_ExpFire_02_H_Rain'"));
	if (ParticleAsset.Succeeded())
	{
		Explosion_Nave = Cast<UParticleSystem> (ParticleAsset.Object);
	}

	//|*| COMPONENTE DE SONIDO DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion02.Explosion02'"));
	if (AssetExplosionSound.Succeeded())
	{
		Sonido_Nave = Cast<USoundBase>(AssetExplosionSound.Object);
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Laser/LaserMissle_Cartoony_Shoot.LaserMissle_Cartoony_Shoot'"));
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
		Proye->SetWorldScale3D(FVector(4.5f, 4.5f, 4.5f));

		Proye->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		Proye->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));

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

void AZ_Ship_Bomber::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_CambioDireccion, this, &AZ_Ship_Bomber::GirarNaveAleatorio, IntervaloCambioDireccion, true);
	GetWorldTimerManager().SetTimer(TimerHandle_GiroAleatorio, this, &AZ_Ship_Bomber::GirarLigeramente, IntervaloGiroAleatorio, true);
}

void AZ_Ship_Bomber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Life <= 0)
	{
		Componente_Destruccion();
	}
}

void AZ_Ship_Bomber::Recibir_Danio(float Danio)
{
	Super::Recibir_Danio(Danio);
}

void AZ_Ship_Bomber::Disparo_Nave(UWorld* World, FVector Location, FRotator Rotation)
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
			const float DisparoOffset = 5500.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
			FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

			// Spawn del proyectil
			AC_Misil_Nuclear* Proyectil = World->SpawnActor<AC_Misil_Nuclear>(AC_Misil_Nuclear::StaticClass(), SpawnLocation, FireRotation);

			// Reproducir el sonido del disparo
			UGameplayStatics::PlaySoundAtLocation(World, Shot_Sound, GetActorLocation());
		}
	}
}

void AZ_Ship_Bomber::Movimiento_Nave(float DeltaTime)
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
