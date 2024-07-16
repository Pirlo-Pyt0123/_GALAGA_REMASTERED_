// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Obstacle_Satelite.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Projectile.h"

AH_Obstacle_Satelite::AH_Obstacle_Satelite()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/destroy/source/Building3.Building3'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
		MeshComponent->SetWorldScale3D(FVector(4.5f, 4.5f, 3.5f));

	}


	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MagicCombatAudio/Death/SuperEvilDeathExplosionOnly.SuperEvilDeathExplosionOnly'"));
	if (SoundAsset.Succeeded())
	{
		SoundComponent = SoundAsset.Object;
	}


	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset111(TEXT("ParticleSystem'/Game/MFK/Particles/Expanders/Par_ExpFire_02_Rain.Par_ExpFire_02_Rain'"));
	if (ParticleAsset111.Succeeded())
	{
		ParticleSystem = ParticleAsset111.Object;
	}

	CollisionComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	Identificador_Object = "Obstacle_Satelite";
}

void AH_Obstacle_Satelite::BeginPlay()
{
	Super::BeginPlay();
}

void AH_Obstacle_Satelite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AH_Obstacle_Satelite::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AGALAGA_REMASTEREDPawn* Player = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);

	if (Player)
	{
		// Call the function to interact with the object
		Componente_Destruccion();
	}

	AC_Projectile* Projectile = Cast<AC_Projectile>(OtherActor);

	if (Projectile)
	{
		// Call the function to interact with the object
		Componente_Destruccion();
		Projectile->Destroy();
	}
}
