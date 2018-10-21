// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class ALamp;
class AProjectile;
class ACoin;
class UMaterial;

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


	UFUNCTION()
		void MoveXAxis(float AxisValue);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerMoveXAxis(float AxisValue, FRotator Rotation);
		void ServerMoveXAxis_Implementation(float AxisValue, FRotator Rotation);
		bool ServerMoveXAxis_Validate(float AxisValue, FRotator Rotation);

	UFUNCTION()
		void MoveYAxis(float AxisValue);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerMoveYAxis(float AxisValue, FRotator Rotation);
		void ServerMoveYAxis_Implementation(float AxisValue, FRotator Rotation);
		bool ServerMoveYAxis_Validate(float AxisValue, FRotator Rotation);

	UPROPERTY(Transient, ReplicatedUsing = OnRep_PosChange)
		FVector CurrentPosition;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_RotChange)
		FRotator CurrentRotation;

	UFUNCTION()
		void OnRep_PosChange();

	UFUNCTION()
		void OnRep_RotChange();

	FVector CurrentVelocity;

	/*UFUNCTION(Reliable, NetMulticast, WithValidation)
		void TurnLight();
		void TurnLight_Implementation();
		bool TurnLight_Validate();

	UFUNCTION(Reliable, Server, WithValidation)
		void Server_TurnLight();
		void Server_TurnLight_Implementation();
		bool Server_TurnLight_Validate();
		(
	*/void TurnLight();

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

	UMaterial* StoredMaterial = nullptr;

	UMaterialInstanceDynamic* DynamicMaterialInst = nullptr;
};
