#include "W_Screen_Message_MA.h"
#include "Components/RichTextBlock.h"
#include "Engine/Engine.h"


void UW_Screen_Message_MA::NativeConstruct()
{
    Super::NativeConstruct();
}

void UW_Screen_Message_MA::SetMissionMessage(const FString& MissionMessage)
{
    if (Mensaje_Epic)
    {
        Mensaje_Epic->SetText(FText::FromString(MissionMessage));
    }
}