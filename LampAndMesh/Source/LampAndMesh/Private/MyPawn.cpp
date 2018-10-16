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
	TriggerCapsule->InitCapsuleSize(65.f, 96.f);
	TriggerCapsule->SetupAttachment(RootComponent);
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMyPawn::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AMyPawn::OnOverlapEnd);
	Lamp = NULL;
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
}

void AMyPawn::TurnLight()
{
	if (Lamp)
	{
		Lamp->ToggleLight();
	}
}

void AMyPawn::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp
		&& OtherActor->GetClass()->IsChildOf<ALamp>())
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *(OtherActor->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *(OtherComp->GetName()));
		Lamp = Cast<ALamp>(OtherActor);
	}
}

void AMyPawn::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		Lamp = NULL;
	}
}

void AMyPawn::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp<float>(AxisValue, -1.f, 1.f) * 100.f;
}

void AMyPawn::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp<float>(AxisValue, -1.f, 1.f) * 100.f;
}