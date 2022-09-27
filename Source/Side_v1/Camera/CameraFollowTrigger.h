// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CameraFollowTrigger.generated.h"
class UBoxComponent; class ACameraManager;
/**
 * 
 */
UCLASS()
class SIDE_V1_API ACameraFollowTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	ACameraFollowTrigger();

private:

	UPROPERTY(VisibleAnywhere)
		USceneComponent* VectorForCameraToCenter;

	UPROPERTY(EditAnywhere)
		ACameraManager* CameraManager;

	UPROPERTY(EditAnywhere)
		bool IsCameraCentered;

	UFUNCTION()
		void OverlapTriggerBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OverlapTriggerEnd(AActor* OverlappedActor, AActor* OtherActor);
	void UpdateCameraManager(bool IsStationary, bool IsFollowingY, FVector VectorToCenter);

};
