// Copyright Epic Games, Inc. All Rights Reserve

#include "GALAGA_REMASTEREDProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Z_Ship_Striker.h"
#include "Z_Enemy_Ship_P.h"
#include "X_Master_Ship_P.h"


AGALAGA_REMASTEREDProjectile::AGALAGA_REMASTEREDProjectile() 
{
	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/Space_Creator/Star_Creator/Star_Creator_Original/Meshes/Sphere_2_Plane.Sphere_2_Plane'"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AGALAGA_REMASTEREDProjectile::OnHit);		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AGALAGA_REMASTEREDProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();

	AZ_Enemy_Ship_P* Nave_Padre = Cast<AZ_Enemy_Ship_P>(OtherActor);

	if (Nave_Padre) 
	{
		Nave_Padre->Recibir_Danio(50);
		GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ship Colision [Enemy]"));
	}



	AX_Master_Ship_P* Nave_Padre_2 = Cast<AX_Master_Ship_P>(OtherActor);

	if (Nave_Padre_2) 
	{
		Nave_Padre_2->Recibir_Danio(50);
		GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ship Colision [Master]"));
	}


	//AZ_Ship_Striker* NAVE = Cast<AZ_Ship_Striker>(OtherActor);

	//if (NAVE) 
	//{
	//	NAVE->Recibir_Danio(50);
	//	GEngine -> AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Ship Colision [STriker]"));
	//}
}