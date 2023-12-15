// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MWBaseProjectile.h"
#include "MWPlayerProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AMWPlayerProjectile : public AMWBaseProjectile
{
	GENERATED_BODY()
protected:
	AMWPlayerProjectile();
	virtual void PreInitializeComponents() override;
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
