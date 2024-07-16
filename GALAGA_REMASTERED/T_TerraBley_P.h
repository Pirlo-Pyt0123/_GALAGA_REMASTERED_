// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T_TerraBley_P.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AT_TerraBley_P : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AT_TerraBley_P();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UStaticMeshComponent* Mesh_TR;

	//Declara el componente de particulas
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
	class UParticleSystemComponent* PPt;


	// Declaración en la clase .h
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
	class UParticleSystemComponent* Particle_Pr;

	// ~~ Componente de Explosion ~~
	UPROPERTY(EditAnywhere, Category = "Componentes")
	class UNiagaraComponent* Expo;	


	// ~~ Componente de Colsion : tipo caja ~~
	UPROPERTY(EditAnywhere, Category = "Componentes")
	class UBoxComponent* Colision_Terra;

	// ~~ Componente de Sonido ~~
	UPROPERTY(EditAnywhere, Category = "Componentes")
	class USoundBase* Sonido_Aparicionn_Terra;

	// ~~ Componente de Sonido ~~
	UPROPERTY(EditAnywhere, Category = "Componentes")
	class USoundBase* Sonido_Desaparicion_Terra;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	virtual void NotifyActoBeginOverlap(AActor* OtherActor);


	virtual void Componente_Desaparecer();

public:

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<TSubclassOf<AActor>> PortalClasses;

	FString Identificador_TerraBley;

	void Generar_Portal();

};