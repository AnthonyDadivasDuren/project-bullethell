#include "Player/PBHPlayerCharacter.h"

APBHPlayerCharacter::APBHPlayerCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void APBHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APBHPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APBHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

