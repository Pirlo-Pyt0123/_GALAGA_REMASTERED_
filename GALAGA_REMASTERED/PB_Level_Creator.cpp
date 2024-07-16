
#include "PB_Level_Creator.h"
#include "Z_Enemy_Ship_P.h"
#include "Z_Ship_Vortex.h"
#include "Z_Ship_Striker.h"
#include "Z_Ship_Tempest.h"
#include "Z_Ship_Specter.h"
#include "Z_Ship_Spark.h"
#include "Z_Ship_Bomber.h"
#include "Z_Ship_Cyclone.h"
#include "X_Master_Ship_Armageddon.h"
#include "X_Master_Ship_Chaos.h"
#include "X_Master_Ship_Colossus.h"
#include "X_Master_Ship_Leviathan.h"
#include "X_Master_Ship_Overlord.h"
#include "X_Master_Ship_Conqueror.h"
#include "X_Master_Ship_Titan.h"
#include "X_Master_Ship_P.h"
#include "EPIC_GALACTUS_FINAL_BOSS.h"
#include "Interactable_Objects_P.h"
#include "PFM_Factory_Capsule_P.h"
#include "PFM_Factory_Obstacle_P.h"
#include "HUD_P_Principal.h"
#include "W_PDD_Game_Started.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

APB_Level_Creator::APB_Level_Creator()
{
	PrimaryActorTick.bCanEverTick = true;
	Enemies_Oleadas = 0;
	Next_Oleada = true;
	Current_Level = 0;
	Passed_Gold = 0;
}

void APB_Level_Creator::BeginPlay()
{
	Super::BeginPlay();

	// Buscar y almacenar referencia al widget de UI
	PlayerHUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	// Verificar si PlayerHUD y GameStartedWidget están inicializados correctamente
	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("GameStartedWidget is initialized correctly"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("GameStartedWidget is not initialized correctly"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerHUD or GameStartedWidget is not initialized"));
	}

	ObstacleFactory = GetWorld()->SpawnActor<APFM_Factory_Obstacle_P>(APFM_Factory_Obstacle_P::StaticClass());
	if (!ObstacleFactory)
	{
		UE_LOG(LogTemp, Error, TEXT("ObstacleFactory is not initialized!"));
	}

	CapsuleFactory = GetWorld()->SpawnActor<APFM_Factory_Capsule_P>(APFM_Factory_Capsule_P::StaticClass());
	if (!CapsuleFactory)
	{
		UE_LOG(LogTemp, Error, TEXT("CapsuleFactory is not initialized!"));
	}

	if (GameStartedWidget)
	{
		GameStartedWidget->UpdateCantidadNaves(ActiveEnemies.Num());
	}

	// Actualizar el número de oleada
	if (GameStartedWidget)
	{
		GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
	}
}

void APB_Level_Creator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameStartedWidget)
	{
		GameStartedWidget->UpdateCantidadNaves(ActiveEnemies.Num());
	}

	// Actualizar el número de oleada
	if (GameStartedWidget)
	{
		GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
	}
}

void APB_Level_Creator::Configuration_Ship_N(float EnemyLife, float EnemySpeed, float EnemyDamage)
{
	CurrentLife = EnemyLife;
	CurrentSpeed = EnemySpeed;
	CurrentDamage = EnemyDamage;
	Passed_Gold++;
	Primary_Creator();
}

void APB_Level_Creator::Configuration_Obstacle(float ObstacleLife, float ObstacleSpeed, float ObstacleDamage)
{
	CurrentLife_Obstacle = ObstacleLife;
	CurrentSpeed_Obstacle = ObstacleSpeed;
	CurrentDamage_Obstacle = ObstacleDamage;
	Passed_Gold++;
	Primary_Creator();
}

void APB_Level_Creator::Configuration_Boss(float BossLife, float BossSpeed, float BossDamage)
{
	CurrentLife_Boss = BossLife;
	CurrentSpeed_Boss = BossSpeed;
	CurrentDamage_Boss = BossDamage;
	Passed_Gold++;
	Primary_Creator();
}

