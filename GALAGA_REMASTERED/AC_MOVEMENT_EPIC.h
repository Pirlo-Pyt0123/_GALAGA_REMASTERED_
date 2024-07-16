#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_MOVEMENT_EPIC.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GALAGA_REMASTERED_API UAC_MOVEMENT_EPIC : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UAC_MOVEMENT_EPIC();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Referencia al jugador
    class AGALAGA_REMASTEREDPawn* PlayerPawn;

    // Movimiento rectilíneo hacia el jugador
    void MoveTowardsPlayer(float DeltaTime);

    void ZigzagMovement(float DeltaTime);

    void CircularMovement(float DeltaTime);

    void SpiralMovement(float DeltaTime);

    void ArcMovement(float DeltaTime);

    void SpecialMovement(float DeltaTime);

    void MovimientoMoribundo(float DeltaTime);

	void RandomDriftMovement(float DeltaTime);

	void SpiralDescentMovement(float DeltaTime);

	void MovimientoDeLazo(float DeltaTime);

	void MovimientoFiguraOcho(float DeltaTime);

	void MovimientoDeRebote(float DeltaTime);

	void MovimientoDeSerpiente(float DeltaTime);

	void MovimientoDeTornado(float DeltaTime);

	void MovimientoEspiralExpansiva(float DeltaTime);

	void MovimientoDeReboteTridimensional(float DeltaTime);

	void MovimientoDePulso(float DeltaTime);

	void MovimientoElipse3D(float DeltaTime);

private:
    // Internal method to get the player's location
    FVector GetPlayerLocation() const;

    // Internal method to move the actor
    void MoveActor(const FVector& NewLocation);

    // Parameter to keep track of the current movement type (could be an enum or simple int)
    int CurrentMovementType;
};
