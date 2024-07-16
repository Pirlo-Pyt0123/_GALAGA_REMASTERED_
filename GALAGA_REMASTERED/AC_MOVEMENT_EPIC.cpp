#include "AC_MOVEMENT_EPIC.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"

// Sets default values for this component's properties
UAC_MOVEMENT_EPIC::UAC_MOVEMENT_EPIC()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // Initialize variables
    PlayerPawn = nullptr;
    CurrentMovementType = 0; // Default movement type
}

// Called when the game starts
void UAC_MOVEMENT_EPIC::BeginPlay()
{
    Super::BeginPlay();

    // Get reference to player pawn
    PlayerPawn = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void UAC_MOVEMENT_EPIC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

   
}

FVector UAC_MOVEMENT_EPIC::GetPlayerLocation() const
{
    if (PlayerPawn)
    {
        return PlayerPawn->GetActorLocation();
    }
    return FVector::ZeroVector;
}

void UAC_MOVEMENT_EPIC::MoveActor(const FVector& NewLocation)
{
    if (AActor* Owner = GetOwner())
    {
        Owner->SetActorLocation(NewLocation);
    }
}

void UAC_MOVEMENT_EPIC::MoveTowardsPlayer(float DeltaTime)
{
	// move at a constant speed towards the player
    if (!PlayerPawn) return;

    // Define movement parameters
    float Speed = 500.0f;  // Speed of the Galactus (adjust as needed for a very large ship)

    // Get the current position of the player
    FVector PlayerPosition = GetPlayerLocation();

    // Get the current position of the Galactus
    FVector CurrentPosition = GetOwner()->GetActorLocation();

    // Calculate the direction vector towards the player
    FVector DirectionToPlayer = (PlayerPosition - CurrentPosition).GetSafeNormal();

    // Calculate the new position
    FVector NewPosition = CurrentPosition + (DirectionToPlayer * Speed * DeltaTime);

    // Set the new position
    MoveActor(NewPosition);

    // Make the Galactus face the player
    FRotator NewRotation = (PlayerPosition - NewPosition).Rotation();
    GetOwner()->SetActorRotation(NewRotation);
}

void UAC_MOVEMENT_EPIC::ZigzagMovement(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Define movement parameters
    float BaseSpeed = 2.0f;  // Base speed of the Galactus
    float ZigzagAmplitude = 8000.0f;  // Amplitude of the zigzag movement
    float ZigzagFrequency = 10.0f;  // Frequency of the zigzag movement

    // Get the current position of the player
    FVector PlayerPosition = GetPlayerLocation();

    // Get the current position of the Galactus
    FVector CurrentPosition = GetOwner()->GetActorLocation();

    // Calculate the direction vector towards the player
    FVector DirectionToPlayer = (PlayerPosition - CurrentPosition).GetSafeNormal();

    // Calculate the zigzag offset
    float Time = GetWorld()->GetTimeSeconds();
    FVector ZigzagOffset = FVector(
        ZigzagAmplitude * FMath::Sin(ZigzagFrequency * Time),
        ZigzagAmplitude * FMath::Cos(ZigzagFrequency * Time),
        0.0f
    );

    // Calculate the new position
    FVector NewPosition = CurrentPosition + (DirectionToPlayer * BaseSpeed * DeltaTime) + ZigzagOffset * DeltaTime;

    // Set the new position
    MoveActor(NewPosition);

    // Make the Galactus face the player
    FRotator NewRotation = (PlayerPosition - NewPosition).Rotation();
    GetOwner()->SetActorRotation(NewRotation);
}

void UAC_MOVEMENT_EPIC::CircularMovement(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Define movement parameters
    float OrbitRadius = 20000.0f;  // Radius of the circular movement
    float OrbitSpeed = 1.0f;    // Speed of the orbit movement

    // Get the current position of the player
    FVector PlayerPosition = GetPlayerLocation();

    // Calculate the current angle based on time
    float Time = GetWorld()->GetTimeSeconds();
    float Angle = OrbitSpeed * Time;

    // Calculate the new position in circular orbit
    FVector NewPosition = PlayerPosition + OrbitRadius * FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.0f);

    // Set the new position
    MoveActor(NewPosition);

    // Make the Galactus face the player
    FRotator NewRotation = (PlayerPosition - NewPosition).Rotation();
    GetOwner()->SetActorRotation(NewRotation);
}

