#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Principal.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UWidget_Principal : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(meta = (BindWidget))
    class UButton* BtnModoFacil;

    UPROPERTY(meta = (BindWidget))
    class UButton* BtnModoNormal;

    UPROPERTY(meta = (BindWidget))
    class UButton* BtnModoDificil;

    UPROPERTY(meta = (BindWidget))
    class UButton* RETURN;

    UPROPERTY()
    class APF_LEVEL_DIFFICULTY_PRIM_B* LevelDifficultyManager;

    virtual void NativeConstruct() override;

    UFUNCTION()
    void OnModoFacilClicked();

    UFUNCTION()
    void OnModoNormalClicked();

    UFUNCTION()
    void OnModoDificilClicked();

    UFUNCTION()
    void OnReturnClicked();

private:
    void SwitchToGameMode();
};
