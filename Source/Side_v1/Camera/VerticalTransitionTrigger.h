// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VerticalTransitionTrigger.generated.h"
class UBoxComponent; class ACameraManager;
UCLASS()
class SIDE_V1_API AVerticalTransitionTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVerticalTransitionTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetCameraZValue(float ZValue);

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TopTrigger;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* MiddleTrigger;
	UPROPERTY(VisibleAnywhere)
		UBoxComponent* BottomTrigger;

	UPROPERTY(EditDefaultsOnly)
		float CameraZValue;

	UPROPERTY(EditAnywhere)
		float TopZValue;

	UPROPERTY(EditAnywhere)
		float BottomZValue;

	UPROPERTY(EditAnywhere)
		ACameraManager* CameraManager;

	// Function sets follow on Z axis to false, and camera Z position on Camera Manager 
	UFUNCTION()
		void OnTopOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Funtion sert follow on z axis to true on Camera Manager
	UFUNCTION()
		void OnMiddleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function sets follow on Z axis to false, and camera Z position on Camera Manager 
	UFUNCTION()
		void OnBottomOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
