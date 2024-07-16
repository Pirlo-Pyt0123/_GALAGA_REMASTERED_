#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "AC_MOVEMENT_EPIC.h"
#include "EPIC_GALACTUS_FINAL_BOSS.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AEPIC_GALACTUS_FINAL_BOSS : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AEPIC_GALACTUS_FINAL_BOSS();

   
	//componente de actor de movimiento
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Componentes")
	class UAC_MOVEMENT_EPIC* Movimiento;


    // Malla del enemigo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    class UStaticMeshComponent* Mesh;

    // Sonido de aparición
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sonido")
    class USoundBase* Sonido_Aparecer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sonido")
    class UAudioComponent* Audio_Aparecer;
	

    // Sonido de disparo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sonido")
    class USoundBase* Sonido_Disparo;

    // Sonido de muerte
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sonido")
    class USoundBase* Sonido_Muerte;

    // Partículas de muerte
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particulas")
    UParticleSystemComponent* Particulas_Muerte;

    // Partículas de disparo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particulas")
    UParticleSystemComponent* Particulas_Disparo;

    // Partículas de impacto
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particulas")
    UParticleSystemComponent* Particulas_Impacto;

    // Partículas de poderes especiales
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particulas")
    UParticleSystemComponent* Poderes_left;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particulas")
    UParticleSystemComponent* Poderes_right;

	//aparicion de enemigo parituclas de aparicion
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aparicion")
	UParticleSystemComponent* Aparicion;

    //particulas de quemadura
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particulas")
	UParticleSystemComponent* Quemadura;

	//particulas de fugas 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particulas")
	UParticleSystemComponent* Fugas;

	//componente de niagara
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	class UNiagaraComponent* Nia_Gal;


    // Vida del enemigo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vida")
    float SUPREME_LIFE;

    float MAX_SUPRME_LIFE;

    // ~~ Componente de Colisión : tipo caja ~~
    UPROPERTY(EditAnywhere, Category = "Componentes")
    class UBoxComponent* Colision_Nave;

    FORCEINLINE void Set_Vida(float Vida_A) 
    { 
        SUPREME_LIFE = Vida_A;

        MAX_SUPRME_LIFE = Vida_A;
    }

    FORCEINLINE void Set_Velocidad_Nave(float Velocidad_A) { Velocity = Velocidad_A; }

    FORCEINLINE void Set_Danio_Disparo(float Danio_A) { Danio_Disparo = Danio_A; }

public:

    FString Identificador_Nave;
    float Speed;
    float Resistencia;
    float Tiempo_Disparo;
    float Intervalo_Disparo;
    FVector Distancia_Disparo;
    float Danio_Recibido;
    float Danio_Disparo;

    float Life;

    float Tiempo_M;
    float Distancia_D_CB;
    float Velocity;




    int DisparoActual;
    float TiempoTotal_Disparo;
    float IntervaloActual_Disparo;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

	class AGALAGA_REMASTEREDPawn* Player;

public:

    FTimerHandle TimerHandle_VictoryWidget;

    class AHUD_P_Principal* PlayerHUD;
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void Recibir_Danio(float Danio);

    void Disparo_Galactus(float DeltaTime);

    void Movimiento_Galactus(float DeltaTime);

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual void Componente_Destruccion();

    void ShowVictoryWidgetAfterDelay();

    class UWidget_Bar_Galactus* GalactusHealthBarWidget;

    void UpdateHUDHealth();


};