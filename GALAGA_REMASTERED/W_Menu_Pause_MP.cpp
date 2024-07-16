// Fill out your copyright notice in the Description page of Project Settings.

#include "W_Menu_Pause_MP.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "HUD_P_Principal.h"
#include "W_Controler_Ma.h"

void UW_Menu_Pause_MP::NativeConstruct()
{
    Super::NativeConstruct();

    if (Continuar_MP)
    {
        Continuar_MP->OnClicked.AddDynamic(this, &UW_Menu_Pause_MP::OnContinuarClicked);
    }

    if (Controles_MP)
    {
        Controles_MP->OnClicked.AddDynamic(this, &UW_Menu_Pause_MP::OnControlesClicked);
    }

    if (Regresar_Menu_Principal_MP)
    {
        Regresar_Menu_Principal_MP->OnClicked.AddDynamic(this, &UW_Menu_Pause_MP::OnRegresarMenuPrincipalClicked);
    }
}

void UW_Menu_Pause_MP::OnContinuarClicked()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(PlayerController->GetHUD());
        if (HUD)
        {
            HUD->HidePauseMenu();
        }
    }
}

void UW_Menu_Pause_MP::OnControlesClicked()
{
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


void UW_Menu_Pause_MP::OnRegresarMenuPrincipalClicked()
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
