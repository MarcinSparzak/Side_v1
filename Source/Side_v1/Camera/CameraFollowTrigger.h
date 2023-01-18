// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CameraFollowTrigger.generated.h"
class UBoxComponent; class ACameraManager;
/**
 * Komponent obszarowy. Po wejœciu w jego pole kamera przestaje œledziæ postaæ i wycentrowuje kamerê na wskazanych wspó³rzêdnych
 */
UCLASS()
class SIDE_V1_API ACameraFollowTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	ACameraFollowTrigger();

private:

	/*
	* Wspó³rzêdne punktu na którym wycentrowana ma zostaæ kamera
	*/
	UPROPERTY(VisibleAnywhere)
		USceneComponent* VectorForCameraToCenter;
	/*
	* Obiekt Kamery g³ównej
	*/
	UPROPERTY(EditAnywhere)
		ACameraManager* CameraManager;
	/*
	* Flaga okreœlaj¹ca czy kamera jest wypoœrodkowana
	*/
	UPROPERTY(EditAnywhere)
		bool IsCameraCentered;

	/*
	* Funkcja uruchamiana gdy postaæ wejdzie w pole komponentu
	*/
	UFUNCTION()
		void OverlapTriggerBegin(AActor* OverlappedActor, AActor* OtherActor);

	/*
	* Funkcja uruchamiana gdy postaæ wyjdzie poza pole komponentu
	*/
	UFUNCTION()
		void OverlapTriggerEnd(AActor* OverlappedActor, AActor* OtherActor);

	/*
	* Funkcja przesy³aj¹ca do obiektu kamery informacje o koniecznoœci aktualizacji jej zachowania
	*/
	void UpdateCameraManager(bool IsStationary, bool IsFollowingY, FVector VectorToCenter);

};
