#include "W_Ma_Options.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameUserSettings.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "Components/AudioComponent.h"
#include "HUD_P_Principal.h"

void UW_Ma_Options::NativeConstruct()
{
    Super::NativeConstruct();

    if (Regresar_Options_O)
    {
        Regresar_Options_O->OnClicked.AddDynamic(this, &UW_Ma_Options::OnRegresarOptionsClicked);
    }

    if (REINICIAR_TODO_BUTTON)
    {
        REINICIAR_TODO_BUTTON->OnClicked.AddDynamic(this, &UW_Ma_Options::OnReiniciarTodoClicked);
    }

    if (APLICAR_GUARDAR_BUTTON)
    {
        APLICAR_GUARDAR_BUTTON->OnClicked.AddDynamic(this, &UW_Ma_Options::OnAplicarGuardarClicked);
    }

    if (DR720X480Button1)
    {
        DR720X480Button1->OnClicked.AddDynamic(this, &UW_Ma_Options::On720x480Clicked);
    }

    if (DR1280X720Button)
    {
        DR1280X720Button->OnClicked.AddDynamic(this, &UW_Ma_Options::On1280x720Clicked);
    }

    if (DR1920X1080Button)
    {
        DR1920X1080Button->OnClicked.AddDynamic(this, &UW_Ma_Options::On1920x1080Clicked);
    }

    if (DR2560X1440Button)
    {
        DR2560X1440Button->OnClicked.AddDynamic(this, &UW_Ma_Options::On2560x1440Clicked);
    }

    if (CALIDAD_GRAFICOS_LOW)
    {
        CALIDAD_GRAFICOS_LOW->OnClicked.AddDynamic(this, &UW_Ma_Options::OnLowQualityClicked);
    }

    if (CALIDAD_GRAFICOS_MEDIUM)
    {
        CALIDAD_GRAFICOS_MEDIUM->OnClicked.AddDynamic(this, &UW_Ma_Options::OnMediumQualityClicked);
    }

    if (CALIDAD_GRAFICOS_HIGH)
    {
        CALIDAD_GRAFICOS_HIGH->OnClicked.AddDynamic(this, &UW_Ma_Options::OnHighQualityClicked);
    }

    if (CALIDAD_GRAFICOS_EPIC)
    {
        CALIDAD_GRAFICOS_EPIC->OnClicked.AddDynamic(this, &UW_Ma_Options::OnEpicQualityClicked);
    }

    if (CALIDAD_GRAFICOS_CINEMATIC)
    {
        CALIDAD_GRAFICOS_CINEMATIC->OnClicked.AddDynamic(this, &UW_Ma_Options::OnCinematicQualityClicked);
    }

    if (Slider_VOLUMEN_PRINCIPAL)
    {
        Slider_VOLUMEN_PRINCIPAL->OnValueChanged.AddDynamic(this, &UW_Ma_Options::OnSliderVolumenPrincipalChanged);
        Slider_VOLUMEN_PRINCIPAL->SetMinValue(0.0f); // Asegurar que el mínimo sea 0.0
        Slider_VOLUMEN_PRINCIPAL->SetMaxValue(1.0f); // Asegurar que el máximo sea 1.0
    }

    if (Slider_VOLUMEN_MUSICA)
    {
        Slider_VOLUMEN_MUSICA->OnValueChanged.AddDynamic(this, &UW_Ma_Options::OnSliderVolumenMusicaChanged);
        Slider_VOLUMEN_MUSICA->SetMinValue(0.0f); // Asegurar que el mínimo sea 0.0
        Slider_VOLUMEN_MUSICA->SetMaxValue(1.0f); // Asegurar que el máximo sea 1.0
    }

    if (Slider_VOLUMEN_EFECTOS)
    {
        Slider_VOLUMEN_EFECTOS->OnValueChanged.AddDynamic(this, &UW_Ma_Options::OnSliderVolumenEfectosChanged);
        Slider_VOLUMEN_EFECTOS->SetMinValue(0.0f); // Asegurar que el mínimo sea 0.0
        Slider_VOLUMEN_EFECTOS->SetMaxValue(1.0f); // Asegurar que el máximo sea 1.0
    }

    LoadSettings();
}

