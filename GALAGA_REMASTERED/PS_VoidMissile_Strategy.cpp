// Fill out your copyright notice in the Description page of Project Settings.


#include "PS_VoidMissile_Strategy.h"
#include "Kismet/GameplayStatics.h"
#include "CJ_Void_Missile.h"



APS_VoidMissile_Strategy::APS_VoidMissile_Strategy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APS_VoidMissile_Strategy::ShotFire(FVector LocationPlayer, bool WeaponPower)
{

    UWorld* const World = GetWorld();

    if (WeaponPower == false)
    {
        const FRotator FireRotation = myPlayerPawn->GetActorRotation();
        const FVector SpawnLocation = LocationPlayer + FireRotation.RotateVector(FVector(3000, 0, -100));

        // Engendrando la bala
        if (World != nullptr)
        {
            World->SpawnActor<ACJ_Void_Missile>(SpawnLocation, FireRotation);
        }
    }
    
}


void APS_VoidMissile_Strategy::BeginPlay()
{
	Super::BeginPlay();

	myPlayerPawn = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void APS_VoidMissile_Strategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APS_VoidMissile_Strategy::SetPlayerPawn(AGALAGA_REMASTEREDPawn* NewPlayerPawn)
{
    myPlayerPawn = NewPlayerPawn;
}