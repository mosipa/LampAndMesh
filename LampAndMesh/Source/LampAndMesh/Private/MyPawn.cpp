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
#include "Coin.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerStart.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Runtime/Networking/Public/Networking.h"
#include "UnrealNetwork.h"
#include "Engine.h"
// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AutoPossessPlayer = EAutoReceiveInput::Disabled;

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
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FoundMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube"));

	if (FoundMesh.Succeeded())
	{
		Cast<UStaticMeshComponent>(PawnMesh)->SetStaticMesh(FoundMesh.Object);
		PawnMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/Materials/M_Pawn"));

	if (FoundMaterial.Succeeded())
	{
		StoredMaterial = FoundMaterial.Object;
	}

	DynamicMaterialInst = UMaterialInstanceDynamic::Create(StoredMaterial, PawnMesh);

	Cast<UStaticMeshComponent>(PawnMesh)->SetMaterial(0, DynamicMaterialInst);

	Lamp = nullptr;
	Coin = nullptr;

	bReplicates = true;
	bReplicateMovement = true;
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

void AMyPawn::OnRep_PosChange()
{
	SetActorLocation(CurrentPosition);
}

void AMyPawn::OnRep_RotChange()
{
	SetActorRotation(CurrentRotation);
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
	if (HasAuthority())
	{
		ClientTurnLight();
	}
	else
	{
		ServerTurnLight();
	}
}

void AMyPawn::ServerTurnLight_Implementation()
{
	TurnLight();
}

bool AMyPawn::ServerTurnLight_Validate()
{
	return true;
}

void AMyPawn::ClientTurnLight_Implementation()
{
	if (Lamp)
	{
		Lamp->ToggleLight();
	}
}

bool AMyPawn::ClientTurnLight_Validate()
{
	return true;
}

void AMyPawn::ChangeColor()
{
	if (HasAuthority())
	{
		ClientChangeColor();
	}
	else
	{
		ServerChangeColor();
	}
}

void AMyPawn::ServerChangeColor_Implementation()
{
	ChangeColor();
}

bool AMyPawn::ServerChangeColor_Validate()
{
	return true;
}

void AMyPawn::ClientChangeColor_Implementation()
{
	if (Lamp)
	{
		Lamp->ChangeColor();
	}
}

bool AMyPawn::ClientChangeColor_Validate()
{
	return true;
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

	if (OtherActor && (OtherActor != this) && OtherComp
		&& OtherActor->GetClass()->IsChildOf<ACoin>())
	{
		Coin = Cast<ACoin>(OtherActor);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Colleceted coin."));
		}
		Coin->DestroyCollected();
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
	if (Role != ROLE_Authority && IsLocallyControlled())
	{
		ServerMoveXAxis(AxisValue, Controller->GetControlRotation());
	}
	CurrentVelocity.X = FMath::Clamp<float>(AxisValue, -1.f, 1.f) * 500.f;
}

bool AMyPawn::ServerMoveXAxis_Validate(float AxisValue, FRotator Rotation)
{
	return true;
}

void AMyPawn::ServerMoveXAxis_Implementation(float AxisValue, FRotator Rotation)
{
	CurrentVelocity.X = FMath::Clamp<float>(AxisValue, -1.f, 1.f) * 500.f;
	SetActorRotation(Rotation);
	CurrentRotation = Rotation;
	SetActorLocation(GetActorLocation());
	CurrentPosition = GetActorLocation();
}

void AMyPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyPawn, CurrentPosition);
	DOREPLIFETIME(AMyPawn, CurrentRotation);
}

void AMyPawn::MoveYAxis(float AxisValue)
{
	if (Role != ROLE_Authority && IsLocallyControlled())
	{
		ServerMoveYAxis(AxisValue, Controller->GetControlRotation());
	}
	CurrentVelocity.Y = FMath::Clamp<float>(AxisValue, -1.f, 1.f) * 500.f;
}

void AMyPawn::ServerMoveYAxis_Implementation(float AxisValue, FRotator Rotation)
{
	CurrentVelocity.Y = FMath::Clamp<float>(AxisValue, -1.f, 1.f) * 500.f;
	SetActorRotation(Rotation);
	CurrentRotation = Rotation;
	SetActorLocation(GetActorLocation());
	CurrentPosition = GetActorLocation();
}

bool AMyPawn::ServerMoveYAxis_Validate(float AxisValue, FRotator Rotation)
{
	return true;
}