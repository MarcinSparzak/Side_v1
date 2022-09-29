// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../Characters/BaseCharacter.h"
#include "DrawDebugHelpers.h"

AGunBase::AGunBase()
{
}

void AGunBase::Attack()
{	
	ABaseCharacter* Player = Cast<ABaseCharacter>(GetOwner());
	if (Player != nullptr) 
	{
		FVector GunLocation = GetActorLocation();

		FVector ShotDirection = UKismetMathLibrary::GetDirectionUnitVector(GunLocation, Player->MouseIntersection);
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
}
