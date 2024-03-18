// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Props/Weapons/WeaponBase.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PlayerCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	MovementComp->bOrientRotationToMovement = true;
	MovementComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	MovementComp->SetPlaneConstraintEnabled(true);
	MovementComp->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &ABaseCharacter::MoveForwardBackward);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Attack);*/
}

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	//UE_LOG(LogTemp, Warning, TEXT("Actor takes damage: %f"), DamageToApply);

	float tmpHealth = Health;
	float damageApplied = 0.0f;
	if (DamageToApply >= Health)
	{
		Health = 0;
		damageApplied = DamageToApply - tmpHealth;
		//UE_LOG(LogTemp, Warning, TEXT("Character is killed"), DamageToApply);
		Death();
	}
	else
	{
		AAIController* EnemyController = Cast<AAIController>(GetController());
		if (EnemyController != nullptr)
		{

			//UE_LOG(LogTemp, Warning, TEXT("Controller found"));
			UBlackboardComponent* Blackboard = EnemyController->GetBlackboardComponent();
			if (Blackboard != nullptr)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Blackboard found"));
				Blackboard->SetValueAsBool(TEXT("IsHitted"), true);
				APlayerCharacter* Target = Cast<APlayerCharacter>(DamageCauser);
				if (Target == nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("Target nullptr"));
				}
				else
				{
					Blackboard->SetValueAsVector(TEXT("PlayerLocation"), DamageCauser->GetActorLocation());
					Blackboard->SetValueAsObject(TEXT("Player"), Target);
					Blackboard->SetValueAsBool(TEXT("IsMoveToPlayerPossible"), true);
				}
			}
		}
		else if (HitAnimation != nullptr)
		{

			//UE_LOG(LogTemp, Warning, TEXT("Play Hit Montage"));
			USkeletalMeshComponent* CharacterMesh = GetMesh();
			UAnimInstance* CharacterAnimBP = CharacterMesh->GetAnimInstance();
			float testAnim = CharacterAnimBP->Montage_Play(HitAnimation);
			//UE_LOG(LogTemp, Warning, TEXT("Anim float: %f"), testAnim);
		}
		Health -= DamageToApply;
		damageApplied = DamageToApply;
		//UE_LOG(LogTemp, Warning, TEXT("Actor life: %f"), Health);
	}
	return damageApplied;
}

bool ABaseCharacter::IsDead()
{
	return Health <=0 ? true : false;
}


void ABaseCharacter::MoveForwardBackward(float AxisValue)
{
	//AddMovementInput(GetActorForwardVector() * AxisValue);
	AddMovementInput(FVector(0.0f, 1.0f, 0.0f), AxisValue);
}

void ABaseCharacter::Death()
{
	//UE_LOG(LogTemp, Warning, TEXT("Base Character Death"));
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	DestroyCharacter();
}


