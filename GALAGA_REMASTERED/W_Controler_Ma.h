// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Controler_Ma.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_Controler_Ma : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UButton* Regre_Main_P;

protected:
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void OnRegresarClicked();
};
