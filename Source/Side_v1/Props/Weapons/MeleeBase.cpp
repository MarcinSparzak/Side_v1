// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeBase.h"
#include "Kismet/KismetMathLibrary.h"

AMeleeBase::AMeleeBase()
{
}

float AMeleeBase::GetBaseDamage()
{
	return BaseDamage;
}

AController* AMeleeBase::GetOwnerController()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

void AMeleeBase::ApplyDamage(ABaseCharacter* Victim, FHitResult HitResult, FVector ShotDirection)
{
	FPointDamageEvent DamageEvent(BaseDamage, HitResult, ShotDirection, nullptr);

	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return;

	Victim->TakeDamage(BaseDamage, DamageEvent, OwnerController, this);
}
