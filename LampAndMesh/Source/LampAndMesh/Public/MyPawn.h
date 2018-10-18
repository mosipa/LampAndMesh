// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class ALamp;
class AProjectile;
class ACoin;

UCLASS()
class LAMPANDMESH_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);

	FVector CurrentVelocity;

	void TurnLight();

	void ChangeColor();

	void TurnLightAndChangeColor();

	void Fire();

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		USceneComponent* PawnMesh = nullptr;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* TriggerCapsule = nullptr;

	ALamp* Lamp;

	ACoin* Coin;
};
