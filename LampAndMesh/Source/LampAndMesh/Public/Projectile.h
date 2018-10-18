// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UCapsuleComponent;
class UProjectileMovementComponent;
class URadialForceComponent;

UCLASS()
class LAMPANDMESH_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BaseMesh = nullptr;

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UMaterial* StoredMaterial = nullptr;

	UMaterialInstanceDynamic* DynamicMaterialInst = nullptr;

	float ProjectileSpeed = 5000.f;

	UPROPERTY(VisibleAnywhere, Category = Component)
		URadialForceComponent* ExplosionForce = nullptr;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float DestroyDelay = 3.f;

	void OnTimerExpire();
};