void UW_Ma_Options::OnRegresarOptionsClicked()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(PlayerController->GetHUD());
        if (HUD)
        {
            HUD->HideOptionsMenu();
            HUD->ShowMainMenu();
        }
    }
}

void UW_Ma_Options::OnReiniciarTodoClicked()
{
    LoadDefaultSettings();
}

void UW_Ma_Options::OnAplicarGuardarClicked()
{
    ApplySettings();
    SaveSettings();
}

void UW_Ma_Options::On720x480Clicked()
{
    SelectedResolution = "720x480";
    ApplySettings();
    SaveSettings();
    UpdateTextBlocks();
}

void UW_Ma_Options::On1280x720Clicked()
{
    SelectedResolution = "1280x720";
    ApplySettings();
    SaveSettings();
    UpdateTextBlocks();
}

void UW_Ma_Options::On1920x1080Clicked()
{
    SelectedResolution = "1920x1080";
    ApplySettings();
    SaveSettings();
    UpdateTextBlocks();
}

void UW_Ma_Options::On2560x1440Clicked()
{
    SelectedResolution = "2560x1440";
    ApplySettings();
    SaveSettings();
    UpdateTextBlocks();
}

void UW_Ma_Options::OnLowQualityClicked()
{
    SelectedGraphicsQuality = "Low";
    ApplySettings();
    SaveSettings();
    UpdateTextBlocks();
}

void UW_Ma_Options::OnMediumQualityClicked()
{
    SelectedGraphicsQuality = "Medium";
    ApplySettings();
    SaveSettings();
    UpdateTextBlocks();
}

void UW_Ma_Options::OnHighQualityClicked()
{
    SelectedGraphicsQuality = "High";
    ApplySettings();
    SaveSettings();
    UpdateTextBlocks();
}

void UW_Ma_Options::OnEpicQualityClicked()
{
    SelectedGraphicsQuality = "Epic";
    ApplySettings();
    SaveSettings();
    UpdateTextBlocks();
}

void UW_Ma_Options::OnCinematicQualityClicked()
{
    SelectedGraphicsQuality = "Cinematic";
    ApplySettings();
    SaveSettings();
    UpdateTextBlocks();
}

void UW_Ma_Options::OnSliderVolumenPrincipalChanged(float Value)
{
    SelectedVolumenPrincipal = FMath::Clamp(Value, 0.0f, 1.0f);
    TextBlock_VOLUMEN_PRINCIPAL->SetText(FText::AsNumber(FMath::RoundToInt(SelectedVolumenPrincipal * 100)));
    if (MasterSoundClass)
    {
        MasterSoundClass->Properties.Volume = SelectedVolumenPrincipal;
    }
}

void UW_Ma_Options::OnSliderVolumenMusicaChanged(float Value)
{
    SelectedVolumenMusica = FMath::Clamp(Value, 0.0f, 1.0f);
    TextBlock_VOLUMEN_MUSICA->SetText(FText::AsNumber(FMath::RoundToInt(SelectedVolumenMusica * 100)));
    if (MusicSoundClass)
    {
        MusicSoundClass->Properties.Volume = SelectedVolumenMusica;
    }
}

void UW_Ma_Options::OnSliderVolumenEfectosChanged(float Value)
{
    SelectedVolumenEfectos = FMath::Clamp(Value, 0.0f, 1.0f);
    TextBlock_VOLUMEN_EFECTOS->SetText(FText::AsNumber(FMath::RoundToInt(SelectedVolumenEfectos * 100)));
    if (EffectsSoundClass)
    {
        EffectsSoundClass->Properties.Volume = SelectedVolumenEfectos;
    }
}

