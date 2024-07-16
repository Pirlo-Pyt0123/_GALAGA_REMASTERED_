// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "T_TerraBley_P.h"
#include "T_TerraBley_Nebula_Core.generated.h"


UCLASS()
class GALAGA_REMASTERED_API AT_TerraBley_Nebula_Core : public AT_TerraBley_P
{
	GENERATED_BODY()


public:

	AT_TerraBley_Nebula_Core();

public:

	virtual void BeginPlay() override;


	virtual void Tick(float DeltaTime) override;

	
};
