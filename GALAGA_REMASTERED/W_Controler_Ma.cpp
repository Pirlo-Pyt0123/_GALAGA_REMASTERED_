// Fill out your copyright notice in the Description page of Project Settings.

#include "W_Controler_Ma.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "HUD_P_Principal.h"

void UW_Controler_Ma::NativeConstruct()
{
    Super::NativeConstruct();

    if (Regre_Main_P)
    {
        Regre_Main_P->OnClicked.AddDynamic(this, &UW_Controler_Ma::OnRegresarClicked);
    }
}

void UW_Controler_Ma::OnRegresarClicked()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(PlayerController->GetHUD());
        if (HUD)
        {
            HUD->HideControlsMenu();
            //HUD->ShowMainMenu(); 
        }
    }
}
