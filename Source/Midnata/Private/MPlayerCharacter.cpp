// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "..\Public\MPlayerCharacter.h"

// Sets default values
AMPlayerCharacter::AMPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateAbstractDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void AMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &AMPlayerCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", EInputEvent::IE_Released, this, &AMPlayerCharacter::EndCrouch);
	PlayerInputComponent->BindAction("SwitchCrouch", EInputEvent::IE_Pressed, this, &AMPlayerCharacter::SwitchCrouch);

	PlayerInputComponent->BindAxis("LookUp", this, &AMPlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &AMPlayerCharacter::AddControllerYawInput);
}


void AMPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}

void AMPlayerCharacter::BeginCrouch()
{
	Crouch();
}

void AMPlayerCharacter::EndCrouch()
{
	UnCrouch();
}

void AMPlayerCharacter::SwitchCrouch()
{
	if (!bIsCrouched)
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}
