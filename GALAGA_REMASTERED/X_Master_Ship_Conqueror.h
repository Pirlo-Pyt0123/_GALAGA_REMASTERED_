// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "X_Master_Ship_P.h"
#include "AC_MOVEMENT_EPIC.h"
#include "X_Master_Ship_Conqueror.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AX_Master_Ship_Conqueror : public AX_Master_Ship_P
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AX_Master_Ship_Conqueror();


	//audio component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class UAudioComponent* Au_Con;
	//niagara Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	class UNiagaraComponent* Nia_Con;

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void Recibir_Danio(float Danio) override;

	virtual void Disparo_Nave(float DeltaTime) override;

	virtual void Movimiento_Nave(float DeltaTime) override;






private:
	TArray<void (UAC_MOVEMENT_EPIC::*)(float)> Movimientos;

	
};
