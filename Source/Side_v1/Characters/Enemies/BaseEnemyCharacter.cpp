// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyCharacter.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	
}


void ABaseEnemyCharacter::BeginPlay()
{

	Super::BeginPlay();
}


void ABaseEnemyCharacter::BaseAttack(FVector TargetPoint)
{
}

void ABaseEnemyCharacter::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("BaseEnemy Death"));
	Super::Death();
}