// Fill out your copyright notice in the Description page of Project Settings.



#include "MWBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"

// Sets default values
AMWBaseProjectile::AMWBaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	
	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParticleSystemComp"));
	ParticleSystem->SetupAttachment(RootComponent);
	ParticleSystem->SetAutoActivate(false);

	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	ProjectileMoveComp->ProjectileGravityScale = 0.f;
}

void AMWBaseProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ParticleSystem->SetAsset(NiagaraAsset);
}

void AMWBaseProjectile::IgnoreInstigatorActor()
{
	APawn* InstigatePawn = GetInstigator();

	if (ensureMsgf(InstigatePawn, TEXT("Instigator not found. Please assign Instigator when spawning projectiles.")))
	{
		//UE_LOG(LogTemp, Warning, TEXT("INSTIGATOR: %s"), *GetNameSafe(InstigatePawn));
		if (!HasAnyFlags(InstigatePawn->GetFlags()))
		{
			APawn* Pawn = Cast<APawn>(InstigatePawn);
			//UE_LOG(LogTemp, Warning, TEXT("INSTIGATOR CASTED: %s"), *GetNameSafe(Pawn));
		}
		else {
			//UE_LOG(LogTemp, Warning, TEXT("No flags found"));
		}
		if (!InstigatePawn->IsMoveInputIgnored())
		{
			InstigatePawn->MoveIgnoreActorAdd(this);
		}
		SphereComponent->IgnoreActorWhenMoving(InstigatePawn, true);
	}
}

float AMWBaseProjectile::GetDamage() const
{
	return Damage;
}

void AMWBaseProjectile::SetDamage(float _Damage)
{
	Damage = _Damage;
}

