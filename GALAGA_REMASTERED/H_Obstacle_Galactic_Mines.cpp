// Fill out your copyright notice in the Description page of Project Settings.


#include "H_Obstacle_Galactic_Mines.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "C_Projectile.h"

AH_Obstacle_Galactic_Mines::AH_Obstacle_Galactic_Mines()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/shield/source/capsuleHHH.capsuleHHH'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);
		MeshComponent->SetWorldScale3D(FVector(600.f, 600.f, 600.f));
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
	CollisionComponent->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	Identificador_Object = "Obstacle_Galactic_Mines";

    ExplosionRadius = 500.0f;  // Set your desired explosion radius here
    ExplosionDamage = 2000.0f;  // Set your desired explosion damage here
}

void AH_Obstacle_Galactic_Mines::BeginPlay()
{
	Super::BeginPlay();
}

void AH_Obstacle_Galactic_Mines::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AH_Obstacle_Galactic_Mines::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    AGALAGA_REMASTEREDPawn* Player = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);
    AC_Projectile* Projectile = Cast<AC_Projectile>(OtherActor);

    if (Player || Projectile)
    {
        // Start the timer for the explosion
        //GetWorld()->GetTimerManager().SetTimer(ExplosionTimerHandle, this, &AH_Obstacle_Galactic_Mines::Explode, 3.0f, false);

        Componente_Destruccion();
        //if (Projectile)
        //{
        //    Projectile->Destroy();
        //}
    }
}

void AH_Obstacle_Galactic_Mines::Explode()
{
    // Apply damage to actors within the explosion radius
    TArray<AActor*> OverlappedActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGALAGA_REMASTEREDPawn::StaticClass(), OverlappedActors);

    for (AActor* Actor : OverlappedActors)
    {
        if (FVector::Dist(Actor->GetActorLocation(), GetActorLocation()) <= ExplosionRadius)
        {
            UGameplayStatics::ApplyDamage(Actor, ExplosionDamage, nullptr, this, nullptr);
        }
    }

    // Destroy the mine
    Componente_Destruccion();
}