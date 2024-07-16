// Fill out your copyright notice in the Description page of Project Settings.


#include "K_Portal_Black_Hole.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


AK_Portal_Black_Hole::AK_Portal_Black_Hole()
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

	Niagara_Portal = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara_Portal")); 
	Niagara_Portal->SetupAttachment(Mesh_Portal);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> ParticleAssetbb(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/NS_Vortex.NS_Vortex'"));
	if (ParticleAssetbb.Succeeded())
	{
		Niagara_Portal->SetAsset(ParticleAssetbb.Object);
		Niagara_Portal->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
		Niagara_Portal->SetWorldScale3D(FVector(4.0f, 4.0f, 4.0f));
	}
  


    static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSDD(TEXT("SoundWave'/Game/StarterContent/Audio/Explosion02.Explosion02'"));
    if (AssetExplosionSDD.Succeeded())
    {
        Sound_Portal = AssetExplosionSDD.Object;
    }

    Collision_Portal->SetBoxExtent(FVector(150.f, 150.f, 150.f));

}

void AK_Portal_Black_Hole::BeginPlay()
{
	Super::BeginPlay();
}

void AK_Portal_Black_Hole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
