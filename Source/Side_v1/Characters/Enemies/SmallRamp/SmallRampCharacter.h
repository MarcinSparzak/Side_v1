// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseEnemyCharacter.h"
#include "SmallRampCharacter.generated.h"
class AMeleeBase;
/**
 * 
 */
UCLASS()
class SIDE_V1_API ASmallRampCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()
	
public:
	ASmallRampCharacter();

	UPROPERTY(EditDefaultsOnly, meta = (Category = "AI|Combat"))
		TSubclassOf<AMeleeBase> WeaponClass;

	AMeleeBase* GetRightHandWeapon();

	UFUNCTION()
	void Attack(FVector TargetPoint);

	UFUNCTION(BlueprintCallable)
		void OnAttackHitTarget(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	virtual void BeginPlay() override;

private:
	FName RightHandSocketName = "hand_r";
	FName LeftHandSocketName = "hand_l";
	AMeleeBase* RightHandWeapon = nullptr;
	AMeleeBase* LeftHandWeapon = nullptr;
	bool isAttacking = false;
	void SendWeaponDetailsToAI();

	bool canUseRightHandAttack = true;
	bool canUseLeftHandAttack = true;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* RightHandMontage = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* LeftHandMontage = nullptr;

	UFUNCTION()
	void OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted);
};
