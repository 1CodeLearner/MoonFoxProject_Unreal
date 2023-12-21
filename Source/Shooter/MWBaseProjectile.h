// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MWBaseProjectile.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(ABSTRACT)
class SHOOTER_API AMWBaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMWBaseProjectile();

	UFUNCTION(BlueprintPure, Category = "Projectile")
	virtual float GetDamage() const;
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SetDamage(float Damage);

protected:
	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UNiagaraComponent* ParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UNiagaraSystem> NiagaraAsset;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMoveComp;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	float FlightSpeed = 0.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	float Damage = 0.f;

protected:
	void IgnoreInstigatorActor();
};
