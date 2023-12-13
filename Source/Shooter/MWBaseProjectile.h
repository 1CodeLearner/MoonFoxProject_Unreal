// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MWBaseProjectile.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;

UCLASS(ABSTRACT)
class SHOOTER_API AMWBaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMWBaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PreInitializeComponents() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UNiagaraComponent* ParticleSystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMoveComp;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	float FlightSpeed = 1500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	FName Name = "DefaultName";
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Duration")
	float FlightDuration = 10.f;
	UFUNCTION(BlueprintNativeEvent, Category = "Duration")
	void DurationEnd();
private:
	FTimerHandle DurationHandle;

};
