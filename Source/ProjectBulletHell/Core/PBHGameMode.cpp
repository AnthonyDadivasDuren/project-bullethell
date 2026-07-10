#include "PBHGameMode.h"
#include "../Player/PBHPlayerCharacter.h"
#include "../Player/PBHPlayerState.h"

APBHGameMode::APBHGameMode()
{
	DefaultPawnClass = APBHPlayerCharacter::StaticClass();
	PlayerStateClass = APBHPlayerState::StaticClass();
}
