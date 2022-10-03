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
	/*	AActor* TmpChar = GetOwner();
		if (TmpChar != nullptr)
		{
			FString TmpName = TmpChar->GetActorNameOrLabel();
			UE_LOG(LogTemp, Warning, TEXT("Actor %s"), *TmpName);
		}*/

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		CollisionParams.AddIgnoredActor(GetOwner());

		FHitResult HitResult;
		bool Success = GetWorld()->LineTraceSingleByChannel(HitResult, GunLocation, EndPointOfGunRange, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);

		if (Success)
		{
			ABaseCharacter* Victim = Cast<ABaseCharacter>(HitResult.GetActor());
			if (Victim != nullptr)
			{
				FPointDamageEvent DamageEvent(BaseDamage, HitResult, ShotDirection, nullptr);
			
				AController* OwnerController = GetOwnerController();
				if (OwnerController == nullptr) return;
				float Damage = Victim->TakeDamage(BaseDamage, DamageEvent, OwnerController, this);
			}
		}

		//TODELETE after development stage
		if (DebugMode)
		{
			DrawDebugLine(GetWorld(), GunLocation, EndPointOfGunRange, FColor::Red, false, 10.0f, 0, 2.0f);
			DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5.0f), FColor::Red, false, 10.0f, 0, 2.0f);
		}
	}
}

AController* AGunBase::GetOwnerController()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}
