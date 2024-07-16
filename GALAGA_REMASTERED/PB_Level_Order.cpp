// Fill out your copyright notice in the Description page of Project Settings.

#include "PB_Level_Order.h"
#include "PB_Level_Creator.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APB_Level_Order::APB_Level_Order()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APB_Level_Order::BeginPlay()
{
	Super::BeginPlay();

	Level_CreatorOP = Cast<APB_Level_Creator>(UGameplayStatics::GetActorOfClass(GetWorld(), APB_Level_Creator::StaticClass()));
	if (!Level_CreatorOP)
	{
		Level_CreatorOP = GetWorld()->SpawnActor<APB_Level_Creator>(APB_Level_Creator::StaticClass());
		if (!Level_CreatorOP) {
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn Level Creator"));
			return;
		}
	}

	Level_CreatorOP->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void APB_Level_Order::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APB_Level_Order::Build_Level_1()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	Level_CreatorOP->Set_Level_1();
}

void APB_Level_Order::Build_Level_1_1()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_1_1();
	}
}

void APB_Level_Order::Build_Level_2()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_2();
	}
}

void APB_Level_Order::Build_Level_2_1()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_2_1();
	}

}

void APB_Level_Order::Build_Level_3()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_3();
	}
}

void APB_Level_Order::Build_Level_3_1()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));

		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_3_1();
	}
}

void APB_Level_Order::Build_Level_4()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_4();
	}
}

void APB_Level_Order::Build_Level_4_1()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_4_1();
	}
}

void APB_Level_Order::Build_Level_5()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_5();
	}
}

void APB_Level_Order::Build_Level_5_1()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_5_1();
	}
}

void APB_Level_Order::Build_Level_6()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_6();
	}
}

void APB_Level_Order::Build_Level_6_1()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_6_1();
	}
}

void APB_Level_Order::Build_Level_7()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_7();
	}
}

void APB_Level_Order::Build_Level_7_1()
{
	if (!Level_CreatorOP)
	{
		UE_LOG(LogTemp, Error, TEXT(" Level_CreatorOP is NULL, make sure it is initialized."));
		return;
	}
	else
	{
		Level_CreatorOP->Set_Level_7_1();
	}
}

APB_Level_Creator* APB_Level_Order::GET_Level_Creator()
{
	return Level_CreatorOP;
}