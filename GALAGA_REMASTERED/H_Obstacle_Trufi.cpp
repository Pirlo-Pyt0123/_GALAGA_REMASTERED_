// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Obstacle_Trufi.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Projectile.h"



AH_Obstacle_Trufi::AH_Obstacle_Trufi()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/trufi/Soviet_flying_car_-_Bukhanka_10-_.Soviet_flying_car_-_Bukhanka_10-_'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);

		MeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Nova/NovaMissle_PoisonExplosion.NovaMissle_PoisonExplosion'"));
	if (SoundAsset.Succeeded())
	{
		SoundComponent = SoundAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset111(TEXT("ParticleSystem'/Game/MFK/Particles/Expanders/Par_ExpFire_01_Rain.Par_ExpFire_01_Rain'"));
	if (ParticleAsset111.Succeeded())
	{
		ParticleSystem = ParticleAsset111.Object;
	}

	CollisionComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	Identificador_Object = "Obstacle_Trufi";
}

void AH_Obstacle_Trufi::BeginPlay()
{
	Super::BeginPlay();
}

void AH_Obstacle_Trufi::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}

void AH_Obstacle_Trufi::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AGALAGA_REMASTEREDPawn* Player = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);
	if (Player)
	{
		Componente_Destruccion();
	}

	AC_Projectile* Projectile = Cast<AC_Projectile>(OtherActor);

	if (Projectile)
	{
		Projectile->Destroy();
		Componente_Destruccion();
	}
}
