// Fill out your copyright notice in the Description page of Project Settings.


#include "CB_Space_Sword.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GALAGA_REMASTEREDPawn.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ACB_Space_Sword::ACB_Space_Sword()
{
	// creando la malla
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/sword/sword6/source/low_uv_sep_SFGS_low002.low_uv_sep_SFGS_low002'"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetVisibility(false);


	ProjectileMesh->OnComponentHit.AddDynamic(this, &ACB_Space_Sword::OnHit);
	// Determinando la velociad de la bala 1

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 25000.f;
	ProjectileMovement->MaxSpeed = 25000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity
	// tiempo de vida de bala
	InitialLifeSpan = 8.0f;

	ProjectileCollision->SetBoxExtent(FVector(250.0f, 250.0f, 250.0f));
	ProjectileCollision->AttachToComponent(ProjectileMesh, FAttachmentTransformRules::KeepRelativeTransform);

	HomingAccelerationMagnitude = 15000.f; // Magnitud de aceleración para el rastreo
	ProjectileMovement->bIsHomingProjectile = true; // Hacer que el proyectil sea un proyectil de rastreo

	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(ProjectileMesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/P_Projectile_BlackHole01_Purple1.P_Projectile_BlackHole01_Purple1'"));

	if (ParticleAsset.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset.Object);

		Proye->bAutoActivate = true;
		Proye->SetWorldScale3D(FVector(8.5f, 8.5f, 8.5f));
	}

}

void ACB_Space_Sword::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	AGALAGA_REMASTEREDPawn* Player = Cast<AGALAGA_REMASTEREDPawn>(OtherActor);

	if (Player)
	{
		Player->Damage_received(200.f);

	}

	this->Destroy();

}

void ACB_Space_Sword::BeginPlay()
{
	Super::BeginPlay();
}

void ACB_Space_Sword::SetHomingTarget(AActor* Target)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->HomingTargetComponent = Target->GetRootComponent();
		ProjectileMovement->HomingAccelerationMagnitude = HomingAccelerationMagnitude;
	}
}

void ACB_Space_Sword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
