// Fill out your copyright notice in the Description page of Project Settings.


#include "K_Portal_Quantum.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"



AK_Portal_Quantum::AK_Portal_Quantum()
{
    PrimaryActorTick.bCanEverTick = true;
    // Set the mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAssetAA(TEXT("StaticMesh'/Game/BETA_NIAGARAS/FINAL_PMESH/Portal/SM_Portal_Inner.SM_Portal_Inner'"));
    if (MeshAssetAA.Succeeded())
    {
        Mesh_Portal->SetStaticMesh(MeshAssetAA.Object);
        Mesh_Portal->SetWorldScale3D(FVector(20.5f, 20.5f, 20.5f));
		Mesh_Portal->SetVisibility(false);
    }

	Niagara_Qu = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Qu"));
	Niagara_Qu->SetupAttachment(RootComponent);
        
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> ParticleAssetbb(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/NS_Quantun.NS_Quantun'"));
	if (ParticleAssetbb.Succeeded())
	{

		Niagara_Qu->SetAsset(ParticleAssetbb.Object);
		Niagara_Qu->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
		Niagara_Qu->SetWorldScale3D(FVector(4.0f, 4.0f,4.0f));

    }

    static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSDD(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion02.Explosion02'"));
    if (AssetExplosionSDD.Succeeded())
    {
        Sound_Portal = AssetExplosionSDD.Object;
    }

    Collision_Portal->SetBoxExtent(FVector(150.f, 150.f, 150.f));
}

void AK_Portal_Quantum::BeginPlay()
{
	Super::BeginPlay();
}

void AK_Portal_Quantum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