void UAC_MOVEMENT_EPIC::SpiralMovement(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Define movement parameters
    float InitialRadius = 20000.0f;  // Initial radius of the spiral
    float SpiralSpeed = 0.1f;     // Speed at which the radius changes
    float RotationSpeed = 1.0f;  // Speed of the spiral rotation

    // Get the current position of the player
    FVector PlayerPosition = GetPlayerLocation();

    // Calculate the current time
    float Time = GetWorld()->GetTimeSeconds();

    // Calculate the current radius based on time
    float CurrentRadius = InitialRadius + SpiralSpeed * Time;

    // Calculate the angle of rotation
    float Angle = RotationSpeed * Time;

    // Calculate the new position in spiral orbit
    FVector NewPosition = PlayerPosition + CurrentRadius * FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.0f);

    // Set the new position
    MoveActor(NewPosition);

    // Make the Galactus face the player
    FRotator NewRotation = (PlayerPosition - NewPosition).Rotation();
    GetOwner()->SetActorRotation(NewRotation);
}

void UAC_MOVEMENT_EPIC::ArcMovement(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Define movement parameters
    float ArcRadius = 20000.0f;     // Radius of the arc
    float ArcSpeed = 1.0f;      // Speed of the arc movement
    float ArcHeight = 600.0f;     // Height of the arc movement

    // Get the current position of the player
    FVector PlayerPosition = GetPlayerLocation();

    // Calculate the current angle based on time
    float Time = GetWorld()->GetTimeSeconds();
    float Angle = ArcSpeed * Time;

    // Calculate the new position in arc movement
    FVector NewPosition = PlayerPosition + ArcRadius * FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0.0f);
    NewPosition.Z += ArcHeight * FMath::Sin(Angle / 2.0f); // Adjust the Z coordinate for arc height

    // Set the new position
    MoveActor(NewPosition);

    // Make the Galactus face the player
    FRotator NewRotation = (PlayerPosition - NewPosition).Rotation();
    GetOwner()->SetActorRotation(NewRotation);
}

void UAC_MOVEMENT_EPIC::SpecialMovement(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Define movement parameters
    float BaseSpeed = 2.0f;  // Base speed
    float ArcFrequency = 0.5f;  // Frequency of the arc movement
    float ArcAmplitude = 5000.0f;  // Amplitude of the arc movement
    float SweepFrequency = 0.3f;  // Frequency of the sweeping movement
    float SweepAmplitude = 700.0f;  // Amplitude of the sweeping movement
    float RotationSpeed = 5.0f;  // Speed of rotation

    // Get the current position
    FVector CurrentPosition = GetOwner()->GetActorLocation();

    // Calculate the time variable
    float Time = GetWorld()->GetTimeSeconds();

    // Calculate arc movement
    float ArcX = ArcAmplitude * FMath::Sin(ArcFrequency * Time);
    float ArcY = ArcAmplitude * FMath::Cos(ArcFrequency * Time);

    // Calculate sweeping movement
    float SweepX = SweepAmplitude * FMath::Sin(SweepFrequency * Time);

    // Combine all movements
    FVector CombinedMovement = FVector(ArcX + SweepX, ArcY, 0.0f) * DeltaTime * BaseSpeed;

    // Calculate the new position
    FVector NewPosition = CurrentPosition + CombinedMovement;

    // Set the new position
    MoveActor(NewPosition);

    // Apply a dramatic rotation to enhance the large-scale movement effect
    FRotator CurrentRotation = GetOwner()->GetActorRotation();
    FRotator NewRotation = CurrentRotation.Add(0.0f, RotationSpeed * DeltaTime, 0.0f);
    GetOwner()->SetActorRotation(NewRotation);
}

