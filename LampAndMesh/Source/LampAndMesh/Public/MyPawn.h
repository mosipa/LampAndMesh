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

	UFUNCTION()
		void TurnLight();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerTurnLight();
		void ServerTurnLight_Implementation();
		bool ServerTurnLight_Validate();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void ClientTurnLight();
		void ClientTurnLight_Implementation();
		bool ClientTurnLight_Validate();

	void ChangeColor();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerChangeColor();
		void ServerChangeColor_Implementation();
		bool ServerChangeColor_Validate();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void ClientChangeColor();
		void ClientChangeColor_Implementation();
		bool ClientChangeColor_Validate();

	void TurnLightAndChangeColor();

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerTurnLightAndChangeColor();
		void ServerTurnLightAndChangeColor_Implementation();
		bool ServerTurnLightAndChangeColor_Validate();

	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void ClientTurnLightAndChangeColor();
		void ClientTurnLightAndChangeColor_Implementation();
		bool ClientTurnLightAndChangeColor_Validate();

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

	ACoin* Coin;

	ALamp* Lamp;

	UMaterial* StoredMaterial = nullptr;

	UMaterialInstanceDynamic* DynamicMaterialInst = nullptr;
};
