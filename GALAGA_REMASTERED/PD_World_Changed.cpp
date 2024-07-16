#include "PD_World_Changed.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APD_World_Changed::APD_World_Changed()
{
    PrimaryActorTick.bCanEverTick = true;

    // Load Material Instances in constructor
    //static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstance01Finder(TEXT("Material'/Game/Space_Creator/Star_Creator/Materials/M_Space_Skybox1.M_Space_Skybox1'"));
    //static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstance02Finder(TEXT("Material'/Game/Space_Creator/Star_Creator/Materials/M_Space_Skybox.M_Space_Skybox'"));

    //static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstance01Finder(TEXT("MaterialInstanceConstant'/Game/Space_Creator/Star_Creator/Materials/M_INS_02.M_INS_01'"));
    //static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstance02Finder(TEXT("MaterialInstanceConstant'/Game/Space_Creator/Star_Creator/Materials/M_INS_02.M_INS_02'"));

    //if (MatInstance01Finder.Succeeded())
    //{
    //    MaterialInstance01 = MatInstance01Finder.Object;
    //}

    //if (MatInstance02Finder.Succeeded())
    //{
    //    MaterialInstance02 = MatInstance02Finder.Object;
   // }
}

// Called when the game starts or when spawned
void APD_World_Changed::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void APD_World_Changed::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APD_World_Changed::ChangeMaterialInstance(UMaterialInstance* NewMaterialInstance)
{
    ApplyMaterialInstance(NewMaterialInstance);
}

void APD_World_Changed::ApplyMaterialInstance(UMaterialInstance* MaterialInstance)
{
    if (!MaterialInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("MaterialInstance is NULL"));
        return;
    }

    // Obtener todos los actores estáticos del mapa
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticMeshActor::StaticClass(), FoundActors);

    for (AActor* Actor : FoundActors)
    {
        AStaticMeshActor* MeshActor = Cast<AStaticMeshActor>(Actor);
        if (MeshActor && MeshActor->GetStaticMeshComponent())
        {
            MeshActor->GetStaticMeshComponent()->SetMaterial(0, MaterialInstance);
        }
    }

    CurrentMaterialInstance = MaterialInstance;
}
