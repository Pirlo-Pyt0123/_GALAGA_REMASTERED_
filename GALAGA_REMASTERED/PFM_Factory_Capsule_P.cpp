#include "PFM_Factory_Capsule_P.h"
#include "G_Capsule_Life.h"
#include "G_Capsule_Health_Half.h"
#include "G_Capsule_Invulnerabilidad.h"
#include "G_Capsule_Health_Total.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AInteractable_Objects_P* APFM_Factory_Capsule_P::Create_Interactable_Object(FString Identificador)
{
    FVector MinSpawnLocation = FVector(-400000.0f, -400000.0f, -400000.0f);
    FVector MaxSpawnLocation = FVector(400000.0f, 400000.0f, 400000.0f);
    float MinDistanceBetweenCapsules = 2500.0f; // Ajustar este valor según sea necesario

    FVector SpawnLocation;
    FRotator Rotation = FRotator(0.f, 0.f, 0.f);

    bool bFoundValidLocation = false;

    for (int32 Attempt = 0; Attempt < 100; ++Attempt)
    {
        SpawnLocation = FVector(
            FMath::RandRange(MinSpawnLocation.X, MaxSpawnLocation.X),
            FMath::RandRange(MinSpawnLocation.Y, MaxSpawnLocation.Y),
            FMath::RandRange(MinSpawnLocation.Z, MaxSpawnLocation.Z)
        );

        bool bIsValidLocation = true;
        for (const FVector& Location : SpawnedLocations)
        {
            if (FVector::Dist(Location, SpawnLocation) < MinDistanceBetweenCapsules)
            {
                bIsValidLocation = false;
                break;
            }
        }

        if (bIsValidLocation)
        {
            bFoundValidLocation = true;
            break;
        }
    }

    if (!bFoundValidLocation)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find a valid spawn location for capsule"));
        return nullptr;
    }

    AInteractable_Objects_P* SpawnedObject = nullptr;

    if (Identificador.Equals("Capsule_Health_Half"))
        SpawnedObject = GetWorld()->SpawnActor<AG_Capsule_Health_Half>(AG_Capsule_Health_Half::StaticClass(), SpawnLocation, Rotation);

    if (Identificador.Equals("Capsule_Health_Total"))
        SpawnedObject = GetWorld()->SpawnActor<AG_Capsule_Health_Total>(AG_Capsule_Health_Total::StaticClass(), SpawnLocation, Rotation);

    if (Identificador.Equals("Capsule_Invulnerabilidad"))
        SpawnedObject = GetWorld()->SpawnActor<AG_Capsule_Invulnerabilidad>(AG_Capsule_Invulnerabilidad::StaticClass(), SpawnLocation, Rotation);

    if (Identificador.Equals("Capsule_Life"))
        SpawnedObject = GetWorld()->SpawnActor<AG_Capsule_Life>(AG_Capsule_Life::StaticClass(), SpawnLocation, Rotation);

    if (SpawnedObject)
    {
        SpawnedLocations.Add(SpawnLocation);
    }

    return SpawnedObject;
}
