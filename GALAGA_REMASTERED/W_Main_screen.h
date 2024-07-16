#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Main_screen.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_Main_screen : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UButton* Game;

    UPROPERTY(meta = (BindWidget))
    class UButton* Options;

    UPROPERTY(meta = (BindWidget))
    class UButton* Controle;

    UPROPERTY(meta = (BindWidget))
    class UButton* Creditos;

    UPROPERTY(meta = (BindWidget))
    class UButton* Salir;

protected:
    virtual void NativeConstruct() override;

public:
    UFUNCTION()
    void OnGameClicked();

    UFUNCTION()
    void OnOptionsClicked();

    UFUNCTION()
    void OnControleClicked();

    UFUNCTION()
    void OnCreditosClicked();

    UFUNCTION()
    void OnSalirClicked();
};
