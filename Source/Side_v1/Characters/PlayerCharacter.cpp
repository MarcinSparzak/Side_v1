// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../Camera/CameraManager.h"
#include "Camera/CameraComponent.h"
#include "BaseCharacterController.h"
#include "../Props/Weapons/GunBase.h"

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

	SetMouseIntersection();
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
	if (IsAiming)
	{
		if (shootRightGun)
		{
			RightHandWeapon->Attack(MouseIntersection);
		}
		else
		{
			LeftHandWeapon->Attack(MouseIntersection);
		}
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*
		Set up Variables for character rotation 
	*/
	APlayerController* TmpPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (TmpPlayerController != nullptr)
	{
		PlayerController = Cast<ABaseCharacterController>(TmpPlayerController);
	}
	if (CameraManager != nullptr)
	{
		CameraObj = Cast<UCameraComponent>(CameraManager->GetComponentByClass(UCameraComponent::StaticClass()));
	}

	SpawnWeapons();

	FRotator tmpRot = GetActorRotation();
	UE_LOG(LogTemp, Warning, TEXT("original rotation %s"), *tmpRot.ToString());
}

void APlayerCharacter::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter Death"));
	ABaseCharacter::Death();
}

void APlayerCharacter::RotateCharacter()
{
	FVector CharacterLocation = GetActorLocation();


	float tmpRotation;
	
	if (CharacterLocation.Y >= MouseIntersection.Y) {
		tmpRotation = -90.0f;
		DirectionY = -1;
	}
	else {
		tmpRotation = 90.0f;
		DirectionY = 1;
	}
	SetActorRotation(FRotator(0, tmpRotation, 0));
}

void APlayerCharacter::SetMouseIntersection()
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
}

void APlayerCharacter::SpawnWeapons()
{
	if (RightWeaponClass != nullptr)
	{
		RightHandWeapon = GetWorld()->SpawnActor<AGunBase>(RightWeaponClass);
		RightHandWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		if (RightHandWeapon != nullptr)
		{
			RightHandWeapon->SetOwner(this);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Weapon not created"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Weapon Class"));

	}
	
	if (LeftWeaponClass != nullptr)
	{
		LeftHandWeapon = GetWorld()->SpawnActor<AGunBase>(LeftWeaponClass);
		LeftHandWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		if (LeftHandWeapon != nullptr)
		{
			LeftHandWeapon->SetOwner(this);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Weapon not created"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Weapon Class"));

	}
}
