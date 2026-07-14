#include "PBHPlayerState.h"
#include "ProjectBulletHell/Abilities/PBHAbilitySystemComponent.h"
#include "ProjectBulletHell/Abilities/PBHAttributeSet.h"

APBHPlayerState::APBHPlayerState()
{
	
	AbilitySystemComponent = CreateDefaultSubobject<UPBHAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UPBHAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* APBHPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}