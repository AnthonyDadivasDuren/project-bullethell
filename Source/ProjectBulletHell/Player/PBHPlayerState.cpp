#include "PBHPlayerState.h"
#include "../Abilities/PBHAbilitySystemComponent.h"
#include "../Abilities/PBHAttributeSet.h"

APBHPlayerState::APBHPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UPBHAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UPBHAttributeSet>(TEXT("AttributeSet"));

	// PlayerState ticks by default; we don't need that for GAS bookkeeping.
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* APBHPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
