#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "PBHPlayerState.generated.h"

class UPBHAbilitySystemComponent;
class UPBHAttributeSet;

/**
 * ASC and AttributeSet live on PlayerState rather than the Character.
 * This is the standard GAS pattern: PlayerState persists across pawn
 * respawns/possession changes, which matters even in single-player if the
 * run structure ever involves re-possessing a new pawn (Returnal-style
 * biome resets, checkpoint respawns, etc). The Character just forwards
 * IAbilitySystemInterface calls to this.
 */
UCLASS()
class PROJECTBULLETHELL_API APBHPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APBHPlayerState();

	//~ Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

	UFUNCTION(BlueprintCallable, Category = "PBH|Abilities")
	UPBHAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PBH|Abilities")
	TObjectPtr<UPBHAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PBH|Abilities")
	TObjectPtr<UPBHAttributeSet> AttributeSet;
};
