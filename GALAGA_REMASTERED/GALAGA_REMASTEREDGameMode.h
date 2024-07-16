#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GALAGA_REMASTEREDGameMode.generated.h"

UCLASS(MinimalAPI)
class AGALAGA_REMASTEREDGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:

    AGALAGA_REMASTEREDGameMode();

protected:

    virtual void BeginPlay() override;
};
