// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ACOptions.generated.h"
class AWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDE_V1_API UACOptions : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACOptions();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, meta = (Category = "ACOptions"))
		int nrOfOptions = 0;


	AWeaponBase* GetWeapon();

private:

	AWeaponBase* Weapon;
};
