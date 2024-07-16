#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "K_Portal_P.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AK_Portal_P : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AK_Portal_P();

    // Declara la malla correspondiente 
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
    class UStaticMeshComponent* Mesh_Portal;

    // Declara el componente de colision
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
    class UBoxComponent* Collision_Portal;

    // Declara el componente de particulas
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
    class UParticleSystemComponent* Particle_Portal;

    // Declara el componente de sonido
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
    class USoundBase* Sound_Portal;

    

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Función para manejar la superposición con otros actores
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    // Función para destruir el componente
    virtual void Component_Destruction();

    // Función para iniciar el siguiente nivel
    void StartNextLevel();

private:
    FTimerHandle TimerHandle;

    class APF_Level_Creator_P* LevelCreator;
    class AHUD_P_Principal* HUD;
    class APlayerController* PlayerController;
};
