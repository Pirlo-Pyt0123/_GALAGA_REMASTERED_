// Fill out your copyright notice in the Description page of Project Settings.


#include "PS_VoidEcho_Sgy.h"
#include "Kismet/GameplayStatics.h"
#include "CJ_Void_Echo.h"


APS_VoidEcho_Sgy::APS_VoidEcho_Sgy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APS_VoidEcho_Sgy::ShotFire(FVector LocationPlayer, bool WeaponPower)
{
	if (WeaponPower == false)
	{
		const FRotator FireRotation = myPlayerPawn->GetActorRotation();



		const FVector SpawnLocation = LocationPlayer + FireRotation.RotateVector(FVector(2500, 0, -100));

		UWorld* const World = GetWorld();
		// engendrando la bala
		if (World != nullptr)
			World->SpawnActor<ACJ_Void_Echo>(SpawnLocation, FireRotation);
	}

	// si la arma esta potenciada dispara tres balas y tambien si tenemos municiones
	if (WeaponPower == true) {
		// ubicacion y rotacion de una de las tres bala (arriba)
		const FVector FireDirection1 = FVector(1.f, 0.2f, 0.f);
		const FRotator FireRotation1 = FireDirection1.Rotation();
		const FVector SpawnLocation1 = LocationPlayer + FireRotation1.RotateVector(FVector(40.f, 20.f, 0.f));

		// ubicacion y rotacion de una de las tres bala (medio)
		const FVector FireDirection2 = FVector(1.f, 0.f, 0.f);
		const FRotator FireRotation2 = FireDirection2.Rotation();
		const FVector SpawnLocation2 = LocationPlayer + FireRotation2.RotateVector(FVector(40.f, 0.f, 0.f));

		// ubicacion y rotacion de una de las tres bala (abajo)
		const FVector FireDirection3 = FVector(1.f, -0.2f, 0.f);
		const FRotator FireRotation3 = FireDirection3.Rotation();
		const FVector SpawnLocation3 = LocationPlayer + FireRotation3.RotateVector(FVector(40.f, -20.f, 0.f));

		// engendrando las balas
		UWorld* const World = GetWorld();
		if (World != nullptr) {
			World->SpawnActor<ACJ_Void_Echo>(SpawnLocation1, FireRotation1);
			World->SpawnActor<ACJ_Void_Echo>(SpawnLocation2, FireRotation2);
			World->SpawnActor<ACJ_Void_Echo>(SpawnLocation3, FireRotation3);
		}
	}
}

void APS_VoidEcho_Sgy::SetPlayerPawn(AGALAGA_REMASTEREDPawn* NewPlayerPawn)
{
	myPlayerPawn = NewPlayerPawn;
}

void APS_VoidEcho_Sgy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APS_VoidEcho_Sgy::BeginPlay()
{
	Super::BeginPlay();

	myPlayerPawn = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}
