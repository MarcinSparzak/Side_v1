// Fill out your copyright notice in the Description page of Project Settings.


#include "SmallRampCharacter.h"
#include "../../../Props/Weapons/MeleeBase.h"
#include "AI/SmallRampAIController.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "../../PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"


ASmallRampCharacter::ASmallRampCharacter()
{
}



void ASmallRampCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*
		Equip Default weapon
	*/
	if (WeaponClass != nullptr)
	{
		RightHandWeapon = GetWorld()->SpawnActor<AMeleeBase>(WeaponClass);
		RightHandWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, RightHandSocketName);
		if (RightHandWeapon != nullptr)
		{
			RightHandWeapon->SetOwner(this);
			//UE_LOG(LogTemp, Warning, TEXT("RightHandWeapon created"));
			SendWeaponDetailsToAI();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("RightHandWeapon not created"));
		}

		LeftHandWeapon = GetWorld()->SpawnActor<AMeleeBase>(WeaponClass);
		LeftHandWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, LeftHandSocketName);
		if (LeftHandWeapon != nullptr)
		{
			LeftHandWeapon->SetOwner(this);
			//UE_LOG(LogTemp, Warning, TEXT("LeftHandWeapon created"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("LeftHandWeapon not created"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Weapon Class"));

	}
}

AMeleeBase* ASmallRampCharacter::GetRightHandWeapon()
{
	return RightHandWeapon;
}

void ASmallRampCharacter::Attack(FVector TargetPoint)
{
	USkeletalMeshComponent* OwnerMesh = GetMesh();
	UAnimInstance* MeshAnimInstance = OwnerMesh->GetAnimInstance();
	
	isAttacking = true;
	if (canUseRightHandAttack)
	{
		if (RightHandMontage != nullptr)
		{
			float montageTime = MeshAnimInstance->Montage_Play(RightHandMontage);
			if (montageTime > 0.1)
			{

				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &ASmallRampCharacter::OnAnimationEnded);
				MeshAnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, RightHandMontage);
			}
		}
	} else if (canUseLeftHandAttack)
	{
		if (LeftHandMontage != nullptr)
		{
			float montageTime = MeshAnimInstance->Montage_Play(LeftHandMontage);
			if (montageTime > 0.1)
			{
				FOnMontageEnded MontageEndedDelegate;
				MontageEndedDelegate.BindUObject(this, &ASmallRampCharacter::OnAnimationEnded);
				MeshAnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, LeftHandMontage);
			}
		}
	}
}

void ASmallRampCharacter::SendWeaponDetailsToAI()
{
	ASmallRampAIController* AIController = Cast<ASmallRampAIController>(GetController());
	if (AIController == nullptr) return;

	AIController->UpdateCharacterWeaponAI(RightHandWeapon->GetWeaponRange());
}


void ASmallRampCharacter::OnAnimationEnded(UAnimMontage* Montage, bool bInterrupted)
{
	canUseRightHandAttack = !canUseRightHandAttack;
	//UE_LOG(LogTemp, Warning, TEXT("ON Montage Ended"));
}

void ASmallRampCharacter::OnAttackHitTarget(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (isAttacking)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Function:DealDamage"));
		FString ComponentName;
		FString VictimName;
		FString VictimComponentName;

		// TODELETE
		VictimName = OtherActor->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("Victim Name: %s"), *VictimName);
		// TODELETE END

		APlayerCharacter* PlayerObj = Cast<APlayerCharacter>(OtherActor);
		if (PlayerObj != nullptr)
		{
			FName SocketName = OverlappedComp->GetAttachSocketName();
			//UE_LOG(LogTemp, Warning, TEXT("Component Socket Name: %s"), *SocketName.ToString());
		
			// Calculate hit direction
			FVector HitDirection = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), OtherActor->GetActorLocation());


			float Damage = 0;
			if (SocketName == RightHandSocketName)
			{
				Damage = RightHandWeapon->GetBaseDamage();
			}
			else if (SocketName == LeftHandSocketName)
			{
				Damage = LeftHandWeapon->GetBaseDamage();
			}
			FPointDamageEvent DamageEvent(Damage, SweepResult, HitDirection, nullptr);
			PlayerObj->TakeDamage(Damage, DamageEvent, GetController(), this);
			isAttacking = !isAttacking;
		}
	}


}
