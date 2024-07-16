// Fill out your copyright notice in the Description page of Project Settings.


#include "PB_D_Supreme_Level.h"
#include "PB_Level_Creator.h"



// Sets default values
APB_D_Supreme_Level::APB_D_Supreme_Level()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void APB_D_Supreme_Level::BeginPlay()
{
	Super::BeginPlay();

}



// Called every frame
void APB_D_Supreme_Level::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



APB_Level_Creator* APB_D_Supreme_Level::GET_Level_Creator()
{
	if (Level_Construction_A)
	{
		return Level_Construction_A->GET_Level_Creator();
	}
	//Log if the Builder is NULL
	UE_LOG(LogTemp, Error, TEXT("Level_Construction_A(): Return nullptr"));
	return nullptr;
}

void APB_D_Supreme_Level::Set_Level_General(AActor* Level_Supreme)
{
	Level_Construction_A = Cast<IPB_Int_Level_Construction>(Level_Supreme);
	if (!Level_Construction_A)
	{
		UE_LOG(LogTemp, Error, TEXT("Level_Construction_A(): is NULL, asegúrese de que este inicializado."));
	}
}


void APB_D_Supreme_Level::Level_Construction(int32 Level)
{
	if (!Level_Construction_A)
	{
		UE_LOG(LogTemp, Error, TEXT("Construct_Level(): is NULL, asegúrese de que este inicializado."));
		return;
	}
	else
	{
		if (1 == Level)
		{
			Level_Construction_A->Build_Level_1();

		}

		if (2 == Level)
		{
			Level_Construction_A->Build_Level_1_1();
		}

		if (3 == Level)
		{
			Level_Construction_A->Build_Level_2();
		}

		if (4 == Level)
		{
			Level_Construction_A->Build_Level_2_1();
		}

		if (5 == Level)
		{
			Level_Construction_A->Build_Level_3();
		}

		if (6 == Level)
		{
			Level_Construction_A->Build_Level_3_1();
		}

		if (7 == Level)
		{
			Level_Construction_A->Build_Level_4();
		}

		if (8 == Level)
		{
			Level_Construction_A->Build_Level_4_1();
		}

		if (9 == Level)
		{
			Level_Construction_A->Build_Level_5();
		}

		if (10 == Level)
		{
			Level_Construction_A->Build_Level_5_1();
		}

		if (11 == Level)
		{
			Level_Construction_A->Build_Level_6();
		}

		if (12 == Level)
		{
			Level_Construction_A->Build_Level_6_1();
		}

		if (13 == Level)
		{
			Level_Construction_A->Build_Level_7();
		}

		if (14 == Level)
		{
			Level_Construction_A->Build_Level_7_1();
		}
	}
}