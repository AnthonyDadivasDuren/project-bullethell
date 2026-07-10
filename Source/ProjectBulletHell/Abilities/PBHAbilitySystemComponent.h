#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PBHAbilitySystemComponent.generated.h"

/**
 * Project-wide ASC subclass. Kept as its own class from day one so we have
 * a single place to hook input-driven ability activation (dash/dodge/fire),
 * targeting data, and any GAS debugging helpers without patching engine code.
 */
UCLASS()
class PROJECTBULLETHELL_API UPBHAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Convenience wrapper used by the player character/controller to fire
	// abilities off Enhanced Input actions via gameplay tag rather than
	// hard class references - keeps input bindings data-driven.
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void TryActivateAbilitiesByTag(FGameplayTag AbilityTag);
};
