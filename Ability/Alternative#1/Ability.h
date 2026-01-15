#pragma region Ability

UENUM(BlueprintType)
enum class ECharacterAbilityType : uint8
{
	Null UMETA(DisplayName = "Select Character Ability"),
	CombatStrike UMETA(DisplayName = "Combat Strike"),
	LaserPulse UMETA(DisplayName = "Laser Pulse"),
	PlasmaShield UMETA(DisplayName = "Plasma Shield"),
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	Null		UMETA(DisplayName = "Select Ability Type"),
	Passive		UMETA(DisplayName = "Passive"),
	Active		UMETA(DisplayName = "Active"),
	Ultimate	UMETA(DisplayName = "Ultimate"),
	Max			UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAbilityEffectType : uint8
{
	Null	UMETA(DisplayName = "Select Ability Effect Type"),
	Damage	UMETA(DisplayName = "Damage"),
	Defense UMETA(DisplayName = "Defense"),
	Heal	UMETA(DisplayName = "Heal"),
	Buff	UMETA(DisplayName = "Buff"),
	Debuff	UMETA(DisplayName = "Debuff"),
	Spawn	UMETA(DisplayName = "Spawn"),
	Custom	UMETA(DisplayName = "Custom"),
	Max		UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EAbilityCostType : uint8
{
	Null		UMETA(DisplayName = "Select Ability Cost Type"),
	Health		UMETA(DisplayName = "Health"),
	Stamina		UMETA(DisplayName = "Stamina"),
	Energy		UMETA(DisplayName = "Energy"),
	Shield		UMETA(DisplayName = "Shield"),
	Max			UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FAbilityModule
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	EAbilityType AbilityType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	EAbilityEffectType EffectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	EAbilityCostType CostType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	float Output;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Magnitude;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Multiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)	
	float Cost;

public:
	FAbilityModule()
	: Title("DefaultAbility")
	, Description("DefaultAbilityDescription")
	, AbilityType(EAbilityType::Passive)
	, EffectType(EAbilityEffectType::Damage)
	, CostType(EAbilityCostType::Health)
	, Output(0.f)
	, Magnitude(0.f)
	, Multiplier(1.f)
	, Duration(0.f)
	, CooldownTime(0.f)
	, Cost(0.f)
	{}

	bool operator!=(const FAbilityModule& Other) const
	{
		return !(*this == Other);
	}

	bool operator==(const FAbilityModule& Other) const
	{
		return
		Title == Other.Title &&
		Description == Other.Description &&
		AbilityType == Other.AbilityType &&
		EffectType == Other.EffectType &&
		CostType == Other.CostType &&
		Output == Other.Output &&
		Magnitude == Other.Magnitude &&
		Multiplier == Other.Multiplier &&
		Duration == Other.Duration &&
		CooldownTime == Other.CooldownTime &&
		Cost == Other.Cost;
	}

	FString GetTitle() const { return Title; }
	FString GetDescription() const { return Description; }
	EAbilityType GetAbilityType() const { return AbilityType; }
	EAbilityEffectType GetEffectType() const { return EffectType; }
	EAbilityCostType GetCostType() const { return CostType; }
	float GetOutput() const { return Output; }
	float GetMagnitude() const { return Magnitude; }
	float GetMultiplier() const { return Multiplier; }
	float GetDuration() const { return Duration; }
	float GetCooldownTime() const { return CooldownTime; }
	float GetCost() const { return Cost; }

	void SetTitle(const FString& InTitle) { Title = InTitle; }
	void SetDescription(const FString& InDescription) { Description = InDescription; }
	void SetAbilityType(EAbilityType InAbilityType) { AbilityType = InAbilityType; }
	void SetEffectType(EAbilityEffectType InEffectType) { EffectType = InEffectType; }
	void SetCostType(EAbilityCostType InCostType) { CostType = InCostType; }
	void SetOutput(float InOutput) { Output = InOutput; }
	void SetMagnitude(float InMagnitude) { Magnitude = InMagnitude; }
	void SetMultiplier(float InMultiplier) { Multiplier = InMultiplier; }
	void SetDuration(float InDuration) { Duration = InDuration; }
	void SetCooldownTime(float InCooldownTime) { CooldownTime = InCooldownTime; }
	void SetCost(float InCost) { Cost = InCost; }
};

USTRUCT(BlueprintType)
struct FCharacterAbilityModule
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
	ECharacterAbilityType AbilityType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityEffectType EffectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "EffectType == EAbilityEffectType::Damage", EditConditionHides))
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)		
	FVector2D PowerRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) 	
	FVector2D DurationRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D CooldownTimeRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAbilityCostType CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D CostRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;

