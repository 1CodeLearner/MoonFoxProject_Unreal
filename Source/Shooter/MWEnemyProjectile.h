// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MWBaseProjectile.h"
#include "MWEnemyProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AMWEnemyProjectile : public AMWBaseProjectile
{
	GENERATED_BODY()
	
protected:
	virtual void PreInitializeComponents() override;
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
