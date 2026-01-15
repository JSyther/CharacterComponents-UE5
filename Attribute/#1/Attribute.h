#pragma region Attribute

UENUM(BlueprintType)
enum class ECharacterAttributeType : uint8
{
	Null			UMETA(DisplayName = "Select Attribute Type"),
	Health			UMETA(DisplayName = "Health"),
	Stamina			UMETA(DisplayName = "Stamina"),
	Energy			UMETA(DisplayName = "Energy"),
	Shield			UMETA(DisplayName = "Shield"),
	Output			UMETA(DisplayName = "Output"),
	Actuation		UMETA(DisplayName = "Actuation"),
	Integrity		UMETA(DisplayName = "Integrity"),
	Capacity		UMETA(DisplayName = "Capacity"),
	Regeneration	UMETA(DisplayName = "Regeneration"),
	Max				UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EPrimaryAttributeType : uint8
{
	Null	UMETA(DisplayName = "Select Primary Attribute"),
	Health	UMETA(DisplayName = "Health"),
	Stamina UMETA(DisplayName = "Stamina"),
	Energy	UMETA(DisplayName = "Energy"),
	Shield	UMETA(DisplayName = "Shield"),
	Max		UMETA(Hidden)
};

UENUM(BlueprintType)
enum class ESecondaryAttributeType : uint8
{
	Null			UMETA(DisplayName = "Select Upgradeable Attribute"),
	Output			UMETA(DisplayName = "Output"),
	Actuation		UMETA(DisplayName = "Actuation"),
	Integrity		UMETA(DisplayName = "Integrity"),
	Capacity		UMETA(DisplayName = "Capacity"),
	Regeneration	UMETA(DisplayName = "Regeneration")
};

USTRUCT(BlueprintType)
struct FAttributeModule
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinimumValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaximumValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentValue;

public:

	FAttributeModule()
	: MinimumValue(0.f)
	, MaximumValue(100.f)
	, CurrentValue(100.f)
	{}

	bool operator!=(const FAttributeModule& Other) const
	{
		return !(*this == Other);
	}

	bool operator==(const FAttributeModule& Other) const
	{
		return
			MinimumValue == Other.MinimumValue &&
			MaximumValue == Other.MaximumValue &&
			CurrentValue == Other.CurrentValue;
	}

	float GetMinimumValue() const { return MinimumValue; }
	float GetMaximumValue() const { return MaximumValue; }
	float GetCurrentValue() const { return CurrentValue; }

	// X: Minimum, Y: Maximum, Z: Current
	FVector GetAttributeValues() const 
	{ 
		return FVector(MinimumValue, MaximumValue, CurrentValue); 
	}

	// 
	void SetValue(float InMinValue, float InMaxValue, float InCurrentValue) 
	{ 
		MinimumValue = InMinValue;
		MaximumValue = InMaxValue;
		CurrentValue = InCurrentValue;
	}
};


USTRUCT(BlueprintType)
struct FCharacterAttribute
{
	GENERATED_BODY()

protected:
	// Primary Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeModule Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeModule Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeModule Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeModule Shield;

	//Passive Attributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeModule Output; // Damage + protection

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeModule Actuation;    // Movement speed + jump height

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeModule Integrity;    // Health + shield

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeModule Capacity;     // Energy pool + efficiency

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeModule Regeneration; // Shield recharge + cooldowns

	// Available Upgrade Points
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UpgradePoint; // Default to 0

public:
	FCharacterAttribute()
	: Health()
	, Stamina()
	, Energy()
	, Shield()
	, Output()
	, Actuation()
	, Integrity()
	, Capacity()
	, Regeneration()
	, UpgradePoint(0)
	{
		Health.SetValue(0.0f, 100.0f, 100.0f);
		Stamina.SetValue(0.0f, 50.0f, 50.0f);
		Energy.SetValue(0.0f, 50.0f, 50.0f);
		Shield.SetValue(0.0f, 25.0f, 25.0f);
		Output.SetValue(10.0f, 100.0f, 10.0f);
		Actuation.SetValue(15.0f, 50.0f, 15.0f);
		Integrity.SetValue(20.0f, 80.0f, 20.0f);
		Capacity.SetValue(10.0f, 50.0f, 10.0f);
		Regeneration.SetValue(2.0f, 20.0f, 2.0f);
	}

	FAttributeModule& GetHealthAttributeModule()		{ return Health; }
	FAttributeModule& GetStaminaAttributeModule()		{ return Stamina; }
	FAttributeModule& GetEnergyAttributeModule()		{ return Energy; }
	FAttributeModule& GetShieldAttributeModule()		{ return Shield; }
	FAttributeModule& GetOutputAttributeModule()		{ return Output; }
	FAttributeModule& GetActuationAttributeModule()		{ return Actuation; }
	FAttributeModule& GetIntegrityAttributeModule()		{ return Integrity; }
	FAttributeModule& GetCapacityAttributeModule()		{ return Capacity; }
	FAttributeModule& GetRegenerationAttributeModule()	{ return Regeneration; }

	FAttributeModule& GetPrimaryAttributeModuleByType(EPrimaryAttributeType Type)
	{
		switch (Type)
		{
		case EPrimaryAttributeType::Health:
			return Health;
		case EPrimaryAttributeType::Stamina:
			return Stamina;
		case EPrimaryAttributeType::Energy:
			return Energy;
		case EPrimaryAttributeType::Shield:
			return Shield;
		default:
			#if WITH_EDITOR
			UE_LOG(LogTemp, Error, TEXT("GetPrimaryAttributeModuleByType: Invalid Primary Attribute Type selected."));
			#endif
			checkNoEntry(); 
			return *(new FAttributeModule());
		}
	}
	FAttributeModule& GetSecondaryAttributeModuleByType(ESecondaryAttributeType Type)
	{
		switch (Type)
		{
		case ESecondaryAttributeType::Output:
			return Output;
		case ESecondaryAttributeType::Actuation:
			return Actuation;
		case ESecondaryAttributeType::Integrity:
			return Integrity;
		case ESecondaryAttributeType::Capacity:
			return Capacity;
		case ESecondaryAttributeType::Regeneration:
			return Regeneration;
		default:
			#if WITH_EDITOR
			UE_LOG(LogTemp, Error, TEXT("GetSecondaryAttributeModuleByType: Invalid Secondary Attribute Type selected."));
			#endif
			checkNoEntry();
			return *(new FAttributeModule());
		}
	}
};

#pragma endregion
