// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MWeapon.h"
#include "MWeaponProjectileLauncher.generated.h"

/**
 * 
 */
UCLASS()
class MIDNATA_API AMWeaponProjectileLauncher : public AMWeapon
{
	GENERATED_BODY()
public:


protected:

	virtual void Attack() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AActor> ProjectileClass;
		
};
