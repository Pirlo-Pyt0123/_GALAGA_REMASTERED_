#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_One_Charging.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_One_Charging : public UUserWidget
{
    GENERATED_BODY()

public:

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* Canvas_Carga_P;

    // Función para remover la pantalla de carga
    UFUNCTION(BlueprintCallable, Category = "UI")
    void RemoveLoadingScreen();

protected:
    // Función que se llama cuando se construye el widget
    virtual void NativeConstruct() override;
};
