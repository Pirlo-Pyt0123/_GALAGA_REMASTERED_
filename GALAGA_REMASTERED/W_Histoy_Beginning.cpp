#include "W_Histoy_Beginning.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"
#include "HUD_P_Principal.h"

void UW_Histoy_Beginning::NativeConstruct()
{
    Super::NativeConstruct();

    // Inicializar el índice de la historia
    CurrentIndex = 0;

    // Cargar las imágenes de la historia
    HistoryImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/HISTORIA_GO/H1_G.H1_G'")));
    HistoryImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/HISTORIA_GO/H2_G.H2_G'")));
    HistoryImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/HISTORIA_GO/H3_G.H3_G'")));
    HistoryImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/HISTORIA_GO/H4_G.H4_G'")));
    HistoryImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/HISTORIA_GO/H5_G.H5_G'")));
    HistoryImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/HISTORIA_GO/H6_G.H6_G'")));



    // Cargar los textos de la historia
    HistoryTexts.Add(FText::FromString(" La historia comienza con nuestra nave, la Estrella de Andromeda, patrullando la galaxia en busca de aventuras. "));
    HistoryTexts.Add(FText::FromString("De repente, una alerta se activa en un planeta cercano, indicando una posible amenaza."));
    HistoryTexts.Add(FText::FromString("Al llegar, inesperadamente, es atacada por los ArcoBox, una civilizacion extraterrestre hostil."));
    HistoryTexts.Add(FText::FromString("Intenta defenderse, pero la cantidad de naves enemigas es abrumadora. No tiene otra alternativa que aterrizar en el planeta de donde provino la alerta."));
    HistoryTexts.Add(FText::FromString("En el planeta, descubre que los ArcoBox intentan obtener la TERRA - BLEY, una gema que otorga poderes inimaginables y que puede aniquilar planetas enteros."));
    HistoryTexts.Add(FText::FromString("Al tratar de detenerlos, los disparos de los ArcoBox impactan la TERRA-BLEY, fragmentandola en trece gemas que se dispersan por toda la galaxia. Nuestro objetivo es recuperarlas."));



    // Cargar los audios de la historia (SoundBase)
    HistorySounds.Add(LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/HISTORY_GALAGA/HISTORY_SOUNDS/historia_0.historia_0'")));
    HistorySounds.Add(LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/HISTORY_GALAGA/HISTORY_SOUNDS/historia01.historia01'")));
    HistorySounds.Add(LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/HISTORY_GALAGA/HISTORY_SOUNDS/historia02.historia02'")));
    HistorySounds.Add(LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/HISTORY_GALAGA/HISTORY_SOUNDS/historia03.historia03'")));
    HistorySounds.Add(LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/HISTORY_GALAGA/HISTORY_SOUNDS/Historia04.Historia04'")));
    HistorySounds.Add(LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/HISTORY_GALAGA/HISTORY_SOUNDS/historia05.historia05'")));

    // Vincular las funciones de los botones
    if (Next_History_Button)
    {
        Next_History_Button->OnClicked.AddDynamic(this, &UW_Histoy_Beginning::OnContinuarHistoriaClicked);
    }

    if (Saltar_Button)
    {
        Saltar_Button->OnClicked.AddDynamic(this, &UW_Histoy_Beginning::OnSaltarHistoriaClicked);
    }

    // Crear el componente de audio y adjuntarlo al actor del jugador
    AudioComponent = NewObject<UAudioComponent>(this);
    if (AudioComponent)
    {
        AudioComponent->RegisterComponent();
        //AudioComponent->bAutoActivate = false;
        //AudioComponent->SetVolumeMultiplier(1.0f);

        if (AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
        {
            AudioComponent->AttachToComponent(PlayerActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to attach AudioComponent to player actor"));
        }
    }


    // Actualizar la historia al primer índice
    UpdateHistory();
}

void UW_Histoy_Beginning::OnContinuarHistoriaClicked()
{
    if (CurrentIndex < HistoryImages.Num() - 1)
    {
        CurrentIndex++;
        UpdateHistory();
    }
    else
    {
        ComenzarJuego();
    }
}

void UW_Histoy_Beginning::OnSaltarHistoriaClicked()
{
    // Detener el audio al saltar la historia
    if (AudioComponent)
    {
        AudioComponent->Stop();
    }
    ComenzarJuego();
}

void UW_Histoy_Beginning::UpdateHistory()
{
    if (HistoryImages.IsValidIndex(CurrentIndex) && Image_Current_His)
    {
        Image_Current_His->SetBrushFromTexture(HistoryImages[CurrentIndex]);
    }
    if (HistoryTexts.IsValidIndex(CurrentIndex) && Multi_Linea_History)
    {
        Multi_Linea_History->SetText(FText::FromString(HistoryTexts[CurrentIndex].ToString()));
    }
    if (HistorySounds.IsValidIndex(CurrentIndex) && AudioComponent)
    {
        AudioComponent->SetSound(HistorySounds[CurrentIndex]);
        AudioComponent->Play();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to update history"));
    }
}

void UW_Histoy_Beginning::ComenzarJuego()
{
    // Detener el audio al comenzar el juego
    if (AudioComponent)
    {
        AudioComponent->Stop();
    }
    AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    if (HUD)
    {
        HUD->ShowLoadingScreen(); // Mostrar la pantalla de carga final
        GetWorld()->GetTimerManager().SetTimerForNextTick([HUD]()
            {
                HUD->StartGameplay(); // Comenzar el juego después de la pantalla de carga final
            });
    }
}
