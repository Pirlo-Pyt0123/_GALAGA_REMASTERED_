#include "W_One_Charging.h"
#include "Components/CanvasPanel.h"

void UW_One_Charging::RemoveLoadingScreen()
{
    if (this->IsInViewport())
    {
        this->RemoveFromParent();
    }
}

void UW_One_Charging::NativeConstruct()
{
    Super::NativeConstruct();
    // Aqu� puedes inicializar cualquier l�gica adicional si es necesario
}
