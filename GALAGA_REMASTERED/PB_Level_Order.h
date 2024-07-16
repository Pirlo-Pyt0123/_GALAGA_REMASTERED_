// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PB_Int_Level_Construction.h"
#include "PB_Level_Order.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APB_Level_Order : public AActor, public IPB_Int_Level_Construction
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APB_Level_Order();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Level")
	class APB_Level_Creator* Level_CreatorOP;

public:

	void Build_Level_1() override;
	void Build_Level_1_1() override;

	void Build_Level_2() override;
	void Build_Level_2_1() override;

	void Build_Level_3() override;
	void Build_Level_3_1() override;

	void Build_Level_4() override;
	void Build_Level_4_1() override;

	void Build_Level_5() override;
	void Build_Level_5_1() override;

	void Build_Level_6() override;
	void Build_Level_6_1() override;

	void Build_Level_7() override;
	void Build_Level_7_1() override;

	virtual class APB_Level_Creator* GET_Level_Creator() override;

};