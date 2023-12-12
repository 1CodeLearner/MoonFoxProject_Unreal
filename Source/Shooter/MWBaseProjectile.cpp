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
}

// Called when the game starts or when spawned
void AMWBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(DurationHandle, this, &AMWBaseProjectile::DurationEnd, FlightDuration, false);
}

void AMWBaseProjectile::DurationEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Testing if it runs first"));
}


void AMWBaseProjectile::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	APawn* InstigatePawn = GetInstigator();
	if (InstigatePawn)
	{
		if (InstigatePawn->IsMoveInputIgnored()) 
		{
			InstigatePawn->MoveIgnoreActorAdd(this);
		}
		SphereComponent->IgnoreActorWhenMoving(InstigatePawn, true);
	}
}
