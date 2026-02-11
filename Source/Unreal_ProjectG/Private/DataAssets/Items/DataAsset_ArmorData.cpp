#include "DataAssets/Items/DataAsset_ArmorData.h"
#include "AbilitySystem/PGAbilitySystemComponent.h"

void UDataAsset_ArmorData::MakeOutgoingArmorEffectSpecHandle(UPGAbilitySystemComponent* InASC, int32 InLevel) const
{
    if (!ArmorGameplayEffectClass && AttributeModifiers.IsEmpty())
    {
        return;
    }

    TSubclassOf<UGameplayEffect> EffectClass = ArmorGameplayEffectClass.LoadSynchronous();
    FGameplayEffectContextHandle EffectContext = InASC->MakeEffectContext();
    EffectContext.AddSourceObject(this);

    FGameplayEffectSpecHandle SpecHandle = InASC->MakeOutgoingSpec(EffectClass, InLevel, EffectContext);

    if (SpecHandle.IsValid())
    {
        for (const auto& Elem : AttributeModifiers)
        {
            FGameplayTag AttributeTag = Elem.Key;
            const FScalableFloat& ScalableVal = Elem.Value;

            float FinalMagnitude = ScalableVal.GetValueAtLevel(InLevel);

            SpecHandle.Data->SetSetByCallerMagnitude(AttributeTag, FinalMagnitude);
        }

        InASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
    }
}
