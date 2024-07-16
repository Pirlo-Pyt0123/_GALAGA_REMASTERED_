// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PB_Int_Level_Construction.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPB_Int_Level_Construction : public UInterface
{
	GENERATED_BODY()
};


class GALAGA_REMASTERED_API IPB_Int_Level_Construction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Build_Level_1() = 0;
	virtual void Build_Level_1_1() = 0;

	virtual void Build_Level_2() = 0;
	virtual void Build_Level_2_1() = 0;

	virtual void Build_Level_3() = 0;
	virtual void Build_Level_3_1() = 0;

	virtual void Build_Level_4() = 0;
	virtual void Build_Level_4_1() = 0;

	virtual void Build_Level_5() = 0;
	virtual void Build_Level_5_1() = 0;

	virtual void Build_Level_6() = 0;
	virtual void Build_Level_6_1() = 0;

	virtual void Build_Level_7() = 0;
	virtual void Build_Level_7_1() = 0;

	virtual class APB_Level_Creator* GET_Level_Creator() = 0;


};
