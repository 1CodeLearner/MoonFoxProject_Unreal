// Fill out your copyright notice in the Description page of Project Settings.


#include "MWPlayerProjectile.h"
#include "MWProjectileInteractable.h"
#include "Components/SphereComponent.h"

void AMWPlayerProjectile::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMWPlayerProjectile::OnOverlap);
}

void AMWPlayerProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UMWProjectileInteractable>()) 
	{
		IMWProjectileInteractable::Execute_Interact(OtherActor, this);
	}
}
