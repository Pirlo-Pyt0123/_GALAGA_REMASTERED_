// Copyright Epic Games, Inc. All Rights Reserved.

#include "GALAGA_REMASTEREDPawn.h"
#include "GALAGA_REMASTEREDProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Engine/CollisionProfile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Z_Enemy_Ship_P.h"
#include "Engine/Engine.h"
#include "T_TerraBley_P.h"
#include "CJ_Aurora_Dagger.h"
#include "CJ_Astro_Bean.h"
#include "CJ_Void_Missile.h"
#include "CJ_Galactic_Ray.h"
#include "CJ_Celestial_Arrow.h"
#include "CJ_Void_Echo.h"
#include "G_Capsule_Life.h"
#include "G_Capsule_Health_Half.h"
#include "G_Capsule_Health_Total.h"
#include "G_Capsule_Invulnerabilidad.h"

#include "X_Master_Ship_P.h"
#include "PS_TypeOfWeapon.h"

#include "PS_Arrow_Strategy.h"
#include "PS_Astro_Beam_Strategy.h"
#include "PS_Dagger_Strategy.h"
#include "PS_Electric_Ray.h"
#include "PS_NovaBomb_Strategy.h"
#include "PS_VoidEcho_Sgy.h"
#include "PS_VoidMissile_Strategy.h"

#include "HUD_P_Principal.h"

#include "Blueprint/UserWidget.h"

#include "W_PDD_Game_Started.h"
#include "K_Portal_P.h"

const FName AGALAGA_REMASTEREDPawn::MoveForwardBinding("MoveForward");
const FName AGALAGA_REMASTEREDPawn::MoveRightBinding("MoveRight");
const FName AGALAGA_REMASTEREDPawn::FireForwardBinding("FireForward");
const FName AGALAGA_REMASTEREDPawn::FireRightBinding("FireRight");
const FName AGALAGA_REMASTEREDPawn::FireUpBinding("FireUp");


