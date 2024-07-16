// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable_Objects_P.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AInteractable_Objects_P : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_Objects_P();

	// Mesh for the interactable object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable")
	class UStaticMeshComponent* MeshComponent;

	// Particle system for the interactable object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable")
	class UParticleSystemComponent* ParticleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable")
	class UParticleSystem* ParticleSystem;

	
	// Collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable")
	class UBoxComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactable")
	class USoundBase* SoundComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString Identificador_Object;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor);

	virtual void Componente_Destruccion();

};
