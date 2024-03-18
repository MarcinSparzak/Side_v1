// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BossCutscene.generated.h"


class ABaseCharacter;
UCLASS(Blueprintable)
class SIDE_V1_API UBossCutscene : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossCutscene();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Cinematics")
	void StartCutscene();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	ABaseCharacter* Boss;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly)
	ABaseCharacter* Player;
};
