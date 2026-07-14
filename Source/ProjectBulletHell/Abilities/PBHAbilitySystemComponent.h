#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "PBHAbilitySystemComponent.generated.h"

UCLASS()
class PROJECTBULLETHELL_API UPBHAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbilityByTag(FGameplayTag AbilityTag);
};
