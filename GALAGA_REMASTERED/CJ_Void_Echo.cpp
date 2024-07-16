// Fill out your copyright notice in the Description page of Project Settings.


#include "CJ_Void_Echo.h"
#include "Z_Enemy_Ship_P.h"
#include "X_Master_Ship_P.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Engine.h"

ACJ_Void_Echo::ACJ_Void_Echo()
{
	PrimaryActorTick.bCanEverTick = true;
	// Creando la malla
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/assetsGENIE/ARROW/ARROW.ARROW'"));
	if (ProjectileMeshAsset.Succeeded())
	{
		ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
		
		ProjectileMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

		ProjectileMesh->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
	}
	
	ProjectileMesh->SetVisibility(false);


	//=======================================================
	//Configurar el componente de movimiento del proyectil
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ACJ_Void_Echo::OnHit);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;

	//Determinando la velocidad de la bala
	ProjectileMovement->InitialSpeed = 150000.f;

	//Determinando la velocidad maxima de la bala
	ProjectileMovement->MaxSpeed = 150000.f;

	//Determinando si la rotacion sigue la velocidad
	ProjectileMovement->bRotationFollowsVelocity = true;

	//Determinando si la bala rebota
	ProjectileMovement->bShouldBounce = false;

	//Determinando la gravedad de la bala
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	//muere despues de 3 segundos por defecto
	InitialLifeSpan = 5.0f;

	// Configurando el campo de colisión de este actor
	ProjectileCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	ProjectileCollision->AttachToComponent(ProjectileMesh, FAttachmentTransformRules::KeepRelativeTransform);


	// Crear el componente de partículas y adjuntarlo a la malla del proyectil
	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(ProjectileMesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/P_Projectile_Trail05_Red.P_Projectile_Trail05_Red'"));
	if (ParticleAsset2.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset2.Object);
		Proye->bAutoActivate = true;

		Proye->SetWorldScale3D(FVector(6.5f, 6.5f, 6.5f));
	}
}

void ACJ_Void_Echo::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();


	//=======================================================
	//Daño a la nave enemiga
	AZ_Enemy_Ship_P* Nave_Padre = Cast<AZ_Enemy_Ship_P>(OtherActor);

	if (Nave_Padre)
	{
		Nave_Padre->Recibir_Danio(200);

	}


	//=======================================================
	//Daño la master ship
	AX_Master_Ship_P* Nave_Padre_2 = Cast<AX_Master_Ship_P>(OtherActor);

	if (Nave_Padre_2)
	{

		Nave_Padre_2->Recibir_Danio(500);

	}
}

void ACJ_Void_Echo::UpdateProjectileDirection(const FVector& NewDirection)
{
	//=======================================================
	//Actualizar la dirección del proyectil
	CurrentDirection = NewDirection.GetSafeNormal();
	ProjectileMovement->Velocity = CurrentDirection * ProjectileMovement->InitialSpeed;

	// Actualizar la rotación del proyectil basada en la dirección
	FRotator NewRotation = CurrentDirection.Rotation();
	NewRotation.Yaw += 90.0f; // Ajustar según necesidades específicas

	SetActorRotation(NewRotation);
}
