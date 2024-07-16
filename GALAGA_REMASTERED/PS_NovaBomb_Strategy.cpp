// Fill out your copyright notice in the Description page of Project Settings.


#include "PS_NovaBomb_Strategy.h"
#include "CJ_Nova_Pulse.h"
#include "Kismet/GameplayStatics.h"


APS_NovaBomb_Strategy::APS_NovaBomb_Strategy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APS_NovaBomb_Strategy::ShotFire(FVector LocationPlayer, bool WeaponPower)
{
    // Obtener la rotación actual del jugador
    const FRotator FireRotation = myPlayerPawn->GetActorRotation();

    if (!WeaponPower)
    {
        // Calcular la ubicación de aparición basándose en la rotación del jugador
        const FVector SpawnLocation = LocationPlayer + FireRotation.RotateVector(FVector(2800, 0, -100));

        UWorld* const World = GetWorld();
        // Engendrar la bala
        if (World != nullptr)
        {
            ACJ_Nova_Pulse* NovaPulse = World->SpawnActor<ACJ_Nova_Pulse>(SpawnLocation, FireRotation);
            if (NovaPulse)
            {
                FVector InitialDirection = FireRotation.Vector();
                NovaPulse->UpdateProjectileDirection(InitialDirection);
            }
        }
    }
   
}

void APS_NovaBomb_Strategy::SetPlayerPawn(AGALAGA_REMASTEREDPawn* NewPlayerPawn)
{
    myPlayerPawn = NewPlayerPawn;
}

void APS_NovaBomb_Strategy::BeginPlay()
{
	Super::BeginPlay();

	myPlayerPawn = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void APS_NovaBomb_Strategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
