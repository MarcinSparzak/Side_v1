// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "../Props/Weapons/WeaponBase.h"
#include "../Camera/CameraManager.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	MovementComp->bOrientRotationToMovement = true;
	MovementComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	MovementComp->SetPlaneConstraintEnabled(true);
	MovementComp->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);

	/*
		Set up Variables for character rotation TODO move to player character
	*/
	CameraManager = Cast<ACameraManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraManager::StaticClass()));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*
		Equip Default weapon
	*/
	if (WeaponClass != nullptr)
	{
		Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
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

	/*
		Set up Variables for character rotation TODO move to player character
	*/
	PlayerController = Cast<ABaseCharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	CameraObj = Cast<UCameraComponent>(CameraManager->GetComponentByClass(UCameraComponent::StaticClass()));

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateCharacter();
	

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ABaseCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Attack);
}

void ABaseCharacter::MoveForwardBackward(float AxisValue)
{
	//AddMovementInput(GetActorForwardVector() * AxisValue);
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), AxisValue);
}
void ABaseCharacter::PullTrigger()
{
	//ABaseCharacterController* PlayerController = Cast<ABaseCharacterController>(UGameplayStatics::GetPlayerController(this, 0));
}
void ABaseCharacter::Attack()
{
	Weapon->Attack();
}
void ABaseCharacter::RotateCharacter()
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
//
//void ABaseCharacter::LookUpDownMouse(float AxisValue)
//{
//	AddControllerPitchInput(AxisValue);
//}

