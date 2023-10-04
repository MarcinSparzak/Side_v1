// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManager.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Character.h"
#include "../Characters/PlayerCharacter.h"

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


	// Place camera at the players location
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	
	FVector PlayerLoction = Player->GetActorLocation();
	SpringArm->SetWorldLocation(FVector(-1200, PlayerLoction.Y, PlayerLoction.Z - 250));
	Camera->SetWorldLocation(FVector(-1200, PlayerLoction.Y, PlayerLoction.Z - 250));


	FTimerHandle DelayTimerHandle;
	GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &ACameraManager::DelayTimerCallback, 0.01f, false);
}

// Called every frame
void ACameraManager::Tick(float DeltaTime)
{
	if (!isPlayingIntro)
	Super::Tick(DeltaTime);
	{
		if (IsCameraStationary)
		{
			FVector TmpVector = CenterCameraAtVector(DeltaTime);
			SpringArm->SetWorldLocation(TmpVector);
		}
		else
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
			if (Player != nullptr)
			{
				FVector TmpVector = FollowPlayerMovement(DeltaTime, Player);
				SpringArm->SetWorldLocation(TmpVector);
			}
		}
	}
}

void ACameraManager::SetCameraZValue(float ZValue)
{
	FVector SpringArmVector = SpringArm->GetComponentLocation();
	SpringArm->SetWorldLocation(FVector(SpringArmVector.X, SpringArmVector.Y, ZValue));
}

FVector ACameraManager::FollowPlayerMovement(float DeltaTime, APlayerCharacter* Player)
{
	FVector SpringArmLocation = SpringArm->GetComponentLocation();

	// Vector on planes that we follow
	FVector PlayerVector = (Player->GetActorLocation() + FVector(0, 0, CameraZValue)) * PlanesToFollow;
	// Using YOffest so that camera is always ahead of character 
	float YOffset = Player->DirectionY * CameraYOffest;

	// Vector on planes that we don't follow
	FVector SpringArmVector = (FVector(1, 1, 1) - PlanesToFollow) * SpringArmLocation;
	SpringArmVector += FVector(0, YOffset, 0);


	//UE_LOG(LogTemp, Warning, TEXT("TmpPlayerVector %s"), *PlayerVector.ToString());
	FVector Result = FMath::VInterpTo(SpringArmLocation, PlayerVector + SpringArmVector, DeltaTime, InterpSpeed);
	return Result;
}

void ACameraManager::SetIsFollowingY(bool NewValue)
{
	IsFollowingY = NewValue;

	float y = IsFollowingY ? 1 : 0;
	float z = IsFollowingZ ? 1 : 0;
	PlanesToFollow.Set(0, y, z);
}

void ACameraManager::SetIsFollowingZ(bool NewValue)
{
	IsFollowingZ = NewValue;

	float y = IsFollowingY ? 1 : 0;
	float z = IsFollowingZ ? 1 : 0;
	PlanesToFollow.Set(0, y, z);
}

/*
* Set if camera should be stationary
*/
void ACameraManager::SetCameraStationary(bool NewValue, FVector PointToCenter)
{
	IsCameraStationary = NewValue;
	LocationToCenter = PointToCenter;
}

/*
* Set new camera location durring centering it on LocationToCenter
* Function has to be called in Tick because it works over a period of time
*/
FVector ACameraManager::CenterCameraAtVector(float DeltaTime)
{
	FVector SpringArmLocation = SpringArm->GetComponentLocation();
	FVector TmpVector = LocationToCenter * FVector(0, 1, 0);
	FVector Result = FMath::VInterpTo(SpringArmLocation, FVector(SpringArmLocation.X, TmpVector.Y, SpringArmLocation.Z), DeltaTime, InterpSpeed);

	return Result;
}

void ACameraManager::SetIsPlayingIntro(bool newValue)
{
	isPlayingIntro = newValue;
}

void ACameraManager::DelayTimerCallback()
{
	SpringArm->bEnableCameraLag = true;
}

