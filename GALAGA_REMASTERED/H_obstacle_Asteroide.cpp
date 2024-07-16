// Fill out your copyright notice in the Description page of Project Settings.


#include "H_obstacle_Asteroide.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Projectile.h"


AH_obstacle_Asteroide::AH_obstacle_Asteroide()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/CF2Shuttle/Meshes/Asteroids/SM_Asteroid_A_Particle.SM_Asteroid_A_Particle'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
		MeshComponent->SetWorldScale3D(FVector(42.f, 42.f, 42.f));
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/Explotion_Asteroide.Explotion_Asteroide'"));
	if (SoundAsset.Succeeded())
	{
		SoundComponent = SoundAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset111(TEXT("ParticleSystem'/Game/MFK/Particles_Tiny/Simple/Clusters/Par_FW_Simple_01_CL1_Tiny.Par_FW_Simple_01_CL1_Tiny'"));
	if (ParticleAsset111.Succeeded())
	{
		ParticleSystem = ParticleAsset111.Object;
	}
	
	CollisionComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	Identificador_Object = "Obstacle_Asteroide";
}

void AH_obstacle_Asteroide::BeginPlay()
{
	Super::BeginPlay();
}

void AH_obstacle_Asteroide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AH_obstacle_Asteroide::NotifyActorBeginOverlap(AActor* OtherActor)
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
		Projectile->Destroy();
		Componente_Destruccion();
	}
}
