// Fill out your copyright notice in the Description page of Project Settings.


#include "MWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMWeapon::AMWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	RootComponent = SkeletalMeshComp;

}

// Called when the game starts or when spawned
void AMWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AMWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMWeapon::Attack()
{
	AActor* WeaponOwner = GetOwner();

	if (WeaponOwner)
	{
		FVector OwnerViewPointLocation;
		FRotator OwnerViewPointRotation;
		WeaponOwner->GetActorEyesViewPoint(OwnerViewPointLocation, OwnerViewPointRotation);
		FVector ShootDirection = OwnerViewPointRotation.Vector();
		FVector TraceEnd = OwnerViewPointLocation + (ShootDirection * Range);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(WeaponOwner);
		QueryParams.bTraceComplex = true;

		//Muzzle trial target param
		FVector MuzzleTrialEndPoint = TraceEnd;

		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, SkeletalMeshComp, MuzzleFlashSocketName);
		}

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, OwnerViewPointLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();

			UGameplayStatics::ApplyPointDamage(HitActor, DMG, ShootDirection, Hit, WeaponOwner->GetInstigatorController(),
				this, DamageType);

			if (MuzzleImpact)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleImpact, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}

			MuzzleTrialEndPoint = Hit.ImpactPoint;
		}
		if (MuzzleTrail)
		{
			FVector MuzzleLocation = SkeletalMeshComp->GetSocketLocation(MuzzleFlashSocketName);

			UParticleSystemComponent* TrailComp = UGameplayStatics::SpawnEmitterAttached(MuzzleTrail, SkeletalMeshComp, 
				MuzzleFlashSocketName);
			if (TrailComp)
			{
				TrailComp->SetVectorParameter(MuzzleTrailTargetName, MuzzleTrialEndPoint);
			}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO WEAPON OWNER"));
	}
		}
}
