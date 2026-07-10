#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "PBHPlayerCharacter.generated.h"

class UPBHAbilitySystemComponent;
class UPBHAttributeSet;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * Player pawn. Deliberately minimal right now - this is the class we'll
 * iterate on hardest for movement/gunplay feel. GAS wiring (ASC forwarding,
 * ability granting) is handled here; actual dash/fire/dodge logic lives in
 * UPBHGameplayAbility subclasses, not in this class, so movement feel
 * tuning stays data-driven rather than hardcoded in C++.
 *
 * Animation: pair this with a GASP-derived AnimInstance/skeleton once the
 * base skeletal mesh and IK rig are imported - this class only owns gameplay
 * state, not animation graph specifics.
 */
UCLASS()
class PROJECTBULLETHELL_API APBHPlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APBHPlayerCharacter();

	//~ Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface

	//~ Begin APawn interface
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//~ End APawn interface

protected:
	virtual void BeginPlay() override;

	// Grants StartingAbilities to the ASC. Called once from PossessedBy
	// (server) / OnRep_PlayerState (client) once the ASC on PlayerState is
	// valid - never grant abilities before that.
	void InitAbilityActorInfo();

	UPROPERTY(EditDefaultsOnly, Category = "PBH|Abilities")
	TArray<TSubclassOf<class UPBHGameplayAbility>> StartingAbilities;

	// --- Enhanced Input ---
	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputAction> DashAction;

	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputAction> FireAction;

	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_Dash(const FInputActionValue& Value);
	void Input_Fire(const FInputActionValue& Value);
	void Input_FireReleased(const FInputActionValue& Value);

private:
	// Cached from PlayerState once possession completes. Not the source of
	// truth - GetAbilitySystemComponent() always resolves through
	// PlayerState - this is just a convenience cache for Tick-frequency
	// lookups later (e.g. reading MoveSpeed each frame for movement blending).
	UPROPERTY()
	TObjectPtr<UPBHAbilitySystemComponent> CachedASC;
};
