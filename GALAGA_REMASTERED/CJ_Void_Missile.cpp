// Fill out your copyright notice in the Description page of Project Settings.


#include "CJ_Void_Missile.h"
#include "Z_Enemy_Ship_P.h"
#include "X_Master_Ship_P.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Engine.h"

ACJ_Void_Missile::ACJ_Void_Missile()
{
	PrimaryActorTick.bCanEverTick = true;
	// Creando la malla
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/VFXSeries1/Meshes/Projectile/VOID_MISSILE.VOID_MISSILE'"));
	if (ProjectileMeshAsset.Succeeded())
	{
		ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
		// Ajustar la rotación de la malla sin afectar el movimiento
		

		// Escala de la malla
		ProjectileMesh->SetWorldScale3D(FVector(10.5f, 10.5f, 10.5f));
	}
	//=======================================================
	//Habilitar visibilidad de la malla
	ProjectileMesh->SetVisibility(false);


	//=======================================================
	//Configurar el componente de movimiento del proyectil
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ACJ_Void_Missile::OnHit);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;

	//Determinando la velocidad de la bala
	ProjectileMovement->InitialSpeed = 150000.f;

	//Determinando la velocidad maxima de la bala
	ProjectileMovement->MaxSpeed = 1500000.f;

	//Determinando si la rotacion sigue la velocidad
	ProjectileMovement->bRotationFollowsVelocity = true;

	//Determinando si la bala rebota
	ProjectileMovement->bShouldBounce = false;

	//Determinando la gravedad de la bala
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	//muere despues de 3 segundos por defecto
	InitialLifeSpan = 5.0f;

	// Configurando el campo de colisión de este actor
	ProjectileCollision->SetBoxExtent(FVector(300.0f, 300.0f, 300.0f));
	ProjectileCollision->AttachToComponent(ProjectileMesh, FAttachmentTransformRules::KeepRelativeTransform);


	// Crear el componente de partículas y adjuntarlo a la malla del proyectil
	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(ProjectileMesh);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/VFXSeries1/Particles/Tails/P_RocketTypeB.P_RocketTypeB'"));
	if (ParticleAsset2.Succeeded())
	{
		Proye->SetTemplate(ParticleAsset2.Object);
		Proye->bAutoActivate = true;
		
		Proye->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
		Proye->SetWorldScale3D(FVector(8.5f, 8.5f, 8.5f));
	}
}

void ACJ_Void_Missile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();


	//=======================================================
	//Daño a la nave enemiga
	AZ_Enemy_Ship_P* Nave_Padre = Cast<AZ_Enemy_Ship_P>(OtherActor);

	if (Nave_Padre)
	{
		Nave_Padre->Recibir_Danio(500);

	}


	//=======================================================
	//Daño la master ship
	AX_Master_Ship_P* Nave_Padre_2 = Cast<AX_Master_Ship_P>(OtherActor);

	if (Nave_Padre_2)
	{
		Nave_Padre_2->Recibir_Danio(800);

	}
}

void ACJ_Void_Missile::UpdateProjectileDirection(const FVector& NewDirection)
{
	//=======================================================
    //---||Actualizar la dirección del proyectil
	CurrentDirection = NewDirection.GetSafeNormal();
	ProjectileMovement->Velocity = CurrentDirection * ProjectileMovement->InitialSpeed;

	//---|| Actualizar la rotación del proyectil basada en la dirección
	FRotator NewRotation = CurrentDirection.Rotation();
	NewRotation.Yaw += 90.0f; // Ajustar según necesidades específicas

}
