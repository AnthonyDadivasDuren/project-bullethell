#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PBHAttributeSet.generated.h"

// Standard boilerplate macro block for GAS attributes: getters, setters, initters.
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Core player attributes.
 * Kept intentionally minimal for the first vertical slice: Health, MaxHealth,
 * MoveSpeed (so dash/movement abilities can modify it via GEs rather than
 * touching CharacterMovementComponent directly), and DashCharges for a
 * Returnal/Kill Knight-style limited-charge dodge.
 *
 * Add Stamina, Ammo, or Overheat here later as separate attributes rather
 * than overloading these - keep each attribute single-purpose.
 */
UCLASS()
class PROJECTBULLETHELL_API UPBHAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPBHAttributeSet();

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPBHAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPBHAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MoveSpeed, Category = "Attributes")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UPBHAttributeSet, MoveSpeed)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DashCharges, Category = "Attributes")
	FGameplayAttributeData DashCharges;
	ATTRIBUTE_ACCESSORS(UPBHAttributeSet, DashCharges)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxDashCharges, Category = "Attributes")
	FGameplayAttributeData MaxDashCharges;
	ATTRIBUTE_ACCESSORS(UPBHAttributeSet, MaxDashCharges)

	//~ Begin UAttributeSet interface
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	//~ End UAttributeSet interface

protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);

	UFUNCTION()
	virtual void OnRep_DashCharges(const FGameplayAttributeData& OldDashCharges);

	UFUNCTION()
	virtual void OnRep_MaxDashCharges(const FGameplayAttributeData& OldMaxDashCharges);
};
