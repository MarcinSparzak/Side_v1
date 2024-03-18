// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
class AGunBase;
UCLASS()
class SIDE_V1_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	APlayerCharacter();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Initiate player attack
	void Attack();

	// Initiate player death
	virtual void Death() override;

	// Gun object in right hand
	AGunBase* RightHandWeapon;
	// Gun object in left hand
	AGunBase* LeftHandWeapon;

	// Class of a weapon to spawn in character right hand
	UPROPERTY(EditDefaultsOnly, meta = (Category = "Player|Weapon"))
		TSubclassOf<AGunBase> RightWeaponClass;
	// Class of a weapon to spawn in character left hand
	UPROPERTY(EditDefaultsOnly, meta = (Category = "Player|Weapon"));
		TSubclassOf<AGunBase> LeftWeaponClass;


	UPROPERTY(BlueprintReadOnly)
		float DirectionY;

	// Boolean to 
	UPROPERTY(BlueprintReadWrite)
	bool shootRightGun = true;

	// Vector of mouse localization on players X plane
	UPROPERTY(BlueprintReadOnly)
		FVector MouseIntersection;

	UPROPERTY(BlueprintReadWrite)
		bool IsAiming;

	// Check if input and stearing is enabled
	UPROPERTY(BlueprintReadWrite)
	bool IsInputEnabled = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	ACameraManager* CameraManager;
	ABaseCharacterController* PlayerController;
	UCameraComponent* CameraObj;

	// Change Character rotation based on mouse cursor placement
	void RotateCharacter();

	// Set FVector MouseIntersection
	void SetMouseIntersection();

	// Create actors according to Weapon classes
	void SpawnWeapons();
};
