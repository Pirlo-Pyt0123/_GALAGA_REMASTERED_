#include "Z_Enemy_Ship_P.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GALAGA_REMASTEREDPawn.h"

// Sets default values
AZ_Enemy_Ship_P::AZ_Enemy_Ship_P()
{
    PrimaryActorTick.bCanEverTick = true;

    Nave_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Nave_Mesh"));
    Nave_Mesh->SetupAttachment(RootComponent);

    Colision_Nave = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision_Nave"));
    Colision_Nave->SetupAttachment(Nave_Mesh);
    Colision_Nave->SetBoxExtent(FVector(150.0f, 150.0f, 150.0f));

 
    // Para el sonido de colision
    static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/Colision_Nave_N.Colision_Nave_N'"));
    if (AssetExplosionSound.Succeeded())
	{
        Colision_sound = Cast<USoundBase>(AssetExplosionSound.Object);
	}

    FireRate = 3.5f; // Ajusta la tasa de disparo
    TimeSinceLastShot = 0.0f;
    Life = 6000.0f; // Ajusta la vida de la nave
    LimiteMovimiento = 120000.f;
}

// Called when the game starts or when spawned
void AZ_Enemy_Ship_P::BeginPlay()
{
    Super::BeginPlay();

    // Obtener al jugador
    Player = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AZ_Enemy_Ship_P::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Life <= 0)
    {
        Componente_Destruccion();
    }

    DetectarPawn();

    if (bPersiguiendoPawn)
    {
        PerseguirPawn(DeltaTime);

        // Manejar el disparo
        TimeSinceLastShot += DeltaTime;
        if (TimeSinceLastShot >= FireRate)
        {
            TimeSinceLastShot = 0.0f;

            FVector Location = GetActorLocation();
            FRotator Rotation = GetActorRotation();

            Disparo_Nave(GetWorld(), Location, Rotation);
        }
    }
    else
    {
        Movimiento_Nave(DeltaTime);
        GetWorldTimerManager().SetTimer(TimerHandle_GiroAleatorio, this, &AZ_Enemy_Ship_P::GirarLigeramente, IntervaloGiroAleatorio, true);
    }
}

void AZ_Enemy_Ship_P::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AZ_Enemy_Ship_P::Recibir_Danio(float Danio)
{
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), Colision_sound, GetActorLocation());
    Life -= Danio;
}

void AZ_Enemy_Ship_P::Disparo_Nave(UWorld* World, FVector Location, FRotator Rotation)
{
    // Dejar esta función vacía para ser implementada por las clases hijas
}


void AZ_Enemy_Ship_P::Movimiento_Nave(float DeltaTime)
{
    // Movimiento siempre en la dirección de GetActorRightVector
    FVector ForwardDirection = GetActorRightVector();
    float DistanceToMove = Velocidad_Nave * DeltaTime;

    if (DistanciaRecorrida + DistanceToMove > DistanciaMovimiento)
    {
        DistanceToMove = DistanciaMovimiento - DistanciaRecorrida;
    }

    FVector NewLocation = GetActorLocation() + (ForwardDirection * DistanceToMove);
    SetActorLocation(NewLocation);

    DistanciaRecorrida += DistanceToMove;

    if (DistanciaRecorrida >= DistanciaMovimiento)
    {
        // Resetear la distancia recorrida
        DistanciaRecorrida = 0.0f;
    }

    VerificarLimitesYRebotar();
}

void AZ_Enemy_Ship_P::Componente_Destruccion()
{
    // Reproducir el sonido de la nave
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sonido_Nave, GetActorLocation());
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion_Nave, GetActorLocation(), GetActorRotation());
    
	Destroy();
}

void AZ_Enemy_Ship_P::PerseguirPawn(float DeltaTime)
{
    AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        FVector Direction = (PlayerPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        FVector NewLocation = GetActorLocation() + (GetActorRightVector() * Velocidad_Nave * DeltaTime);
        FVector GodPower = Direction + NewLocation;
        SetActorLocation(GodPower);

        FRotator NewRotation = Direction.Rotation();
        SetActorRotation(NewRotation);
    }
}

