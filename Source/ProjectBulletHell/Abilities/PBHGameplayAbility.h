
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PBHGameplayAbility.generated.h"

UCLASS(Abstract)
class PROJECTBULLETHELL_API UPBHGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPBHGameplayAbility();
	
	UPROPERTY(EditDefaultsOnly, Category = "PBH|Ability")
	FGameplayTag AbilityInputTag;
};