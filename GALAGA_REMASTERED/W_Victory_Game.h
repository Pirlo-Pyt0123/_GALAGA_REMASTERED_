// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Victory_Game.generated.h"


UCLASS()
class GALAGA_REMASTERED_API UW_Victory_Game : public UUserWidget
{
	GENERATED_BODY()


public:

    virtual void NativeConstruct() override;


    UPROPERTY(meta = (BindWidget))
    class UTextBlock* You_Win_Tex_Box;


};