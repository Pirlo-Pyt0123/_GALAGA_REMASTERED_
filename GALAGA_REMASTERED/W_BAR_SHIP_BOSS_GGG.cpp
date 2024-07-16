#include "W_BAR_SHIP_BOSS_GGG.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Materials/MaterialInterface.h"

void UW_BAR_SHIP_BOSS_GGG::NativeConstruct()
{
    Super::NativeConstruct();

    // Inicializa las imágenes y el índice
    FillImages = { LET_MEGA_MM5,CLODD, Barra_06, Barra_05, Barra_02, LET_MEGA_MM5, CBRA };
    ImageIndex = 0;

    SetRandomFillImage(); // Llamada a la función para establecer la imagen de relleno al construirse el widget
}

void UW_BAR_SHIP_BOSS_GGG::UpdateHealthBar(float HealthPercentage, const FString& HealthText)
{
    if (PROGRESBAR_BOSS_HEALTH)
    {
        PROGRESBAR_BOSS_HEALTH->SetPercent(HealthPercentage);
    }

    if (TEXT_HEALTH_BOSS)
    {
        TEXT_HEALTH_BOSS->SetText(FText::FromString(HealthText));
    }
}

void UW_BAR_SHIP_BOSS_GGG::SetRandomFillImage()
{
    if (PROGRESBAR_BOSS_HEALTH)
    {
        int32 RandomIndex = FMath::RandRange(0, FillImages.Num() - 1);
        UObject* SelectedImage = FillImages[RandomIndex];

        FSlateBrush Brush;
        Brush.DrawAs = ESlateBrushDrawType::Image;

        if (UMaterialInterface* Material = Cast<UMaterialInterface>(SelectedImage))
        {
            Brush.SetResourceObject(Material);
            UE_LOG(LogTemp, Log, TEXT("Selected Material: %s"), *Material->GetName());
        }
        else if (UTexture2D* Texture = Cast<UTexture2D>(SelectedImage))
        {
            Brush.SetResourceObject(Texture);
            UE_LOG(LogTemp, Log, TEXT("Selected Texture: %s"), *Texture->GetName());
        }

        PROGRESBAR_BOSS_HEALTH->WidgetStyle.FillImage = Brush;
    }
}
