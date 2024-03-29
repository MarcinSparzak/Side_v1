// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraFollowTrigger.h"
#include "Components/BoxComponent.h"
#include "../Characters/BaseCharacter.h"
#include "CutsceneManager.h"
#include "CameraManager.h"

ACameraFollowTrigger::ACameraFollowTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &ACameraFollowTrigger::OverlapTriggerBegin);
	OnActorEndOverlap.AddDynamic(this, &ACameraFollowTrigger::OverlapTriggerEnd);


	VectorForCameraToCenter = CreateDefaultSubobject<USceneComponent>("Vector For Camera to Center");
	VectorForCameraToCenter->SetupAttachment(RootComponent);

	//CutsceneManager = CreateDefaultSubobject<UCutsceneManager>("Cutscene Manager");
	//AddOwnedComponent(CutsceneManager);
}

// Called when the game starts or when spawned
void ACameraFollowTrigger::BeginPlay()
{
	Super::BeginPlay();
	CutsceneManager = GetComponentByClass<UCutsceneManager>();

}

/*
* Funkcja uruchamiana gdy posta� wejdzie w pole komponentu
*/
void ACameraFollowTrigger::OverlapTriggerBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	APlayerCharacter* MainCharacter = Cast<APlayerCharacter>(OtherActor);
	if (MainCharacter != nullptr)
	{
		UpdateCameraManager(true, false);
		if (CutsceneManager == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Cutscene"));
		}
		else
		{
			CutsceneManager->StartCutscene();
		}
	}
}

/*
* Funkcja uruchamiana gdy posta� wyjdzie poza pole komponentu
*/
void ACameraFollowTrigger::OverlapTriggerEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	APlayerCharacter* MainCharacter = Cast<APlayerCharacter>(OtherActor);
	if (MainCharacter != nullptr)
	{
		UpdateCameraManager(false, true);
	}
}

/*
* Funkcja przesy�aj�ca do obiektu kamery informacje o konieczno�ci aktualizacji jej zachowania
*/
void ACameraFollowTrigger::UpdateCameraManager(bool IsStationary, bool IsFollowingY)
{
	CameraManager->SetIsFollowingY(IsFollowingY);

	CameraManager->SetCameraStationary(IsStationary, VectorForCameraToCenter->GetComponentLocation());
}


