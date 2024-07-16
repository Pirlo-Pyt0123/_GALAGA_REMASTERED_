#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PB_Int_Level_Acces.h"
#include "PB_Level_Creator.generated.h"

UCLASS()
class GALAGA_REMASTERED_API APB_Level_Creator : public AActor, public IPB_Int_Level_Acces
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APB_Level_Creator();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

public:

    void Call_Level_Function(int32 Level);

    UFUNCTION()
    void OnEnemyDestroyed(AActor* DestroyedActor);

    UFUNCTION()
    void OnObstacleDestroyed(AActor* DestroyedActor);

    UFUNCTION()
    void OnCapsuleDestroyed(AActor* DestroyedActor);

    TArray<class AZ_Enemy_Ship_P*> ActiveEnemies;
    TArray<class AInteractable_Objects_P*> ActiveObstacles;
    TArray<class AInteractable_Objects_P*> ActiveCapsules;

    FTimerHandle SpawnTimerHandle;

    class AZ_Enemy_Ship_P* Enemy_Ship_P;

    class APFM_Factory_Obstacle_P* ObstacleFactory;

    class APFM_Factory_Capsule_P* CapsuleFactory;

    int32 Current_Level;
    int32 Enemies_Oleadas;
    bool Next_Oleada;

    int32 Passed_Gold;

    void Primary_Creator();

    void RemoveNullPointersObstacles();
    void RemoveNullPointersCapsules();

    void ClearObstacles(TArray<AInteractable_Objects_P*>& ObstaclesToClear);

    void ClearCapsules(TArray<AInteractable_Objects_P*>& CapsulesToClear);

public:

    float CurrentLife;
    float CurrentSpeed;
    float CurrentDamage;

    float CurrentLife_Obstacle;
    float CurrentSpeed_Obstacle;
    float CurrentDamage_Obstacle;

    float CurrentLife_Boss;
    float CurrentSpeed_Boss;
    float CurrentDamage_Boss;

    float CurrentLife_Boss_Galactus;
    float CurrentSpeed_Boss_Galactus;
    float CurrentDamage_Boss_Galactus;

    FORCEINLINE void Set_Level_1() override;
    FORCEINLINE void Set_Level_1_1() override;

    FORCEINLINE void Set_Level_2() override;
    FORCEINLINE void Set_Level_2_1() override;

    FORCEINLINE void Set_Level_3() override;
    FORCEINLINE void Set_Level_3_1() override;

    FORCEINLINE void Set_Level_4() override;
    FORCEINLINE void Set_Level_4_1() override;

    FORCEINLINE void Set_Level_5() override;
    FORCEINLINE void Set_Level_5_1() override;

    FORCEINLINE void Set_Level_6() override;
    FORCEINLINE void Set_Level_6_1() override;

    FORCEINLINE void Set_Level_7() override;
    FORCEINLINE void Set_Level_7_1() override;

    void SpawnEnemies(TSubclassOf<AZ_Enemy_Ship_P> ShipClass, FVector BaseLocation, FVector Offset, int Count, float Health, float Speed, float Damage);

    void Configuration_Ship_N(float EnemyLife, float EnemySpeed, float EnemyDamage) override;

    void Configuration_Obstacle(float ObstacleLife, float ObstacleSpeed, float ObstacleDamage) override;

    void Configuration_Boss(float BossLife, float BossSpeed, float BossDamage) override;

    void Configuration_Boss_Galactus(float BossGalactusLife, float BossGalactusSpeed, float BossGalactusDamage) override;

    void SpawnObstacles(int Count);
    void SpawnCapsules(int Count);

    class AHUD_P_Principal* PlayerHUD;
    class UW_PDD_Game_Started* GameStartedWidget;
    int32 TopeOleada;
    int32 OleadaActual;
};