#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_BAR_SHIP_BOSS_GGG.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_BAR_SHIP_BOSS_GGG : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* PROGRESBAR_BOSS_HEALTH;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TEXT_HEALTH_BOSS;

    void UpdateHealthBar(float HealthPercentage, const FString& HealthText);

private:
    void SetRandomFillImage();

    UPROPERTY(EditAnywhere, Category = "Images")
    UMaterialInterface* LET_MEGA_MM5;

    UPROPERTY(EditAnywhere, Category = "Images")
    UTexture2D* Barra_06;

    UPROPERTY(EditAnywhere, Category = "Images")
    UTexture2D* Barra_05;

    UPROPERTY(EditAnywhere, Category = "Images")
    UTexture2D* Barra_02;

    UPROPERTY(EditAnywhere, Category = "Images")
    UTexture2D* CLODD;

    UPROPERTY(EditAnywhere, Category = "Images")
    UTexture2D* CBRA;

    private:
    TArray<UObject*> FillImages;
    int32 ImageIndex;
};
