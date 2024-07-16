#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Screen_Message_MA.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_Screen_Message_MA : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void SetMissionMessage(const FString& MissionMessage);

private:
    UPROPERTY(meta = (BindWidget))
    class URichTextBlock* Mensaje_Epic;
};