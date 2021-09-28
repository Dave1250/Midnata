// Fill out your copyright notice in the Description page of Project Settings.


#include "MWeaponProjectileLauncher.h"

void AMWeaponProjectileLauncher::Attack()
{
	AActor* WeaponOwner = GetOwner();

	if (WeaponOwner && ProjectileClass)
	{
		FVector OwnerViewPointLocation;
		FRotator OwnerViewPointRotation;
		WeaponOwner->GetActorEyesViewPoint(OwnerViewPointLocation, OwnerViewPointRotation);

		FVector MuzzleLocation = SkeletalMeshComp->GetSocketLocation(MuzzleFlashSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, OwnerViewPointRotation, SpawnParams);
	}
}
