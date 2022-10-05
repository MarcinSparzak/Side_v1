// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"
class ACameraManager; class AWeaponBase; class ABaseCharacterController; class UCameraComponent;
UCLASS()
class SIDE_V1_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FVector MouseIntersection;

	bool IsDead();
private:
	//
	float Health;

	UPROPERTY(EditAnywhere)
	float MaxHealth;

	// Axis and action functions
	void MoveForwardBackward(float AxisValue);
	void Attack();
	
	// Setting up weapons for character to be equiped with default weapon
	UPROPERTY()
	AWeaponBase* Weapon;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeaponBase> WeaponClass;

	virtual void Death();
};
