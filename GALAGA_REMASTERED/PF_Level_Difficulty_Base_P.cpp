// Fill out your copyright notice in the Description page of Project Settings.


#include "PF_Level_Difficulty_Base_P.h"
//
//int32 APF_Level_Difficulty_Base_P::Next_Level_oo = 1;
APF_Level_Difficulty_Base_P::APF_Level_Difficulty_Base_P()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APF_Level_Difficulty_Base_P::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APF_Level_Difficulty_Base_P::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