AGALAGA_REMASTEREDPawn::AGALAGA_REMASTEREDPawn()
{

	PrimaryActorTick.bCanEverTick = true;
	// Load and set the Ship Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/CF2Shuttle/Meshes/SM_CF2_Shuttle.SM_CF2_Shuttle'"));
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	if (ShipMesh.Succeeded())
	{
		ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
		ShipMeshComponent->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	// Create and configure the CameraBoom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.0f;
	CameraBoom->SocketOffset = FVector(-3600.f, 0.f, 1200.f);
	CameraBoom->bEnableCameraLag = false;
	CameraBoom->CameraLagSpeed = 5.f;

	// Create and configure the CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	OriginalCameraLocation = CameraBoom->SocketOffset;
	AcceleratedCameraLocation = FVector(-4500.f, 0.f, 1200.f); // Ajusta este valor según sea necesario

	// Create and configure the Collision Component
	Colision_Pawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision_Pawn"));
	Colision_Pawn->SetupAttachment(ShipMeshComponent);
	Colision_Pawn->SetBoxExtent(FVector(1100.f, 500.f, 400.f));

	// Handling Parameters
	Acceleration = 1000.f;
	TurnSpeed = 50.f;

	MaxSpeed = 500.f;
	MinSpeed = 500.f;

	MoveSpeed = 1000.0f;
	GunOffset = FVector(400.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
	bIsLookingBack = false;

	bIsAccelerating = false;
	DefaultAcceleration = 3000.0f; // Ajusta este valor según sea necesario

	Standard_Speed = 10000.0f;
	Increased_Speed = 35000.0f;
	Ultra_Increased_Speed = 60000.0f;


	Acceleration = DefaultAcceleration;
	CurrentForwardSpeed = 5500.0f; // Velocidad inicial
	MaxeSpeed = 5500.0f; // Velocidad máxima
	MineSpeed = 500.0f; // Velocidad mínima

	// Inicializar variables
	bIsSuperAccelerating = false;
	SuperAccelerationPower = 25000.0f; // Potencia de aceleración mega espacial
	SuperAcceleratedCameraLocation = FVector(-3000.f, 0.f, 700.f); // Posición de cámara durante la super aceleración

	//vidas actuales
	CurrentLives = 3;


	// Load and set the Fire Sound
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MagicCombatAudio/NovaExplosion/Nova_Frost.Nova_Frost'"));
	if (FireAudio.Succeeded())
	{
		FireSound = FireAudio.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SelectAudio(TEXT("SoundWave'/Game/Importaciones/Sonidos_Armas/Sounds/Wavs/S_Spturretmov.S_Spturretmov'"));
	if (SelectAudio.Succeeded())
	{
		SelectSound = SelectAudio.Object;
	}

	// Creación del AudioComponent
	AccelerationAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AccelerationAudioComponent"));
	AccelerationAudioComponent->SetupAttachment(RootComponent);
	AccelerationAudioComponent->bAutoActivate = false;

	// Configuración del sonido de aceleración
	static ConstructorHelpers::FObjectFinder<USoundBase> AccelerationAudio(TEXT("SoundWave'/Game/CF2Shuttle/Sounds/S_Rocket_Medium.S_Rocket_Medium'"));
	if (AccelerationAudio.Succeeded())
	{
		AccelerationAudioComponent->SetSound(AccelerationAudio.Object);
	}

	AceLeftB = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AceLeftB"));
	AceRightA = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AceRightA"));

	// Attach both particle systems to the ship's mesh component
	AceLeftB->SetupAttachment(ShipMeshComponent);
	AceRightA->SetupAttachment(ShipMeshComponent);

	// Load the particle system asset
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Ace(TEXT("ParticleSystem'/Game/VFXSeries1/Particles/Tails/PROP_PAWN.PROP_PAWN'"));
	if (Ace.Succeeded())
	{
		// Configure the left particle system
		AceLeftB->SetTemplate(Ace.Object);
		AceLeftB->SetWorldScale3D(FVector(6.0f, 6.0f, 6.0f));
		AceLeftB->SetRelativeLocation(FVector(-400.0f, -350.0f, 70.0f));
		AceLeftB->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

		// Configure the right particle system
		AceRightA->SetTemplate(Ace.Object);
		AceRightA->SetWorldScale3D(FVector(6.0f, 6.0f, 6.0f));
		AceRightA->SetRelativeLocation(FVector(-400.0f, 350.0f, 70.0f)); // Adjust the Y coordinate to place it to the right
		AceRightA->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	}


	// Attach particle systems to the sides of the ship
	ProyecAceLeft = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AccelerationParticlesComponentLeft"));
	ProyecAceRight = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AccelerationParticlesComponentRight"));

	// Attach both particle systems to the ship's mesh component
	ProyecAceLeft->SetupAttachment(ShipMeshComponent);
	ProyecAceRight->SetupAttachment(ShipMeshComponent);

	// Load the particle system asset
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AccelerationParticlesAsset(TEXT("ParticleSystem'/Game/VFXSeries1/Particles/Tails/PROP_PAWN.PROP_PAWN'"));
	if (AccelerationParticlesAsset.Succeeded())
	{
		// Configure the left particle system
		ProyecAceLeft->SetTemplate(AccelerationParticlesAsset.Object);
		ProyecAceLeft->bAutoActivate = false;
		ProyecAceLeft->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
		//rotacion de la particula
		ProyecAceLeft->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		ProyecAceLeft->SetRelativeLocation(FVector(-400.0f, -150.0f, 70.0f)); // Adjust the Y coordinate to place it to the left

		// Configure the right particle system
		ProyecAceRight->SetTemplate(AccelerationParticlesAsset.Object);
		ProyecAceRight->bAutoActivate = false;
		ProyecAceRight->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
		ProyecAceRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		ProyecAceRight->SetRelativeLocation(FVector(-400.0f, 150.0f, 70.0f)); // Adjust the Y coordinate to place it to the right
	}

	Invulnerabilidad_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Invulnerabilidad_Particles"));
	Invulnerabilidad_Particle->SetupAttachment(ShipMeshComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Inv_ParticlesAsset(TEXT("ParticleSystem'/Game/StylizedFX_2/ParticleSystems/shield/Escudo_Invulnerabilidad.Escudo_Invulnerabilidad'"));

	if (Inv_ParticlesAsset.Succeeded())
	{
		Invulnerabilidad_Particle->SetTemplate(Inv_ParticlesAsset.Object);
		Invulnerabilidad_Particle->bAutoActivate = false;
		Invulnerabilidad_Particle->SetWorldScale3D(FVector(15.0f, 15.0f, 15.0f));
		Invulnerabilidad_Particle->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Invulnerabilidad_Particle->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	}

	bIsShooting = false;

	MaxLife = 3000.f;
	Life = 3000.f;
	//shoting

	//sonidos de las estrategias 
	static ConstructorHelpers::FObjectFinder<USoundBase> ShotSoundAstroBeam(TEXT("SoundWave'/Game/BOSS_SOUNDS/ASTRO_BEAN.ASTRO_BEAN'"));
	if (ShotSoundAstroBeam.Succeeded())
	{
		SoundAstroBeam = ShotSoundAstroBeam.Object;


	}

	static ConstructorHelpers::FObjectFinder<USoundBase> ShotSoundDagger(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MagicCombatAudio/Death/FireDeath.FireDeath'"));
	if (ShotSoundDagger.Succeeded())
	{
		SoundDagger = ShotSoundDagger.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> ShotSoundArrow(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MagicCombatAudio/Death/SuperEvilDeath.SuperEvilDeath'"));
	if (ShotSoundArrow.Succeeded())
	{
		SoundArrow = ShotSoundArrow.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> ShotSoundNovaBomb(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Nova/NovaMissle_CartoonyExplosion.NovaMissle_CartoonyExplosion'"));

	if (ShotSoundNovaBomb.Succeeded())
	{
		SoundNovaBomb = ShotSoundNovaBomb.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> ShotSoundVoidMissile(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Rocket/RocketMissile_FireShoot.RocketMissile_FireShoot'"));
	if (ShotSoundVoidMissile.Succeeded())
	{
		SoundVoidMissile = ShotSoundVoidMissile.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> ShotSoundElectricRay(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Lightning/LightningMissle3_Shoot.LightningMissle3_Shoot'"));
	if (ShotSoundElectricRay.Succeeded())
	{
		SoundElectricRay = ShotSoundElectricRay.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> ShotSoundVoidEcho(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MagicCombatAudio/Flamethrower/Flamethrower_IceShort.Flamethrower_IceShort'"));
	if (ShotSoundVoidEcho.Succeeded())
	{
		SoundVoidEcho = ShotSoundVoidEcho.Object;
	}

	// Load Explosion Sound
	static ConstructorHelpers::FObjectFinder<USoundBase> ExplosionSoundAsset(TEXT("SoundWave'/Game/Explode/A_Explode_18.A_Explode_18'"));
	if (ExplosionSoundAsset.Succeeded())
	{
		ExplosionSound = ExplosionSoundAsset.Object;
	}

	// Load Explosion Particle Effect
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionEffectAsset(TEXT("ParticleSystem'/Game/StylizedFX_2/ParticleSystems/P_MagicArrow_Hit_1.P_MagicArrow_Hit_1'"));
	if (ExplosionEffectAsset.Succeeded())
	{
		ExplosionEffect = ExplosionEffectAsset.Object;
	}

	// Load Teleport Sound
	static ConstructorHelpers::FObjectFinder<USoundBase> TeleportSoundAsset(TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/REAPARICION.REAPARICION'"));
	if (TeleportSoundAsset.Succeeded())
	{
		TeleportSound = TeleportSoundAsset.Object;
	}

	TeleportEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Aparicion"));
	TeleportEffect->SetupAttachment(ShipMeshComponent);

	// Load Teleport Particle Effect
	static ConstructorHelpers::FObjectFinder<UParticleSystem> TeleportEffectAsset(TEXT("ParticleSystem'/Game/GoodFXLevelUp/FX/Particles/PS_GFXLU_galaxy.PS_GFXLU_Galaxy'"));
	if (TeleportEffectAsset.Succeeded())
	{
		TeleportEffect->SetTemplate(TeleportEffectAsset.Object);
		TeleportEffect->SetWorldScale3D(FVector(7.0f, 7.0f, 7.0f));
		TeleportEffect->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> DestroyedSoundAsset(TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/Destruction_Ship_Princ.Destruction_Ship_Princ'"));
	if (DestroyedSoundAsset.Succeeded())
	{
		AmbientExplosionSound = DestroyedSoundAsset.Object;
	}


	//para el sonido de megapropulsor
	static ConstructorHelpers::FObjectFinder<USoundBase> InvulnerabilidadSoundAsset(TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/Sound_Invulnerabildad_God.Sound_Invulnerabildad_God'"));
	if (InvulnerabilidadSoundAsset.Succeeded())
	{
		Invulnerabilidad_Sound = InvulnerabilidadSoundAsset.Object;
	}


	static ConstructorHelpers::FObjectFinder<USoundBase> HealingSoundAsset(TEXT("SoundWave'/Game/Musica_D/EpicToonSFX/MissleSetAudio/Nuke/NukeMissle_CartoonyExplosion.NukeMissle_CartoonyExplosion'"));
	if (HealingSoundAsset.Succeeded())
	{
		ColisionSound = HealingSoundAsset.Object;
	}

	Invulnerabilidad_Sound_Component = CreateDefaultSubobject<UAudioComponent>(TEXT("MegaSpeedAudioComponent"));
	Invulnerabilidad_Sound_Component->SetupAttachment(RootComponent);
	Invulnerabilidad_Sound_Component->bAutoActivate = false;

	CurrentTerraBley = 0;

	// Inicialización de nuevas variables
	CurrentSpeedProgress = 1.0f; // Barra de progreso comienza llena
	SpeedRegenRate = 0.25f; // Ajusta según sea necesario (incremento más lento)
	SpeedDepleteRate = 0.05f; // Ajusta según sea necesario (decremento más lento)
	bIsSpeedDepleting = false;

	bCanAccelerate = true;
	bCanSuperAccelerate = true;
	ActiveInvulnerability = false;
	PassedInvul = false;
	AmountInvulnerability = 3;
	bIsHealing = false;
	HealingRate = 50.0f; // La tasa a la que se incrementa la vida por segundo
	LifeIncrement = 0.0f;
	TimeLeft = 30;
}

void AGALAGA_REMASTEREDPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// Bind axis inputs
	PlayerInputComponent->BindAxis("Thrust", this, &AGALAGA_REMASTEREDPawn::ThrustInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &AGALAGA_REMASTEREDPawn::MoveUpInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGALAGA_REMASTEREDPawn::MoveRightInput);

	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
	PlayerInputComponent->BindAxis(FireUpBinding);


	PlayerInputComponent->BindAction("TogglePauseMenu", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::TogglePauseMenu);

	PlayerInputComponent->BindAction("ToggleMissionMessage", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::ToggleMissionMessage);




	// Bind action inputs for shooting different weapons
	PlayerInputComponent->BindAction("AstroBean", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::Shoot_AstroBean);
	PlayerInputComponent->BindAction("AuroraDagger", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::Shoot_AuroraDagger);
	PlayerInputComponent->BindAction("CelestialArrow", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::Shoot_CelestialArrow);
	PlayerInputComponent->BindAction("NovaPulse", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::Shoot_NovaPulse);
	PlayerInputComponent->BindAction("VoidMissil", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::Shoot_VoidMissil);
	PlayerInputComponent->BindAction("GalacticRay", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::Shoot_GalacticRay);
	PlayerInputComponent->BindAction("VoidEcho", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::Shoot_VoidEcho);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::ShootWeapon);

	// Bind action inputs for acceleration
	PlayerInputComponent->BindAction("Accelerate", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::StartAccelerating);
	PlayerInputComponent->BindAction("Accelerate", IE_Released, this, &AGALAGA_REMASTEREDPawn::StopAccelerating);

	// Bind action inputs for the thruster
	PlayerInputComponent->BindAction("Thruster", IE_Pressed, this, &AGALAGA_REMASTEREDPawn::Active_C_Invulnerability);
	//PlayerInputComponent->BindAction("Thruster", IE_Released, this, &AGALAGA_REMASTEREDPawn::Deactive_C_Invulnerability);
}


void AGALAGA_REMASTEREDPawn::ToggleMissionMessage()
{
	AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (HUD)
	{
		HUD->ToggleMissionMessage();
	}
}

void AGALAGA_REMASTEREDPawn::TogglePauseMenu()
{
	AHUD_P_Principal* HUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (HUD)
	{
		if (HUD->bIsPaused)
		{
			HUD->HidePauseMenu();
		}
		else
		{
			HUD->ShowPauseMenu();
		}
	}
}

void AGALAGA_REMASTEREDPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSuperAccelerating && bCanSuperAccelerate)
	{
		//GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Super Acelerando"));

		CurrentAcceleration = Ultra_Increased_Speed;
		MaxSpeed = Ultra_Increased_Speed;
		MinSpeed = Ultra_Increased_Speed/2;
		bIsSpeedDepleting = true;
	}
	if (bIsAccelerating && bCanAccelerate)
	{
		//GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Acelerando"));

		CurrentAcceleration = Increased_Speed;
		MaxSpeed = Increased_Speed;
		MinSpeed = Increased_Speed/2;
		bIsSpeedDepleting = true;
	}
	else
	{
		CurrentAcceleration = Standard_Speed;
		MaxSpeed = Standard_Speed;
		MinSpeed = Standard_Speed;
		bIsSpeedDepleting = false;
	}

	// Actualiza la velocidad en función de la aceleración
	CurrentForwardSpeed += CurrentAcceleration * DeltaTime;
	CurrentForwardSpeed = FMath::Clamp(CurrentForwardSpeed, MinSpeed, MaxSpeed);

	// Movimiento basado en la velocidad actual con algo de inercia
	FVector LocalMove = FVector(CurrentForwardSpeed * DeltaTime, 0.f, 0.f);
	AddActorLocalOffset(LocalMove, true);

	// Rotación basada en el tiempo de cuadro y las velocidades actuales
	FRotator DeltaRotation(180, 180, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaTime;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaTime;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaTime;
	AddActorLocalRotation(DeltaRotation);

	// Movimiento adicional en el espacio 3D (para movimiento en Y y Z)
	FVector StrafeMove = FVector(0.f, CurrentStrafeSpeed * DeltaTime, CurrentVerticalSpeed * DeltaTime);
	AddActorLocalOffset(StrafeMove, true);

	// Interpolación de la ubicación de la cámara para suavizar la transición
	FVector TargetCameraLocation = bIsSuperAccelerating ? SuperAcceleratedCameraLocation :
		(bIsAccelerating ? AcceleratedCameraLocation : OriginalCameraLocation);
	CameraBoom->SocketOffset = FMath::VInterpTo(CameraBoom->SocketOffset, TargetCameraLocation, DeltaTime, 5.f);

	// Manejo del disparo
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const float FireUpValue = GetInputAxisValue(FireUpBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, FireUpValue);

	// Actualización de la barra de velocidad
	if (bIsSpeedDepleting)
	{
		CurrentSpeedProgress -= SpeedDepleteRate * DeltaTime;
	}
	else
	{
		CurrentSpeedProgress += SpeedRegenRate * DeltaTime;
	}
	CurrentSpeedProgress = FMath::Clamp(CurrentSpeedProgress, 0.0f, 1.0f);
	UpdateHUDSpeed(CurrentSpeedProgress);

	// Verificar si la barra de progreso está vacía
	if (CurrentSpeedProgress <= 0.0f)
	{
		bCanAccelerate = false;
		bCanSuperAccelerate = false;
		bIsAccelerating = false;
		bIsSuperAccelerating = false;

		// Desactivar partículas si la barra de progreso está vacía
		ProyecAceLeft->Deactivate();
		ProyecAceRight->Deactivate();
		StopAccelerating();
	}
	else
	{
		bCanAccelerate = true;
		bCanSuperAccelerate = true;
	}

	UpdateHUDLives();

	if (Life <= 0)
	{
		LoseLife();
		Componente_Explotion();

	}

	if (bIsHealing)
	{
		IncrementLife(DeltaTime);
	}
}


void AGALAGA_REMASTEREDPawn::ActualizarReferenciaEstrategias()
{
	// Actualizar las referencias en cada estrategia
	if (AstroBeamStrategy) AstroBeamStrategy->SetPlayerPawn(this);
	if (DaggerStrategy) DaggerStrategy->SetPlayerPawn(this);
	if (ArrowStrategy) ArrowStrategy->SetPlayerPawn(this);
	if (NovaBombStrategy) NovaBombStrategy->SetPlayerPawn(this);
	if (VoidMissileStrategy) VoidMissileStrategy->SetPlayerPawn(this);
	if (ElectricRayStrategy) ElectricRayStrategy->SetPlayerPawn(this);
	if (VoidEchoStrategy) VoidEchoStrategy->SetPlayerPawn(this);
}

void AGALAGA_REMASTEREDPawn::BeginPlay()
{
	Super::BeginPlay();

	if (!CameraComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraComponent is not initialized"));
	}

	TypeOfWeapon = GetWorld()->SpawnActor<APS_TypeOfWeapon>(APS_TypeOfWeapon::StaticClass());

	// Inicializa las estrategias
	AstroBeamStrategy = GetWorld()->SpawnActor<APS_Astro_Beam_Strategy>(APS_Astro_Beam_Strategy::StaticClass());
	DaggerStrategy = GetWorld()->SpawnActor<APS_Dagger_Strategy>(APS_Dagger_Strategy::StaticClass());
	ArrowStrategy = GetWorld()->SpawnActor<APS_Arrow_Strategy>(APS_Arrow_Strategy::StaticClass());
	NovaBombStrategy = GetWorld()->SpawnActor<APS_NovaBomb_Strategy>(APS_NovaBomb_Strategy::StaticClass());
	VoidMissileStrategy = GetWorld()->SpawnActor<APS_VoidMissile_Strategy>(APS_VoidMissile_Strategy::StaticClass());
	ElectricRayStrategy = GetWorld()->SpawnActor<APS_Electric_Ray>(APS_Electric_Ray::StaticClass());
	VoidEchoStrategy = GetWorld()->SpawnActor<APS_VoidEcho_Sgy>(APS_VoidEcho_Sgy::StaticClass());


	// Obtener la posición actual de la cámara
	FVector CameraLocation = CameraBoom->GetComponentLocation();

	// Ajustar la posición de la cámara (en este caso, subir la cámara)
	CameraLocation.Z += 500.0f;  // Ajusta según sea necesario
	CameraLocation.X += -800.0f; // Ajusta según sea necesario

	// Establecer la nueva posición de la cámara
	CameraBoom->SetWorldLocation(CameraLocation);

	PlayerHUD = Cast<AHUD_P_Principal>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());

	// Verificar si PlayerHUD y GameStartedWidget están inicializados correctamente
	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			UpdateHUDSpeed(CurrentForwardSpeed / MaxSpeed);
			UpdateHUDHealth(Life / MaxLife);
			UpdateHUDLives();
			UpdateHUDTerraBleyCount();
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

}


// Funciones para actualizar el HUD
void AGALAGA_REMASTEREDPawn::UpdateHUDWeaponImage(int32 WeaponIndex)
{
	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			GameStartedWidget->UpdateWeaponImage(WeaponIndex);
		}
	}
}

void AGALAGA_REMASTEREDPawn::UpdateHUDHealth(float Health)
{
	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			GameStartedWidget->SetHealthProgress(Health);
		}
	}
}

void AGALAGA_REMASTEREDPawn::UpdateHUDSpeed(float Speed)
{
	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			GameStartedWidget->SetSpeedProgress(Speed);
		}
	}
}

void AGALAGA_REMASTEREDPawn::UpdateHUDLives()
{
	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			GameStartedWidget->UpdateLifeImages(CurrentLives);
		}
	}
}

void AGALAGA_REMASTEREDPawn::UpdateHUDTerraBleyCount()
{
	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			GameStartedWidget->UpdateTerraBleyCount(CurrentTerraBley);
		}
	}
}


void AGALAGA_REMASTEREDPawn::ThrustInput(float Val)
{
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	float CurrentAcc = bHasInput ? (Val * Acceleration) : (-0.5f * Acceleration);
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

void AGALAGA_REMASTEREDPawn::MoveUpInput(float Val)
{
	float TargetPitchSpeed = (Val * TurnSpeed * -1.f);
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void AGALAGA_REMASTEREDPawn::MoveRightInput(float Val)
{
	// Calcula la velocidad de giro (Yaw) objetivo
	float TargetYawSpeed = (Val * TurnSpeed);
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// Verifica si estamos girando significativamente
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;

	// Calcula la inclinación (Roll) objetivo para girar levemente
	float TargetRollSpeed = bIsTurning ? (Val * -10.0f) : (GetActorRotation().Roll * -2.f);
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// Aplica las rotaciones al Pawn
	FRotator DeltaRotation(0.f, 0.f, 0.f);
	DeltaRotation.Yaw = CurrentYawSpeed * GetWorld()->GetDeltaSeconds();
	DeltaRotation.Roll = CurrentRollSpeed * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(DeltaRotation);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AGALAGA_REMASTEREDPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (AZ_Enemy_Ship_P* Nave_Enemiga = Cast<AZ_Enemy_Ship_P>(OtherActor))
	{
		Damage_received(250.f);
		Nave_Enemiga->Componente_Destruccion();
	}

	if (AX_Master_Ship_P* Nave_Maestra = Cast< AX_Master_Ship_P>(OtherActor))
	{
		Damage_received(3000.f);
		Nave_Maestra->Recibir_Danio(2500.f);
	}

	if (AT_TerraBley_P* TerraBley = Cast<AT_TerraBley_P>(OtherActor))
	{
		TerraBley->Componente_Desaparecer();
		CollectTerraBley();
	}

	if (AG_Capsule_Life* LifeCapsule = Cast<AG_Capsule_Life>(OtherActor))
	{
		LifeCapsule->Componente_Destruccion();
		ConsumeLifeCapsule();
	}

	if (AG_Capsule_Health_Half* HealthHalf = Cast<AG_Capsule_Health_Half>(OtherActor))
	{
		HealthHalf->Componente_Destruccion();
		ConsumeHealthCapsule2();
	}

	if (AG_Capsule_Health_Total* HealthTotal = Cast<AG_Capsule_Health_Total>(OtherActor))
	{
		HealthTotal->Componente_Destruccion();
		ConsumeHealthCapsule();
	}

	if(AG_Capsule_Invulnerabilidad* InvulnerabilityCapsule = Cast<AG_Capsule_Invulnerabilidad>(OtherActor))
	{
		InvulnerabilityCapsule->Componente_Destruccion();
		AmountInvulnerability++;
		UpdateHUDInvulnerabilityCountCapsule();
	}

	//if(AK_Portal_P* Portal = Cast<AK_Portal_P>(OtherActor))
	//{
	//	Portal->Component_Destruction();
	//}

}


void AGALAGA_REMASTEREDPawn::ShotTimerExpired()
{
	bCanFire = true;
}



void AGALAGA_REMASTEREDPawn::Damage_received(float Damage)
{
	if (ActiveInvulnerability == false) 
	{

		if (ColisionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ColisionSound, GetActorLocation());
		}

		Life -= Damage;
		if (Life < 0) Life = 0;
		UpdateHUDHealth(Life / MaxLife);

		UpdateHUDSpeed(CurrentForwardSpeed / MaxSpeed);
	}
	else 
	{
		return ;
	}
}



void AGALAGA_REMASTEREDPawn::Shoot_AstroBean()
{
	ValueShootWeapon = 1;
	UpdateHUDWeaponImage(ValueShootWeapon);
	if (SelectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SelectSound, GetActorLocation());
	}
}

void AGALAGA_REMASTEREDPawn::Shoot_AuroraDagger()
{
	ValueShootWeapon = 2;
	UpdateHUDWeaponImage(ValueShootWeapon);
	if (SelectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SelectSound, GetActorLocation());
	}
}

void AGALAGA_REMASTEREDPawn::Shoot_CelestialArrow()
{
	ValueShootWeapon = 3;
	UpdateHUDWeaponImage(ValueShootWeapon);
	if (SelectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SelectSound, GetActorLocation());
	}
}

void AGALAGA_REMASTEREDPawn::Shoot_NovaPulse()
{
	ValueShootWeapon = 4;
	UpdateHUDWeaponImage(ValueShootWeapon);
	if (SelectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SelectSound, GetActorLocation());
	}
}

void AGALAGA_REMASTEREDPawn::Shoot_VoidMissil()
{
	ValueShootWeapon = 5;
	UpdateHUDWeaponImage(ValueShootWeapon);
	if (SelectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SelectSound, GetActorLocation());
	}
}

void AGALAGA_REMASTEREDPawn::Shoot_GalacticRay()
{
	ValueShootWeapon = 6;
	UpdateHUDWeaponImage(ValueShootWeapon);
	if (SelectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SelectSound, GetActorLocation());
	}
}

