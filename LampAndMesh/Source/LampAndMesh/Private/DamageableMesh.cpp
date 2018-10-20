// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageableMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"
#include "Engine/World.h"
#include "Coin.h"

// Sets default values
ADamageableMesh::ADamageableMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UDestructibleComponent>(FName("Mesh"));
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = Cast<USceneComponent>(Mesh);
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
	ApplyDamageToMesh(DamageAmount);
	SpawnCoins();
	return DamageAmount;
}

void ADamageableMesh::SpawnCoins()
{
	float TSec = GetWorld()->GetTimeSeconds();
	float XCord = this->GetActorLocation().X + 100.f * FMath::Sin(TSec);
	float YCord = this->GetActorLocation().Y + 100.f * FMath::Cos(TSec);
	float ZCord = this->GetActorLocation().Z;

	FVector SpawnLocation = FVector(XCord, YCord, ZCord);

	GetWorld()->SpawnActor<ACoin>(
		SpawnLocation,
		this->GetActorRotation()
	);
}

void ADamageableMesh::ApplyDamageToMesh(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health == 0) { this->Destroy(); }
}