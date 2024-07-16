#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Creditos_MP.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_Creditos_MP : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UButton* Regresar_Main_Cred;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* V_Creditos_A;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    UFUNCTION()
    void OnRegresarClicked();

    FVector2D InitialPosition;
    float Speed;

};
