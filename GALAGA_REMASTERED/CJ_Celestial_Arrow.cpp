// Fill out your copyright notice in the Description page of Project Settings.


#include "CJ_Celestial_Arrow.h"
#include "Z_Enemy_Ship_P.h"
#include "X_Master_Ship_P.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Engine.h"
ACJ_Celestial_Arrow::ACJ_Celestial_Arrow()
{
	PrimaryActorTick.bCanEverTick = true;
    // Creando la malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/assetsGENIE/ARROW/ARROW.ARROW'"));
    if (ProjectileMeshAsset.Succeeded())
    {
		ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);

		//aparicion de la malla
		
		

		
    }
	
    ProjectileMesh->OnComponentHit.AddDynamic(this, &ACJ_Celestial_Arrow::OnHit);

    

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 150000.f;
	ProjectileMovement->MaxSpeed = 150000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; 

	// Duración de vida del proyectil
	InitialLifeSpan = 5.0f;

    // Configurando el campo de colisión de este actor
    ProjectileCollision->SetBoxExtent(FVector(250.0f, 250.0f, 250.0f));
    ProjectileCollision->AttachToComponent(ProjectileMesh, FAttachmentTransformRules::KeepRelativeTransform);


	Proye = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Proye"));
	Proye->SetupAttachment(ProjectileMesh);
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset2(TEXT("ParticleSystem'/Game/MagicProjectilesVol2/Particles/Projectiles/P_Projectile_BlackHole01_Purple1.P_Projectile_BlackHole01_Purple1'"));
    if (ParticleAsset2.Succeeded())
    {
        Proye->SetTemplate(ParticleAsset2.Object);
        Proye->bAutoActivate = true;
		Proye->SetWorldScale3D(FVector(20.5f, 20.5f, 20.5f));
    }
}

void ACJ_Celestial_Arrow::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
		Nave_Padre_2->Recibir_Danio(200);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ship Colision [Master]"));
	}
}

void ACJ_Celestial_Arrow::UpdateProjectileDirection(const FVector& NewDirection)
{
	// Normalizar la dirección del proyectil
	CurrentDirection = NewDirection.GetSafeNormal();

	// Actualizar la velocidad del proyectil según la nueva dirección
	ProjectileMovement->Velocity = CurrentDirection * ProjectileMovement->InitialSpeed;
}

void ACJ_Celestial_Arrow::BeginPlay()
{
	Super::BeginPlay();


}

void ACJ_Celestial_Arrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