void AZ_Enemy_Ship_P::DetectarPawn()
{
    AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        FVector DistanceToPawn = PlayerPawn->GetActorLocation() - GetActorLocation();

        if (DistanceToPawn.Size() <= 70000.0f)  // Detecta al pawn en un radio de 70000 unidades
        {

            bPersiguiendoPawn = true;
            bPlayerDetected = true; // Marca que el jugador ha sido detectado
            GetWorldTimerManager().SetTimer(TimerHandle_PerseguirPawn, this, &AZ_Enemy_Ship_P::DejarDePerseguir, 15.0f, false);
        }
    }
}

void AZ_Enemy_Ship_P::DejarDePerseguir()
{

    bPersiguiendoPawn = false;
    bPlayerDetected = false; // Marca que el jugador ya no está detectado
}

void AZ_Enemy_Ship_P::GirarNaveAleatorio()
{
    // Lista de ángulos posibles
    TArray<float> Angulos = { 20.0f, 35.0f, 45.0f, 60.0f, 90.0f, 120.0f, 150.0f, 180.0f, 210.0f, 240.0f, 270.0f, 300.0f, 330.0f, 360.0f };

    // Seleccionar un ángulo aleatorio de la lista
    float AnguloAleatorio = Angulos[FMath::RandRange(0, Angulos.Num() - 1)];

    // Elegir aleatoriamente un eje para girar
    int32 RandomAxis = FMath::RandRange(0, 2);
    FRotator NewRotation = GetActorRotation();
    switch (RandomAxis)
    {
    case 0:  // Girar en el eje X
        NewRotation.Pitch += AnguloAleatorio;
        break;
    case 1:  // Girar en el eje Y
        NewRotation.Yaw += AnguloAleatorio;
        break;
    case 2:  // Girar en el eje Z
        NewRotation.Roll += AnguloAleatorio;
        break;
    }
    SetActorRotation(NewRotation);
}

void AZ_Enemy_Ship_P::GirarLigeramente()
{
    // Lista de ángulos posibles
    TArray<float> Angulos = { 20.0f, 35.0f, 45.0f, 60.0f, 90.0f, 120.0f, 150.0f, 180.0f, 210.0f, 240.0f, 270.0f, 300.0f, 330.0f, 360.0f };

    // Seleccionar un ángulo aleatorio de la lista
    float AnguloAleatorio = Angulos[FMath::RandRange(0, Angulos.Num() - 1)];

    // Elegir aleatoriamente un eje para girar
    int32 RandomAxis = FMath::RandRange(0, 2);
    FRotator NewRotation = GetActorRotation();
    switch (RandomAxis)
    {
    case 0:  // Girar en el eje X
        NewRotation.Pitch += AnguloAleatorio;
        break;
    case 1:  // Girar en el eje Y
        NewRotation.Yaw += AnguloAleatorio;
        break;
    case 2:  // Girar en el eje Z
        NewRotation.Roll += AnguloAleatorio;
        break;
    }
    SetActorRotation(NewRotation);
}

void AZ_Enemy_Ship_P::VerificarLimitesYRebotar()
{
    FVector Location = GetActorLocation();
    bool Rebotar = false;

    if (FMath::Abs(Location.X) > LimiteMovimiento)
    {
        Location.X = FMath::Clamp(Location.X, -LimiteMovimiento, LimiteMovimiento);
        Rebotar = true;
    }

    if (FMath::Abs(Location.Y) > LimiteMovimiento)
    {
        Location.Y = FMath::Clamp(Location.Y, -LimiteMovimiento, LimiteMovimiento);
        Rebotar = true;
    }

    if (FMath::Abs(Location.Z) > LimiteMovimiento)
    {
        Location.Z = FMath::Clamp(Location.Z, -LimiteMovimiento, LimiteMovimiento);
        Rebotar = true;
    }

    if (Rebotar)
    {
        SetActorLocation(Location);
        GirarNaveAleatorio();  // Girar la nave en un ángulo aleatorio y en uno de los ejes aleatoriamente
    }
}
