#include "PBHGA_Dash.h"
#include "GameFramework/Character.h"
#include "ProjectBulletHell/Player/PBHPlayerCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../PBHAttributeSet.h"

UPBHGA_Dash::UPBHGA_Dash()
{
	AbilityInputTag = FGameplayTag::RequestGameplayTag(FName("Ability.Dash"));
	SetAssetTags(FGameplayTagContainer(AbilityInputTag));
}

void UPBHGA_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	APBHPlayerCharacter* Character = Cast<APBHPlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!Character) { return; }
	
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (ASC)
	{
		if (UPBHAttributeSet* AttributeSet = const_cast<UPBHAttributeSet*>(ASC->GetSet<UPBHAttributeSet>()))
		{
			AttributeSet->SetDashCharges(AttributeSet->GetDashCharges() - 1.0f);
		}
	}
	
	if (DashInvulnerabilityEffect)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DashInvulnerabilityEffect);
		if (SpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
		}
	}
	
	FVector DashDirection = Character->GetLastMovementInputVector();
	
	if (DashDirection.IsNearlyZero())
	{
		DashDirection = Character->GetActorForwardVector();
	}
	DashDirection.Z = 0.0f;
	DashDirection.Normalize();
	const float Speed = DashDistance / DashDuration;
	FVector LaunchVelocity = DashDirection * Speed;
	
	Character->LaunchCharacter(LaunchVelocity, true, true);
	Character->GetCharacterMovement()->GravityScale = 0.0f;
	
	UAbilityTask_WaitDelay* WaitTask = UAbilityTask_WaitDelay::WaitDelay(this, DashDuration);
	
	WaitTask->OnFinish.AddDynamic(this, &UPBHGA_Dash::OnDashFinished);
	
	WaitTask->ReadyForActivation();
}

void UPBHGA_Dash::OnDashFinished()
{
	if (APBHPlayerCharacter* Character = Cast<APBHPlayerCharacter>(CurrentActorInfo->AvatarActor.Get()))
	{
		Character->GetCharacterMovement()->GravityScale = 1.0f;
	}
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

bool UPBHGA_Dash::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	const UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	if (!ASC)
	{
		return false;
	}

	const UPBHAttributeSet* AttributeSet = ASC->GetSet<UPBHAttributeSet>();
	if (!AttributeSet)
	{
		return false;
	}

	return AttributeSet->GetDashCharges() > 0.0f;
}
