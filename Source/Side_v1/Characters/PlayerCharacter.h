// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
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

	virtual void Attack() override;

	// Setting up weapons for character to be equiped with default weapon
	UPROPERTY()
		AWeaponBase* Weapon;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AWeaponBase> WeaponClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Helper for character rotation TODO move to player character
	ACameraManager* CameraManager;
	ABaseCharacterController* PlayerController;
	UCameraComponent* CameraObj;
	void RotateCharacter();


};
