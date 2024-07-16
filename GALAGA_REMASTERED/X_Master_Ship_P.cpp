// Fill out your copyright notice in the Description page of Project Settings.


#include "X_Master_Ship_P.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "T_TerraBley_P.h"
#include "T_TerraBley_Void_Gem.h"
#include "T_TerraBley_Star_Shard.h"
#include "T_TerraBley_Nebula_Core.h"
#include "T_TerraBley_Eclipse_Gem.h"
#include "T_TerraBley_Cosmic_Seal.h"
#include "HUD_P_Principal.h"
#include "W_BAR_SHIP_BOSS_GGG.h"
#include "G_Capsule_Health_Total.h"
#include "G_Capsule_Health_Half.h"
#include "G_Capsule_Life.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"




// Sets default values
AX_Master_Ship_P::AX_Master_Ship_P()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Nave_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nave_Mesh"));

	Nave_Mesh->SetupAttachment(RootComponent);

	Colision_Nave = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision_Nave"));
	Colision_Nave->SetupAttachment(RootComponent);


	
	// Initialize the classes for TerraBleys
	TerraBleyClasses = { AT_TerraBley_Void_Gem::StaticClass(), AT_TerraBley_Star_Shard::StaticClass(), AT_TerraBley_Nebula_Core::StaticClass(), AT_TerraBley_Eclipse_Gem::StaticClass(), AT_TerraBley_Cosmic_Seal::StaticClass() };	


	// Initialize the classes for Capsules
	CapsuleClasses = { AG_Capsule_Health_Total::StaticClass(), AG_Capsule_Health_Half::StaticClass(), AG_Capsule_Life::StaticClass() };

	Move = CreateDefaultSubobject<UAC_MOVEMENT_EPIC>(TEXT("Move"));


	TiempoTotal = 0.0f;
	IntervaloActual = 5.0f;  // Duración de cada intervalo en segundos
	MovimientoActual = 0;

	DisparoActual = 0;
	Tiempo_Disparo = 0.0f;
	IntervaloActual_Disparo = 5.0f;  // Duración de cada intervalo en segundos




}

// Called when the game starts or when spawned
void AX_Master_Ship_P::BeginPlay()
{
	Super::BeginPlay();

	PY = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	HUD->ShowBossHealthBar();

	if (HUD && HUD->GameStartedWidget)
	{
		BossHealthBarWidget = Cast<UW_BAR_SHIP_BOSS_GGG>(HUD->BossHealthBarWidget);
		if (BossHealthBarWidget)
		{
			UpdateHealthBar();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("BossHealthBarWidget is not initialized correctly"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HUD or BossHealthBarWidget is not initialized"));
	}
}

// Called every frame
void AX_Master_Ship_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Life <= 0)
	{
		Componente_Destruccion();
	}
	else if (Life > 0)
	{
		UpdateHealthBar();
	}
}



void AX_Master_Ship_P::Componente_Destruccion()
{
	// Reproducir el sonido de la nave
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sonido_Nave, GetActorLocation());

	
	// Destruir la nave
	this->Destroy();

	Generate_TerraBley();
	Generate_Capsules();

	if (HUD && HUD->BossHealthBarWidget)
	{
		HUD->HideBossHealthBar();
	}
	
}

void AX_Master_Ship_P::Recibir_Danio(float Danio)
{
	Life -= Danio;
	if (Life < 0) Life = 0;
	UpdateHealthBar();
	

}

void AX_Master_Ship_P::Disparo_Nave(float DeltaTime)
{
	
}

void AX_Master_Ship_P::Movimiento_Nave(float DeltaTime)
{
	
}

void AX_Master_Ship_P::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AGALAGA_REMASTEREDPawn* Jugador = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);

	if (Jugador)
	{
		Recibir_Danio(1000.f);
		
	}
}

void AX_Master_Ship_P::Generate_Capsules()
{
	int32 NumberOfCapsules = FMath::RandRange(1, 3); // Generate 1 to 3 capsules

	for (int32 i = 0; i < NumberOfCapsules; ++i)
	{
		if (CapsuleClasses.Num() > 0)
		{
			int32 Index = FMath::RandRange(0, CapsuleClasses.Num() - 1);
			TSubclassOf<AActor> SelectedClass = CapsuleClasses[Index];

			// Spawn the capsule
			AActor* Capsule = GetWorld()->SpawnActor<AActor>(SelectedClass, GetActorLocation(), FRotator::ZeroRotator);
			if (Capsule)
			{
				// Add an impulse to the capsule to spread it out
				UPrimitiveComponent* CapsuleComponent = Cast<UPrimitiveComponent>(Capsule->GetRootComponent());
				if (CapsuleComponent)
				{
					FVector ImpulseDirection = FMath::VRand().GetSafeNormal(); // Random direction
					float ImpulseStrength = 500.0f; // Adjust as needed
					CapsuleComponent->AddImpulse(ImpulseDirection * ImpulseStrength, NAME_None, true);
				}
			}
		}
	}
}

void AX_Master_Ship_P::Generate_TerraBley()
{
	if (TerraBleyClasses.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, TerraBleyClasses.Num() - 1);
		TSubclassOf<AT_TerraBley_P> SelectedClass = TerraBleyClasses[Index];

		FString ClassName = SelectedClass->GetName();

		TerraBleyClasses.RemoveAt(Index);  // Remove the class from the list

		GetWorld()->SpawnActor<AT_TerraBley_P>(SelectedClass, GetActorLocation(), FRotator::ZeroRotator);
	}
}

void AX_Master_Ship_P::UpdateHealthBar()
{
	if (HUD && HUD->BossHealthBarWidget)
	{
		BossHealthBarWidget = Cast<UW_BAR_SHIP_BOSS_GGG>(HUD->BossHealthBarWidget);
		if (BossHealthBarWidget)
		{
			float HealthPercentage = Life / MaxHealth;
			FString HealthString = FString::Printf(TEXT("%.0f"), Life);
			BossHealthBarWidget->UpdateHealthBar(HealthPercentage, HealthString);
		}
	}
}

