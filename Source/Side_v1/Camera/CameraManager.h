// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraManager.generated.h"
class USpringArmComponent; class UCameraComponent;
UCLASS()
class SIDE_V1_API ACameraManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACameraManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetCameraZValue(float ZValue);
	FVector FollowPlayerMovement(float DeltaTime);
	void SetIsFollowingY(bool NewValue);
	void SetIsFollowingZ(bool NewValue);
	void SetCameraStationary(bool NewValue, FVector PointToCenter);
	FVector CenterCameraAtVector(float DeltaTime);

	UPROPERTY(EditDefaultsOnly)
	float SpringArmLength;

private:
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
		FVector PlanesToFollow;

	UPROPERTY(EditDefaultsOnly)
		float InterpSpeed;

	bool IsFollowingY = true;
	bool IsFollowingZ = false;
	bool IsCameraStationary = false;
	FVector LocationToCenter;
	float CameraZValue = 120.0f;

};