void APB_Level_Creator::Configuration_Boss_Galactus(float BossGalactusLife, float BossGalactusSpeed, float BossGalactusDamage)
{
	CurrentLife_Boss_Galactus = BossGalactusLife;
	CurrentSpeed_Boss_Galactus = BossGalactusSpeed;
	CurrentDamage_Boss_Galactus = BossGalactusDamage;
	Passed_Gold++;
	Primary_Creator();
}

void APB_Level_Creator::Primary_Creator()
{
	if (Passed_Gold == 4)
	{
		Call_Level_Function(1);
	}
}

void APB_Level_Creator::RemoveNullPointersObstacles()
{
	ActiveObstacles.RemoveAll([](AInteractable_Objects_P* Actor) { return !IsValid(Actor); });
}

void APB_Level_Creator::RemoveNullPointersCapsules()
{
	ActiveCapsules.RemoveAll([](AInteractable_Objects_P* Actor) { return !IsValid(Actor); });
}

void APB_Level_Creator::ClearObstacles(TArray<AInteractable_Objects_P*>& ObstaclesToClear)
{
	for (AInteractable_Objects_P* Obstacle : ObstaclesToClear)
	{
		if (IsValid(Obstacle))
		{
			Obstacle->Destroy();
		}
	}
	ActiveObstacles.Empty();
}

void APB_Level_Creator::ClearCapsules(TArray<AInteractable_Objects_P*>& CapsulesToClear)
{
	for (AInteractable_Objects_P* Capsule : CapsulesToClear)
	{
		if (IsValid(Capsule))
		{
			Capsule->Destroy();
		}
	}
	ActiveCapsules.Empty();
}

void APB_Level_Creator::Call_Level_Function(int32 Level)
{
	switch (Level)
	{
	case 1:
		OleadaActual += 1;
		Set_Level_1();
		break;
	case 2:
		OleadaActual++;
		Set_Level_1_1();
		break;
	case 3:
		OleadaActual++;
		Set_Level_2();
		break;
	case 4:
		OleadaActual++;
		Set_Level_2_1();
		break;
	case 5:
		OleadaActual++;
		Set_Level_3();
		break;
	case 6:
		OleadaActual++;
		Set_Level_3_1();
		break;
	case 7:
		OleadaActual++;
		Set_Level_4();
		break;
	case 8:
		OleadaActual++;
		Set_Level_4_1();
		break;
	case 9:
		OleadaActual++;
		Set_Level_5();
		break;
	case 10:
		OleadaActual++;
		Set_Level_5_1();
		break;
	case 11:
		OleadaActual++;
		Set_Level_6();
		break;
	case 12:
		OleadaActual++;
		Set_Level_6_1();
		break;
	case 13:
		OleadaActual++;
		Set_Level_7();
		break;
	case 14:
		Set_Level_7_1();
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown level number %d"), Level);
		break;
	}
}