void AGALAGA_REMASTEREDPawn::Shoot_VoidEcho()
{
	ValueShootWeapon = 7;
	UpdateHUDWeaponImage(ValueShootWeapon);
	if (SelectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SelectSound, GetActorLocation());
	}
}

void AGALAGA_REMASTEREDPawn::ShootWeapon()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{

		switch (ValueShootWeapon)
		{
		case 1:
			TypeOfWeapon->AlterShootingType(AstroBeamStrategy);

			//reproducir sonido de la estrategia
			if (SoundAstroBeam)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SoundAstroBeam, GetActorLocation());
			}
			break;
		case 2:
			TypeOfWeapon->AlterShootingType(DaggerStrategy);

			//reproducir sonido de la estrategia
			if (SoundDagger)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SoundDagger, GetActorLocation());
			}
			break;
		case 3:
			TypeOfWeapon->AlterShootingType(ArrowStrategy);

			//reproducir sonido de la estrategia
			if (SoundArrow)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SoundArrow, GetActorLocation());
			}
			break;
		case 4:
			TypeOfWeapon->AlterShootingType(NovaBombStrategy);

			//reproducir sonido de la estrategia

			if (SoundNovaBomb)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SoundNovaBomb, GetActorLocation());
			}
			break;
		case 5:
			TypeOfWeapon->AlterShootingType(VoidMissileStrategy);

			//reproducir sonido de la estrategia

			if (SoundVoidMissile)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SoundVoidMissile, GetActorLocation());
			}
			break;
		case 6:
			TypeOfWeapon->AlterShootingType(ElectricRayStrategy);

			//reproducir sonido de la estrategia

			if (SoundElectricRay)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SoundElectricRay, GetActorLocation());
			}
			break;
		case 7:
			TypeOfWeapon->AlterShootingType(VoidEchoStrategy);

			//reproducir sonido de la estrategia

			if (SoundVoidEcho)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SoundVoidEcho, GetActorLocation());
			}
			break;
		default:
			break;
		}
	}

	FVector LocationPlayer = GetActorLocation();


	TypeOfWeapon->UseWeapon(LocationPlayer, rotBull);

};


