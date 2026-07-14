// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectBulletHell/Player/PBHPlayerCharacter.h"
#include "PBHGameMode.h"

APBHGameMode::APBHGameMode()
{
	DefaultPawnClass = APBHPlayerCharacter::StaticClass();
}