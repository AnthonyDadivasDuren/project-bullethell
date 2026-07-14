#pragma once

#include "CoreMinimal.h"
#include "../PBHGameplayAbility.h"
#include "PBHGA_Dash.generated.h"

UCLASS()
class PROJECTBULLETHELL_API UPBHGA_Dash : public UPBHGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPBHGA_Dash();
	
	// --- Engine Overrides ---
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	// --- Functions ---
	UFUNCTION()
	void OnDashFinished();
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr,
	FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
protected:
	// --- Dash Tuning ---
	UPROPERTY(EditDefaultsOnly, Category= "PBH|Dash")
	float DashDistance = 350.0f;
	
	UPROPERTY(EditDefaultsOnly, Category= "PBH|Dash")
	float DashDuration = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, Category = "PBH|Dash")
	TSubclassOf<class UGameplayEffect> DashInvulnerabilityEffect;
};
