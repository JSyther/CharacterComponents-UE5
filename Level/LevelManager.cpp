#pragma region Level 

FCharacterLevelData& ULevelManager::GetLevelData()
{

	return LevelData.GetLevelData();
}

float ULevelManager::GetCurrentExperience()
{
	return LevelData.GetLevelData().GetExperience();
}

float ULevelManager::GetNextLevelExperienceThreshold()
{
	int32 CurrentLevel = CharacterData.GetLevelData().GetLevel();

	return LevelData.GetLevelData().GetExperienceThreshold()[CurrentLevel];
}

int32 ULevelManager::GetLevel()
{
	return LevelData.GetLevelData().GetLevel();
}

int32 ULevelManager::GetMaxLevel()
{
	return LevelData.GetLevelData().GetMaxLevel();
}

float ULevelManager::GetExperienceRewardBonus()
{
	return LevelData.GetLevelData().GetExperienceRewardBonus();
}

void ULevelManager::AddExperience(float Amount)
{
	if(Amount <= 0.f)
	{
		return;
	}

	// Current level and max level
	int32 CurrentLevel = LevelData.GetLevelData().GetLevel();
	const int32 MaxLevel = LevelData.GetLevelData().GetMaxLevel();

	// Current experience and experience thresholds
	float CurrentExperience = LevelData.GetLevelData().GetExperience();
	const TArray<float>& ExperienceThresholds = LevelData.GetLevelData().GetExperienceThreshold();

	// Validate experience thresholds
	if(!ExperienceThresholds.IsValidIndex(CurrentLevel))
	{
		#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("AddExperience: Experience thresholds not properly configured."));
		#endif
		return;
	}

	// Remaining experience to process
	float RemainingExperience = Amount;

	// Loop to handle multiple level-ups if enough experience is provided
	while (RemainingExperience > 0.0f && CurrentLevel < MaxLevel)
	{
		const float RequiredXP = ExperienceThresholds[CurrentLevel];
		const float ExperienceToLevelUp = RequiredXP - CurrentExperience;	

		// Enough XP to level up 
		if (RemainingExperience >= ExperienceToLevelUp)
		{
			RemainingExperience -= ExperienceToLevelUp;
			CurrentExperience = 0.0f;

			LevelUp(); // single level increment
			CurrentLevel = CharacterData.GetLevelData().GetLevel();

			// Max level reached after level up 
			if (CurrentLevel >= MaxLevel)
			{
				CurrentExperience = 0.0f;
				RemainingExperience = 0.0f;
				break;
			}
		}
		else
		{
			// Not enough XP to level up, just add the remaining experience
			CurrentExperience += RemainingExperience;
			RemainingExperience = 0.0f;
		}
	}
}

void ULevelManager::LevelUp()
{
	// Increment level by 1 if not at max level
	// Get current and max level
	int32 CurrentLevel = LevelData.GetLevelData().GetLevel();
	int32 MaxLevel = LevelData.GetLevelData().GetMaxLevel();

	// Level up if not at max level
	if (CurrentLevel < MaxLevel)
	{
		LevelData.GetLevelData().SetLevel(CurrentLevel + 1);
	}
	else
	{
		#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("LevelUp: Character has reached maximum level already."));
		#endif
	}
}

#pragma endregion
