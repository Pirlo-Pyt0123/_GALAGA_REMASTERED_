#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Transition_CP.generated.h"

UCLASS()
class GALAGA_REMASTERED_API UW_Transition_CP : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    class UImage* Transition_Image_P;

    void SetTransitionImage(UTexture2D* NewImage);

protected:

    TArray<UTexture2D*> TransitionImages;
    static int32 CurrentImageIndex; 

    void ChangeImage();


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    class UAudioComponent* AudioComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
    class USceneComponent* SceneRoot;

public:
    void StartTransition();
};