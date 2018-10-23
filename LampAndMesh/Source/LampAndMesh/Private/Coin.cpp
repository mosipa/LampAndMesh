// Fill out your copyright notice in the Description page of Project Settings.

#include "Coin.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UCapsuleComponent>(FName("Collision Mesh"));
	CollisionMesh->InitCapsuleSize(15.f, 25.f);
	RootComponent = Cast<USceneComponent>(CollisionMesh);
	CollisionMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule"));

	if (FoundMesh.Succeeded())
	{
		BaseMesh->SetStaticMesh(FoundMesh.Object);
		BaseMesh->SetRelativeScale3D(FVector(.25f, .25f, .25f));
		BaseMesh->SetRelativeLocation(FVector(0.f, 0.f, -10.f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/Materials/M_Coin"));

	if (FoundMaterial.Succeeded())
	{
		StoredMaterial = FoundMaterial.Object;
	}

	DynamicMaterialInst = UMaterialInstanceDynamic::Create(StoredMaterial, BaseMesh);

	BaseMesh->SetMaterial(0, DynamicMaterialInst);

	bReplicates = true;
}

void ACoin::DestroyCollected()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Colleceted coin."));
	}
	this->Destroy();
}