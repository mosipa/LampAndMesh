// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageableMesh.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADamageableMesh::ADamageableMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void ADamageableMesh::BeginPlay()
{
	Super::BeginPlay();
	Health = 100.f;
}

// Called every frame
void ADamageableMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ADamageableMesh::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Received dmg: %f"), DamageAmount);
	Health -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Health left: %f"), Health);
	return 1.f;
}