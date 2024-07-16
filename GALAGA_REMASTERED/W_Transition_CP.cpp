#include "W_Transition_CP.h"
#include "Components/Image.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundWave.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"

int32 UW_Transition_CP::CurrentImageIndex = 0;

void UW_Transition_CP::NativeConstruct()
{
    Super::NativeConstruct();

    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC1_0.PC1_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC10_0.PC10_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC11_0.PC11_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC12_0.PC12_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC2_0.PC2_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC3_0.PC3_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC4_0.PC4_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC5_0_.PC5_0_'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC6_0.PC6_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC7_0.PC7_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC8_0.PC8_0'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/GEMA_UNIDAD_COMPLET.GEMA_UNIDAD_COMPLET'")));
    TransitionImages.Add(LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/HISTORY_GALAGA/PANTALLA_CARGA/PC9_0.PC9_0'")));

    ChangeImage();

    // Crear y configurar el componente de audio
    AudioComponent = NewObject<UAudioComponent>(this);
    if (AudioComponent)
    {
        AudioComponent->RegisterComponent();

        // Intentar obtener el actor del jugador y adjuntar el componente de audio
        if (APlayerController* PlayerController = GetOwningPlayer())
        {
            if (APawn* PlayerPawn = PlayerController->GetPawn())
            {
                AudioComponent->AttachToComponent(PlayerPawn->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

                USoundBase* TransitionSound = LoadObject<USoundBase>(nullptr, TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/TRANSICION_PORTAL.TRANSICION_PORTAL'"));
                if (TransitionSound)
                {
                    AudioComponent->SetSound(TransitionSound);
                    AudioComponent->Play();
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to load transition sound"));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to attach AudioComponent to player pawn: Player pawn not found"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to attach AudioComponent to player controller: Player controller not found"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create AudioComponent"));
    }
}

void UW_Transition_CP::ChangeImage()
{
    if (TransitionImages.IsValidIndex(CurrentImageIndex))
    {
        UTexture2D* CurrentImage = TransitionImages[CurrentImageIndex];
        if (CurrentImage)
        {
            Transition_Image_P->SetBrushFromTexture(CurrentImage);
        }
    }
    CurrentImageIndex++;
}

void UW_Transition_CP::SetTransitionImage(UTexture2D* NewImage)
{
    if (Transition_Image_P)
    {
        Transition_Image_P->SetBrushFromTexture(NewImage);
    }
}

void UW_Transition_CP::StartTransition()
{
    ChangeImage();
}
