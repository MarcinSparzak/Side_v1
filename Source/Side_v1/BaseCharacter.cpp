// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ABaseCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void ABaseCharacter::MoveForwardBackward(float AxisValue)
{
	//AddMovementInput(GetActorForwardVector() * AxisValue);
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), AxisValue);
}
//
//void ABaseCharacter::LookUpDownMouse(float AxisValue)
//{
//	AddControllerPitchInput(AxisValue);
//}

