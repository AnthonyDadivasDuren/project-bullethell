#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PBHGameMode.generated.h"

/**
 * Minimal GameModeBase for now (no match state / multiplayer flow needed
 * yet). DefaultPawnClass / PlayerStateClass are set in the constructor so
 * the greybox test level works without per-level GameMode overrides.
 */
UCLASS()
class PROJECTBULLETHELL_API APBHGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APBHGameMode();
};
