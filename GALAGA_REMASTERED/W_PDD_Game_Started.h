#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PDD_Game_Started.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_PDD_Game_Started : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* Progress_Health;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* Progress_Speed20;

    UPROPERTY(meta = (BindWidget))
    class UButton* BUTTON_PAUSE;

    UPROPERTY(meta = (BindWidget))
    class UImage* Image_Life_01;

    UPROPERTY(meta = (BindWidget))
    class UImage* Image_Life_02;

    UPROPERTY(meta = (BindWidget))
    class UImage* Image_Life_03;

    UPROPERTY(meta = (BindWidget))
    class UImage* Image_Life_04;

    UPROPERTY(meta = (BindWidget))
    class UImage* Image_Life_05;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TerrraBley_Contador;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Time_Ivulnerabilidad_Text;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Amount_Invulnerabilidad_Text;

    UPROPERTY(meta = (BindWidget))
    class UImage* Image_Invulnerabilidad;

    UPROPERTY(meta = (BindWidget))
    class UImage* Cambio_Arma_SGO;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_NUM_OLEADA;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TextBlock_CANTIDAD_NAVES;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Images")
    UTexture2D* WeaponImage01;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Images")
    UTexture2D* WeaponImage02;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Images")
    UTexture2D* WeaponImage03;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Images")
    UTexture2D* WeaponImage04;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Images")
    UTexture2D* WeaponImage05;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Images")
    UTexture2D* WeaponImage06;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Images")
    UTexture2D* WeaponImage07;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Invulnerability Images")
    UTexture2D* InvulnerabilityImageDefault;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Invulnerability Images")
    UTexture2D* InvulnerabilityImageActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Textures")
    UTexture2D* HealthBarTextureDefault;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar Textures")
    UTexture2D* HealthBarTextureInvulnerable;

    void UpdateInvulnerabilityCount(int32 Count);
    void UpdateInvulnerabilityTimer(int32 TimeLeft);
    void UpdateCantidadNaves(int32 Count);
    void UpdateOleada(int32 Oleada, int32 Count2);
    void SetHealthProgress(float Value);
    void SetSpeedProgress(float Value);
    void UpdateLifeImages(int32 Lives);
    void UpdateTerraBleyCount(int32 Count);
    void UpdateWeaponImage(int32 WeaponIndex);
    void SetInvulnerabilityImage(bool bIsActive);
    void SetHealthBarTexture(bool bIsInvulnerable);

    void SetOleadaTextVisibility(bool bIsVisible);

    UFUNCTION()
    void OnPauseButtonClicked();

};
