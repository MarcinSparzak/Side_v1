// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"
class ACameraManager;  class ABaseCharacterController; class UCameraComponent;
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

	virtual void Death();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForwardBackward(float AxisValue);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	bool IsDead();

	UFUNCTION(BlueprintImplementableEvent)
		void DestroyCharacter();
private:
	//
	float Health;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100;

	UPROPERTY(EditDefaultsOnly, meta = (Category = "Player|Combat"))
		UAnimMontage* HitAnimation;

	UPROPERTY(EditDefaultsOnly, meta = (Category = "Player|Combat"))
		UAnimMontage* DeathAnimation;
};
