// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageableMesh.h"


// Sets default values
ADamageableMesh::ADamageableMesh()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

