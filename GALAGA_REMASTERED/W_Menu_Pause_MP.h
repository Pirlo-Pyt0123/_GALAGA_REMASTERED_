// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Menu_Pause_MP.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_Menu_Pause_MP : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UButton* Continuar_MP;

    UPROPERTY(meta = (BindWidget))
    class UButton* Controles_MP;

    UPROPERTY(meta = (BindWidget))
    class UButton* Regresar_Menu_Principal_MP;

private:
    UFUNCTION()
    void OnContinuarClicked();

    UFUNCTION()
    void OnControlesClicked();

    UFUNCTION()
    void OnRegresarMenuPrincipalClicked();
};
