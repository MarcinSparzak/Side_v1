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
	FVector FollowPlayerMovement(float DeltaTime, ACharacter* Player);
	void SetIsFollowingY(bool NewValue);
	void SetIsFollowingZ(bool NewValue);
	/*
	* Funkcja ustalaj�ca czy kamera powinna by� stacjonarna czy dynamicznie �ledzi� posta�
	*/
	void SetCameraStationary(bool NewValue, FVector PointToCenter);
	/*
	* Funkcja wyznaczaj�ca now� lokalizacj� kamery podczas wycentrowywania jej wyznaczonym miejscu.
	* Funkcja mysi by� wywo�ywana w TICK, a nie w SetCameraStationary, poniewa� musi by� wykonywana w przedziale czau.
	*/
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

	UFUNCTION()
		void DelayTimerCallback();

	bool IsFollowingY = true;
	bool IsFollowingZ = false;
	bool IsCameraStationary = false;
	FVector LocationToCenter;
	float CameraZValue = 120.0f;

};