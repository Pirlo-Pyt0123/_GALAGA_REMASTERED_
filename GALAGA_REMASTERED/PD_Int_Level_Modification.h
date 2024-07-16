#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PD_Int_Level_Modification.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPD_Int_Level_Modification : public UInterface
{
    GENERATED_BODY()
};

class GALAGA_REMASTERED_API IPD_Int_Level_Modification
{
    GENERATED_BODY()

public:
    // Add interface functions to this class. This is the class that will be inherited to implement this interface.
    virtual void ChangeMaterialInstance(UMaterialInstance* NewMaterial) = 0;
};
