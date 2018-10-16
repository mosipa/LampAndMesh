// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Public/DrawDebugHelpers.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Launching projectile"));

	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * 400.f);

	ProjectileMovementComponent->Activate();
}