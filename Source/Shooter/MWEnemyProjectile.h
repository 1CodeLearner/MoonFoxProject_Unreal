// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MWBaseProjectile.h"
#include "MWEnemyProjectile.generated.h"

/**
 *
 */
class UNiagaraSystem;
UCLASS()
class SHOOTER_API AMWEnemyProjectile : public AMWBaseProjectile
{
	GENERATED_BODY()
public:
	AMWEnemyProjectile();
protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual void Fire(FTransform Transform);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void Reset();

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void EnableNiagara(bool enable);
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float FlightDuration;
private:
	UPROPERTY()
	FTimerHandle ResetHandle;
};
