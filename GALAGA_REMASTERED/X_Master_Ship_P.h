// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "T_TerraBley_P.h"
#include "AC_MOVEMENT_EPIC.h"
#include "X_Master_Ship_P.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AX_Master_Ship_P : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AX_Master_Ship_P();

public:

    // Componentes Base para las Naves Enemigas

    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UStaticMeshComponent* Nave_Mesh;

    // ~~ Componente de Explosion ~~
    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UParticleSystemComponent* Explosion_Nave;

    // ~~ Componente de Colsion : tipo caja ~~
    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UBoxComponent* Colision_Nave;

    //capsule component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Colision")
    class UCapsuleComponent* Colli;

    // ~~ Componente de Sonido ~~
    UPROPERTY(EditAnywhere, Category = "Componentes")
    class USoundBase* Sonido_Nave;

    UPROPERTY(EditAnywhere, Category = "Componentes")
    class USoundBase* Shot_Sound;

    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UParticleSystemComponent* Proye;

	UPROPERTY(EditAnywhere, Category = "Componentes")
	class UParticleSystemComponent* Spawn;


    //componente de movimiento
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componentes")
    class UAC_MOVEMENT_EPIC* Move;

   



protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;


public:

    virtual void Componente_Destruccion();

    virtual void Recibir_Danio(float Danio);

    virtual void Disparo_Nave(float DeltaTime);

    virtual void Movimiento_Nave(float DeltaTime);

    virtual void NotifyActorBeginOverlap(AActor* OtherActor);

public:

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

    float MaxHealth;
    float CurrentHealth;






private:

	void Generate_Capsules();
    // Generate TerraBley
    void Generate_TerraBley();

    // TerraBley classes
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TArray<TSubclassOf<AT_TerraBley_P>> TerraBleyClasses;

    //capsules classes
	UPROPERTY(EditAnyWhere, Category = "Spawning")
    TArray<TSubclassOf<class AActor>> CapsuleClasses;




public:


    // Setter for Life (Health)
    FORCEINLINE void Set_Vida(float Vida_A)
    {
        Life = Vida_A;
        MaxHealth = Life;
        CurrentHealth = Life;
        UpdateHealthBar();
    }

    FORCEINLINE void Set_Velocidad_Nave(float Velocidad_A) { Velocity = Velocidad_A; }

    FORCEINLINE void Set_Danio_Disparo(float Danio_A) { Danio_Disparo = Danio_A; }

	class AGALAGA_REMASTEREDPawn* PY;



public:

    void UpdateHealthBar();

    class AHUD_P_Principal* HUD;

    class UW_BAR_SHIP_BOSS_GGG* BossHealthBarWidget;



public:

    float TiempoTotal;
    float IntervaloActual;
    int MovimientoActual;

	int DisparoActual;
	float TiempoTotal_Disparo;
	float IntervaloActual_Disparo;



    
};