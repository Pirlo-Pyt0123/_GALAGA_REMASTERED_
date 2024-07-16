// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K_Portal_P.h"
#include "K_Portal_SOLARE.generated.h"


UCLASS()
class GALAGA_REMASTERED_API AK_Portal_SOLARE : public AK_Portal_P
{
	GENERATED_BODY()

public:

	AK_Portal_SOLARE();

	//niagar component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Niagara", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* Niagara_SOLARE;

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	
};
