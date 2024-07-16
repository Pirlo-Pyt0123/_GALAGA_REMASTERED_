// EPIC_GALACTUS_FINAL_BOSS.cpp

#include "EPIC_GALACTUS_FINAL_BOSS.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "C_Ametralladora_plasma.h"
#include "C_Projectile.h"
#include "AC_MOVEMENT_EPIC.h"
#include "HUD_P_Principal.h"
#include "Widget_Bar_Galactus.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "CB_Space_Sword.h"
#include "CB_Asteroid_Sword.h"
#include "CB_Ice_Sword.h"
#include "CB_Lava_Sword.h"

// Sets default values
AEPIC_GALACTUS_FINAL_BOSS::AEPIC_GALACTUS_FINAL_BOSS()
{
    // Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Assets/Meshes/Scifi_Ship_Cruiser-FBX.Scifi_Ship_Cruiser-FBX'"));
    if (MeshAsset.Succeeded())
    {
        Mesh->SetStaticMesh(MeshAsset.Object);


		
    }
	Particulas_Muerte = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particulas_Muerte"));
	Particulas_Muerte->SetupAttachment(Mesh);

    // Particula de la nave
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MFK/Particles_Tiny/FlatRings/Clusters/Par_FW_FlatRing_02_CL2_Rain_Tiny.Par_FW_FlatRing_02_CL2_Rain_Tiny'"));

	if (ParticleAsset.Succeeded())
	{
		Particulas_Muerte->SetTemplate(ParticleAsset.Object);
		Particulas_Muerte->bAutoActivate = false;
		Particulas_Muerte->SetWorldScale3D(FVector(10000.5f, 10000.5f, 10000.5f));
	}



    // Sonidos
    static ConstructorHelpers::FObjectFinder<USoundBase> SonidoAparecer(TEXT("SoundWave'/Game/BOSS_SOUNDS/GALACTUS_USFX0.GALACTUS_USFX0'"));
    if (SonidoAparecer.Succeeded())
    {
        Sonido_Aparecer = SonidoAparecer.Object;
    }

   

    Audio_Aparecer = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio_Aparecer"));
    Audio_Aparecer->bAutoActivate = false;
    Audio_Aparecer->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetExplosionSound(TEXT("SoundWave'/Game/BOSS_SOUNDS/METAMO.METAMO'"));
	if (AssetExplosionSound.Succeeded())
	{
		Audio_Aparecer->SetSound(AssetExplosionSound.Object);
	}



	Nia_Gal = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Nia_Gal"));
	Nia_Gal->SetupAttachment(Mesh);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset(TEXT("NiagaraSystem'/Game/GrimzaFX/Particles/GAL_EPIC.GAL_EPIC'"));
	if (NiagaraAsset.Succeeded())
	{
		Nia_Gal->SetAsset(NiagaraAsset.Object);
		Nia_Gal->SetWorldScale3D(FVector(17.8f, 17.8f, 17.8f));
	}




    static ConstructorHelpers::FObjectFinder<USoundBase> SonidoDisparo(TEXT("SoundWave'/Game/BOSS_SOUNDS/ASTRO_BEAN.ASTRO_BEAN'"));
    if (SonidoDisparo.Succeeded())
    {
        Sonido_Disparo = SonidoDisparo.Object;
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> SonidoMuerte(TEXT("SoundWave'/Game/BOSS_SOUNDS/EXPLO_BOSS.EXPLO_BOSS'"));
    if (SonidoMuerte.Succeeded())
    {
        Sonido_Muerte = SonidoMuerte.Object;
    }

    Poderes_left = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Poderes_left"));
    Poderes_left->SetupAttachment(Mesh);

    Poderes_right = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Poderes_right"));
    Poderes_right->SetupAttachment(Mesh);

    // Particulas de poderes especiales
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticlePoderes(TEXT("ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/P_Projectile_WaterBall01_Blue.P_Projectile_WaterBall01_Blue'"));
    if (ParticlePoderes.Succeeded())
    {
        Poderes_left->SetTemplate(ParticlePoderes.Object);
        Poderes_left->bAutoActivate = true;
        Poderes_left->SetRelativeLocation(FVector(8000.0f, -10000.0f, 0.0f));
        Poderes_left->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
        Poderes_left->SetWorldScale3D(FVector(50.5f, 50.5f, 50.5f));

        Poderes_right->SetTemplate(ParticlePoderes.Object);
        Poderes_right->bAutoActivate = true;
        Poderes_right->SetRelativeLocation(FVector(-8000.0f, -10000.0f, 0.0f));
        Poderes_right->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
        Poderes_right->SetWorldScale3D(FVector(50.5f, 50.5f, 50.5f));
    }

	Aparicion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Aparicion"));
	Aparicion->SetupAttachment(Mesh);

	// Particulas de aparicion
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAparicion(TEXT("ParticleSystem'/Game/MFK/Particles/Expanders/Par_ExpFire_01_Rain.Par_ExpFire_01_Rain'"));
	if (ParticleAparicion.Succeeded())
	{
	
		Aparicion->SetTemplate(ParticleAparicion.Object);
		Aparicion->bAutoActivate = true;

		Aparicion->SetWorldScale3D(FVector(40.5f, 40.5f, 40.5f));

	}

	Quemadura = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Quemadura"));
	Quemadura->SetupAttachment(Mesh);

	// Particulas de quemadura
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleQuemadura(TEXT("ParticleSystem'/Game/StylizedFX_2/ParticleSystems/P_Fire_2.P_Fire_2'"));
	if (ParticleQuemadura.Succeeded())
	{

		Quemadura->SetTemplate(ParticleQuemadura.Object);
		Quemadura->bAutoActivate = false;
		Quemadura->SetWorldScale3D(FVector(50.5f, 50.5f, 50.5f));

	}

	Fugas = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fugas"));
	Fugas->SetupAttachment(Mesh);

	// Particulas de fugas
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleFugas(TEXT("ParticleSystem'/Game/StylizedFX_2/ParticleSystems/P_MagicArrow_Hit_2.P_MagicArrow_Hit_2'"));
	if (ParticleFugas.Succeeded())
	{

		Fugas->SetTemplate(ParticleFugas.Object);
		Fugas->bAutoActivate = false;
		Fugas->SetWorldScale3D(FVector(80.5f, 80.5f, 80.5f));

	}



	// Sonido de disparo
	static ConstructorHelpers::FObjectFinder<USoundBase> AssetShotSound(TEXT("SoundWave'/Game/BOSS_SOUNDS/AMETRALLADORA.AMETRALLADORA'"));
	if (AssetShotSound.Succeeded())
	{
		Sonido_Disparo = Cast<USoundBase>(AssetShotSound.Object);
	}

    // Collision
    Colision_Nave = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision_Nave"));
    Colision_Nave->SetupAttachment(Mesh);


	//componente de movimiento
	Movimiento = CreateDefaultSubobject<UAC_MOVEMENT_EPIC>(TEXT("Movimiento"));

    MAX_SUPRME_LIFE = 100000.0f;

    DisparoActual = 0;
    Tiempo_Disparo = 0.0f;
    IntervaloActual_Disparo = 5.0f;  // Duración de cada intervalo en segundos

}

// Called when the game starts or when spawned
void AEPIC_GALACTUS_FINAL_BOSS::BeginPlay()
{
    Super::BeginPlay();

    // Sonido de aparecer
    if (Sonido_Aparecer  && Audio_Aparecer)
	{
		Audio_Aparecer->SetSound(Sonido_Aparecer);
		Audio_Aparecer->Play();
	}


	Player = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

    PlayerHUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
    PlayerHUD->ShowGalactusHealthBar();

    if (PlayerHUD && PlayerHUD->GameStartedWidget)
    {
        GalactusHealthBarWidget = Cast<UWidget_Bar_Galactus>(PlayerHUD->GalactusHealthBarWidget);
        if (GalactusHealthBarWidget)
        {
            UpdateHUDHealth();
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("GalactusHealthBarWidget is not initialized correctly"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HUD or GalactusHealthBarWidget is not initialized"));
    }


}

// Called every frame
void AEPIC_GALACTUS_FINAL_BOSS::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
	//vida de la nave
    Movimiento_Galactus(DeltaTime);

	Disparo_Galactus(DeltaTime);

    if (SUPREME_LIFE <= 0)
    {
        Componente_Destruccion();
    }
    else if (SUPREME_LIFE > 0)
    {
        UpdateHUDHealth();
    }


  
}

void AEPIC_GALACTUS_FINAL_BOSS::Recibir_Danio(float Danio)
{
    SUPREME_LIFE -= Danio;
    if (SUPREME_LIFE < 0) SUPREME_LIFE = 0;
    UpdateHUDHealth();

    // Activar partículas de fugas en cada impacto
    if (!Fugas->IsActive())
    {
        Fugas->Activate(true);
    }
}

void AEPIC_GALACTUS_FINAL_BOSS::Disparo_Galactus(float DeltaTime)
{
    // Actualizar el temporizador
    Tiempo_Disparo += DeltaTime;

    // Verificar si es tiempo de disparar
    if (Tiempo_Disparo >= IntervaloActual_Disparo)
    {
        // Reiniciar el temporizador
        Tiempo_Disparo = 0.0f;

        // Obtener el mundo y la referencia al jugador
        UWorld* World = GetWorld();
        Player  = Cast<AGALAGA_REMASTEREDPawn>(UGameplayStatics::GetPlayerPawn(World, 0));

        if (World != nullptr && Player != nullptr)
        {
            // Obtener la posición y la rotación actuales de la nave enemiga
            FVector EnemyLocation = GetActorLocation();
            FRotator EnemyRotation = GetActorRotation();

            // Obtener la posición del jugador
            FVector PlayerLocation = Player->GetActorLocation();

            // Calcular la dirección del disparo hacia el jugador
            FVector DisparoDirection = (PlayerLocation - EnemyLocation).GetSafeNormal();
            FRotator FireRotation = DisparoDirection.Rotation();

            // Configurar la distancia de disparo
            const float DisparoOffset = 12000.0f; // Distancia desde la nave hasta donde aparecerá el proyectil
            FVector SpawnLocation = EnemyLocation + DisparoDirection * DisparoOffset;

            // Alternar entre diferentes tipos de disparos con variaciones
            switch (DisparoActual)
            {
            case 0:
                // Disparo individual con efecto de rastreo
            {
                ACB_Space_Sword* Proyectil = World->SpawnActor<ACB_Space_Sword>(ACB_Space_Sword::StaticClass(), SpawnLocation, FireRotation);
                if (Proyectil)
                {
                    Proyectil->SetHomingTarget(Player);
                }
            }
            break;

            case 1:
                // Disparo triple en arco
                for (int i = -1; i <= 1; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 20.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    ACB_Lava_Sword* Proyectil = World->SpawnActor<ACB_Lava_Sword>(ACB_Lava_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->SetHomingTarget(Player);
                    }
                }
                break;

            case 2:
                // Disparo en espiral con velocidad oscilante
                for (int i = 0; i < 12; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 30.0f; // Ajustar el ángulo de disparo
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    AdjustedLocation.Z += FMath::Sin(FMath::DegreesToRadians(i * 30.0f)) * 200.0f; // Variación en altura
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 8000.f + FMath::Sin(i * 30.0f) * 4000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 8000.f + FMath::Sin(i * 30.0f) * 4000.f;
                        Proyectil->SetHomingTarget(Player);
                    }
                }
                break;

            case 3:
                // Disparo en ráfaga con proyectiles explosivos
                for (int i = 0; i < 5; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    FVector AdjustedLocation = EnemyLocation + FireRotation.Vector() * (DisparoOffset + i * 100.0f);
                    ACB_Space_Sword* Proyectil = World->SpawnActor<ACB_Space_Sword>(ACB_Space_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 15000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 15000.f;
                        Proyectil->SetHomingTarget(Player);
                    }
                }
                break;

            case 4:
                // Disparo en todas las direcciones con velocidad variable
                for (int i = 0; i < 360; i += 45)
                {
                    FRotator AdjustedRotation = FRotator(0, i, 0);
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 10000.f + FMath::RandRange(-2000.f, 2000.f);
                        Proyectil->ProjectileMovement->MaxSpeed = 10000.f + FMath::RandRange(-2000.f, 2000.f);
                        Proyectil->SetHomingTarget(Player);
                    }
                }
                break;

            case 5:
                // Disparo en línea recta con zigzag
                for (int i = 0; i < 3; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    FVector AdjustedLocation = EnemyLocation + FireRotation.Vector() * (DisparoOffset + i * 200.0f);
                    AdjustedLocation.X += (i % 2 == 0) ? 200.0f : -200.0f; // Zigzag
                    ACB_Ice_Sword* Proyectil = World->SpawnActor<ACB_Ice_Sword>(ACB_Ice_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 12000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 12000.f;
                        Proyectil->SetHomingTarget(Player);
                    }
                }
                break;

            case 6:
                // Disparo en forma de estrella
                for (int i = 0; i < 5; i++)
                {
                    FRotator AdjustedRotation = FireRotation;
                    AdjustedRotation.Yaw += i * 72.0f; // 360 grados dividido por 5 puntas de estrella
                    FVector AdjustedLocation = EnemyLocation + AdjustedRotation.Vector() * DisparoOffset;
                    ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                    if (Proyectil)
                    {
                        Proyectil->ProjectileMovement->InitialSpeed = 10000.f;
                        Proyectil->ProjectileMovement->MaxSpeed = 10000.f;
                        Proyectil->SetHomingTarget(Player);
                    }
                }
                break;

            case 7:
                // Disparo que se divide en múltiples proyectiles
            {
                ACB_Asteroid_Sword* Proyectil = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), SpawnLocation, FireRotation);
                if (Proyectil)
                {
                    Proyectil->SetHomingTarget(Player);

                    // Configurar un evento para dividir el proyectil
                    FTimerHandle TimerHandle;
                    FTimerDelegate TimerDelegate = FTimerDelegate::CreateLambda([=]()
                        {
                            FVector SplitLocation = Proyectil->GetActorLocation();
                            FRotator SplitRotation = Proyectil->GetActorRotation();
                            for (int j = 0; j < 5; j++)
                            {
                                FRotator AdjustedRotation = SplitRotation;
                                AdjustedRotation.Yaw += j * 72.0f;
                                FVector AdjustedLocation = SplitLocation + AdjustedRotation.Vector() * 200.0f;
                                ACB_Asteroid_Sword* SplitProjectile = World->SpawnActor<ACB_Asteroid_Sword>(ACB_Asteroid_Sword::StaticClass(), AdjustedLocation, AdjustedRotation);
                                if (SplitProjectile)
                                {
                                    SplitProjectile->ProjectileMovement->InitialSpeed = 6000.f;
                                    SplitProjectile->ProjectileMovement->MaxSpeed = 6000.f;
                                    SplitProjectile->SetHomingTarget(Player);
                                }
                            }
                            Proyectil->Destroy();
                        });

                    // Configurar el temporizador para dividir el proyectil después de 1 segundo
                    World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.0f, false);
                }
            }
            break;

            default:
                break;
            }

            // Alternar al siguiente tipo de disparo
            DisparoActual = (DisparoActual + 1) % 8;
        }

        // Reproducir el sonido del disparo
        UGameplayStatics::PlaySoundAtLocation(World, Sonido_Disparo, GetActorLocation());
    }
}

