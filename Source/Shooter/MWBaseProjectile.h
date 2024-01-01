// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UMDamageSystem.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	float FlightSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	FMWDamageInfo FDamageInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	bool bIsHomingProjectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	float HomingMagnitude;

protected:
	void IgnoreInstigatorActor();
};
