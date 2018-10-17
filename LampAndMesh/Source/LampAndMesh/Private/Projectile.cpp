// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Public/DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision Mesh"));
	CollisionMesh->InitCapsuleSize(25.f, 25.f);
	RootComponent = Cast<USceneComponent>(CollisionMesh);
	CollisionMesh->SetVisibility(true);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));

	if (FoundMesh.Succeeded())
	{
		BaseMesh->SetStaticMesh(FoundMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/Materials/M_Projectile"));

	if (FoundMaterial.Succeeded())
	{
		StoredMaterial = FoundMaterial.Object;
	}

	DynamicMaterialInst = UMaterialInstanceDynamic::Create(StoredMaterial, BaseMesh);

	BaseMesh->SetMaterial(0, DynamicMaterialInst);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile()
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * ProjectileSpeed);
	ProjectileMovementComponent->Activate();
}