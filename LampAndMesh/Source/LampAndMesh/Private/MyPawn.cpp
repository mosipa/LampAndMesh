// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Lamp.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(-250.f, 0.f, 250.f));
	Camera->SetRelativeRotation(FRotator(-25.f, 0.f, 0.f));
	
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pawn Mesh"));
	PawnMesh->SetupAttachment(RootComponent);

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	TriggerCapsule->InitCapsuleSize(50.f, 70.f);
	TriggerCapsule->SetupAttachment(RootComponent);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMyPawn::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AMyPawn::OnOverlapEnd);
	
	Lamp = nullptr;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}


// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::MoveXAxis);

	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::MoveYAxis);

	PlayerInputComponent->BindAction("TurnLight", IE_Pressed, this, &AMyPawn::TurnLight);

	PlayerInputComponent->BindAction("ChangeColor", IE_Pressed, this, &AMyPawn::ChangeColor);

	PlayerInputComponent->BindAction("TurnLightAndChangeColor", IE_Pressed, this, &AMyPawn::TurnLightAndChangeColor);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyPawn::Fire);
}

void AMyPawn::Fire()
{
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(GetActorLocation() + FVector(100.f, 0.f, 50.f), GetActorRotation());
	Projectile->LaunchProjectile();
}

void AMyPawn::TurnLight()
{
	if (Lamp)
	{
		Lamp->ToggleLight();
	}
}

void AMyPawn::ChangeColor()
{
	if(Lamp)
	{
		Lamp->ChangeColor();
	}
}

void AMyPawn::TurnLightAndChangeColor()
{
	if (Lamp)
	{
		Lamp->TurnLightAndChangeColor();
	}
}

void AMyPawn::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp
		&& OtherActor->GetClass()->IsChildOf<ALamp>())
	{
		Lamp = Cast<ALamp>(OtherActor);
	}
}

void AMyPawn::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		Lamp = nullptr;
	}
}

void AMyPawn::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp<float>(AxisValue, -1.f, 1.f) * 500.f;
}

void AMyPawn::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp<float>(AxisValue, -1.f, 1.f) * 500.f;
}