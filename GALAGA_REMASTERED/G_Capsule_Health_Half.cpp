// Fill out your copyright notice in the Description page of Project Settings.


#include "G_Capsule_Health_Half.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "GALAGA_REMASTEREDPawn.h"


AG_Capsule_Health_Half::AG_Capsule_Health_Half()
{
	PrimaryActorTick.bCanEverTick = true;

	Identificador_Object = "Capsule_Health_Half";

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshAsset.Object);

		MeshComponent->SetVisibility(false);

		MeshComponent->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
	}
	// particulas 
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/VE_PowerUps/Particles/Capsule/Health/PS_05_R_GoldBar.PS_05_R_GoldBar'"));
	if (ParticleAsset.Succeeded())
	{
		ParticleComponent->SetTemplate(ParticleAsset.Object);
		ParticleComponent->bAutoActivate = true;
		ParticleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		ParticleComponent->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
	}
	CollisionComponent->SetBoxExtent(FVector(350.0f, 350.0f, 350.0f));

	static ConstructorHelpers::FObjectFinder<USoundBase> SoundAsset(TEXT("SoundWave'/Game/GoodFXLevelUp/SFX/Sound_Wave/A_GFXLU_HEALHolyshortrelief_by_BOOMLibrary_.A_GFXLU_HEALHolyshortrelief_by_BOOMLibrary_'"));
	if (SoundAsset.Succeeded())
	{
		SoundComponent = SoundAsset.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset111(TEXT("ParticleSystem'/Game/GoodFXLevelUp/FX/Particles/PS_GFXLU_Wind.PS_GFXLU_Wind'"));
	if (ParticleAsset111.Succeeded())
	{
		ParticleSystem = ParticleAsset111.Object;
	}
}

void AG_Capsule_Health_Half::BeginPlay()
{
	Super::BeginPlay();
}

void AG_Capsule_Health_Half::Tick(float Deltatime)
{
	Super::Tick(Deltatime);
}

void AG_Capsule_Health_Half::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AGALAGA_REMASTEREDPawn* Player = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);
	if (Player)
	{
		Componente_Destruccion();
	}
}
