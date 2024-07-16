// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K_Portal_P.h"
#include "K_Portal_Quantum.generated.h"


UCLASS()
class GALAGA_REMASTERED_API AK_Portal_Quantum : public AK_Portal_P
{
	GENERATED_BODY()

public:

	AK_Portal_Quantum();

	//niagara system
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Particles")
	class UNiagaraComponent* Niagara_Qu;

	

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;


	
};
