// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Lamp.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"

// Sets default values
ALamp::ALamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(FName("Point Light"));
	PointLight->LightColor = FColor::Yellow;
	PointLight->bVisible = true;
	
	RootComponent = PointLight;

	PointLightSphere = CreateDefaultSubobject<USphereComponent>(FName("Point Light Sphere"));
	PointLightSphere->InitSphereRadius(400.f);
	PointLightSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PointLightSphere->AttachToComponent(PointLight, FAttachmentTransformRules::SnapToTargetIncludingScale);

	Colors.Add(FColor::Red);
	Colors.Add(FColor::Blue);
	Colors.Add(FColor::Yellow);
	ElNum = 0;
}

// Called when the game starts or when spawned
void ALamp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALamp::ToggleLight()
{
	PointLight->ToggleVisibility();
}

void ALamp::ChangeColor()
{
	PointLight->SetLightColor(Colors[ElNum]);
	ElNum++;
	ElNum = ElNum % Colors.Num();
}

void ALamp::TurnLightAndChangeColor()
{
	ToggleLight();
	ChangeColor();
}