void AGALAGA_REMASTEREDPawn::ConsumeLifeCapsule()
{
	if (CurrentLives < 5)
	{
		CurrentLives++;
		UpdateHUDLives();
	}
}

void AGALAGA_REMASTEREDPawn::ConsumeHealthCapsule()
{
	Life += 350.f;
	if (Life <= 3000.f)
	{
		UpdateHUDHealth(Life / MaxLife);
	}
	else if(Life > 3000.f)
	{
		Life = 3000.f;
		UpdateHUDHealth(Life / MaxLife);

	}
}

void AGALAGA_REMASTEREDPawn::ConsumeHealthCapsule2()
{
	Life += 850.f;
	if (Life <= 3000.f) 
	{
		UpdateHUDHealth(Life / MaxLife);
	}
	else if(Life > 3000.f)
	{
		Life = 3000.f;
		UpdateHUDHealth(Life / MaxLife);
	
	}
}

void AGALAGA_REMASTEREDPawn::Active_C_Invulnerability()
{
	if (AmountInvulnerability > 0)
	{
		if(PassedInvul == false)
		{
			AmountInvulnerability--;
			UpdateHUDInvulnerabilityCount();
			UpdateHUDInvulnerabilityTimer(TimeLeft);
			if (GameStartedWidget)
			{
				GameStartedWidget->SetHealthBarTexture(true);
				GameStartedWidget->SetInvulnerabilityImage(true);
			}

			Invulnerabilidad_Particle->Activate();

			if (Invulnerabilidad_Sound && Invulnerabilidad_Sound_Component)
			{
				Colision_Pawn->SetBoxExtent(FVector(1700.f, 1700.f, 1700.f));
				Invulnerabilidad_Sound_Component->SetSound(Invulnerabilidad_Sound);
				Invulnerabilidad_Sound_Component->Play();
			}

			ActiveInvulnerability = true;
			PassedInvul = true;
			GetWorld()->GetTimerManager().SetTimer(InvulnerabilityTimerHandle, [this] {InvulnerabilityTick(); }, 1.0f, true);
		}
	}
}

