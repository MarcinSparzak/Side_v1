// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraFollowTrigger.h"
#include "Components/BoxComponent.h"
#include "../Characters/BaseCharacter.h"
#include "CameraManager.h"

ACameraFollowTrigger::ACameraFollowTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACameraFollowTrigger::OverlapTriggerBegin);
	OnActorEndOverlap.AddDynamic(this, &ACameraFollowTrigger::OverlapTriggerEnd);


	VectorForCameraToCenter = CreateDefaultSubobject<USceneComponent>("Vector For Camera to Center");
	VectorForCameraToCenter->SetupAttachment(RootComponent);
}

/*
* Funkcja uruchamiana gdy postaæ wejdzie w pole komponentu
*/
void ACameraFollowTrigger::OverlapTriggerBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
	ABaseCharacter* MainCharacter = Cast<ABaseCharacter>(OtherActor);
	if (MainCharacter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UpdateCameraManager"));
		UpdateCameraManager(true, false, VectorForCameraToCenter->GetComponentLocation());
	}
}

/*
* Funkcja uruchamiana gdy postaæ wyjdzie poza pole komponentu
*/
void ACameraFollowTrigger::OverlapTriggerEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	ABaseCharacter* MainCharacter = Cast<ABaseCharacter>(OtherActor);
	if (MainCharacter != nullptr)
	{
		FVector Point = FVector(0, 0, 0);
		UpdateCameraManager(false, true, Point);
	}
}

/*
* Funkcja przesy³aj¹ca do obiektu kamery informacje o koniecznoœci aktualizacji jej zachowania
*/
void ACameraFollowTrigger::UpdateCameraManager(bool IsStationary, bool IsFollowingY, FVector VectorToCenter)
{
	CameraManager->SetIsFollowingY(IsFollowingY);
	if (IsCameraCentered)
	{
		CameraManager->SetCameraStationary(IsStationary, VectorForCameraToCenter->GetComponentLocation());
	}
}


