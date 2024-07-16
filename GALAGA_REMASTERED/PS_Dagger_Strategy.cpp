#include "PS_Dagger_Strategy.h"
#include "CJ_Aurora_Dagger.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"

APS_Dagger_Strategy::APS_Dagger_Strategy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APS_Dagger_Strategy::ShotFire(FVector LocationPlayer, bool WeaponPower)
{
	if (myPlayerPawn)
	{
		const FRotator FireRotation = myPlayerPawn->GetActorRotation();
		const FVector SpawnLocation1 = LocationPlayer + FireRotation.RotateVector(FVector(2000,-2000,-100));
		const FVector SpawnLocation2 = LocationPlayer + FireRotation.RotateVector(FVector(2000, 2000, -100));

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			World->SpawnActor<ACJ_Aurora_Dagger>(SpawnLocation1, FireRotation);
			World->SpawnActor<ACJ_Aurora_Dagger>(SpawnLocation2, FireRotation);
		}

		
	}
}

void APS_Dagger_Strategy::BeginPlay()
{
	Super::BeginPlay();
	myPlayerPawn = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void APS_Dagger_Strategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APS_Dagger_Strategy::SetPlayerPawn(AGALAGA_REMASTEREDPawn* NewPlayerPawn)
{
	myPlayerPawn = NewPlayerPawn;
}