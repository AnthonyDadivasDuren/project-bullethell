#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PBHAttributeSet.generated.h"

struct FGameplayEffectModCallbackData;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class PROJECTBULLETHELL_API UPBHAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPBHAttributeSet();
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPBHAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPBHAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_DashCharges, Category = "Attributes")
	FGameplayAttributeData DashCharges;
	ATTRIBUTE_ACCESSORS(UPBHAttributeSet, DashCharges)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxDashCharges, Category = "Attributes")
	FGameplayAttributeData MaxDashCharges;
	ATTRIBUTE_ACCESSORS(UPBHAttributeSet, MaxDashCharges)
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
protected:
	
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UFUNCTION()
	virtual void OnRep_DashCharges(const FGameplayAttributeData& OldDashCharges);
	
	UFUNCTION()
	virtual void OnRep_MaxDashCharges(const FGameplayAttributeData& OldMaxDashCharges);
	
};
