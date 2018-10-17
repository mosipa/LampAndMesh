// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageableMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"

// Sets default values
ADamageableMesh::ADamageableMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UDestructibleComponent>(FName("Mesh"));
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
	
	Health = 50.f;
}

// Called when the game starts or when spawned
void ADamageableMesh::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADamageableMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ADamageableMesh::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Dmg TAKEN"));
	ApplyDamage(DamageAmount);
	return DamageAmount;
}

void ADamageableMesh::ApplyDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health == 0) { Destroyed(); }
}

void ADamageableMesh::Destroyed()
{
	this->Destroy();
}