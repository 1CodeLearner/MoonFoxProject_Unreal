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
	Reset();
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

void AMWEnemyProjectile::Fire(FTransform Transform)
{
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);

	SetActorTransform(Transform);
	ProjectileMoveComp->SetVelocityInLocalSpace(FVector(FlightSpeed, 0.f, 0.f));

	ParticleSystem->Activate();
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	IgnoreInstigatorActor();

	GetWorld()->GetTimerManager().SetTimer(ResetHandle, this, &AMWEnemyProjectile::ResetState, FlightDuration, false);
}

void AMWEnemyProjectile::ResetState()
{
	if (GetInstigator())
	{
		if (ResetHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(ResetHandle);

		SetActorHiddenInGame(true);
		SetActorTickEnabled(false);

		SetActorLocation(GetInstigator()->GetActorLocation());
		ProjectileMoveComp->SetVelocityInLocalSpace(FVector(0.f, 0.f, 0.f));

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ParticleSystem->Deactivate();
	}
}