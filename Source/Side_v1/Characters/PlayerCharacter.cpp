// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../Camera/CameraManager.h"
#include "Camera/CameraComponent.h"
#include "BaseCharacterController.h"

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
		Set up Variables for character rotation 
	*/
	CameraManager = Cast<ACameraManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraManager::StaticClass()));
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateCharacter();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*
		Set up Variables for character rotation 
	*/
	PlayerController = Cast<ABaseCharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	CameraObj = Cast<UCameraComponent>(CameraManager->GetComponentByClass(UCameraComponent::StaticClass()));

}

void APlayerCharacter::RotateCharacter()
{
	if (PlayerController == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not found"));
		return;
	}

	if (CameraManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera Manager not found"));
		return;
	}

	if (CameraObj == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera component not found"));
		return;
	}

	FVector CameraLocation = CameraObj->GetComponentLocation();

	FVector MouseWorldLocation;
	FVector MouseRotation;
	PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseRotation);

	FVector IntersectionLineEnd = MouseRotation * (CameraManager->SpringArmLength * 2) + MouseWorldLocation;

	FVector CharacterLocation = GetActorLocation();
	MouseIntersection = FMath::LinePlaneIntersection(CameraLocation, IntersectionLineEnd, CharacterLocation, FVector(1.0, 0.0, 0.0));


	float tmpRotation = CharacterLocation.Y >= MouseIntersection.Y ? -90.0f : 90.0f;
	SetActorRotation(FRotator(0, tmpRotation, 0));
}
