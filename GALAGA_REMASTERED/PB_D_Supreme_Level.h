// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PB_Int_Level_Construction.h"
#include "PB_Int_Level_Acces.h"
#include "PB_D_Supreme_Level.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APB_D_Supreme_Level : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APB_D_Supreme_Level();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	IPB_Int_Level_Construction* Level_Construction_A;

public:

	class APB_Level_Creator* GET_Level_Creator();

	void Set_Level_General(AActor* Level_Supreme);

	void Level_Construction(int32 Level);


};