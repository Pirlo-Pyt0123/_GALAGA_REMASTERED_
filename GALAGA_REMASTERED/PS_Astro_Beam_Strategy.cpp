// Fill out your copyright notice in the Description page of Project Settings.


#include "PS_Astro_Beam_Strategy.h"
#include "Kismet/GameplayStatics.h"
#include "CJ_Astro_Bean.h"




APS_Astro_Beam_Strategy::APS_Astro_Beam_Strategy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APS_Astro_Beam_Strategy::ShotFire(FVector LocationPlayer, bool WeaponPower)
{
	if (WeaponPower == false)
	{
		const FRotator FireRotation = myPlayerPawn->GetActorRotation();
		


		const FVector SpawnLocation = LocationPlayer + FireRotation.RotateVector(FVector(2800, 0, -800));

		UWorld* const World = GetWorld();
		// engendrando la bala
		if (World != nullptr)
			World->SpawnActor<ACJ_Astro_Bean>(SpawnLocation, FireRotation);
	}

	
}

void APS_Astro_Beam_Strategy::BeginPlay()
{
	Super::BeginPlay();

	myPlayerPawn = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void APS_Astro_Beam_Strategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APS_Astro_Beam_Strategy::SetPlayerPawn(AGALAGA_REMASTEREDPawn* NewPlayerPawn)
{
	myPlayerPawn = NewPlayerPawn;
}