void APB_Level_Creator::Set_Level_1()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 1;
		Next_Oleada = false;

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(2000.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);

		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 5, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 4, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}

		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Chaos* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Chaos>(AX_Master_Ship_Chaos::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_1_1()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 2;
		Next_Oleada = false;

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);

		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 5, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 3, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Leviathan* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Leviathan>(AX_Master_Ship_Leviathan::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_2()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 3;
		Next_Oleada = false;

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);

		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 4, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 4, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Colossus* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Colossus>(AX_Master_Ship_Colossus::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss + 100.0f);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss + 20.0f);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss + 10.0f);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_2_1()
{

	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 4;
		Next_Oleada = false;


		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);

		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 2, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 4, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		Enemies_Oleadas--;


		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Overlord* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Overlord>(AX_Master_Ship_Overlord::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_3()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 5;
		Next_Oleada = false;

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);


		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 1, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 4, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 4, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Chaos* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Chaos>(AX_Master_Ship_Chaos::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss + 100.0f);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss + 20.0f);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss + 10.0f);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_3_1()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 6;
		Next_Oleada = false;


		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);


		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 2, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 3, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Titan* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Titan>(AX_Master_Ship_Titan::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_4()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 7;
		Next_Oleada = false;


		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);


		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 2, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 4, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Colossus* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Colossus>(AX_Master_Ship_Colossus::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);

		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_4_1()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 8;
		Next_Oleada = false;


		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);


		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 2, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 3, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		SpawnEnemies(AZ_Ship_Spark::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}

	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Conqueror* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Conqueror>(AX_Master_Ship_Conqueror::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_5()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 1;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 9;
		Next_Oleada = false;


		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);

		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 2, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		SpawnEnemies(AZ_Ship_Spark::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 300.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Armageddon* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Armageddon>(AX_Master_Ship_Armageddon::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_5_1()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 10;
		Next_Oleada = false;


		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);

		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 2, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		SpawnEnemies(AZ_Ship_Spark::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 300.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		Enemies_Oleadas--;


		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Overlord* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Overlord>(AX_Master_Ship_Overlord::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_6()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;;
		Current_Level = 11;
		Next_Oleada = false;


		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);

		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 2, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		SpawnEnemies(AZ_Ship_Spark::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 300.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		SpawnEnemies(AZ_Ship_Striker::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 200.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Colossus* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Colossus>(AX_Master_Ship_Colossus::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_6_1()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 1;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 12;
		Next_Oleada = false;

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);

		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 2, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		SpawnEnemies(AZ_Ship_Spark::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 300.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		SpawnEnemies(AZ_Ship_Striker::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 200.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		SpawnEnemies(AZ_Ship_Tempest::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 400.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Titan* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Titan>(AX_Master_Ship_Titan::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_7()
{
	if (Next_Oleada)
	{
		Enemies_Oleadas = 2;
		TopeOleada = Enemies_Oleadas;
		OleadaActual = 1;
		Current_Level = 13;
		Next_Oleada = false;

		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(true);
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
			}
		}

		SpawnObstacles(150);
		SpawnCapsules(35);
	}

	if (Enemies_Oleadas > 0 && ActiveEnemies.Num() == 0)
	{
		FVector BaseLocation = FVector(0.0f, 0.0f, 0.0f);
		FVector Offset = FVector(2000.0f, 2000.0f, 2000.0f);

		SpawnEnemies(AZ_Ship_Vortex::StaticClass(), BaseLocation, Offset, 1, CurrentLife, CurrentSpeed, CurrentDamage);

		SpawnEnemies(AZ_Ship_Bomber::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 30.f, CurrentSpeed + 5.f, CurrentDamage + 8.f);

		SpawnEnemies(AZ_Ship_Cyclone::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 40.f, CurrentSpeed + 900.f, CurrentDamage + 100.f);

		SpawnEnemies(AZ_Ship_Specter::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 90.f, CurrentSpeed + 1300.f, CurrentDamage + 500.f);

		SpawnEnemies(AZ_Ship_Spark::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 300.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		SpawnEnemies(AZ_Ship_Striker::StaticClass(), BaseLocation, Offset, 2, CurrentLife + 200.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		SpawnEnemies(AZ_Ship_Tempest::StaticClass(), BaseLocation, Offset, 1, CurrentLife + 400.f, CurrentSpeed + 1900.f, CurrentDamage + 600.f);

		Enemies_Oleadas--;

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				if (TopeOleada == OleadaActual)
				{
					OleadaActual = TopeOleada;
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
				else
				{
					GameStartedWidget->UpdateOleada(TopeOleada, OleadaActual);
				}
			}
		}
	}
	else if (Enemies_Oleadas == 0 && ActiveEnemies.Num() == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetOleadaTextVisibility(false);
		}
		TArray<AInteractable_Objects_P*> ObstaclesToClear = ActiveObstacles;
		TArray<AInteractable_Objects_P*> CapsulesToClear = ActiveCapsules;

		// Limpiar los obstáculos y cápsulas fuera de la iteración del array
		ClearObstacles(ObstaclesToClear);
		ClearCapsules(CapsulesToClear);
		FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
		FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

		// Spawn del jefe
		AX_Master_Ship_Armageddon* BossShip = GetWorld()->SpawnActor<AX_Master_Ship_Armageddon>(AX_Master_Ship_Armageddon::StaticClass(), BaseLocationBoss, DefaultRotation);

		if (BossShip)
		{
			BossShip->Set_Vida(CurrentLife_Boss);
			BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss);
			BossShip->Set_Danio_Disparo(CurrentDamage_Boss);
		}
		Next_Oleada = true;
	}
}

void APB_Level_Creator::Set_Level_7_1()
{
	FVector BaseLocationBoss = FVector(4000.0f, 0.0f, 210.0f);
	FRotator DefaultRotation = FRotator(0.0f, 0.0f, 0.0f);

	// Spawn del jefe final Galactus
	AEPIC_GALACTUS_FINAL_BOSS* BossShip = GetWorld()->SpawnActor<AEPIC_GALACTUS_FINAL_BOSS>(AEPIC_GALACTUS_FINAL_BOSS::StaticClass(), BaseLocationBoss, DefaultRotation);

	if (BossShip)
	{
		BossShip->Set_Vida(CurrentLife_Boss_Galactus);
		BossShip->Set_Velocidad_Nave(CurrentSpeed_Boss_Galactus);
		BossShip->Set_Danio_Disparo(CurrentDamage_Boss_Galactus);
	}

}

void APB_Level_Creator::SpawnEnemies(TSubclassOf<AZ_Enemy_Ship_P> ShipClass, FVector BaseLocation, FVector Offset, int Count, float Health, float Speed, float Damage)
{
	FRotator defaultRotation = FRotator(0.0f, 0.0f, 0.0f);

	// Definir los límites dentro de los cuales se pueden crear las naves
	const float XRange = 400000.0f;
	const float YRange = 400000.0f;
	const float ZRange = 400000.0f;
	const float MinDistanceBetweenShips = 10500.0f; // Distancia mínima entre naves

	TArray<FVector> SpawnLocations;

	for (int i = 0; i < Count; i++)
	{
		FVector location = BaseLocation + Offset * i;

		// Asegurar que las naves siempre se crean dentro de los rangos especificados y separadas por la distancia mínima
		bool bLocationIsValid = false;

		while (!bLocationIsValid)
		{
			location = BaseLocation + FVector(
				FMath::RandRange(-XRange, XRange),
				FMath::RandRange(-YRange, YRange),
				FMath::RandRange(0.0f, ZRange)
			);

			bLocationIsValid = true;

			for (const FVector& SpawnedLocation : SpawnLocations)
			{
				if (FVector::Dist(location, SpawnedLocation) < MinDistanceBetweenShips)
				{
					bLocationIsValid = false;
					break;
				}
			}
		}

		auto EnemyShip = GetWorld()->SpawnActor<AZ_Enemy_Ship_P>(ShipClass, location, defaultRotation);
		if (EnemyShip)
		{
			EnemyShip->Set_Vida(Health);
			EnemyShip->Set_Velocidad_Nave(Speed);
			EnemyShip->Set_Danio_Disparo(Damage);

			EnemyShip->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnEnemyDestroyed);
			ActiveEnemies.Add(EnemyShip);

			SpawnLocations.Add(location);
		}
	}

	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			GameStartedWidget->UpdateCantidadNaves(ActiveEnemies.Num());
		}
	}
}

void APB_Level_Creator::OnEnemyDestroyed(AActor* DestroyedActor)
{
	AZ_Enemy_Ship_P* DestroyedShip = Cast<AZ_Enemy_Ship_P>(DestroyedActor);
	if (DestroyedShip)
	{
		ActiveEnemies.RemoveSingle(DestroyedShip);

		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateCantidadNaves(ActiveEnemies.Num());
			}
		}

		if (ActiveEnemies.Num() == 0)
		{
			if (Enemies_Oleadas > 0)
			{
				GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, [this]() {
					Call_Level_Function(Current_Level);  // Llama a la función de nivel adecuada
					}, 5.0f, false);
			}
			else
			{

				GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, [this]() {
					Call_Level_Function(Current_Level);  // Llama a la función de nivel adecuada
					}, 5.0f, false);

			}
		}
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateCantidadNaves(ActiveEnemies.Num());
			}
		}
	}
}

