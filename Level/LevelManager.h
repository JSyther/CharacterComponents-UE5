#pragma region Level

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> ExperienceThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxLevel;

	// This experience bonus when enemy is defeated to increase XP gain for player
	float ExperienceRewardBonus;

private:
	// Initialize Experience Thresholds for Leveling Up
	void InitializeExperienceThresholds()
	{
		ExperienceThreshold.Empty();

		const int32 MaximumLevel = MaxLevel;
		const int32 MaxIndex = MaximumLevel + 1; // Include Level 0
		const int32 NumSegments = 10;
		const float BaseStep = 100.f; // Level 1 starts at 101
		const float StepMultiplier = 1.1f;

		ExperienceThreshold.Add(0); // Level 0

		int32 LevelsPerSegment = MaximumLevel / NumSegments;
		float CurrentThreshold = 0.f;
		float CurrentStep = BaseStep;

		for (int32 Segment = 0; Segment < NumSegments; ++Segment)
		{
			for (int32 LevelInSegment = 0; LevelInSegment < LevelsPerSegment; ++LevelInSegment)
			{
				CurrentThreshold += CurrentStep;

				// Round nicely, e.g., nearest 10
				int32 RoundedThreshold = FMath::RoundToInt(CurrentThreshold / 10.f) * 10;
				ExperienceThreshold.Add(RoundedThreshold);
			}

			CurrentStep *= StepMultiplier;
		}

		// Fill remaining levels if MaxLevel not divisible by segments
		int32 RemainingLevels = MaximumLevel - (ExperienceThreshold.Num() - 1);
		for (int32 i = 0; i < RemainingLevels; ++i)
		{
			CurrentThreshold += CurrentStep;
			int32 RoundedThreshold = FMath::RoundToInt(CurrentThreshold / 10.f) * 10;
			ExperienceThreshold.Add(RoundedThreshold);
		}
	}


public:
	// Constructor
	FLevelData()
	: Experience(0.f)
	, Level(0)
	, MaxLevel(100)
	, ExperienceRewardBonus(30.f)
	{
		InitializeExperienceThresholds();
	}

	// Getter for current experience 
	float GetExperience() const
	{
		return Experience;
	}

	// Getter for experience thresholds
	TArray<float> GetExperienceThreshold() const
	{
		return ExperienceThreshold;
	}

	// Getter for current level
	int32 GetLevel() const
	{
		return Level;
	}

	// Getter for maximum level
	int32 GetMaxLevel() const
	{
		return MaxLevel;
	}

	// Getter for experience reward bonus
	int32 GetExperienceRewardBonus() const
	{
		int32 CurrentLevel = Level;
		int32 NextLevelExperience = ExperienceThreshold.IsValidIndex(CurrentLevel) ? ExperienceThreshold[CurrentLevel] : 0;

		int32 RewardBonus = FMath::RoundToInt(ExperienceRewardBonus + (CurrentLevel * 2) + (NextLevelExperience / 100.f));

		return RewardBonus;
	}

	// Getter for maximum level
	void SetExperience(float InExperience)
	{
		Experience = FMath::Max(0.f, InExperience);

		int32 CurrentLevelIndex = Level - 1;
		float ExperienceToNextLevel = 0.f;

		if (ExperienceThreshold.IsValidIndex(CurrentLevelIndex))
		{
			ExperienceToNextLevel = ExperienceThreshold[CurrentLevelIndex];
		}
	}

	// Setter for experience thresholds
	void SetExperienceThreshold(const TArray<float>& InThreshold)
	{
		ExperienceThreshold = InThreshold;
	}

	// Setter for maximum level
	void SetLevel(int32 InLevel)
	{
		Level = FMath::Clamp(InLevel, 1, MaxLevel);
	}

	// Setter for maximum level
	void SetMaxLevel(int32 InMaxLevel)
	{
		MaxLevel = InMaxLevel;
	}

	// Setter for experience reward bonus
	void SetExperienceRewardBonus(float InBonus)
	{
		ExperienceRewardBonus = InBonus;
	}

	// Increase Experience
	void IncreaseExperience(float Amount)
	{
		if (Amount <= 0.f || Level >= MaxLevel)
		{
			return;
		}

		SetExperience(Experience + Amount);

		while (Level < MaxLevel)
		{
			const int32 ThresholdIndex = Level - 1;

			if (!ExperienceThreshold.IsValidIndex(ThresholdIndex))
			{
				break;
			}

			const float RequiredXP = ExperienceThreshold[ThresholdIndex];

			if (Experience < RequiredXP)
			{
				break;
			}

			// Consume XP required for this level
			SetExperience(Experience - RequiredXP);

			// Level up
			SetLevel(Level + 1);
		}
	}

	// Decrease Experience
	void DecreaseExperience(float Amount)
	{
		SetExperience(FMath::Max(0.f, Experience - Amount));
	}

	// Level Up
	void LevelUp()
	{
		if (Level < MaxLevel)
		{
			int32 NextLevel = Level + 1;
			SetLevel(NextLevel);
		}
	}
};

#pragma endregion



#pragma region Level

public:
	// Level management functions can be added here
	UFUNCTION(BlueprintCallable, Category = "Level")
	FLevelData& GetLevelData();

	// Returns the current experience
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetCurrentExperience();

	// Returns the experience threshold for the next level
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetNextLevelExperienceThreshold();

	// Returns the current level
	UFUNCTION(BlueprintCallable, Category = "Level")
	int32 GetLevel();

	// Returns the maximum level
	UFUNCTION(BlueprintCallable, Category = "Level")
	int32 GetMaxLevel();

	// Returns the experience reward bonus
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetExperienceRewardBonus();

#pragma endregion


#pragma region Level

public:
	// Level management functions can be added here
	UFUNCTION(BlueprintCallable, Category = "Level")
	FLevelData& GetLevelData();

	// Returns the current experience
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetCurrentExperience();

	// Returns the experience threshold for the next level
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetNextLevelExperienceThreshold();

	// Returns the current level
	UFUNCTION(BlueprintCallable, Category = "Level")
	int32 GetLevel();

	// Returns the maximum level
	UFUNCTION(BlueprintCallable, Category = "Level")
	int32 GetMaxLevel();

	// Returns the experience reward bonus
	UFUNCTION(BlueprintCallable, Category = "Level")
	float GetExperienceRewardBonus();

	// Increase Experience
	UFUNCTION(BlueprintCallable, Category = "Level")
	void AddExperience(float Amount);

	// Level Up Function
	UFUNCTION(BlueprintCallable, Category = "Level")
	void LevelUp();

#pragma endregion




