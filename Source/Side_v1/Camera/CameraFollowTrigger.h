// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CameraFollowTrigger.generated.h"
class UBoxComponent; class ACameraManager;
/**
 * Komponent obszarowy. Po wej�ciu w jego pole kamera przestaje �ledzi� posta� i wycentrowuje kamer� na wskazanych wsp�rz�dnych
 */
UCLASS()
class SIDE_V1_API ACameraFollowTrigger : public ATriggerBox
{
	GENERATED_BODY()

public:
	ACameraFollowTrigger();

private:

	/*
	* Wsp�rz�dne punktu na kt�rym wycentrowana ma zosta� kamera
	*/
	UPROPERTY(VisibleAnywhere)
		USceneComponent* VectorForCameraToCenter;
	/*
	* Obiekt Kamery g��wnej
	*/
	UPROPERTY(EditAnywhere)
		ACameraManager* CameraManager;
	/*
	* Flaga okre�laj�ca czy kamera jest wypo�rodkowana
	*/
	UPROPERTY(EditAnywhere)
		bool IsCameraCentered;

	/*
	* Funkcja uruchamiana gdy posta� wejdzie w pole komponentu
	*/
	UFUNCTION()
		void OverlapTriggerBegin(AActor* OverlappedActor, AActor* OtherActor);

	/*
	* Funkcja uruchamiana gdy posta� wyjdzie poza pole komponentu
	*/
	UFUNCTION()
		void OverlapTriggerEnd(AActor* OverlappedActor, AActor* OtherActor);

	/*
	* Funkcja przesy�aj�ca do obiektu kamery informacje o konieczno�ci aktualizacji jej zachowania
	*/
	void UpdateCameraManager(bool IsStationary, bool IsFollowingY, FVector VectorToCenter);

};