void AGALAGA_REMASTEREDPawn::InvulnerabilityTick()
{
	if (TimeLeft > -1)
	{
		TimeLeft--;
		UpdateHUDInvulnerabilityTimer(TimeLeft);
	}
	if(TimeLeft == 0)
	{
		if (GameStartedWidget)
		{
			GameStartedWidget->SetInvulnerabilityImage(false);
		}
		GetWorld()->GetTimerManager().ClearTimer(InvulnerabilityTimerHandle);
		if (Invulnerabilidad_Sound && Invulnerabilidad_Sound_Component->IsPlaying())
		{
			Colision_Pawn->SetBoxExtent(FVector(1100.f, 500.f, 400.f));
			Invulnerabilidad_Particle->Deactivate();
			Invulnerabilidad_Sound_Component->Stop();
		}
		Deactive_C_Invulnerability();
		TimeLeft = 30;

	}
}

void AGALAGA_REMASTEREDPawn::Deactive_C_Invulnerability()
{
	if (GameStartedWidget)
	{
		GameStartedWidget->SetHealthBarTexture(false);
		GameStartedWidget->SetInvulnerabilityImage(false);
	}
	ActiveInvulnerability = false;
	PassedInvul = false;
}


void AGALAGA_REMASTEREDPawn::UpdateHUDInvulnerabilityCount()
{
	if(ActiveInvulnerability == false)
	{
		if (PlayerHUD && PlayerHUD->GameStartedWidget)
		{
			GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
			if (GameStartedWidget)
			{
				GameStartedWidget->UpdateInvulnerabilityCount(AmountInvulnerability);
			}
		}
	}
	else
	{
		return;
	}
}

