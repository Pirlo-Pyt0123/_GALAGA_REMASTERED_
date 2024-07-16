// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Obstacle_Cometa.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Projectile.h"

AH_Obstacle_Cometa::AH_Obstacle_Cometa()
{
	PrimaryActorTick.bCanEverTick = true;


	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/CF2Shuttle/Meshes/Asteroids/SM_Asteroid_B.SM_Asteroid_B'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
		MeshComponent->SetWorldScale3D(FVector(40.f, 40.f, 40.f));
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/Explotion_Asteroide.Explotion_Asteroide'"));
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

	Identificador_Object = "Obstacle_Cometa";
}

void AH_Obstacle_Cometa::BeginPlay()
{
	Super::BeginPlay();
}

void AH_Obstacle_Cometa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AH_Obstacle_Cometa::NotifyActorBeginOverlap(AActor* OtherActor)
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
