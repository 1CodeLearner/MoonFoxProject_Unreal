	// Fill out your copyright notice in the Description page of Project Settings.



#include "MWBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AMWBaseProjectile::AMWBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	ParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ParticleSystemComp"));
	ParticleSystem->SetupAttachment(RootComponent);
	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMoveComp"));
	UE_LOG(LogTemp, Warning, TEXT("%s's FlightSpeed: %f"), *GetNameSafe(this), FlightSpeed);
	ProjectileMoveComp->InitialSpeed = FlightSpeed;
	ProjectileMoveComp->ProjectileGravityScale = 0.f;
}

float AMWBaseProjectile::GetDamage() const
{
	return Damage;
}

void AMWBaseProjectile::SetDamage(float _Damage)
{
	Damage = _Damage;
}

void AMWBaseProjectile::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	APawn* InstigatePawn = GetInstigator();
	if (InstigatePawn)
	{
		if (!InstigatePawn->IsMoveInputIgnored()) 
		{
			InstigatePawn->MoveIgnoreActorAdd(this);
		}
		SphereComponent->IgnoreActorWhenMoving(InstigatePawn, true);
	}
}