void AEPIC_GALACTUS_FINAL_BOSS::Movimiento_Galactus(float DeltaTime)
{
    if (SUPREME_LIFE > 80000.0f)
    {
        Movimiento->CircularMovement(DeltaTime);
    }
    else if (SUPREME_LIFE > 50000.0f)
    {
        Movimiento->MoveTowardsPlayer(DeltaTime);
    }
    else if (SUPREME_LIFE > 20000.0f)
    {
        Movimiento->ArcMovement(DeltaTime);
    }
	else if (SUPREME_LIFE > 10000.0f)
	{
		Movimiento->MoveTowardsPlayer(DeltaTime);
	}
    else
    {
        Movimiento->MovimientoMoribundo(DeltaTime);
    }

    if (SUPREME_LIFE <= 50000.0f && SUPREME_LIFE > 20000.0f)
    {
        if (!Quemadura->IsActive())
        {
            Quemadura->Activate(true);
        }
    }
    

    if (SUPREME_LIFE <= 20000.0f)
    {

        if (!Fugas->IsActive())
        {
            Fugas->Activate(true);
        }
    }
   
	

}

void AEPIC_GALACTUS_FINAL_BOSS::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

	AGALAGA_REMASTEREDPawn* Players = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);
	if (Players)
	{
		Players->Damage_received(800);
	}

    //collision con mis projectiles
	AC_Projectile* Proyectil = Cast<AC_Projectile>(OtherActor);
	if (Proyectil)
	{
		Proyectil->Destroy();
        Recibir_Danio(500);
		//activa las fugas0
		Fugas->Activate();
	}
	

}

