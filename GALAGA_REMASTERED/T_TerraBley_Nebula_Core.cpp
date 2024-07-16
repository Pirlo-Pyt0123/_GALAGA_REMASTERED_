// Fill out your copyright notice in the Description page of Project Settings.


#include "T_TerraBley_Nebula_Core.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AT_TerraBley_Nebula_Core::AT_TerraBley_Nebula_Core()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Stylized_Crystals/Mesh/crystal_37.crystal_37'"));
	if (MeshAsset.Succeeded())
	{
		Mesh_TR->SetStaticMesh(MeshAsset.Object);
		Mesh_TR->SetWorldScale3D(FVector(30.5f, 30.5f, 30.5f));
	}
	//simple particle system

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/VE_PowerUps/Particles/Particle_Terrabley.Particle_Terrabley'"));
	if (ParticleAsset.Succeeded())
	{
		PPt->SetTemplate(ParticleAsset.Object);
		PPt->SetWorldScale3D(FVector(6.5f, 6.5f, 0.5f));
	}

	//|*| COMPONENTE DE SONIDO DE LA NAVE |*|
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/GoodFXLevelUp/SFX/Sound_Wave/A_GFXLU_video-game-modern-game-play-element-spell-ice-prison.A_GFXLU_video-game-modern-game-play-element-spell-ice-prison'"));
	if (AssetExplosionSound.Succeeded())
	{
		Sonido_Aparicionn_Terra = Cast<USoundBase>(AssetExplosionSound.Object);
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSoundDesaparacion(TEXT("SoundWave'/Game/GoodFXLevelUp/SFX/Sound_Wave/Terrabley_Sco.Terrabley_Sco'"));
	if (AssetShotSoundDesaparacion.Succeeded())
	{
		Sonido_Desaparicion_Terra = Cast<USoundBase>(AssetShotSoundDesaparacion.Object);
	}

	Colision_Terra->SetRelativeLocation(FVector(450.f, 450.f, 450.f));

	Identificador_TerraBley = "Three";

}

void AT_TerraBley_Nebula_Core::BeginPlay()
{
	Super::BeginPlay();
}

void AT_TerraBley_Nebula_Core::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

