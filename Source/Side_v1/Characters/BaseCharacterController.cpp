// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void ABaseCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	ACharacter* CharacterObject = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (CharacterObject != nullptr)
	{
		float tmpRotation;
		FVector MouseLocation;
		FVector MouseRotation;

		DeprojectMousePositionToWorld(MouseLocation, MouseRotation);

		FVector ActorLocation = CharacterObject->GetActorLocation();

		tmpRotation = ActorLocation.Y >= MouseLocation.Y ? -90.0f : 90.0f;
		CharacterObject->SetActorRotation(FRotator(0, tmpRotation, 0));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Character"));
	}
}