void AGALAGA_REMASTEREDPawn::UpdateHUDInvulnerabilityCountCapsule()
{
	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			GameStartedWidget->UpdateInvulnerabilityCount(AmountInvulnerability);
		}
	}
}

void AGALAGA_REMASTEREDPawn::UpdateHUDInvulnerabilityTimer(int32 TimeLeftPPP)
{
	if (PlayerHUD && PlayerHUD->GameStartedWidget)
	{
		GameStartedWidget = Cast<UW_PDD_Game_Started>(PlayerHUD->GameStartedWidget);
		if (GameStartedWidget)
		{
			GameStartedWidget->UpdateInvulnerabilityTimer(TimeLeftPPP);
		}
	}
}


void AGALAGA_REMASTEREDPawn::LoseLife()
{
	if (CurrentLives > 0)
	{
		CurrentLives--;
		UpdateHUDLives();
	}
}

void AGALAGA_REMASTEREDPawn::Componente_Explotion()
{
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	}

	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
	}

	if (CurrentLives == 0)
	{
		Destroy();
		if (PlayerHUD)
		{
			if (AmbientExplosionSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, AmbientExplosionSound, GetActorLocation());
			}


			PlayerHUD->ShowGameOverScreen();
		}
	}
	else if (CurrentLives >= 1)
	{
		HandleTeleport();
	}
}

