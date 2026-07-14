#include "PBHAbilitySystemComponent.h"

void UPBHAbilitySystemComponent::ActivateAbilityByTag(FGameplayTag AbilityTag)
{
	if (!AbilityTag.IsValid())
	{
		return;
	}
	
	FGameplayTagContainer TagContainer(AbilityTag);
	TryActivateAbilitiesByTag(TagContainer);
}
