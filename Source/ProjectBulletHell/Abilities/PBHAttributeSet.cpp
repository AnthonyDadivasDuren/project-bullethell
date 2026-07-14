#include "PBHAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UPBHAttributeSet::UPBHAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
	
	InitDashCharges(2.0f);
	InitMaxDashCharges(2.0f);
}

void UPBHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UPBHAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPBHAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always); 
	
	DOREPLIFETIME_CONDITION_NOTIFY(UPBHAttributeSet, DashCharges, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPBHAttributeSet, MaxDashCharges, COND_None, REPNOTIFY_Always);
	
}

void UPBHAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute())
	{
		NewValue= FMath::Clamp(NewValue, 0.0f, GetMaxHealth()); 
	}
	
	if (Attribute == GetDashChargesAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxDashCharges());
	}
}

void UPBHAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	
	if (Data.EvaluatedData.Attribute == GetDashChargesAttribute())
	{
		SetDashCharges(FMath::Clamp(GetDashCharges(), 0.0f, GetMaxDashCharges()));
	}
}

void UPBHAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPBHAttributeSet, Health, OldHealth);
}

void UPBHAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPBHAttributeSet, MaxHealth, OldMaxHealth);
}

void UPBHAttributeSet::OnRep_DashCharges(const FGameplayAttributeData& OldDashCharges)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPBHAttributeSet, DashCharges, OldDashCharges);
}

void UPBHAttributeSet::OnRep_MaxDashCharges(const FGameplayAttributeData& OldMaxDashCharges)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPBHAttributeSet, MaxDashCharges, OldMaxDashCharges);
}