void UAC_MOVEMENT_EPIC::MovimientoMoribundo(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Define movement parameters
    float BaseSpeed = 4.0f;  // Base speed for erratic movement
    float Frequency = 20.0f;  // Frequency of erratic changes
    float Amplitude = 200.0f;  // Amplitude of erratic changes
    float RotationSpeed = 6.0f;  // Speed of erratic rotation

    // Get the current position of the Galactus
    FVector CurrentPosition = GetOwner()->GetActorLocation();

    // Calculate the erratic offset based on sine waves
    float Time = GetWorld()->GetTimeSeconds();
    FVector ErraticOffset = FVector(
        FMath::FRandRange(-1.0f, 1.0f) * Amplitude * FMath::Sin(Frequency * Time),
        FMath::FRandRange(-1.0f, 1.0f) * Amplitude * FMath::Cos(Frequency * Time),
        FMath::FRandRange(-1.0f, 1.0f) * Amplitude * FMath::Sin(Frequency * Time)
    );

    // Calculate the new position
    FVector NewPosition = CurrentPosition + ErraticOffset * DeltaTime * BaseSpeed;

    // Set the new position
    MoveActor(NewPosition);

    // Apply an erratic rotation to enhance the effect
    FRotator CurrentRotation = GetOwner()->GetActorRotation();
    FRotator NewRotation = CurrentRotation.Add(FMath::FRandRange(-1.0f, 1.0f) * RotationSpeed * DeltaTime, FMath::FRandRange(-1.0f, 1.0f) * RotationSpeed * DeltaTime, FMath::FRandRange(-1.0f, 1.0f) * RotationSpeed * DeltaTime);
    GetOwner()->SetActorRotation(NewRotation);
}

void UAC_MOVEMENT_EPIC::RandomDriftMovement(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Define movement parameters
    float DriftSpeed = 300.0f;  // Speed of the drift movement
    float DriftAmplitude = 500.0f;  // Amplitude of the drift movement

    // Get the current position
    FVector CurrentPosition = GetOwner()->GetActorLocation();

    // Calculate the random drift offsets
    FVector DriftOffset = FVector(
        FMath::FRandRange(-DriftAmplitude, DriftAmplitude),
        FMath::FRandRange(-DriftAmplitude, DriftAmplitude),
        FMath::FRandRange(-DriftAmplitude, DriftAmplitude)
    );

    // Calculate the new position
    FVector NewPosition = CurrentPosition + (DriftOffset * DeltaTime * DriftSpeed);

    // Set the new position
    MoveActor(NewPosition);
}

void UAC_MOVEMENT_EPIC::SpiralDescentMovement(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Define movement parameters
    float DescentSpeed = 200.0f;  // Speed of the descent
    float SpiralRadius = 1000.0f;  // Radius of the spiral
    float SpiralFrequency = 1.0f;  // Frequency of the spiral

    // Get the current position
    FVector CurrentPosition = GetOwner()->GetActorLocation();

    // Calculate the time variable
    float Time = GetWorld()->GetTimeSeconds();

    // Calculate the spiral offsets
    float SpiralX = SpiralRadius * FMath::Cos(SpiralFrequency * Time);
    float SpiralY = SpiralRadius * FMath::Sin(SpiralFrequency * Time);
    float DescentZ = -DescentSpeed * Time;

    // Calculate the new position
    FVector NewPosition = CurrentPosition + FVector(SpiralX, SpiralY, DescentZ) * DeltaTime;

    // Set the new position
    MoveActor(NewPosition);
}

void UAC_MOVEMENT_EPIC::MovimientoDeLazo(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Definir parámetros de movimiento
    float AmplitudLazo = 4000.0f;  // Amplitud del lazo
    float FrecuenciaLazo = 1.0f;  // Frecuencia del lazo

    // Obtener la posición actual
    FVector PosicionActual = GetOwner()->GetActorLocation();

    // Calcular la variable de tiempo
    float Tiempo = GetWorld()->GetTimeSeconds();

    // Calcular los desplazamientos del lazo
    float DesplazamientoX = AmplitudLazo * FMath::Sin(FrecuenciaLazo * Tiempo);
    float DesplazamientoY = AmplitudLazo * FMath::Sin(FrecuenciaLazo * Tiempo) * FMath::Cos(FrecuenciaLazo * Tiempo);

    // Calcular la nueva posición
    FVector NuevaPosicion = PosicionActual + FVector(DesplazamientoX, DesplazamientoY, 0.0f) * DeltaTime;

    // Establecer la nueva posición
    MoveActor(NuevaPosicion);
}

void UAC_MOVEMENT_EPIC::MovimientoFiguraOcho(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Definir parámetros de movimiento
    float AmplitudFiguraOcho = 1000.0f;  // Amplitud de la figura ocho
    float FrecuenciaFiguraOcho = 1.0f;  // Frecuencia de la figura ocho

    // Obtener la posición actual
    FVector PosicionActual = GetOwner()->GetActorLocation();

    // Calcular la variable de tiempo
    float Tiempo = GetWorld()->GetTimeSeconds();

    // Calcular los desplazamientos de la figura ocho
    float DesplazamientoX = AmplitudFiguraOcho * FMath::Sin(FrecuenciaFiguraOcho * Tiempo);
    float DesplazamientoY = AmplitudFiguraOcho * FMath::Sin(FrecuenciaFiguraOcho * Tiempo) * FMath::Cos(FrecuenciaFiguraOcho * Tiempo) * FMath::Sin(FrecuenciaFiguraOcho * Tiempo);

    // Calcular la nueva posición
    FVector NuevaPosicion = PosicionActual + FVector(DesplazamientoX, DesplazamientoY, 0.0f) * DeltaTime;

    // Establecer la nueva posición
    MoveActor(NuevaPosicion);
}

