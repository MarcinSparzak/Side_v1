// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../Characters/BaseCharacterController.h"
#include "../../Camera/CameraManager.h"
#include "Camera/CameraComponent.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

AGunBase::AGunBase()
{
}

void AGunBase::Attack()
{
	ABaseCharacterController* PlayerController = Cast<ABaseCharacterController>(UGameplayStatics::GetPlayerController(this, 0));
	if (PlayerController == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not found"));
		return;
	}

	if (CameraManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera Manager not found"));
		return;
	}

	UCameraComponent* CameraObj = Cast<UCameraComponent>(CameraManager->GetComponentByClass(UCameraComponent::StaticClass()));
	if (CameraObj == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Camera component not found"));
		return;
	}
	
	FVector CameraLocation = CameraObj->GetComponentLocation();
	
	AActor* Player = GetOwner();
	FVector PlayerLocation = Player->GetActorLocation();
	FVector GunLocation = GetActorLocation();

	FVector MouseWorldLocation;
	FVector MouseRotation;
	PlayerController->DeprojectMousePositionToWorld(MouseWorldLocation, MouseRotation);

	FVector IntersectionLineEnd = MouseRotation * MouseDistanceFromPlane + MouseWorldLocation;

	FVector Intersection = FMath::LinePlaneIntersection(CameraLocation, IntersectionLineEnd, GunLocation, FVector(1.0, 0.0, 0.0));

	FVector ShotDirection = UKismetMathLibrary::GetDirectionUnitVector(GunLocation, Intersection);
	int GunRange = 1000;

	FVector EndPointOfGunRange = ShotDirection * GunRange + GunLocation;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, GunLocation, EndPointOfGunRange, ECollisionChannel::ECC_Visibility);

	//TODELETE after development stage
	if (DebugMode)
	{
		DrawDebugLine(GetWorld(), GunLocation, EndPointOfGunRange, FColor::Red, false, 10.0f, 0, 2.0f);
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5.0f), FColor::Red, false, 10.0f, 0, 2.0f);
	}
}
