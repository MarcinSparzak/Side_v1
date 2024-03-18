// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CameraFollowTrigger.generated.h"
class UBoxComponent; class ACameraManager; class UCutsceneManager;
/**
 * Area component.
 * After stepping into component camera strops following character and is centered at VectorForCameraToCenter
 */
UCLASS()
class SIDE_V1_API ACameraFollowTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	ACameraFollowTrigger();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Cinematics")
	void DebugEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

	/*
	* Coordinates of a point where camera should be centered
	*/
	UPROPERTY(VisibleAnywhere)
		USceneComponent* VectorForCameraToCenter;
	/*
	* Camera Manager object for communication
	*/
	UPROPERTY(EditAnywhere)
		ACameraManager* CameraManager;

	UFUNCTION()
		void OverlapTriggerBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OverlapTriggerEnd(AActor* OverlappedActor, AActor* OtherActor);

	/*
	* Funkcja przesy³aj¹ca do obiektu kamery informacje o koniecznoœci aktualizacji jej zachowania
	*/
	void UpdateCameraManager(bool IsStationary, bool IsFollowingY);

	UPROPERTY()
	UCutsceneManager* CutsceneManager;

	
};
