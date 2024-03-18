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
	SpringArm->SetWorldLocation(FVector(-1700, PlayerLoction.Y, PlayerLoction.Z - 350));
	Camera->SetWorldLocation(FVector(-1700, PlayerLoction.Y, PlayerLoction.Z - 250));


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

// Depracted
void ACameraManager::SetCameraZValue(float ZValue)
{
	FVector SpringArmVector = SpringArm->GetComponentLocation();
	SpringArm->SetWorldLocation(FVector(SpringArmVector.X, SpringArmVector.Y, ZValue));
}

void ACameraManager::SetCameraZValueBasedOnMousePosition()
{
	// Check if object are set properly
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not found"));
		return;
	}

	if (Camera == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera component not found"));
		return;
	}

	FVector CameraLocation = Camera->GetComponentLocation();

	// Get placement and rotaion of mouse cursor in world
	FVector MouseWorldLocation;
	FVector MouseRotation;
	PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseRotation);

	// Create line from Mouse World Location towards players plane
	FVector IntersectionLineEnd = MouseRotation * (SpringArmLength * 2) + MouseWorldLocation;

	// Find a point of intersection between created line and players plane
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	FVector CharacterLocation = Player->GetActorLocation();
	FVector MouseIntersection = FMath::LinePlaneIntersection(CameraLocation, IntersectionLineEnd, CharacterLocation, FVector(1.0, 0.0, 0.0));

	// Set Z limits for mouse cursor between which camera does not change it's Z value
	float playerMouseZDifference = CharacterLocation.Z - MouseIntersection.Z;
	float UpperModifier = 100.0f;
	float LowerModifier = -150.0f;
	float mouseZLimit = 150.0f;
	if (playerMouseZDifference >= mouseZLimit)
	{
		CameraZValue = LowerModifier;
	}
	else if (playerMouseZDifference <= -mouseZLimit)
	{
		CameraZValue = UpperModifier;
	}
	else {
		CameraZValue = 0.0f;
	}
}

/*
	Called every frame to set locotion for camera oposing player character
*/
FVector ACameraManager::FollowPlayerMovement(float DeltaTime, APlayerCharacter* Player)
{
	FVector SpringArmLocation = SpringArm->GetComponentLocation();

	// Change Camera Z value if player is looking up or down
	SetCameraZValueBasedOnMousePosition();

	// Vector on planes that we follow
	FVector PlayerVector = Player->GetActorLocation() * PlanesToFollow;
	// Using YOffest so that camera is always ahead of character 
	float YOffset = Player->DirectionY * CameraYOffest;
	PlayerVector += FVector(0, YOffset, CameraZValue);

	// Vector on planes that we don't follow
	FVector SpringArmVector = (FVector(1, 1, 1) - PlanesToFollow) * SpringArmLocation;
	//SpringArmVector += FVector(0, YOffset, CameraZValue);

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
	FVector TmpVector = LocationToCenter * FVector(1, 1, 1);
	FVector Result = FMath::VInterpTo(SpringArmLocation, FVector(TmpVector.X, TmpVector.Y, TmpVector.Z), DeltaTime, InterpSpeed);

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


