// Fill out your copyright notice in the Description page of Project Settings.
#include "W_Creditos_MP.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "HUD_P_Principal.h"

void UW_Creditos_MP::NativeConstruct()
{
    Super::NativeConstruct();

    if (Regresar_Main_Cred)
    {
        Regresar_Main_Cred->OnClicked.AddDynamic(this, &UW_Creditos_MP::OnRegresarClicked);
    }

    if (V_Creditos_A)
    {
        InitialPosition = V_Creditos_A->RenderTransform.Translation;
        Speed = 50.0f; // Ajusta la velocidad del desplazamiento según sea necesario
    }
}

void UW_Creditos_MP::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (V_Creditos_A)
    {
        FVector2D NewPosition = V_Creditos_A->RenderTransform.Translation;
        NewPosition.Y -= Speed * InDeltaTime;
        V_Creditos_A->SetRenderTranslation(NewPosition);
    }
}

void UW_Creditos_MP::OnRegresarClicked()
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
