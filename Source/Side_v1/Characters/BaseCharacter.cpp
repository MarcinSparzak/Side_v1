// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Props/Weapons/WeaponBase.h"

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

	Health = MaxHealth;

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
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Attack);
}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Actor takes damage: %f"), DamageApplied);
	return DamageApplied;
}


void ABaseCharacter::MoveForwardBackward(float AxisValue)
{
	//AddMovementInput(GetActorForwardVector() * AxisValue);
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), AxisValue);
}
void ABaseCharacter::Attack()
{
	Weapon->Attack();
}


