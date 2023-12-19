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
	virtual void PreInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UNiagaraComponent* ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	TObjectPtr<UNiagaraSystem> NiagaraAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMoveComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	float FlightSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	float Damage = 0.f;
};
