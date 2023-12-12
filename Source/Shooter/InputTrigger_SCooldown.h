// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "InputTrigger_SCooldown.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UInputTrigger_SCooldown : public UInputTriggerTimedBase
{
	GENERATED_BODY()

protected:
	virtual ETriggerType GetTriggerType_Implementation() const override ;

	virtual ETriggerState UpdateState_Implementation(
		const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Trigger")
	bool ReadyToTrigger();
public:
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))
	float HoldTimeThreshold = 0.5f;
};
