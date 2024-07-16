#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "W_Ma_Options.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_Ma_Options : public UUserWidget
{
    GENERATED_BODY()

public:
    // El botón que ayuda a regresar a la pantalla principal del juego
    UPROPERTY(meta = (BindWidget))
    class UButton* Regresar_Options_O;

    // Para el botón de Reiniciar configuración del juego: se tiene que reiniciar la configuración del juego a la configuración por defecto
    UPROPERTY(meta = (BindWidget))
    class UButton* REINICIAR_TODO_BUTTON;

    // Para el botón de Guardar configuración del juego: se tiene que guardar la configuración del juego
    UPROPERTY(meta = (BindWidget))
    class UButton* APLICAR_GUARDAR_BUTTON;

    // Botones para la resolución de pantalla: 720x480, 1280x720, 1920x1080, 2560x1440
    UPROPERTY(meta = (BindWidget))
    class UButton* DR720X480Button1;

    UPROPERTY(meta = (BindWidget))
    class UButton* DR1280X720Button;

    UPROPERTY(meta = (BindWidget))
    class UButton* DR1920X1080Button;

    UPROPERTY(meta = (BindWidget))
    class UButton* DR2560X1440Button;

    // Texto que especifica la resolución con la que se está jugando
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_CAMBIO_RESOLUCION;

    // Botones para la calidad de gráficos
    UPROPERTY(meta = (BindWidget))
    class UButton* CALIDAD_GRAFICOS_LOW;

    UPROPERTY(meta = (BindWidget))
    class UButton* CALIDAD_GRAFICOS_MEDIUM;

    UPROPERTY(meta = (BindWidget))
    class UButton* CALIDAD_GRAFICOS_HIGH;

    UPROPERTY(meta = (BindWidget))
    class UButton* CALIDAD_GRAFICOS_EPIC;

    UPROPERTY(meta = (BindWidget))
    class UButton* CALIDAD_GRAFICOS_CINEMATIC;

    // Texto de la calidad de gráficos
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_CALIDAD_GRAFICOS;

    // Slider para el volumen principal del juego
    UPROPERTY(meta = (BindWidget))
    class USlider* Slider_VOLUMEN_PRINCIPAL;

    // Texto del volumen principal
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_VOLUMEN_PRINCIPAL;

    // Slider para el volumen de la música del juego
    UPROPERTY(meta = (BindWidget))
    class USlider* Slider_VOLUMEN_MUSICA;

    // Texto del volumen de la música
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_VOLUMEN_MUSICA;

    // Slider para el volumen de los efectos de sonido del juego
    UPROPERTY(meta = (BindWidget))
    class USlider* Slider_VOLUMEN_EFECTOS;

    // Texto del volumen de los efectos de sonido
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_VOLUMEN_EFECTOS;

protected:
    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void OnRegresarOptionsClicked();

    UFUNCTION()
    void OnReiniciarTodoClicked();

    UFUNCTION()
    void OnAplicarGuardarClicked();

    UFUNCTION()
    void On720x480Clicked();

    UFUNCTION()
    void On1280x720Clicked();

    UFUNCTION()
    void On1920x1080Clicked();

    UFUNCTION()
    void On2560x1440Clicked();

    UFUNCTION()
    void OnLowQualityClicked();

    UFUNCTION()
    void OnMediumQualityClicked();

    UFUNCTION()
    void OnHighQualityClicked();

    UFUNCTION()
    void OnEpicQualityClicked();

    UFUNCTION()
    void OnCinematicQualityClicked();

    UFUNCTION()
    void OnSliderVolumenPrincipalChanged(float Value);

    UFUNCTION()
    void OnSliderVolumenMusicaChanged(float Value);

    UFUNCTION()
    void OnSliderVolumenEfectosChanged(float Value);

    void ApplySettings();
    void SaveSettings();
    void LoadSettings();
    void LoadDefaultSettings();
    void UpdateTextBlocks();

    UPROPERTY(EditAnywhere, Category = "Audio")
    USoundMix* MasterSoundMix;

    USoundClass* MasterSoundClass;
    USoundClass* MusicSoundClass;
    USoundClass* EffectsSoundClass;

    void LoadSoundClasses();

    FString SelectedResolution;
    FString SelectedGraphicsQuality;
    float SelectedVolumenPrincipal;
    float SelectedVolumenMusica;
    float SelectedVolumenEfectos;
};
