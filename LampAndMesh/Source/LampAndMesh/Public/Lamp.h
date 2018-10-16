// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lamp.generated.h"

class UPointLightComponent;
class USphereComponent;

UCLASS()
class LAMPANDMESH_API ALamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALamp();

	virtual void Tick(float DeltaTime) override;

	void ToggleLight();
	void ChangeColor();
	void TurnLightAndChangeColor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Light Setup")
		UPointLightComponent* PointLight = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Light Setup")
		USphereComponent* PointLightSphere = nullptr;

	TArray<FColor> Colors;

	int32 ElNum;
};
