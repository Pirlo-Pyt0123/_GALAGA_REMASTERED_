// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Obstacle_Desechos.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Projectile.h"


AH_Obstacle_Desechos::AH_Obstacle_Desechos()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);

		
		MeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
		MeshComponent->SetWorldScale3D(FVector(35.5f, 35.5f, 35.5f));
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

	CollisionComponent->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));

	Identificador_Object = "Obstacle_Desechos";
	
}

void AH_Obstacle_Desechos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveObstacle(DeltaTime);
}

void AH_Obstacle_Desechos::BeginPlay()
{
	Super::BeginPlay();
}

void AH_Obstacle_Desechos::MoveObstacle(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * DeltaTime * 100.0f;
	SetActorLocation(NewLocation);
}

void AH_Obstacle_Desechos::NotifyActorBeginOverlap(AActor* OtherActor)
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
