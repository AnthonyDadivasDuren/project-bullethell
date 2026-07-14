#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "PBHCharacterBase.generated.h"

UCLASS(Abstract)
class PROJECTBULLETHELL_API APBHCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	
public:
	APBHCharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return nullptr; }
};