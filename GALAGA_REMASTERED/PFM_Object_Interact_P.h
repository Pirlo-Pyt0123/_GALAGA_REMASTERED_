// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable_Objects_P.h"
#include "PFM_Object_Interact_P.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APFM_Object_Interact_P : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APFM_Object_Interact_P();

public:

	AInteractable_Objects_P* Get_Interactable_Object(FString Identificador);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual AInteractable_Objects_P* Create_Interactable_Object(FString Identificador) PURE_VIRTUAL(AInteractable_Objects_P::Create_Interactable_Object, return nullptr;);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
