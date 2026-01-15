#pragma region Attribute

float UAttributeManager::GetCurrentAttributeValueByType(ECharacterAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ECharacterAttributeType::Health:
		return CharacterData.GetAttributeData().GetHealthAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Energy:
		return CharacterData.GetAttributeData().GetEnergyAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Shield:
		return CharacterData.GetAttributeData().GetShieldAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetStaminaAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetCurrentValue();
	case ECharacterAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetCurrentAttributeValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;

	default:
		return 0.0f;
	}
}

float UAttributeManager::GetMinimumAttributeValueByType(ECharacterAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ECharacterAttributeType::Health:
		return CharacterData.GetAttributeData().GetHealthAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Energy:
		return CharacterData.GetAttributeData().GetEnergyAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Shield:
		return CharacterData.GetAttributeData().GetShieldAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetStaminaAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetMinimumValue();
	case ECharacterAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetMinimumAttributeValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

float UAttributeManager::GetMaximumAttributeValueByType(ECharacterAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ECharacterAttributeType::Health:
		return CharacterData.GetAttributeData().GetHealthAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Energy:
		return CharacterData.GetAttributeData().GetEnergyAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Shield:
		return CharacterData.GetAttributeData().GetShieldAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetStaminaAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetMaximumValue();
	case ECharacterAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetMaximumAttributeByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

FAttributeModule UAttributeManager::GetPrimaryAttributeModuleByType(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
		return CharacterData.GetAttributeData().GetPrimaryAttributeModuleByType(EPrimaryAttributeType::Health);
	case EPrimaryAttributeType::Energy:
		return CharacterData.GetAttributeData().GetPrimaryAttributeModuleByType(EPrimaryAttributeType::Energy);
	case EPrimaryAttributeType::Shield:
		return CharacterData.GetAttributeData().GetPrimaryAttributeModuleByType(EPrimaryAttributeType::Shield);
	case EPrimaryAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetPrimaryAttributeModuleByType(EPrimaryAttributeType::Stamina);
	case EPrimaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeModuleByType: Selected AttributeType is Null."));
#endif
		return FAttributeModule();
	default:
		return FAttributeModule();
	}
}

float UAttributeManager::GetPrimaryAttributeCurrentValueByType(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
	{
		auto& Health = CharacterData.GetAttributeData().GetHealthAttributeModule();
		return Health.GetCurrentValue();
	}
	case EPrimaryAttributeType::Energy:
	{
		auto& Energy = CharacterData.GetAttributeData().GetEnergyAttributeModule();
		return Energy.GetCurrentValue();
	}

	case EPrimaryAttributeType::Shield:
	{
		auto& Shield = CharacterData.GetAttributeData().GetShieldAttributeModule();
		return Shield.GetCurrentValue();
	}

	case EPrimaryAttributeType::Stamina:
	{
		auto& Stamina = CharacterData.GetAttributeData().GetStaminaAttributeModule();
		return Stamina.GetCurrentValue();
	}

	case EPrimaryAttributeType::Null:
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeCurrentValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	}

	default:
		return 0.0f;
	}
}

float UAttributeManager::GetPrimaryAttributeMinimumValueByType(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
	{
		auto& Health = CharacterData.GetAttributeData().GetHealthAttributeModule();
		return Health.GetMinimumValue();
	}

	case EPrimaryAttributeType::Energy:
	{
		auto& Energy = CharacterData.GetAttributeData().GetEnergyAttributeModule();
		return Energy.GetMinimumValue();
	}

	case EPrimaryAttributeType::Shield:
	{
		auto& Shield = CharacterData.GetAttributeData().GetShieldAttributeModule();
		return Shield.GetMinimumValue();
	}

	case EPrimaryAttributeType::Stamina:
	{
		auto& Stamina = CharacterData.GetAttributeData().GetStaminaAttributeModule();
		return Stamina.GetMinimumValue();
	}

	case EPrimaryAttributeType::Null:
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeMinimumValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	}

	default:
		return 0.0f;
	}
}

