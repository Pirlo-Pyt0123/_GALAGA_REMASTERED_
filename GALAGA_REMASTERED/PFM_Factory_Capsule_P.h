// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PFM_Object_Interact_P.h"
#include "PFM_Factory_Capsule_P.generated.h"


UCLASS()
class GALAGA_REMASTERED_API APFM_Factory_Capsule_P : public APFM_Object_Interact_P
{
	GENERATED_BODY()

public:

	virtual AInteractable_Objects_P* Create_Interactable_Object(FString Identificador) override;
private:
	TArray<FVector> SpawnedLocations;
	
};