void APB_Level_Creator::SpawnObstacles(int Count)
{
	for (int i = 0; i < Count; i++)
	{
		if (ObstacleFactory)
		{
			AInteractable_Objects_P* Obstacle = ObstacleFactory->Create_Interactable_Object("Obstacle_Asteroide");
			if (Obstacle)
			{
				Obstacle->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnObstacleDestroyed);
				ActiveObstacles.Add(Obstacle);
			}

			Obstacle = ObstacleFactory->Create_Interactable_Object("Obstacle_Cometa");
			if (Obstacle)
			{
				Obstacle->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnObstacleDestroyed);
				ActiveObstacles.Add(Obstacle);
			}

			Obstacle = ObstacleFactory->Create_Interactable_Object("Obstacle_Galactic_Mines");
			if (Obstacle)
			{
				Obstacle->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnObstacleDestroyed);
				ActiveObstacles.Add(Obstacle);
			}

			Obstacle = ObstacleFactory->Create_Interactable_Object("Obstacle_Satelite");
			if (Obstacle)
			{
				Obstacle->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnObstacleDestroyed);
				ActiveObstacles.Add(Obstacle);
			}

			Obstacle = ObstacleFactory->Create_Interactable_Object("Obstacle_Trufi");
			if (Obstacle)
			{
				Obstacle->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnObstacleDestroyed);
				ActiveObstacles.Add(Obstacle);
			}

			Obstacle = ObstacleFactory->Create_Interactable_Object("Obstacle_Desechos");
			if (Obstacle)
			{
				Obstacle->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnObstacleDestroyed);
				ActiveObstacles.Add(Obstacle);
			}

			Obstacle = ObstacleFactory->Create_Interactable_Object("Obstacle_Station");
			if (Obstacle)
			{
				Obstacle->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnObstacleDestroyed);
				ActiveObstacles.Add(Obstacle);
			}
		}
	}
}

