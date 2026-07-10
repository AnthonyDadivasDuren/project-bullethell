#pragma once

#include "NativeGameplayTags.h"

/**
 * Native gameplay tags for ability activation. Declared here rather than
 * left as INI-defined tags so they're compile-time checked and easy to
 * find/rename via IDE refactor tools. Add new Ability.* tags here as new
 * abilities (weapon swap, alt-fire, block/parry if that ends up in scope) are added.
 */
namespace PBHGameplayTags
{
	PROJECTBULLETHELL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Dash);
	PROJECTBULLETHELL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Fire_Primary);
	PROJECTBULLETHELL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Fire_Alt);

	PROJECTBULLETHELL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Dashing);
	PROJECTBULLETHELL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Invulnerable);
	PROJECTBULLETHELL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Firing);
}
