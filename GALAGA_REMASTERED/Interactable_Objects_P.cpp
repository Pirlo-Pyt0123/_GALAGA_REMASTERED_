// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Objects_P.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractable_Objects_P::AInteractable_Objects_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);


	// Create and attach the particle component
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(MeshComponent);

	

	// Create and attach the collision component
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(MeshComponent);

	//Para el componente de particula
	ParticleSystem = CreateDefaultSubobject<UParticleSystem>(TEXT("ParticleSystem"));


	// Para el componente de sonido
	SoundComponent = CreateDefaultSubobject<USoundBase>(TEXT("SoundComponent"));

}

// Called when the game starts or when spawned
void AInteractable_Objects_P::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractable_Objects_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractable_Objects_P::NotifyActorBeginOverlap(AActor* OtherActor)
{
}

void AInteractable_Objects_P::Componente_Destruccion()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundComponent, GetActorLocation());

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation(), FRotator::ZeroRotator, true);

	this->Destroy();
}

