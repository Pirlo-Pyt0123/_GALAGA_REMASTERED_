// Fill out your copyright notice in the Description page of Project Settings.


#include "G_Capsule_Life.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "GALAGA_REMASTEREDPawn.h"


AG_Capsule_Life::AG_Capsule_Life()
{
	PrimaryActorTick.bCanEverTick = true;

	Identificador_Object = "Capsule_Life";

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);

		//0 visibilidad
		MeshComponent->SetVisibility(false);
		// Escala de la malla
		MeshComponent->SetWorldScale3D(FVector(7.5f, 7.5f, 7.5f));
	}
	


	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/VE_PowerUps/Particles/Capsule/LIfe/PS_04_Y_HeartSpawn.PS_04_Y_HeartSpawn'"));
	if (ParticleAsset.Succeeded())
	{
		ParticleComponent->SetTemplate(ParticleAsset.Object);
		ParticleComponent->bAutoActivate = true;
		ParticleComponent->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
	}
	CollisionComponent->SetBoxExtent(FVector(150.0f, 150.0f, 150.0f));

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("SoundWave'/Game/GoodFXLevelUp/SFX/Sound_Wave/A_GFXLU_WAV_UI07.A_GFXLU_WAV_UI07'"));
	if (SoundAsset.Succeeded())
	{
		SoundComponent = SoundAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset111(TEXT("ParticleSystem'/Game/GoodFXLevelUp/FX/Particles/PS_GFXLU_Heal.PS_GFXLU_Heal'"));
	if (ParticleAsset111.Succeeded())
	{
		ParticleSystem = ParticleAsset111.Object;
		
	}
}

void AG_Capsule_Life::BeginPlay()
{
	Super::BeginPlay();

}

void AG_Capsule_Life::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AG_Capsule_Life::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AGALAGA_REMASTEREDPawn* Player = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);
	if (Player)
	{
		Componente_Destruccion();

	}
}
