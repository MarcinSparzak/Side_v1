// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../Camera/CameraManager.h"
#include "Camera/CameraComponent.h"
#include "BaseCharacterController.h"
#include "../Props/Weapons/WeaponBase.h"

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SetGenericTeamId(FGenericTeamId(1));

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

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ABaseCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Attack);
}

void APlayerCharacter::Attack()
{
	Weapon->Attack(MouseIntersection);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*
		Set up Variables for character rotation 
	*/
	PlayerController = Cast<ABaseCharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	CameraObj = Cast<UCameraComponent>(CameraManager->GetComponentByClass(UCameraComponent::StaticClass()));


	/*
		Equip Default weapon
	*/
	if (WeaponClass != nullptr)
	{
		Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		if (Weapon != nullptr)
		{
			Weapon->SetOwner(this);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Weapon not created"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Weapon Class"));

	}
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
