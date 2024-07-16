#include "Widget_Principal.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "PF_LEVEL_DIFFICULTY_PRIM_B.h"
#include "HUD_P_Principal.h"

void UWidget_Principal::NativeConstruct()
{
    Super::NativeConstruct();

    if (BtnModoFacil)
    {
        BtnModoFacil->OnClicked.AddDynamic(this, &UWidget_Principal::OnModoFacilClicked);
    }

    if (BtnModoNormal)
    {
        BtnModoNormal->OnClicked.AddDynamic(this, &UWidget_Principal::OnModoNormalClicked);
    }

    if (BtnModoDificil)
    {
        BtnModoDificil->OnClicked.AddDynamic(this, &UWidget_Principal::OnModoDificilClicked);
    }

    if (RETURN)
    {
        RETURN->OnClicked.AddDynamic(this, &UWidget_Principal::OnReturnClicked);
    }

    if (LevelDifficultyManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("LevelDifficultyManager successfully obtained in NativeConstruct"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to obtain LevelDifficultyManager in NativeConstruct"));
    }
}

void UWidget_Principal::OnModoFacilClicked()
{
    AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    if (HUD)
    {
        HUD->StartGameplayFacil();
    }
}

void UWidget_Principal::OnModoNormalClicked()
{
    AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    if (HUD)
    {
        HUD->StartGameplayNormal();
    }
}

void UWidget_Principal::OnModoDificilClicked()
{
    AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    if (HUD)
    {
        HUD->StartGameplayDificil();
    }
}

void UWidget_Principal::OnReturnClicked()
{
    // Mostrar el menú principal
    AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    if (HUD)
    {

        HUD->HideDifficultySelection();
        HUD->ShowMainMenu();
    }
}
