// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Obstacle_Station.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Projectile.h"

AH_Obstacle_Station::AH_Obstacle_Station()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Stylized_Crystals/Mesh/crystal_28_2.crystal_28_2'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
		MeshComponent->SetWorldScale3D(FVector(18.5f, 18.5f, 18.5f));
		MeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAssets(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Nova/NovaMissle_PoisonExplosion.NovaMissle_PoisonExplosion'"));
	if (SoundAssets.Succeeded())
	{
		SoundComponent = SoundAssets.Object;
	}


	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset111a(TEXT("ParticleSystem'/Game/MFK/Particles/Expanders/Par_ExpFire_01_Rain.Par_ExpFire_01_Rain'"));
	if (ParticleAsset111a.Succeeded())
	{
		ParticleSystem = ParticleAsset111a.Object;
	}
	CollisionComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	Identificador_Object = "Obstacle_Station";

}

void AH_Obstacle_Station::BeginPlay()
{
	Super::BeginPlay();
}

void AH_Obstacle_Station::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AH_Obstacle_Station::NotifyActorBeginOverlap(AActor* OtherActor)
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
