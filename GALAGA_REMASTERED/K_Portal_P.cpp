
#include "K_Portal_P.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "PF_Level_Creator_P.h"
#include "HUD_P_Principal.h"
#include "W_Transition_CP.h"



AK_Portal_P::AK_Portal_P()
{
    PrimaryActorTick.bCanEverTick = true;

    Mesh_Portal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("P_Portal"));
    RootComponent = Mesh_Portal;

    Collision_Portal = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision_Portal"));
    Collision_Portal->SetupAttachment(Mesh_Portal);
    Collision_Portal->SetBoxExtent(FVector(400.f, 400.f, 400.f));

    Particle_Portal = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalParticle"));
    Particle_Portal->SetupAttachment(Collision_Portal);
}

void AK_Portal_P::BeginPlay()
{
    Super::BeginPlay();
    LevelCreator = Cast<APF_Level_Creator_P>(UGameplayStatics::GetActorOfClass(GetWorld(), APF_Level_Creator_P::StaticClass()));
    PlayerController = GetWorld()->GetFirstPlayerController();
    HUD = Cast<AHUD_P_Principal>(PlayerController->GetHUD());
}

void AK_Portal_P::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AK_Portal_P::NotifyActorBeginOverlap(AActor* OtherActor)
{
    AGALAGA_REMASTEREDPawn* Player = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);
    if (Player)
    {
        Component_Destruction();

        if (HUD)
        {
            HUD->ShowTransitionScreen();
        }

        // Inicia el siguiente nivel después de 7 segundos
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this] {StartNextLevel();}, 7.0f, false);
    }
}


void AK_Portal_P::StartNextLevel()
{
    if (LevelCreator)
    {
        LevelCreator->Next_Level_PPP();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find level creator instance"));
    }

    if (HUD)
    {
        HUD->HideTransitionScreen();
    }

}


void AK_Portal_P::Component_Destruction()
{
   this -> Destroy();
}