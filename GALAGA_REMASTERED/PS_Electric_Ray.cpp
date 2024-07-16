// Fill out your copyright notice in the Description page of Project Settings.


#include "PS_Electric_Ray.h"
#include "Kismet/GameplayStatics.h"
#include "CJ_Galactic_Ray.h"



APS_Electric_Ray::APS_Electric_Ray()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APS_Electric_Ray::ShotFire(FVector LocationPlayer, bool WeaponPower)
{
	if (WeaponPower == false)
	{
		const FRotator FireRotation = myPlayerPawn->GetActorRotation();

		const FVector SpawnLocation = LocationPlayer + FireRotation.RotateVector(FVector(2700, 0, -300));

		UWorld* const World = GetWorld();
		// engendrando la bala
		if (World != nullptr)
			World->SpawnActor<ACJ_Galactic_Ray>(SpawnLocation, FireRotation);
	}

	
}

void APS_Electric_Ray::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APS_Electric_Ray::BeginPlay()
{
	Super::BeginPlay();

	myPlayerPawn = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void APS_Electric_Ray::SetPlayerPawn(AGALAGA_REMASTEREDPawn* NewPlayerPawn)
{
	myPlayerPawn = NewPlayerPawn;
}
