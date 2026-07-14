#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "PBHPlayerState.generated.h"

class UPBHAbilitySystemComponent;
class UPBHAttributeSet;

UCLASS()
class PROJECTBULLETHELL_API APBHPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	APBHPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintCallable, Category = "PBH|Abilities")
	UPBHAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PBH|Abilities")
	TObjectPtr<UPBHAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PBH|Abilities")
	TObjectPtr<UPBHAttributeSet> AttributeSet;
	
};
