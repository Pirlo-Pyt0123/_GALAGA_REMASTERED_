#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PD_Int_Level_Modification.h"
#include "PD_World_Changed.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APD_World_Changed : public AActor, public IPD_Int_Level_Modification
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APD_World_Changed();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    virtual void ChangeMaterialInstance(UMaterialInstance* NewMaterialInstance) override;

private:
    UPROPERTY()
    UMaterialInstance* CurrentMaterialInstance;

    UPROPERTY()
    UMaterialInstance* MaterialInstance01;

    UPROPERTY()
    UMaterialInstance* MaterialInstance02;

    void ApplyMaterialInstance(UMaterialInstance* MaterialInstance);
};
