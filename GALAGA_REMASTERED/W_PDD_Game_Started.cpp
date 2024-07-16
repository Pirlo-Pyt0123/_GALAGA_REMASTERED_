#include "W_PDD_Game_Started.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Engine/Engine.h"
#include "HUD_P_Principal.h"
#include "Kismet/GameplayStatics.h"

void UW_PDD_Game_Started::NativeConstruct()
{
    Super::NativeConstruct();

    // Cargar las texturas de las armas
    WeaponImage01 = LoadObject<UTexture2D>(nullptr, TEXT("/Game/HISTORY_GALAGA/ROG/A01.A01"));
    WeaponImage02 = LoadObject<UTexture2D>(nullptr, TEXT("/Game/HISTORY_GALAGA/ROG/A02.A02"));
    WeaponImage03 = LoadObject<UTexture2D>(nullptr, TEXT("/Game/HISTORY_GALAGA/ROG/A03.A03"));
    WeaponImage04 = LoadObject<UTexture2D>(nullptr, TEXT("/Game/HISTORY_GALAGA/ROG/A04.A04"));
    WeaponImage05 = LoadObject<UTexture2D>(nullptr, TEXT("/Game/HISTORY_GALAGA/ROG/A05.A05"));
    WeaponImage06 = LoadObject<UTexture2D>(nullptr, TEXT("/Game/HISTORY_GALAGA/ROG/A06.A06"));
    WeaponImage07 = LoadObject<UTexture2D>(nullptr, TEXT("/Game/HISTORY_GALAGA/ROG/A07.A07"));

    // Cargar las texturas de la invulnerabilidad
    InvulnerabilityImageDefault = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Widged/Barras/OFICIAL_INVULNERABILIDAD.OFICIAL_INVULNERABILIDAD"));
    InvulnerabilityImageActive = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Widged/Barras/OFICIAL_INVULNERABILIDAD_APAGADO.OFICIAL_INVULNERABILIDAD_APAGADO"));


    // Cargar las texturas de la barra de salud
    HealthBarTextureDefault = LoadObject<UTexture2D>(nullptr, TEXT("/Game/StarterContent/Textures/T_Fire_Tiled_D.T_Fire_Tiled_D"));
    HealthBarTextureInvulnerable = LoadObject<UTexture2D>(nullptr, TEXT("/Game/GoodFXLevelUp/FX/Resource/Textures/T_GFXLU_Fire_Glow.T_GFXLU_Fire_Glow"));

    if (BUTTON_PAUSE)
    {
        BUTTON_PAUSE->OnClicked.AddDynamic(this, &UW_PDD_Game_Started::OnPauseButtonClicked);
    }
}

void UW_PDD_Game_Started::UpdateInvulnerabilityCount(int32 Count)
{
    if (Amount_Invulnerabilidad_Text)
    {
        Amount_Invulnerabilidad_Text->SetText(FText::AsNumber(Count));
    }
}

void UW_PDD_Game_Started::UpdateInvulnerabilityTimer(int32 TimeLeft)
{
    if (Time_Ivulnerabilidad_Text)
    {
        if (TimeLeft > 0)
        {
            Time_Ivulnerabilidad_Text->SetText(FText::AsNumber(TimeLeft));
            Time_Ivulnerabilidad_Text->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            Time_Ivulnerabilidad_Text->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void UW_PDD_Game_Started::UpdateCantidadNaves(int32 Count)
{
    if (TextBlock_CANTIDAD_NAVES)
    {
        FText FormattedText = FText::Format(FText::FromString(TEXT("Cantidad de Naves: {0}")), FText::AsNumber(Count));
        TextBlock_CANTIDAD_NAVES->SetText(FormattedText);
    }
}

void UW_PDD_Game_Started::UpdateOleada(int32 Oleada, int32 Count2)
{
    if (TextBlock_NUM_OLEADA)
    {
        // Formatear el texto combinando las dos variables con el texto adicional
        FText FormattedTextOleada = FText::Format(
            FText::FromString(TEXT("Oleada: {0} / {1}")),
            FText::AsNumber(Oleada),
            FText::AsNumber(Count2)
        );

        // Actualizar el TextBlock con el texto formateado
        TextBlock_NUM_OLEADA->SetText(FormattedTextOleada);
    }
}



void UW_PDD_Game_Started::SetHealthProgress(float Value)
{
    if (Progress_Health)
    {
        Progress_Health->SetPercent(Value);
    }
}

void UW_PDD_Game_Started::SetSpeedProgress(float Value)
{
    if (Progress_Speed20)
    {
        Progress_Speed20->SetPercent(Value);
    }
}

void UW_PDD_Game_Started::UpdateLifeImages(int32 Lives)
{
    TArray<UImage*> LifeImages = { Image_Life_01, Image_Life_02, Image_Life_03, Image_Life_04, Image_Life_05 };

    for (int32 i = 0; i < LifeImages.Num(); ++i)
    {
        if (LifeImages[i])
        {
            LifeImages[i]->SetVisibility(i < Lives ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
        }
    }
}

void UW_PDD_Game_Started::UpdateTerraBleyCount(int32 Count)
{
    if (TerrraBley_Contador)
    {
        TerrraBley_Contador->SetText(FText::AsNumber(Count));
    }
}

void UW_PDD_Game_Started::UpdateWeaponImage(int32 WeaponIndex)
{
    if (Cambio_Arma_SGO)
    {
        UTexture2D* NewTexture = nullptr;

        switch (WeaponIndex)
        {
        case 1:
            NewTexture = WeaponImage01;
            break;
        case 2:
            NewTexture = WeaponImage02;
            break;
        case 3:
            NewTexture = WeaponImage03;
            break;
        case 4:
            NewTexture = WeaponImage04;
            break;
        case 5:
            NewTexture = WeaponImage05;
            break;
        case 6:
            NewTexture = WeaponImage06;
            break;
        case 7:
            NewTexture = WeaponImage07;
            break;
        default:
            break;
        }

        if (NewTexture)
        {
            Cambio_Arma_SGO->SetBrushFromTexture(NewTexture);
        }
    }
}


void UW_PDD_Game_Started::SetInvulnerabilityImage(bool bIsActive)
{
    if (Image_Invulnerabilidad)
    {
        UTexture2D* NewTexture = bIsActive ? InvulnerabilityImageActive : InvulnerabilityImageDefault;
        if (NewTexture)
        {
            Image_Invulnerabilidad->SetBrushFromTexture(NewTexture);
        }
    }
}

void UW_PDD_Game_Started::SetHealthBarTexture(bool bIsInvulnerable)
{
    if (Progress_Health)
    {
        UTexture2D* NewTexture = bIsInvulnerable ? HealthBarTextureInvulnerable : HealthBarTextureDefault;
        if (NewTexture)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(NewTexture);
            Progress_Health->WidgetStyle.FillImage.SetResourceObject(NewTexture);
        }
    }
}

void UW_PDD_Game_Started::SetOleadaTextVisibility(bool bIsVisible)
{
    if (TextBlock_CANTIDAD_NAVES)
    {
        TextBlock_CANTIDAD_NAVES->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }

    if (TextBlock_NUM_OLEADA)
    {
        TextBlock_NUM_OLEADA->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}


void UW_PDD_Game_Started::OnPauseButtonClicked()
{
    AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    if (HUD)
    {
        HUD->ShowPauseMenu();
    }
}