void AEPIC_GALACTUS_FINAL_BOSS::Componente_Destruccion()
{
    if (Particulas_Muerte)
    {
        Particulas_Muerte->Activate(true);
    }

    if (Sonido_Muerte)
    {
        UGameplayStatics::PlaySoundAtLocation(this, Sonido_Muerte, GetActorLocation());
    }
    if (Audio_Aparecer)
    {
        Audio_Aparecer->Stop();
	}


    PlayerHUD->HideGalactusHealthBar();
    this->Destroy();

    GetWorld()->GetTimerManager().SetTimer(TimerHandle_VictoryWidget, [this]() 
    {
        //PlayerHUD->HideGameStartedWidget();
        ShowVictoryWidgetAfterDelay();
        
    }, 4.0f, false);

}

void AEPIC_GALACTUS_FINAL_BOSS::ShowVictoryWidgetAfterDelay()
{
    if (PlayerHUD)
    {
        PlayerHUD->ShowVictoryWidget();
    }
}

void AEPIC_GALACTUS_FINAL_BOSS::UpdateHUDHealth()
{
    if (PlayerHUD && PlayerHUD->GalactusHealthBarWidget)
    {
        GalactusHealthBarWidget = Cast<UWidget_Bar_Galactus>(PlayerHUD->GalactusHealthBarWidget);
        if (GalactusHealthBarWidget)
        {
            float HealthPercentage = SUPREME_LIFE / MAX_SUPRME_LIFE;
            FString HealthString = FString::Printf(TEXT("%.0f"), SUPREME_LIFE);
            GalactusHealthBarWidget->UpdateHealthBar(HealthPercentage, HealthString);
        }
    }
}