public:
	// Constructor 
	FCharacterAbilityModule()
	: Title("DefaultAbility")
	, Description("DefaultAbilityDescription")
	, AbilityType(ECharacterAbilityType::Null)
	, DamageType(EDamageType::Null)
	, PowerRange(FVector2D::ZeroVector)
	, DurationRange(FVector2D::ZeroVector)
	, CooldownTimeRange(FVector2D::ZeroVector)
	, CostType(EAbilityCostType::Null)
	, CostRange(FVector2D::ZeroVector)
	, Range(0.f)
	, Radius(0.f)
	{
	}

	// Equality operators
	bool operator==(const FCharacterAbilityModule& Other) const
	{
		return
		Title == Other.Title &&
		Description == Other.Description &&
		AbilityType == Other.AbilityType &&
		DamageType == Other.DamageType &&
		PowerRange == Other.PowerRange &&
		DurationRange == Other.DurationRange &&
		CooldownTimeRange == Other.CooldownTimeRange &&
		CostType == Other.CostType &&
		CostRange == Other.CostRange &&
		Range == Other.Range &&
		Radius == Other.Radius;
	}

	// Inequality operators
	bool operator!=(const FCharacterAbilityModule& Other) const
	{
		return !(*this == Other);
	}

	FString GetTitle() const { return Title; }
	FString GetDescription() const { return Description; }
	ECharacterAbilityType GetAbilityType() const { return AbilityType; }
	EAbilityEffectType GetEffectType() const { return EffectType; }
	EDamageType GetDamageType() const { return DamageType; }
	FVector2D GetPowerRange() const { return PowerRange; }
	FVector2D GetDurationRange() const { return DurationRange; }
	FVector2D GetCooldownTimeRange() const { return CooldownTimeRange; }
	EAbilityCostType GetCostType() const { return CostType; }
	FVector2D GetCostRange() const { return CostRange; }
	float GetRange() const { return Range; }
	float GetRadius() const { return Radius; }

	float GetRandomPower() const { return FMath::FRandRange(PowerRange.X, PowerRange.Y); }
	float GetRandomDuration() const { return FMath::FRandRange(DurationRange.X, DurationRange.Y); }
	float GetRandomCooldownTime() const { return FMath::FRandRange(CooldownTimeRange.X, CooldownTimeRange.Y); }
	float GetRandomCost() const { return FMath::FRandRange(CostRange.X, CostRange.Y); }

	void SetTitle(const FString& InTitle) { Title = InTitle; }
	void SetDescription(const FString& InDescription) { Description = InDescription; }
	void SetAbilityType(ECharacterAbilityType InAbilityType) { AbilityType = InAbilityType; }
	void SetEffectType(EAbilityEffectType InEffectType) { EffectType = InEffectType; }
	void SetDamageType(EDamageType InDamageType) { DamageType = InDamageType; }
	void SetPowerRange(const FVector2D& InPowerRange) { PowerRange = InPowerRange; }
	void SetDurationRange(const FVector2D& InDurationRange) { DurationRange = InDurationRange; }
	void SetCooldownTimeRange(const FVector2D& InCooldownTimeRange) { CooldownTimeRange = InCooldownTimeRange; }
	void SetCostType(EAbilityCostType InCostType) { CostType = InCostType; }
	void SetCostRange(const FVector2D& InCostRange) { CostRange = InCostRange; }
	void SetRange(float InRange) { Range = InRange; }
	void SetRadius(float InAreaRadius) { Radius = InAreaRadius; }

};

USTRUCT(BlueprintType)
struct FCharacterAbilityData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCharacterAbilityModule CombatStrike;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCharacterAbilityModule LaserPulse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCharacterAbilityModule PlasmaShield;

