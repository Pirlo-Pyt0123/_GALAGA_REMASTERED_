// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Screen_Level_Iden.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_Screen_Level_Iden : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Mensaje_Pantalla_Level;

    // PARA EL COLOR DE FONDO DEL MENSAJE 
    UPROPERTY(meta = (BindWidget))
    class UImage* Colors_Change;

    UFUNCTION(BlueprintCallable)
    void SetLevelMessage(const FString& LevelMessage);

    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    void StartMove();

private:
    bool bIsMoving;
    FVector2D StartPosition;
    FVector2D EndPosition;

    TArray<UMaterialInterface*> BackgroundMaterials;

    void ChangeBackgroundColor();
};