void UW_Ma_Options::ApplySettings()
{
    if (UGameUserSettings* UserSettings = GEngine->GetGameUserSettings())
    {
        // Aplicar configuraciones de resolución
        if (SelectedResolution == "720x480")
        {
            UserSettings->SetScreenResolution(FIntPoint(720, 480));
        }
        else if (SelectedResolution == "1280x720")
        {
            UserSettings->SetScreenResolution(FIntPoint(1280, 720));
        }
        else if (SelectedResolution == "1920x1080")
        {
            UserSettings->SetScreenResolution(FIntPoint(1920, 1080));
        }
        else if (SelectedResolution == "2560x1440")
        {
            UserSettings->SetScreenResolution(FIntPoint(2560, 1440));
        }

        // Aplicar configuraciones de calidad gráfica
        int32 QualityLevel = 2; // Por defecto a High
        if (SelectedGraphicsQuality == "Low")
        {
            QualityLevel = 0;
        }
        else if (SelectedGraphicsQuality == "Medium")
        {
            QualityLevel = 1;
        }
        else if (SelectedGraphicsQuality == "High")
        {
            QualityLevel = 2;
        }
        else if (SelectedGraphicsQuality == "Epic")
        {
            QualityLevel = 3;
        }
        else if (SelectedGraphicsQuality == "Cinematic")
        {
            QualityLevel = 4;
        }
        UserSettings->SetOverallScalabilityLevel(QualityLevel);

        UserSettings->ApplySettings(true);
    }

    // Aplicar configuraciones de audio
    if (MasterSoundClass)
    {
        MasterSoundClass->Properties.Volume = SelectedVolumenPrincipal;
    }

    if (MusicSoundClass)
    {
        MusicSoundClass->Properties.Volume = SelectedVolumenMusica;
    }

    if (EffectsSoundClass)
    {
        EffectsSoundClass->Properties.Volume = SelectedVolumenEfectos;
    }

    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, MasterSoundClass, SelectedVolumenPrincipal, 1.0f, 0.0f);
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, MusicSoundClass, SelectedVolumenMusica, 1.0f, 0.0f);
    UGameplayStatics::SetSoundMixClassOverride(GetWorld(), MasterSoundMix, EffectsSoundClass, SelectedVolumenEfectos, 1.0f, 0.0f);
    UGameplayStatics::PushSoundMixModifier(GetWorld(), MasterSoundMix);
}


void UW_Ma_Options::SaveSettings()
{
    if (UGameUserSettings* UserSettings = GEngine->GetGameUserSettings())
    {
        UserSettings->SaveSettings();
    }

    // Guardar configuraciones de audio en archivo de configuración
    GConfig->SetFloat(TEXT("/Script/Engine.AudioSettings"), TEXT("MasterVolume"), SelectedVolumenPrincipal, GGameIni);
    GConfig->SetFloat(TEXT("/Script/Engine.AudioSettings"), TEXT("MusicVolume"), SelectedVolumenMusica, GGameIni);
    GConfig->SetFloat(TEXT("/Script/Engine.AudioSettings"), TEXT("EffectsVolume"), SelectedVolumenEfectos, GGameIni);
    GConfig->Flush(true, GGameIni);
}

