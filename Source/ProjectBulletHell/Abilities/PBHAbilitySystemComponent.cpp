#include "PBHAbilitySystemComponent.h"

void UPBHAbilitySystemComponent::TryActivateAbilitiesByTag(FGameplayTag AbilityTag)
{
	if (!AbilityTag.IsValid())
	{
		return;
	}

	FGameplayTagContainer TagContainer(AbilityTag);
	Super::TryActivateAbilitiesByTag(TagContainer);
}
