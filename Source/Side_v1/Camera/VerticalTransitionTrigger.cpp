// Fill out your copyright notice in the Description page of Project Settings.


#include "VerticalTransitionTrigger.h"
#include "Components/BoxComponent.h"
#include "../Characters/BaseCharacter.h"
#include "CameraManager.h"

// Sets default values
AVerticalTransitionTrigger::AVerticalTransitionTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TopTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TopTrigger"));
	TopTrigger->SetupAttachment(Root);

	MiddleTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("MiddleTrigger"));
	MiddleTrigger->SetupAttachment(Root);

	BottomTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BottomTrigger"));
	BottomTrigger->SetupAttachment(Root);

	TopTrigger->OnComponentBeginOverlap.AddDynamic(this, &AVerticalTransitionTrigger::OnTopOverlapBegin);
	MiddleTrigger->OnComponentBeginOverlap.AddDynamic(this, &AVerticalTransitionTrigger::OnMiddleOverlapBegin);
	BottomTrigger->OnComponentBeginOverlap.AddDynamic(this, &AVerticalTransitionTrigger::OnBottomOverlapBegin);
}

// Called when the game starts or when spawned
void AVerticalTransitionTrigger::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVerticalTransitionTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVerticalTransitionTrigger::SetCameraZValue(float ZValue)
{
	CameraZValue = ZValue;
}

void AVerticalTransitionTrigger::OnTopOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* MainCharacter = Cast<ABaseCharacter>(OtherActor);
	if (MainCharacter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Top Overlap"));
		CameraManager->SetCameraZValue(TopZValue);
		CameraManager->SetIsFollowingZ(false);
	}
}

void AVerticalTransitionTrigger::OnMiddleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* MainCharacter = Cast<ABaseCharacter>(OtherActor);
	if (MainCharacter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Middle Overlap"));
		CameraManager->SetIsFollowingZ(true);
	}
}

void AVerticalTransitionTrigger::OnBottomOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* MainCharacter = Cast<ABaseCharacter>(OtherActor);
	if (MainCharacter != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bottom Overlap"));

		CameraManager->SetCameraZValue(BottomZValue);
		CameraManager->SetIsFollowingZ(false);
	}
}

