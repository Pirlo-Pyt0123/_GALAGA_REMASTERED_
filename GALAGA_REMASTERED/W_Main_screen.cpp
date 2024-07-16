#include "W_Main_screen.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "HUD_P_Principal.h"

void UW_Main_screen::NativeConstruct()
{
    Super::NativeConstruct();

    if (Game)
    {
        Game->OnClicked.AddDynamic(this, &UW_Main_screen::OnGameClicked);
    }

    if (Options)
    {
        Options->OnClicked.AddDynamic(this, &UW_Main_screen::OnOptionsClicked);
    }

    if (Controle)
    {
        Controle->OnClicked.AddDynamic(this, &UW_Main_screen::OnControleClicked);
    }

    if (Creditos)
    {
        Creditos->OnClicked.AddDynamic(this, &UW_Main_screen::OnCreditosClicked);
    }

    if (Salir)
    {
        Salir->OnClicked.AddDynamic(this, &UW_Main_screen::OnSalirClicked);
    }
}

void UW_Main_screen::OnGameClicked()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(PlayerController->GetHUD());
        if (HUD)
        {
            HUD->ShowDifficultySelection();
        }
    }
}

void UW_Main_screen::OnOptionsClicked()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(PlayerController->GetHUD());
        if (HUD)
        {
            HUD->ShowOptionsMenu();
        }
    }
}

void UW_Main_screen::OnControleClicked()
{
    // Lógica para mostrar el menú de controles
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(PlayerController->GetHUD());
        if (HUD)
        {
            HUD->ShowControlsMenu();
        }
    }
}

void UW_Main_screen::OnCreditosClicked()
{
    // Lógica para mostrar el menú de créditos
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(PlayerController->GetHUD());
        if (HUD)
        {
            HUD->ShowCreditsMenu();
        }
    }
}

void UW_Main_screen::OnSalirClicked()
{
    // Lógica para salir del juego
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
    }
}
