#include "W_Screen_Level_Iden.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"

void UW_Screen_Level_Iden::NativeConstruct()
{
    Super::NativeConstruct();

    // Load background materials
    BackgroundMaterials.Add(LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Game/INTERFAZ/MP_GREEN_Inst.MP_GREEN_Inst'")));
    BackgroundMaterials.Add(LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Game/INTERFAZ/MP_PURPLE_Inst.MP_PURPLE_Inst'")));
    BackgroundMaterials.Add(LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Game/INTERFAZ/MP_RED_Inst.MP_RED_Inst'")));
    BackgroundMaterials.Add(LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Game/INTERFAZ/MP_SKY_BLUE_Inst.MP_SKY_BLUE_Inst'")));
    BackgroundMaterials.Add(LoadObject<UMaterialInterface>(nullptr, TEXT("MaterialInstanceConstant'/Game/INTERFAZ/MP_YELLOW_Inst.MP_YELLOW_Inst'")));
}

void UW_Screen_Level_Iden::SetLevelMessage(const FString& LevelMessage)
{
    if (Mensaje_Pantalla_Level)
    {
        Mensaje_Pantalla_Level->SetText(FText::FromString(LevelMessage));
        ChangeBackgroundColor();
    }
}

void UW_Screen_Level_Iden::ChangeBackgroundColor()
{
    if (Colors_Change && BackgroundMaterials.Num() > 0)
    {
        int32 RandomIndex = FMath::RandRange(0, BackgroundMaterials.Num() - 1);
        UMaterialInterface* RandomMaterial = BackgroundMaterials[RandomIndex];
        Colors_Change->SetBrushFromMaterial(RandomMaterial);
    }
}

void UW_Screen_Level_Iden::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (bIsMoving)
    {
        // Handle the movement logic
    }
}

void UW_Screen_Level_Iden::StartMove()
{
    bIsMoving = true;
    // Initialize StartPosition and EndPosition
}
