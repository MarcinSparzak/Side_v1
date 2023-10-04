// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "../../Characters/PlayerCharacter.h"
#include "MeleeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIDE_V1_API AMeleeBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AMeleeBase();

	UFUNCTION()
		float GetBaseDamage();

private:
	UPROPERTY(EditAnywhere)
		float BaseDamage;


	AController* GetOwnerController();

	void ApplyDamage(ABaseCharacter* Victim, FHitResult HitResult, FVector ShotDirection);
};