public:
	FCharacterAbilityData()
		: CombatStrike()
		, LaserPulse()
		, PlasmaShield()
	{
		InitializeCombatStrikeAbility();
		InitializeLaserPulseAbility();
		InitializePlasmaShieldAbility();
	}

private:

	// Initialize Abilities
	void InitializeCombatStrikeAbility()
	{
		CombatStrike.SetTitle("Combat Strike");
		CombatStrike.SetDescription("A powerful melee attack that deals significant damage to a single target.");
		CombatStrike.SetAbilityType(ECharacterAbilityType::CombatStrike);
		CombatStrike.SetEffectType(EAbilityEffectType::Damage);
		CombatStrike.SetDamageType(EDamageType::Physical);
		CombatStrike.SetPowerRange(FVector2D(10.0f, 15.f));
		CombatStrike.SetDurationRange(FVector2D(0.0f, 0.0f));
		CombatStrike.SetCooldownTimeRange(FVector2D(2.0f, 3.0f));
		CombatStrike.SetCostType(EAbilityCostType::Energy);
		CombatStrike.SetCostRange(FVector2D(8.f, 10.f));
		CombatStrike.SetRange(100.0f);
		CombatStrike.SetRadius(30.0f);
	}

	// Initialize Laser Pulse Ability
	void InitializeLaserPulseAbility()
	{
		LaserPulse.SetTitle("Laser Pulse");
		LaserPulse.SetDescription("Fires a concentrated beam of energy that damages enemies in its path.");
		LaserPulse.SetAbilityType(ECharacterAbilityType::LaserPulse);
		LaserPulse.SetEffectType(EAbilityEffectType::Damage);
		LaserPulse.SetDamageType(EDamageType::Energy);
		LaserPulse.SetPowerRange(FVector2D(8.0f, 12.f));
		LaserPulse.SetDurationRange(FVector2D(0.f, 0.f));
		LaserPulse.SetCooldownTimeRange(FVector2D(2.f, 4.f));
		LaserPulse.SetCostType(EAbilityCostType::Energy);
		LaserPulse.SetCostRange(FVector2D(7.f, 12.f));
		LaserPulse.SetRange(500.0f);
		LaserPulse.SetRadius(20.0f);
	}

	// Initialize Plasma Shield Ability
	void InitializePlasmaShieldAbility()
	{
		PlasmaShield.SetTitle("Plasma Shield");
		PlasmaShield.SetDescription("Generates a protective shield that absorbs incoming damage for a short duration.");
		PlasmaShield.SetAbilityType(ECharacterAbilityType::PlasmaShield);
		PlasmaShield.SetEffectType(EAbilityEffectType::Defense);
		PlasmaShield.SetDamageType(EDamageType::Null);
		PlasmaShield.SetPowerRange(FVector2D(0.f, 0.f));
		PlasmaShield.SetDurationRange(FVector2D(5.f, 10.f));
		PlasmaShield.SetCooldownTimeRange(FVector2D(10.f, 15.f));
		PlasmaShield.SetCostType(EAbilityCostType::Energy);
		PlasmaShield.SetCostRange(FVector2D(15.f, 25.f));
		PlasmaShield.SetRange(0.0f);
		PlasmaShield.SetRadius(0.0f);
	}

public:
	FCharacterAbilityModule FindCharacterAbilityByType(ECharacterAbilityType AbilityType) const
	{
		switch (AbilityType)
		{
		case ECharacterAbilityType::CombatStrike:
			return CombatStrike;
		case ECharacterAbilityType::LaserPulse:
			return LaserPulse;
		case ECharacterAbilityType::PlasmaShield:
			return PlasmaShield;
		default:
			return FCharacterAbilityModule();
		}
	}

	const FCharacterAbilityModule* FindCharacterAbilityByTypePtr(ECharacterAbilityType AbilityType) const
	{
		switch (AbilityType)
		{
		case ECharacterAbilityType::CombatStrike:
			return &CombatStrike;

		case ECharacterAbilityType::LaserPulse:
			return &LaserPulse;

		case ECharacterAbilityType::PlasmaShield:
			return &PlasmaShield;

		default:
			return nullptr;
		}
	}

};


#pragma endregion
