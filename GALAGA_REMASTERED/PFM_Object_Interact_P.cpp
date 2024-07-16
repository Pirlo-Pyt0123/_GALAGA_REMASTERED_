// Fill out your copyright notice in the Description page of Project Settings.


#include "PFM_Object_Interact_P.h"

// Sets default values
APFM_Object_Interact_P::APFM_Object_Interact_P()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AInteractable_Objects_P* APFM_Object_Interact_P::Get_Interactable_Object(FString Identificador)
{
	AInteractable_Objects_P * Interactable_Object = Create_Interactable_Object(Identificador);
	return Interactable_Object;
}

// Called when the game starts or when spawned
void APFM_Object_Interact_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APFM_Object_Interact_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