void APB_Level_Creator::SpawnCapsules(int Count)
{
	for (int i = 0; i < Count; i++)
	{
		if (CapsuleFactory)
		{
			AInteractable_Objects_P* Capsule = CapsuleFactory->Create_Interactable_Object("Capsule_Health_Half");
			if (Capsule)
			{
				Capsule->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnCapsuleDestroyed);
				ActiveCapsules.Add(Capsule);
			}

			Capsule = CapsuleFactory->Create_Interactable_Object("Capsule_Health_Total");
			if (Capsule)
			{
				Capsule->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnCapsuleDestroyed);
				ActiveCapsules.Add(Capsule);
			}

			Capsule = CapsuleFactory->Create_Interactable_Object("Capsule_Invulnerabilidad");
			if (Capsule)
			{
				Capsule->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnCapsuleDestroyed);
				ActiveCapsules.Add(Capsule);
			}

			Capsule = CapsuleFactory->Create_Interactable_Object("Capsule_Life");
			if (Capsule)
			{
				Capsule->OnDestroyed.AddDynamic(this, &APB_Level_Creator::OnCapsuleDestroyed);
				ActiveCapsules.Add(Capsule);
			}
		}
	}
}

void APB_Level_Creator::OnObstacleDestroyed(AActor* DestroyedActor)
{
	AInteractable_Objects_P* DestroyedObstacle = Cast<AInteractable_Objects_P>(DestroyedActor);
	if (DestroyedObstacle)
	{
		ActiveObstacles.RemoveSingle(DestroyedObstacle);
	}
}

void APB_Level_Creator::OnCapsuleDestroyed(AActor* DestroyedActor)
{
	AInteractable_Objects_P* DestroyedCapsule = Cast<AInteractable_Objects_P>(DestroyedActor);
	if (DestroyedCapsule)
	{
		ActiveCapsules.RemoveSingle(DestroyedCapsule);
	}
}