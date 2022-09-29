// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
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

	virtual void Attack() override;

private:

	UPROPERTY(EditAnywhere)
	bool DebugMode;
};
