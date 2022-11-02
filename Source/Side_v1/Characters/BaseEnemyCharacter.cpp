// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"
#include "../Props/Weapons/WeaponBase.h"
#include "BaseEnemyAIController.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	
}


void ABaseEnemyCharacter::BeginPlay()
{

	Super::BeginPlay();
	/*
			Equip Default weapon
		*/
	if (WeaponClass != nullptr)
	{
		Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		if (Weapon != nullptr)
		{
			Weapon->SetOwner(this);
			UE_LOG(LogTemp, Warning, TEXT("Weapon created"));
			SendWeaponDetailsToAI();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Weapon not created"));
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Weapon Class"));

	}
}

void ABaseEnemyCharacter::SendWeaponDetailsToAI()
{
	ABaseEnemyAIController* AIController = Cast<ABaseEnemyAIController>(GetController());
	if (AIController == nullptr) return;

	AIController->UpdateCharacterWeaponAI(Weapon->GetWeaponRange());
}


AWeaponBase* ABaseEnemyCharacter::GetWeapon()
{
	return Weapon;
}

void ABaseEnemyCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Perform Attack"));
}
