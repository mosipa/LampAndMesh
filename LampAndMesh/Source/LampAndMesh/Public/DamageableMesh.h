// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageableMesh.generated.h"

class UDestructibleComponent;

UCLASS()
class LAMPANDMESH_API ADamageableMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageableMesh();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		UDestructibleComponent* Mesh;

	float Health;

	void ApplyDamageToMesh(float DamageAmount);

	void SpawnCoins();
	
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSpawnCoins();
		void ServerSpawnCoins_Implementation();
		bool ServerSpawnCoins_Validate();

	UFUNCTION(Client, Reliable, WithValidation)
		void ClientSpawnCoins();
		void ClientSpawnCoins_Implementation();
		bool ClientSpawnCoins_Validate();
		
};