float UAttributeManager::GetPrimaryAttributeMaximumValueByType(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
	{
		auto& Health = CharacterData.GetAttributeData().GetHealthAttributeModule();
		return Health.GetMaximumValue();
	}

	case EPrimaryAttributeType::Energy:
	{
		auto& Energy = CharacterData.GetAttributeData().GetEnergyAttributeModule();
		return Energy.GetMaximumValue();
	}

	case EPrimaryAttributeType::Shield:
	{
		auto& Shield = CharacterData.GetAttributeData().GetShieldAttributeModule();
		return Shield.GetMaximumValue();
	}

	case EPrimaryAttributeType::Stamina:
	{
		auto& Stamina = CharacterData.GetAttributeData().GetStaminaAttributeModule();
		return Stamina.GetMaximumValue();
	}

	case EPrimaryAttributeType::Null:
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeMaximumValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	}

	default:
		return 0.0f;
	}
}

FAttributeModule UAttributeManager::GetSecondaryAttributeModuleByType(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Output);
	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Actuation);
	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Integrity);
	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Capacity);
	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetSecondaryAttributeModuleByType(ESecondaryAttributeType::Regeneration);
	case ESecondaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeModuleByType: Selected AttributeType is Null."));
#endif
		return FAttributeModule();
	default:
		return FAttributeModule();
	}
}

float UAttributeManager::GetSecondaryAttributeCurrentValueByType(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetCurrentValue();
	case ESecondaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeCurrentValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

float UAttributeManager::GetSecondaryAttributeMinimumValueByType(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetMinimumValue();
	case ESecondaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeMinimumValueByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

float UAttributeManager::GetSecondaryAttributeMaximumByType(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetMaximumValue();
	case ESecondaryAttributeType::Null:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeMaximumByType: Selected AttributeType is Null."));
#endif
		return 0.0f;
	default:
		return 0.0f;
	}
}

float UAttributeManager::GetMaximumAttributeByType(ECharacterAttributeType AttributeType)
{
	return GetMaximumAttributeValueByType(AttributeType);
}

void UAttributeManager::SetPrimaryAttributeValueByType(EPrimaryAttributeType AttributeType, float MinValue, float MaxValue, float CurrentValue)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
	{
		auto& Health = CharacterData.GetAttributeData().GetHealthAttributeModule();
		Health.SetValue(MinValue, MaxValue, CurrentValue);
		OnHealthAttributeChanged.Broadcast(Health.GetMinimumValue(), Health.GetMaximumValue(), Health.GetCurrentValue());

		if(Health.GetCurrentValue() <= 0.0f)
		{
			SetCharacterState(ECharacterState::Death);
		}	

		break;
	}
	case EPrimaryAttributeType::Energy:
	{
		auto& Energy = CharacterData.GetAttributeData().GetEnergyAttributeModule();
		Energy.SetValue(MinValue, MaxValue, CurrentValue);
		OnEnergyAttributeChanged.Broadcast(Energy.GetMinimumValue(), Energy.GetMaximumValue(), Energy.GetCurrentValue());
		break;
	}
	case EPrimaryAttributeType::Shield:
	{
		auto& Shield = CharacterData.GetAttributeData().GetShieldAttributeModule();
		Shield.SetValue(MinValue, MaxValue, CurrentValue);
		OnShieldAttributeChanged.Broadcast(Shield.GetMinimumValue(), Shield.GetMaximumValue(), Shield.GetCurrentValue());
		break;
	}
	case EPrimaryAttributeType::Stamina:
	{
		auto& Stamina = CharacterData.GetAttributeData().GetStaminaAttributeModule();
		Stamina.SetValue(MinValue, MaxValue, CurrentValue);
		OnStaminaAttributeChanged.Broadcast(Stamina.GetMinimumValue(), Stamina.GetMaximumValue(), Stamina.GetCurrentValue());
		break;
	}
	default:
		break;
	}
}

