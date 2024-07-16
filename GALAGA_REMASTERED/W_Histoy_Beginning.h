#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h" // Incluye USoundBase aquí
#include "W_Histoy_Beginning.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_Histoy_Beginning : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    // Imagen que cambia durante la historia
    UPROPERTY(meta = (BindWidget))
    class UImage* Image_Current_His;

    // TextBox multilinea que cambia durante la historia
    UPROPERTY(meta = (BindWidget))
    class URichTextBlock* Multi_Linea_History;

    // Botón para continuar la historia
    UPROPERTY(meta = (BindWidget))
    class UButton* Next_History_Button;

    // Botón para saltar la historia
    UPROPERTY(meta = (BindWidget))
    class UButton* Saltar_Button;

private:
    int32 CurrentIndex;
    TArray<UTexture2D*> HistoryImages;
    TArray<FText> HistoryTexts;
    TArray<USoundBase*> HistorySounds;
    UAudioComponent* AudioComponent;

    UFUNCTION()
    void OnContinuarHistoriaClicked();

    UFUNCTION()
    void OnSaltarHistoriaClicked();

    void UpdateHistory();
    void ComenzarJuego();
};