void UAC_MOVEMENT_EPIC::MovimientoDeRebote(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Definir parámetros de movimiento
    float VelocidadRebote = 20.0f;  // Velocidad del rebote
    float AmplitudRebote = 6000.0f;  // Amplitud del rebote
    float FrecuenciaRebote = 2.0f;  // Frecuencia del rebote

    // Obtener la posición actual
    FVector PosicionActual = GetOwner()->GetActorLocation();

    // Calcular la variable de tiempo
    float Tiempo = GetWorld()->GetTimeSeconds();

    // Calcular los desplazamientos del rebote
    float DesplazamientoX = AmplitudRebote * FMath::Abs(FMath::Sin(FrecuenciaRebote * Tiempo));
    float DesplazamientoY = AmplitudRebote * FMath::Abs(FMath::Cos(FrecuenciaRebote * Tiempo));

    // Calcular la nueva posición
    FVector NuevaPosicion = PosicionActual + FVector(DesplazamientoX, DesplazamientoY, 0.0f) * DeltaTime;

    // Establecer la nueva posición
    MoveActor(NuevaPosicion);
}

void UAC_MOVEMENT_EPIC::MovimientoDeSerpiente(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Definir parámetros de movimiento
    float VelocidadSerpiente = 10.0f;  // Velocidad de la serpiente
    float AmplitudSerpiente = 400.0f;  // Amplitud del movimiento de serpiente
    float FrecuenciaSerpiente = 2.0f;  // Frecuencia del movimiento de serpiente

    // Obtener la posición actual
    FVector PosicionActual = GetOwner()->GetActorLocation();

    // Calcular la variable de tiempo
    float Tiempo = GetWorld()->GetTimeSeconds();

    // Calcular los desplazamientos del movimiento de serpiente
    float DesplazamientoX = AmplitudSerpiente * FMath::Sin(FrecuenciaSerpiente * Tiempo);
    float DesplazamientoY = AmplitudSerpiente * FMath::Sin(FrecuenciaSerpiente * Tiempo + PI / 2);

    // Calcular la nueva posición
    FVector NuevaPosicion = PosicionActual + FVector(DesplazamientoX, DesplazamientoY, 0.0f) + FVector(VelocidadSerpiente * DeltaTime, 0.0f, 0.0f);

    // Establecer la nueva posición
    MoveActor(NuevaPosicion);
}

void UAC_MOVEMENT_EPIC::MovimientoDeTornado(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Definir parámetros de movimiento
    float VelocidadAscenso = 10.0f;  // Velocidad de ascenso
    float RadioTornado = 2000.0f;  // Radio del tornado
    float FrecuenciaTornado = 2.0f;  // Frecuencia de rotación del tornado

    // Obtener la posición actual
    FVector PosicionActual = GetOwner()->GetActorLocation();

    // Calcular la variable de tiempo
    float Tiempo = GetWorld()->GetTimeSeconds();

    // Calcular los desplazamientos del tornado
    float DesplazamientoX = RadioTornado * FMath::Cos(FrecuenciaTornado * Tiempo);
    float DesplazamientoY = RadioTornado * FMath::Sin(FrecuenciaTornado * Tiempo);
    float DesplazamientoZ = VelocidadAscenso * Tiempo;

    // Calcular la nueva posición
    FVector NuevaPosicion = PosicionActual + FVector(DesplazamientoX, DesplazamientoY, DesplazamientoZ) * DeltaTime;

    // Establecer la nueva posición
    MoveActor(NuevaPosicion);
}