void UAttributeManager::SetSecondaryAttributeValueByType(ESecondaryAttributeType AttributeType, float MinValue, float MaxValue, float CurrentValue)
{
	switch (AttributeType)
	{
		case ESecondaryAttributeType::Output:
		{
			auto& Output = CharacterData.GetAttributeData().GetOutputAttributeModule();
			Output.SetValue(MinValue, MaxValue, CurrentValue);
			OnOutputAttributeChanged.Broadcast(Output.GetMinimumValue(), Output.GetMaximumValue(), Output.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Actuation:
		{
			auto& Actuation = CharacterData.GetAttributeData().GetActuationAttributeModule();
			Actuation.SetValue(MinValue, MaxValue, CurrentValue);
			OnActuationAttributeChanged.Broadcast(Actuation.GetMinimumValue(), Actuation.GetMaximumValue(), Actuation.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Integrity:
		{
			auto& Integrity = CharacterData.GetAttributeData().GetIntegrityAttributeModule();
			Integrity.SetValue(MinValue, MaxValue, CurrentValue);
			OnIntegrityAttributeChanged.Broadcast(Integrity.GetMinimumValue(), Integrity.GetMaximumValue(), Integrity.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Capacity:
		{
			auto& Capacity = CharacterData.GetAttributeData().GetCapacityAttributeModule();
			Capacity.SetValue(MinValue, MaxValue, CurrentValue);
			OnCapacityAttributeChanged.Broadcast(Capacity.GetMinimumValue(), Capacity.GetMaximumValue(), Capacity.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Regeneration:
		{
			auto& Regeneration = CharacterData.GetAttributeData().GetRegenerationAttributeModule();
			Regeneration.SetValue(MinValue, MaxValue, CurrentValue);
			OnRegenerationAttributeChanged.Broadcast(Regeneration.GetMinimumValue(), Regeneration.GetMaximumValue(), Regeneration.GetCurrentValue());
			break;
		}

		case ESecondaryAttributeType::Null:
		{
			#if WITH_EDITOR
			UE_LOG(LogTemp, Error, TEXT("SetSecondaryAttributeCurrentValueByType: Selected AttributeType is Null."));
			#endif
			break;
		}
	}
}

bool UAttributeManager::HasPrimaryAttributeValue(EPrimaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case EPrimaryAttributeType::Health:
		return CharacterData.GetAttributeData().GetHealthAttributeModule().GetCurrentValue() > 0.0f;

	case EPrimaryAttributeType::Energy:
		return CharacterData.GetAttributeData().GetEnergyAttributeModule().GetCurrentValue() > 0.0f;

	case EPrimaryAttributeType::Shield:
		return CharacterData.GetAttributeData().GetShieldAttributeModule().GetCurrentValue() > 0.0f;

	case EPrimaryAttributeType::Stamina:
		return CharacterData.GetAttributeData().GetStaminaAttributeModule().GetCurrentValue() > 0.0f;

	case EPrimaryAttributeType::Null:
	default:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("HasPrimaryAttributeValue: Invalid AttributeType."));
#endif
		return false;
	}
}

bool UAttributeManager::HasSecondaryAttributeValue(ESecondaryAttributeType AttributeType)
{
	switch (AttributeType)
	{
	case ESecondaryAttributeType::Output:
		return CharacterData.GetAttributeData().GetOutputAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Actuation:
		return CharacterData.GetAttributeData().GetActuationAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Integrity:
		return CharacterData.GetAttributeData().GetIntegrityAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Capacity:
		return CharacterData.GetAttributeData().GetCapacityAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Regeneration:
		return CharacterData.GetAttributeData().GetRegenerationAttributeModule().GetCurrentValue() > 0.0f;

	case ESecondaryAttributeType::Null:
	default:
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("HasSecondaryAttributeValue: Invalid AttributeType."));
#endif
		return false;
	}
}

#pragma endregion
