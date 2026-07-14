#include "PBHGameMode.h"
#include "../Player/PBHPlayerState.h"
#include "ProjectBulletHell/Player/PBHPlayerCharacter.h"


APBHGameMode::APBHGameMode()
{
	DefaultPawnClass = APBHPlayerCharacter::StaticClass();
	PlayerStateClass = APBHPlayerState::StaticClass();
	
	// Add these if/when you build the corresponding classes:
	// PlayerControllerClass = APBHPlayerController::StaticClass();
	// HUDClass = APBHHUD::StaticClass();
	// GameStateClass = APBHGameState::StaticClass();
}