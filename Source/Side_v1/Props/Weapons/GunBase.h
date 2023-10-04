// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "../../Characters/PlayerCharacter.h"
#include "GunBase.generated.h"

/**
 * 
 */
UCLASS()
class SIDE_V1_API AGunBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AGunBase();

	virtual void Attack(FVector TargetPoint) override;

private:

	bool DebugMode = false;

	UPROPERTY(EditAnywhere)
	float BaseDamage;

	UPROPERTY(EditAnywhere)
	float ShotDispersion = 5.0f;

	// Default particle effect for muzzle flash
	UPROPERTY(EditAnywhere)
		UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
		UParticleSystem* ParticleHit_World;

	UPROPERTY(EditAnywhere)
		UParticleSystem* ParticleHit_Enemy;

	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocketName = TEXT("Muzzle_01");
	
	AController* GetOwnerController();

	bool TraceShot(FHitResult& HitResult, FVector GunLocation, FVector ShotDirection);
	void ApplyDamage(ABaseCharacter* Victim, FHitResult HitResult, FVector ShotDirection);
};
