	// Fill out your copyright notice in the Description page of Project Settings.



#include "MWBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MWProjectileInteractable.h"



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
	ProjectileMoveComp->Velocity = FVector(FlightSpeed, 0.f, 0.f);
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

// Called when the game starts or when spawned
void AMWBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(DurationHandle, this, &AMWBaseProjectile::DurationEnd, FlightDuration, false);
}

void AMWBaseProjectile::DurationEnd_Implementation()
{
	Destroy();
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
