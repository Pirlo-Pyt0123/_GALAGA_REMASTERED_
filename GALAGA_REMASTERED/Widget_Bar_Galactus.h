// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Bar_Galactus.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UWidget_Bar_Galactus : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* PROGRESBAR_BOSS_GALACTUS;


    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TEXT_HEALTH_GALACTUS;

    void UpdateHealthBar(float HealthPercentage, const FString& HealthText);

	
};