void AGALAGA_REMASTEREDPawn::HandleTeleport()
{
	//DESACTIVAR LA COLISION DEL JUGADOR
	SetActorEnableCollision(false);


	SetActorLocation(FVector(0.f, 0.f, 0.f));

	if (TeleportSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, TeleportSound, GetActorLocation());
	}

	TeleportEffect->Activate();
	bIsHealing = true;
	LifeIncrement = 0.0f;
	UpdateHUDHealth(Life / MaxLife);

	GetWorld()->GetTimerManager().SetTimer(CollisionTimerHandle, [this]
		{
			RestoreCollision();

		}, 3.0f, false);
}



void AGALAGA_REMASTEREDPawn::RestoreCollision()
{
	//RESTABLECER LA COLISION DE LA NAVE
	SetActorEnableCollision(true);
}

void AGALAGA_REMASTEREDPawn::IncrementLife(float DeltaTime)
{
	LifeIncrement += HealingRate * DeltaTime;
	Life = FMath::Min(Life + LifeIncrement, MaxLife);
	UpdateHUDHealth(Life / MaxLife); // Actualiza la barra de vida

	if (Life >= MaxLife)
	{
		bIsHealing = false; // Detener el proceso de curación cuando la vida esté completa
	}
}

void AGALAGA_REMASTEREDPawn::CollectTerraBley()
{
	if (CurrentTerraBley < 13)
	{
		CurrentTerraBley++;
		UpdateHUDTerraBleyCount();
	}
}

void AGALAGA_REMASTEREDPawn::StartAccelerating()
{
	if (bCanAccelerate && CurrentSpeedProgress > 0.0f)
	{
		bIsAccelerating = true;
		UGameplayStatics::PlaySoundAtLocation(this, AccelerationSound, GetActorLocation());
		if (AccelerationAudioComponent && !AccelerationAudioComponent->IsPlaying())
		{
			AccelerationAudioComponent->Play();
		}
		ProyecAceLeft->Activate();
		ProyecAceRight->Activate();

		if (CurrentSpeedProgress <= 0.f)
		{
			StopAccelerating();
			ProyecAceLeft->Deactivate();
			ProyecAceRight->Deactivate();
		}
	}
	else
	{
		bIsAccelerating = false;
		//Desactivar la particula de aceleracion
		ProyecAceLeft->Deactivate();
		ProyecAceRight->Deactivate();
	}
}

void AGALAGA_REMASTEREDPawn::StopAccelerating()
{
	bIsAccelerating = false;
	if (AccelerationAudioComponent && AccelerationAudioComponent->IsPlaying())
	{
		AccelerationAudioComponent->Stop();
	}
	ProyecAceLeft->Deactivate();
	ProyecAceRight->Deactivate();
}
