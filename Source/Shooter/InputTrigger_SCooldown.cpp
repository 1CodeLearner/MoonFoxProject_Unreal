// Fill out your copyright notice in the Description page of Project Settings.


#include "InputTrigger_SCooldown.h"

ETriggerType UInputTrigger_SCooldown::GetTriggerType_Implementation() const
{

	return ETriggerType::Explicit;
}

ETriggerState UInputTrigger_SCooldown::UpdateState_Implementation(
	const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime)
{
	HeldDuration = CalculateHeldDuration(PlayerInput, DeltaTime);

	ETriggerState State = Super::UpdateState_Implementation(PlayerInput, ModifiedValue, DeltaTime);
	
	if (HeldDuration >= HoldTimeThreshold && State == ETriggerState::None)
	{
		State = ETriggerState::Triggered;
	}

	return State;
}

bool UInputTrigger_SCooldown::ReadyToTrigger()
{
	return HeldDuration >= HoldTimeThreshold;
}
