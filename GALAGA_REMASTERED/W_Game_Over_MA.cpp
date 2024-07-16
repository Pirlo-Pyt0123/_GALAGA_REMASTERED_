#include "W_Game_Over_MA.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "HUD_P_Principal.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

void UW_Game_Over_MA::NativeConstruct()
{
    Super::NativeConstruct();

    if (Menu_Regreso_Button)
    {
        Menu_Regreso_Button->OnClicked.AddDynamic(this, &UW_Game_Over_MA::OnMenuRegresoClicked);
    }

    if (Salir_Button)
    {
        Salir_Button->OnClicked.AddDynamic(this, &UW_Game_Over_MA::OnSalirClicked);
    }
}

void UW_Game_Over_MA::OnMenuRegresoClicked()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
    for (AActor* Actor : FoundActors)
    {
        if (Actor)
        {
            Actor->Destroy();
        }
    }
    UGameplayStatics::OpenLevel(GetWorld(), FName("Map_Espacial"));
}

void UW_Game_Over_MA::OnSalirClicked()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
    }
}
