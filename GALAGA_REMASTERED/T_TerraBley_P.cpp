// Fill out your copyright notice in the Description page of Project Settings.


#include "T_TerraBley_P.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"

#include "Components/BoxComponent.h"
#include "GALAGA_REMASTEREDPawn.h"

#include "K_Portal_P.h"
#include "K_Portal_Celestial.h"
#include "K_Portal_Quantum.h"
#include "K_Portal_Black_Hole.h"
#include "K_Portal_SOLARE.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


// Sets default values
AT_TerraBley_P::AT_TerraBley_P()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh_TR = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("T-TERRA"));
	Mesh_TR->SetupAttachment(RootComponent);

	PPt = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PPt"));
	PPt->SetupAttachment(Mesh_TR);

	//Inicializa el componente de colision
	Colision_Terra = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision_Terra"));
	Colision_Terra->SetupAttachment(Mesh_TR);

	Particle_Pr = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle_Pr"));
	Particle_Pr->SetupAttachment(Mesh_TR);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/GoodFXLevelUp/FX/Particles/PS_GFXLU_galaxy.PS_GFXLU_Galaxy'"));
	if (ParticleAsset.Succeeded())
	{
		Particle_Pr-> SetTemplate(ParticleAsset.Object);
	}


	Expo = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Expo"));
	Expo->SetupAttachment(Mesh_TR);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/NiagaraExplosion01/Niagaras/Air/N_ExplosionAir_009.N_ExplosionAir_009'"));
	if (NiagaraAsset.Succeeded())
	{
		Expo->SetAsset(NiagaraAsset.Object);
		Expo->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		Expo->SetAutoActivate(true);
	}



	PortalClasses.Add(AK_Portal_Celestial::StaticClass());
	PortalClasses.Add(AK_Portal_Quantum::StaticClass());
	PortalClasses.Add(AK_Portal_Black_Hole::StaticClass());
	PortalClasses.Add(AK_Portal_SOLARE::StaticClass());
	//PortalClasses.Add(AK_Portal_Black_Hole::StaticClass());

	Colision_Terra->SetRelativeLocation(FVector(150.f, 150.f, 150.f));

}

void AT_TerraBley_P::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AT_TerraBley_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Configura la cantidad de rotación por segundo
	float RotationRate = 90.0f; // Grados por segundo
	FRotator NewRotation = FRotator(0.0f, RotationRate * DeltaTime, 0.0f);

	// Aplicar la rotación al objeto TerraBley
	AddActorLocalRotation(NewRotation);

}


void AT_TerraBley_P::NotifyActoBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AGALAGA_REMASTEREDPawn* Nave_Principal = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);

	if (Nave_Principal)
	{

		Componente_Desaparecer();
	}

}

void AT_TerraBley_P::Componente_Desaparecer()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sonido_Desaparicion_Terra, GetActorLocation());
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle_Pr->Template, GetActorLocation());

	this->Destroy();

	Generar_Portal();
}

void AT_TerraBley_P::Generar_Portal()
{

	if (PortalClasses.Num() > 0)
	{
		// Elegir un portal aleatorio de la lista de clases disponibles
		int32 Index = FMath::RandRange(0, PortalClasses.Num() - 1);
		TSubclassOf<AActor> SelectedClass = PortalClasses[Index];

		// Calcular nueva ubicación para el portal a 2500 unidades de distancia
		FVector Direction = GetActorForwardVector().GetSafeNormal(); // Normalizar el vector de dirección
		FVector NewLocation = GetActorLocation() + Direction * 9500.0f; // Calcula la nueva ubicación

		// Spawn the portal at the new location
		AActor* SpawnedPortal = GetWorld()->SpawnActor<AActor>(SelectedClass, NewLocation, FRotator::ZeroRotator);
	}
}