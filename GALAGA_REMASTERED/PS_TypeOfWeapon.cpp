#include "PS_TypeOfWeapon.h"

APS_TypeOfWeapon::APS_TypeOfWeapon()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APS_TypeOfWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APS_TypeOfWeapon::AlterShootingType(AActor* MyChanceWeapon)
{
    ChangeWeapon = Cast<IPS_ChangeWeapon>(MyChanceWeapon);

    if (!ChangeWeapon)
    {
        UE_LOG(LogTemp, Error, TEXT("AlterShoot(): ¡El actor no es una estrategia de ChangeWeapon! ¿Estás seguro de que el actor implementa esa interfaz? "));
    }
}

void APS_TypeOfWeapon::UseWeapon(FVector _LocationPlayer, bool Activate)
{
    if (!ChangeWeapon)
    {
        UE_LOG(LogTemp, Error, TEXT("Change(): ChangeWeapon es NULL, asegúrese de que esté inicializado."));
        return;
    }

    ChangeWeapon->ShotFire(_LocationPlayer, Activate);
}

void APS_TypeOfWeapon::BeginPlay()
{
    Super::BeginPlay();
}
