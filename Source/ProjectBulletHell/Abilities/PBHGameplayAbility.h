#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PBHGameplayAbility.generated.h"

/**
 * Base class for every player ability (dash/dodge, fire, alt-fire, weapon
 * swap, ability-driven movement states, etc). Centralizing this now means
 * we have one place to add shared behavior later - e.g. a common "activation
 * failed" feedback hook, or a shared cost/cooldown convention - without
 * touching every individual ability.
 *
 * InstancingPolicy defaults to InstancedPerActor in the constructor since
 * that's the right default for most player abilities (dash, fire); one-off
 * stateless abilities can override it per-instance if needed.
 */
UCLASS(Abstract, HideCategories = Input, Meta = (ShortTooltip = "Project Bullet Hell base gameplay ability."))
class PROJECTBULLETHELL_API UPBHGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPBHGameplayAbility();

	// Gameplay tag that identifies this ability for input-driven activation
	// (see UPBHAbilitySystemComponent::TryActivateAbilitiesByTag). Set this
	// per-ability in the class default / Blueprint child, e.g.
	// Ability.Dash, Ability.Fire.Primary, Ability.Fire.Alt.
	UPROPERTY(EditDefaultsOnly, Category = "PBH|Ability")
	FGameplayTag AbilityInputTag;
};
