// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"
class ACameraManager;
UCLASS()
class SIDE_V1_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ACameraManager* CameraManager;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attack();
};
