// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PF_Level_Difficulty_Base_P.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APF_Level_Difficulty_Base_P : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APF_Level_Difficulty_Base_P();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	// Métodos virtual puro para configurar las naves
	virtual void Setting_Enemy_Ship_Basic() PURE_VIRTUAL(APF_Level_Difficulty_Base_P::Setting_Enemy_Ship_Basic,);

	// Métodos virtual puro para configurar los obstáculos
	virtual void Setting_Obstacles_General() PURE_VIRTUAL(APF_Level_Difficulty_Base_P::Setting_Obstacles_General,);

	virtual void Setting_Boss_Ship_Basic() PURE_VIRTUAL(APF_Level_Difficulty_Base_P::Setting_Boss_Ship_Basic,);

	virtual void Setting_Boss_Galactus() PURE_VIRTUAL(APF_Level_Difficulty_Base_P::Seting_Boss_Galactus,);


};
