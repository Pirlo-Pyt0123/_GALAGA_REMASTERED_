// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Bar_Galactus.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInterface.h"

void UWidget_Bar_Galactus::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_Bar_Galactus::UpdateHealthBar(float HealthPercentage, const FString& HealthText)
{
	if (PROGRESBAR_BOSS_GALACTUS)
	{
		PROGRESBAR_BOSS_GALACTUS->SetPercent(HealthPercentage);
	}

	if (TEXT_HEALTH_GALACTUS)
	{
		TEXT_HEALTH_GALACTUS->SetText(FText::FromString(HealthText));
	}
}
