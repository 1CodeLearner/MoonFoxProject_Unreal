// Fill out your copyright notice in the Description page of Project Settings.


#include "MWEnemyProjectile.h"
#include "Components/SphereComponent.h"
#include "MWProjectileInteractable.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"

AMWEnemyProjectile::AMWEnemyProjectile()
{
	SphereComponent->SetCollisionProfileName("EnemyProjectile");
	FlightDuration = 5.f;
	ActorToTarget = nullptr;
	ResetValue = 0.7;
}

void AMWEnemyProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMWEnemyProjectile::OnOverlap);
}

void AMWEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	IgnoreInstigatorActor();
	ResetState();
}

void AMWEnemyProjectile::Tick(float DeltaSecond)
{
	if (ProjectileMoveComp->bIsHomingProjectile && ActorToTarget)
	{
		float value = GetDotProductTo(ActorToTarget);
		if (value < -.7f)
		{
			ResetState();
		}
	}
}

void AMWEnemyProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//const TArray<AActor*> Actors = OverlappedComponent->GetMoveIgnoreActors();

	//for (int i = 0; i < Actors.Max(); i++) {
	//	UE_LOG(LogTemp, Warning, TEXT("INSTIGATOR: %s"), *GetNameSafe(Actors[i]));
	//}¡¡	

	if (OtherActor != GetInstigator() && OtherActor->Implements<UMWProjectileInteractable>())
	{
		//UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *GetNameSafe(OtherActor));
		IMWProjectileInteractable::Execute_ProjectileInteract(OtherActor, GetInstigator(), FDamageInfo);
	}
	ResetState();
}

void AMWEnemyProjectile::Fire(FTransform Transform, AActor* TargetActor)
{
	if (ProjectileMoveComp->bIsHomingProjectile && !TargetActor)
		ensureMsgf(TargetActor, TEXT("TargetActor missing! if Homing Projectile, pass a reference to Target Actor!"));

	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);

	SetActorTransform(Transform);
	UpdateProjectileComponent(true, TargetActor);

	ParticleSystem->Activate();
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	IgnoreInstigatorActor();

	if (!ProjectileMoveComp->bIsHomingProjectile)
		GetWorld()->GetTimerManager().SetTimer(ResetHandle, this, &AMWEnemyProjectile::ResetState, FlightDuration, false);
}

void AMWEnemyProjectile::ResetState()
{
	if (ensure(GetInstigator()))
	{
		if (ResetHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(ResetHandle);

		SetActorHiddenInGame(true);
		SetActorTickEnabled(false);

		SetActorLocation(GetInstigator()->GetActorLocation());
		UpdateProjectileComponent(false, nullptr);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ParticleSystem->Deactivate();
	}
}

void AMWEnemyProjectile::UpdateProjectileComponent(bool bIsEnabled, AActor* TargetActor)
{
	if (ProjectileMoveComp->bIsHomingProjectile && TargetActor)
	{
		ActorToTarget = TargetActor;
		ProjectileMoveComp->HomingTargetComponent = TargetActor->GetRootComponent();
		ProjectileMoveComp->HomingAccelerationMagnitude = HomingMagnitude;
	}
	else
	{
		ActorToTarget = nullptr;
	}

	if (bIsEnabled)
	{
		ProjectileMoveComp->SetUpdatedComponent(RootComponent);
		ProjectileMoveComp->SetVelocityInLocalSpace(FVector(FlightSpeed, 0.f, 0.f));
	}
	else
	{
		FHitResult Hit;
		ProjectileMoveComp->StopSimulating(Hit);
	}
}