void UW_Ma_Options::LoadSettings()
{
    LoadSoundClasses();

    if (UGameUserSettings* UserSettings = GEngine->GetGameUserSettings())
    {
        // Cargar configuraciones de resolución
        FIntPoint Resolution = UserSettings->GetScreenResolution();
        if (Resolution == FIntPoint(720, 480))
        {
            SelectedResolution = "720x480";
        }
        else if (Resolution == FIntPoint(1280, 720))
        {
            SelectedResolution = "1280x720";
        }
        else if (Resolution == FIntPoint(1920, 1080))
        {
            SelectedResolution = "1920x1080";
        }
        else if (Resolution == FIntPoint(2560, 1440))
        {
            SelectedResolution = "2560x1440";
        }

        // Cargar configuraciones de calidad gráfica
        int32 QualityLevel = UserSettings->GetOverallScalabilityLevel();
        switch (QualityLevel)
        {
        case 0:
            SelectedGraphicsQuality = "Low";
            break;
        case 1:
            SelectedGraphicsQuality = "Medium";
            break;
        case 2:
            SelectedGraphicsQuality = "High";
            break;
        case 3:
            SelectedGraphicsQuality = "Epic";
            break;
        case 4:
            SelectedGraphicsQuality = "Cinematic";
            break;
        }

        // Cargar configuraciones de audio
        if (GConfig)
        {
            GConfig->GetFloat(TEXT("/Script/Engine.AudioSettings"), TEXT("MasterVolume"), SelectedVolumenPrincipal, GGameIni);
            GConfig->GetFloat(TEXT("/Script/Engine.AudioSettings"), TEXT("MusicVolume"), SelectedVolumenMusica, GGameIni);
            GConfig->GetFloat(TEXT("/Script/Engine.AudioSettings"), TEXT("EffectsVolume"), SelectedVolumenEfectos, GGameIni);
        }

        UpdateTextBlocks();
    }
}

void UW_Ma_Options::LoadDefaultSettings()
{
    if (UGameUserSettings* UserSettings = GEngine->GetGameUserSettings())
    {
        UserSettings->SetToDefaults();
        UserSettings->ApplySettings(true);

        SelectedResolution = "1280x720";
        SelectedGraphicsQuality = "High";
        SelectedVolumenPrincipal = 1.0f;
        SelectedVolumenMusica = 1.0f;
        SelectedVolumenEfectos = 1.0f;

        ApplySettings();
        SaveSettings();
        UpdateTextBlocks();
    }
}

void UW_Ma_Options::UpdateTextBlocks()
{
    if (TextBlock_CAMBIO_RESOLUCION)
    {
        TextBlock_CAMBIO_RESOLUCION->SetText(FText::FromString(SelectedResolution));
    }

    if (TextBlock_CALIDAD_GRAFICOS)
    {
        TextBlock_CALIDAD_GRAFICOS->SetText(FText::FromString(SelectedGraphicsQuality));
    }

    if (TextBlock_VOLUMEN_PRINCIPAL)
    {
        TextBlock_VOLUMEN_PRINCIPAL->SetText(FText::AsNumber(FMath::RoundToInt(SelectedVolumenPrincipal * 100)));
    }

    if (TextBlock_VOLUMEN_MUSICA)
    {
        TextBlock_VOLUMEN_MUSICA->SetText(FText::AsNumber(FMath::RoundToInt(SelectedVolumenMusica * 100)));
    }

    if (TextBlock_VOLUMEN_EFECTOS)
    {
        TextBlock_VOLUMEN_EFECTOS->SetText(FText::AsNumber(FMath::RoundToInt(SelectedVolumenEfectos * 100)));
    }

    if (Slider_VOLUMEN_PRINCIPAL)
    {
        Slider_VOLUMEN_PRINCIPAL->SetValue(SelectedVolumenPrincipal);
    }

    if (Slider_VOLUMEN_MUSICA)
    {
        Slider_VOLUMEN_MUSICA->SetValue(SelectedVolumenMusica);
    }

    if (Slider_VOLUMEN_EFECTOS)
    {
        Slider_VOLUMEN_EFECTOS->SetValue(SelectedVolumenEfectos);
    }
}

void UW_Ma_Options::LoadSoundClasses()
{
    MasterSoundClass = LoadObject<USoundClass>(nullptr, TEXT("SoundClass'/Game/Widged/Master.Master'"));
    MusicSoundClass = LoadObject<USoundClass>(nullptr, TEXT("SoundClass'/Game/Widged/Music.Music'"));
    EffectsSoundClass = LoadObject<USoundClass>(nullptr, TEXT("SoundClass'/Game/Widged/Effects.Effects'"));
    MasterSoundMix = LoadObject<USoundMix>(nullptr, TEXT("SoundMix'/Game/Widged/MasterSoundMix.MasterSoundMix'"));
}
