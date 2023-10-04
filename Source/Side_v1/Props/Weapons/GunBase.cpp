// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../../Characters/BaseCharacter.h"
#include "../../Characters/PlayerCharacter.h"
#include "DrawDebugHelpers.h"

AGunBase::AGunBase()
{
}

void AGunBase::Attack(FVector TargetPoint)
{	
	ABaseCharacter* Shooter = Cast<ABaseCharacter>(GetOwner());
	if (Shooter != nullptr)
	{
		USkeletalMeshComponent* ShooterMesh = Shooter->GetMesh();

		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, ShooterMesh, MuzzleSocketName);

		FVector GunLocation = ShooterMesh->GetSocketLocation(MuzzleSocketName);

		FVector ShotDirection = UKismetMathLibrary::GetDirectionUnitVector(GunLocation, TargetPoint);
		
		FHitResult HitResult;
		bool Success = TraceShot(HitResult, GunLocation, ShotDirection);

		if (Success)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.BoneName.ToString());
			ABaseCharacter* Victim = Cast<ABaseCharacter>(HitResult.GetActor());
			if (Victim != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleHit_Enemy, HitResult.Location, ShotDirection.Rotation());
				ApplyDamage(Victim, HitResult, ShotDirection);
			}
			else
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleHit_World, HitResult.Location, ShotDirection.Rotation());
			}
		}
	}
}

AController* AGunBase::GetOwnerController()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

bool AGunBase::TraceShot(FHitResult& HitResult, FVector GunLocation, FVector ShotDirection)
{
	float XDispersion = FMath::RandRange(-ShotDispersion, ShotDispersion);
	float ZDispersion = FMath::RandRange(-ShotDispersion, ShotDispersion);
	FVector EndPointOfGunRange = ShotDirection * WeaponRange + GunLocation + FVector(XDispersion, 0.0, ZDispersion);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(GetOwner());



	bool result = GetWorld()->LineTraceSingleByChannel(HitResult, GunLocation, EndPointOfGunRange, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams);

	if (DebugMode)
	{

		UE_LOG(LogTemp, Warning, TEXT("Draw Debug"));
		DrawDebugLine(GetWorld(), GunLocation, EndPointOfGunRange, FColor::Red, false, 1.0f, 0, 2.0f);
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5.0f), FColor::Red, false, 1.0f, 0, 2.0f);
	}

	return result;
}

void AGunBase::ApplyDamage(ABaseCharacter* Victim, FHitResult HitResult, FVector ShotDirection)
{
	FPointDamageEvent DamageEvent(BaseDamage, HitResult, ShotDirection, nullptr);

	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return;

	Victim->TakeDamage(BaseDamage, DamageEvent, OwnerController, this);
}
