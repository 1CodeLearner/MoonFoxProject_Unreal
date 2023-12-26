// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UMDamageSystem.generated.h"

UENUM(BlueprintType)
enum class EMWDamageType : uint8
{
	NONE UMETA(DisplayName = "None"),
	MELEE UMETA(DisplayName = "Melee"),
	PROJECTILE UMETA(DisplayName = "Projectile"),
	EXPLOSION UMETA(DisplayName = "Explosion"),
	ENVIRONMENT UMETA(DisplayName = "Environment")
};

UENUM(BlueprintType)
enum class EMWDamageResponse : uint8
{
	NONE UMETA(DisplayName = "None"),
	HITREACTION UMETA(DisplayName = "HitReaction"),
	STAGGER	UMETA(DisplayName = "Stagger"),
	STUN UMETA(DisplayName = "Stun"),
	KNOCKBACK UMETA(DisplayName = "KnockBack")
};

USTRUCT(BlueprintType)
struct FMWDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMWDamageType E_DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMWDamageResponse E_DamageResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldDamageInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeBlocked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeParried;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldForceInterrupt;
};

UCLASS()
class SHOOTER_API UUMDamageSystem : public UObject
{
	GENERATED_BODY()

};
