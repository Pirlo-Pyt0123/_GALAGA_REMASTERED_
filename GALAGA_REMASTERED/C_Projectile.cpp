// Copyright Epic Games, Inc. All Rights Reserve

#include "C_Projectile.h"

AC_Projectile::AC_Projectile()
{
	// Configure este peón para llamar a Tick() en cada cuadro. Puede desactivarlo para mejorar el rendimiento si no lo necesita.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PP"));
	// Establecer la malla de la nave como el componente raíz de la nave
	ProjectileMesh->SetupAttachment(RootComponent);
	

	

	ProjectileCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Ship Collision"));
	//ProjectileCollision->AttachToComponent(ProjectileMesh, FAttachmentTransformRules::KeepRelativeTransform);

	// Muere después de 3 segundos por defecto
	InitialLifeSpan = 10.f;

	// Daño del proyectil predeterminado
	
}

