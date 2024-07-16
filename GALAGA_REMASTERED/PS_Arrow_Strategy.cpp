#include "PS_Arrow_Strategy.h"
#include "Kismet/GameplayStatics.h"
#include "CJ_Celestial_Arrow.h"

APS_Arrow_Strategy::APS_Arrow_Strategy()
{
    PrimaryActorTick.bCanEverTick = false;
}

void APS_Arrow_Strategy::ShotFire(FVector LocationPlayer, bool WeaponPower)
{
	if (WeaponPower == false)
	{
		const FRotator FireRotation = myPlayerPawn->GetActorRotation();

		const FVector SpawnLocation = LocationPlayer + FireRotation.RotateVector(FVector(2000, 0, -100));

		UWorld* const World = GetWorld();
		// engendrando la bala
		if (World != nullptr) {
			ACJ_Celestial_Arrow* Projectil1 = World->SpawnActor<ACJ_Celestial_Arrow>(SpawnLocation, FireRotation);
			Projectil1->SetActorRotation(FRotator(FireRotation.Pitch, FireRotation.Yaw,180));

		}

	}
}

void APS_Arrow_Strategy::BeginPlay()
{
    Super::BeginPlay();

	myPlayerPawn = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void APS_Arrow_Strategy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APS_Arrow_Strategy::SetPlayerPawn(AGALAGA_REMASTEREDPawn* NewPlayerPawn)
{
	myPlayerPawn = NewPlayerPawn;
}
