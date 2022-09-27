// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Character.h"

// Sets default values
ACameraManager::ACameraManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


}

// Called when the game starts or when spawned
void ACameraManager::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->SetViewTarget(this);

}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsCameraStationary)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Stationary"));
		FVector TmpVector = CenterCameraAtVector(DeltaTime);
		SpringArm->SetWorldLocation(TmpVector);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Dynamic"));
		float y = IsFollowingY ? 1 : 0;
		float z = IsFollowingZ ? 1 : 0;
		PlanesToFollow.Set(0, y, z);
		FVector TmpVector = FollowPlayerMovement(DeltaTime);
		SpringArm->SetWorldLocation(TmpVector);
	}

}

void ACameraManager::SetCameraZValue(float ZValue)
{
	FVector SpringArmVector = SpringArm->GetComponentLocation();
	SpringArm->SetWorldLocation(FVector(SpringArmVector.X, SpringArmVector.Y, ZValue));
}

FVector ACameraManager::FollowPlayerMovement(float DeltaTime)
{
	FVector SpringArmLocation = SpringArm->GetComponentLocation();

	// Get Player location on planes that we follow
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	FVector PlayerVector = Player->GetActorLocation() * PlanesToFollow;

	// Get SpringArm on planes that we don't follow
	FVector SpringArmVector = (FVector(1, 1, 1) - PlanesToFollow) * SpringArmLocation;

	FVector Result = FMath::VInterpTo(SpringArmLocation, PlayerVector + SpringArmVector, DeltaTime, InterpSpeed);

	return Result;
}

void ACameraManager::SetIsFollowingY(bool NewValue)
{
	IsFollowingY = NewValue;
}

void ACameraManager::SetIsFollowingZ(bool NewValue)
{
	IsFollowingZ = NewValue;
}

void ACameraManager::SetCameraStationary(bool NewValue, FVector PointToCenter)
{
	IsCameraStationary = NewValue;
	LocationToCenter = PointToCenter;
}

FVector ACameraManager::CenterCameraAtVector(float DeltaTime)
{
	FVector SpringArmLocation = SpringArm->GetComponentLocation();
	FVector TmpVector = LocationToCenter * FVector(0, 1, 0);
	FVector Result = FMath::VInterpTo(SpringArmLocation, FVector(SpringArmLocation.X, TmpVector.Y, SpringArmLocation.Z), DeltaTime, InterpSpeed);

	return Result;
}