void UAC_MOVEMENT_EPIC::MovimientoEspiralExpansiva(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Definir parámetros de movimiento
    float RadioInicial = 3000.0f;
    float VelocidadExpansion = 100.0f;
    float VelocidadRotacion = 2.0f;

    // Obtener la posición del jugador
    FVector PosicionJugador = GetPlayerLocation();

    // Calcular el tiempo actual
    float Tiempo = GetWorld()->GetTimeSeconds();

    // Calcular el radio actual basado en el tiempo
    float RadioActual = RadioInicial + VelocidadExpansion * Tiempo;

    // Calcular el ángulo de rotación
    float Angulo = VelocidadRotacion * Tiempo;

    // Calcular la nueva posición en espiral expansiva
    FVector NuevaPosicion = PosicionJugador + RadioActual * FVector(FMath::Cos(Angulo), FMath::Sin(Angulo), 0.0f);

    // Establecer la nueva posición
    MoveActor(NuevaPosicion);

    // Hacer que la nave mire hacia el jugador
    FRotator NuevaRotacion = (PosicionJugador - NuevaPosicion).Rotation();
    GetOwner()->SetActorRotation(NuevaRotacion);
}

void UAC_MOVEMENT_EPIC::MovimientoDeReboteTridimensional(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Definir parámetros de movimiento
    float VelocidadRebote = 200.0f;  // Velocidad de rebote

    // Obtener la posición actual y los límites del área de juego
    FVector PosicionActual = GetOwner()->GetActorLocation();
    FVector Limites = FVector(10000.0f, 10000.0f, 10000.0f);  // Limites del área de juego

    // Calcular la nueva posición
    FVector NuevaPosicion = PosicionActual + VelocidadRebote * DeltaTime * FVector(FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(-1.0f, 1.0f), FMath::FRandRange(-1.0f, 1.0f));

    // Chequear si la nave está fuera de los límites y revertir la dirección si es necesario
    if (NuevaPosicion.X > Limites.X || NuevaPosicion.X < -Limites.X)
        VelocidadRebote *= -1;
    if (NuevaPosicion.Y > Limites.Y || NuevaPosicion.Y < -Limites.Y)
        VelocidadRebote *= -1;
    if (NuevaPosicion.Z > Limites.Z || NuevaPosicion.Z < -Limites.Z)
        VelocidadRebote *= -1;

    // Establecer la nueva posición
    MoveActor(NuevaPosicion);
}

void UAC_MOVEMENT_EPIC::MovimientoDePulso(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Definir parámetros de movimiento
    float VelocidadBase = 20.0f;  // Velocidad base
    float AmplitudPulso = 500.0f;  // Amplitud del pulso
    float FrecuenciaPulso = 2.0f;  // Frecuencia del pulso

    // Obtener la posición actual
    FVector PosicionActual = GetOwner()->GetActorLocation();

    // Calcular la variable de tiempo
    float Tiempo = GetWorld()->GetTimeSeconds();

    // Calcular el desplazamiento del pulso
    float Desplazamiento = AmplitudPulso * FMath::Sin(FrecuenciaPulso * Tiempo);

    // Calcular la nueva posición
    FVector NuevaPosicion = PosicionActual + FVector(Desplazamiento, Desplazamiento, Desplazamiento) * DeltaTime * VelocidadBase;

    // Establecer la nueva posición
    MoveActor(NuevaPosicion);
}

void UAC_MOVEMENT_EPIC::MovimientoElipse3D(float DeltaTime)
{
    if (!PlayerPawn) return;

    // Definir parámetros de movimiento
    float VelocidadBase = 20.0f;
    float AmplitudX = 2000.0f;
    float AmplitudY = 1000.0f;
    float AmplitudZ = 3000.0f;
    float FrecuenciaElipse = 5.0f;

    // Obtener la posición actual de la nave
    FVector PosicionActual = GetOwner()->GetActorLocation();

    // Calcular el tiempo actual
    float Tiempo = GetWorld()->GetTimeSeconds();

    // Calcular el offset de elipse tridimensional
    FVector ElipseOffset = FVector(
        AmplitudX * FMath::Sin(FrecuenciaElipse * Tiempo),
        AmplitudY * FMath::Cos(FrecuenciaElipse * Tiempo),
        AmplitudZ * FMath::Sin(FrecuenciaElipse * Tiempo + PI / 2)
    );

    // Calcular la nueva posición
    FVector NuevaPosicion = PosicionActual + ElipseOffset * DeltaTime * VelocidadBase;

    // Establecer la nueva posición
    MoveActor(NuevaPosicion);

    // Hacer que la nave mire hacia el jugador
    FVector PosicionJugador = GetPlayerLocation();
    FRotator NuevaRotacion = (PosicionJugador - NuevaPosicion).Rotation();
    GetOwner()->SetActorRotation(NuevaRotacion);
}

