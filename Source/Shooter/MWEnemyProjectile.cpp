// Fill out your copyright notice in the Description page of Project Settings.


#include "MWEnemyProjectile.h"
#include "Components/SphereComponent.h"
#include "MWProjectileInteractable.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"

AMWEnemyProjectile::AMWEnemyProjectile()
{
	SphereComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);

	FlightDuration = 20.f;
}

void AMWEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetActorHiddenInGame(true);
	Reset();
}

void AMWEnemyProjectile::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMWEnemyProjectile::OnOverlap);
}

void AMWEnemyProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UMWProjectileInteractable>())
	{
		IMWProjectileInteractable::Execute_ProjectileInteract(OtherActor, GetInstigator(), GetDamage());
	}
	Reset();
}

void AMWEnemyProjectile::Fire(FTransform Transform)
{
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);

	SetActorTransform(Transform);
	ProjectileMoveComp->SetVelocityInLocalSpace(FVector(FlightSpeed, 0.f, 0.f));

	ParticleSystem->Activate();
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	GetWorld()->GetTimerManager().SetTimer(ResetHandle, this, &AMWEnemyProjectile::Reset, FlightDuration, false);

	UE_LOG(LogTemp, Warning, TEXT("INSTIGATOR: %s"), *GetNameSafe(GetInstigator()));
}

void AMWEnemyProjectile::Reset()
{
	APawn* testing = GetInstigator();

	if (ensureMsgf(testing, TEXT("Instigator not found. Please assign Instigator when spawning projectiles.")))
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
