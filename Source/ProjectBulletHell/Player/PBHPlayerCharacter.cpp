// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PBHPlayerCharacter.h"

// Sets default values
APBHPlayerCharacter::APBHPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APBHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APBHPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APBHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

