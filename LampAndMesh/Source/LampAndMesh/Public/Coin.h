// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class UCapsuleComponent;

UCLASS()
class LAMPANDMESH_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

	void DestroyCollected();

private:
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BaseMesh = nullptr;

	UMaterial* StoredMaterial = nullptr;

	UMaterialInstanceDynamic* DynamicMaterialInst = nullptr;
};
