// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Z_Enemy_Ship_P.h"
#include "Z_Ship_Cyclone.generated.h"


UCLASS()
class GALAGA_REMASTERED_API AZ_Ship_Cyclone : public AZ_Enemy_Ship_P
{
	GENERATED_BODY()

public:

	AZ_Ship_Cyclone();


protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void Recibir_Danio(float Danio) override;

    // Implementar la función de disparo
    virtual void Disparo_Nave(UWorld* World, FVector Location, FRotator Rotation) override;
};
