// Fill out your copyright notice in the Description page of Project Settings.


#include "MWEnemyProjectile.h"
#include "Components/SphereComponent.h"
#include "MWProjectileInteractable.h"

AMWEnemyProjectile::AMWEnemyProjectile()
{
	SphereComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
}

void AMWEnemyProjectile::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMWEnemyProjectile::OnOverlap);
}

void AMWEnemyProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player")) 
	{
		IMWProjectileInteractable::Execute_ProjectileInteract(OtherActor,GetInstigator(), GetDamage() );
		Destroy();
	}
}
