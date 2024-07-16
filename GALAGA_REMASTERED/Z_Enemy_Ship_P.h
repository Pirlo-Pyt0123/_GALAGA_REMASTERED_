#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Z_Enemy_Ship_P.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AZ_Enemy_Ship_P : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AZ_Enemy_Ship_P();


    // ~~ Componente de Malla para la nave ~~
    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UStaticMeshComponent* Nave_Mesh;

    // ~~ Componente de Explosión ~~
    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UParticleSystem* Explosion_Nave;

    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UParticleSystemComponent* Proye;

    // ~~ Componente de Colisión: tipo caja ~~
    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UBoxComponent* Colision_Nave;

    // ~~ Componente de Sonido ~~
    UPROPERTY(EditAnywhere, Category = "Componentes")
    class USoundBase* Sonido_Nave;

    UPROPERTY(EditAnywhere, Category = "Componentes")
    class USoundBase* Shot_Sound;

    UPROPERTY(EditAnywhere, Category = "Componentes")
    class USoundBase* Colision_sound;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void Recibir_Danio(float Danio);

    // Función de disparo virtual pura para ser implementada por las clases hijas
    virtual void Disparo_Nave(UWorld* World, FVector Location, FRotator Rotation);

    virtual void Movimiento_Nave(float DeltaTime);

    virtual void Componente_Destruccion();

    virtual void PerseguirPawn(float DeltaTime);
    virtual void DetectarPawn();
    virtual void DejarDePerseguir();

    // Componentes adicionales y lógica de movimiento
    FTimerHandle TimerHandle_CambioDireccion;
    FTimerHandle TimerHandle_GiroAleatorio;
    FTimerHandle TimerHandle_PerseguirPawn;
    FTimerHandle TimerHandle_FireRate;


    float DistanciaRecorrida;
    float Velocidad_Nave;
    float DistanciaMovimiento;
    float IntervaloCambioDireccion;
    float LimiteMovimiento;
    float IntervaloGiroAleatorio;
    bool bPersiguiendoPawn;
    bool bPlayerDetected;

    float FireRate; // Tasa de disparo en segundos
    float TimeSinceLastShot; // Tiempo transcurrido desde el último disparo
    FVector LastKnownPlayerPosition;

    void GirarNaveAleatorio();
    void GirarLigeramente();
    void VerificarLimitesYRebotar();

    class AGALAGA_REMASTEREDPawn* Player;

    FString Identificador_Nave;
    float Speed;
    float Resistencia;
    float Tiempo_Disparo;
    float Tiempo_Disparo_Generar;
    FVector Distancia_Disparo;
    float Danio_Recibido;
    float Danio_Disparo;

    float Life;

    float Tiempo_M;
    float Distancia_D_CB;
    float Velocity;
    float Shot_Ship;

    FORCEINLINE void Set_Vida(float Vida_A) { Life = Vida_A; }

    FORCEINLINE void Set_Velocidad_Nave(float Velocidad_A) { Velocity = Velocidad_A; }

    FORCEINLINE void Set_Danio_Disparo(float Danio_A) { Danio_Disparo = Danio_A; }

private:
    int32 RangoPersecucion;

    bool bPositiveRotation;
};
