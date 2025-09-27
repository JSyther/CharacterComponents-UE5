// Copyright © 2025 Reverse-A. All Rights Reserved.

#pragma once

#include "DevelopmentUtility/DiagnosticSystem.h"
#include "GameplayFramework/Technology/TechTierData.h"
#include "AbilityData.generated.h"

#pragma region AbilityModule

#pragma region State

UENUM(BlueprintType)
enum class EAbilityState : uint8
{
	Locked   UMETA(DisplayName = "Locked"),
	Unlocked UMETA(DisplayName = "Unlocked")
};

#pragma endregion

#pragma region Delegates

// Broadcasts when the ability's internal state (e.g., Locked, Active, Inactive) changes.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityStateChanged, EAbilityState, NewState);

// Broadcasts when the tech tier of the ability changes (e.g., from Tier1 to Tier2).
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTechTierChanged, ETechTier, NewTier);

// Broadcasts when the current point value of the ability changes (i.e., spent or earned points).
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPointChanged, int32, NewPoint);

// Broadcasts when the maximum allowed point limit for the ability is modified.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxPointChanged, int32, NewMaxPoint);

// Broadcasts when the number of points allocated to the ability changes from the global pool.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllocatedPointChanged, int32, NewAllocatedPoint);

// Broadcasts when the number of reset points (e.g., available refunds or respecs) changes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResetPointChanged, int32, NewResetPoint);

// Broadcasts when the credit value required to upgrade the current tech tier is modified.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradeCreditValueChanged, float, NewValue);

// Broadcasts when the credit value required to downgrade from the current tech tier is modified.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDowngradeCreditValueChanged, float, NewValue);


#pragma endregion

#pragma region Structure

USTRUCT(BlueprintType)
struct FAbilityModule
{
    GENERATED_BODY()

#pragma region DataEntry

private:
    // Current unlock state of the ability (e.g., Locked, Unlocked, Active).
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    EAbilityState AbilityState;

    // Current technology tier of the ability.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    ETechTier TechTier;

    // Number of active (used) points on this ability.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    uint8 Point;

    // Maximum number of points this ability can hold.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    uint8 MaxPoint;

    // Number of points allocated from the character's pool to this ability.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    uint8 AllocatedPoint;

    // Points to be refunded after a reset; snapshot of AllocatedPoint.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    uint8 ResetPoint;

    // Mapping of upgrade credit costs per tech tier level.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    TMap<ETechTier, float> UpgradeCreditCosts;

    // Mapping of downgrade credit costs per tech tier level.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    TMap<ETechTier, float> DowngradeCreditCosts;

#pragma endregion

#pragma region Delegate

public:

    // Called when ability state (Locked/Unlocked/etc.) changes.
    UPROPERTY(BlueprintAssignable)
    FOnAbilityStateChanged OnAbilityStateChanged;

    // Called when the tech tier of the ability changes.
    UPROPERTY(BlueprintAssignable)
    FOnTechTierChanged OnTechTierChanged;

    // Called when the current ability point value changes.
    UPROPERTY(BlueprintAssignable)
    FOnPointChanged OnPointChanged;

    // Called when the maximum point value for the ability changes.
    UPROPERTY(BlueprintAssignable)
    FOnMaxPointChanged OnMaxPointChanged;

    // Called when allocated points are modified.
    UPROPERTY(BlueprintAssignable)
    FOnAllocatedPointChanged OnAllocatedPointChanged;

    // Called when reset points (used for refunds) are updated.
    UPROPERTY(BlueprintAssignable)
    FOnResetPointChanged OnResetPointChanged;

    // Called when the upgrade credit value for the current tier changes.
    UPROPERTY(BlueprintAssignable)
    FOnUpgradeCreditValueChanged OnUpgradeCreditValueChanged;

    // Called when the downgrade credit value for the current tier changes.
    UPROPERTY(BlueprintAssignable)
    FOnDowngradeCreditValueChanged OnDowngradeCreditValueChanged;

#pragma endregion

#pragma region Constructor

public:

    // Default constructor initializing ability module with default values.
    FAbilityModule()
    : AbilityState(EAbilityState::Locked)
    , TechTier(ETechTier::Null)
    , Point(0)
    , MaxPoint(10)
    , AllocatedPoint(0)
    , ResetPoint(0)
    , UpgradeCreditCosts()
    , DowngradeCreditCosts()
    {   }

#pragma endregion

#pragma region Accessor

    // Retrieves the current ability state.
    EAbilityState GetAbilityState() const
    {
        // Return the current ability state
        return AbilityState;
    }

    // Retrieves the technology tier classification of this ability.
    ETechTier GetTechTier() const
    {
        // Return the current tech tier
        return TechTier;
    }

    // Retrieves the current points allocated to this ability.
    int8 GetPoint() const
    {
        // Return the current points
        return Point;
    }

    // Retrieves the maximum possible points for this ability.
    int8 GetMaxPoint() const
    {
        // Return the maximum possible points
        return MaxPoint;
    }

    // Retrieves the allocated points for this ability.
    int8 GetAllocatedPoint() const
    {
        // Return the allocated points
        return AllocatedPoint;
    }

    // Retrieves the stored reset point value to return or refund to the character.
    int8 GetResetPoint() const
    {
        return ResetPoint;
    }

    // Returns the whole map Upgrade Credits map
    const TMap<ETechTier, float>& GetUpgradeCredits() const
    {
        return UpgradeCreditCosts;
    }

    // Returns upgrade cost for a specific tech tier; logs error if not found.
    float GetUpgradeCreditByKey(ETechTier Key) const
    {
        if (!UpgradeCreditCosts.Contains(Key))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("UpgradeCreditCost does not contain the key.");
            #endif

            return 0.0f;
        }


        #if DEV_DEBUG_MODE
        UE_LOG
        (
            LogTemp,
            Log,
            TEXT("Returning cost %.2f for key '%s'."), UpgradeCreditCosts[Key], *UEnum::GetValueAsString(Key)
        );
        #endif

        return UpgradeCreditCosts[Key];
    }

    // Returns the cost required to upgrade from the current tech tier.
    float RequiredUpgradeCredits() const
    {
        // Check if the UpgradeCreditCost map is empty
        if (UpgradeCreditCosts.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("UpgradeCreditCost map is empty.");
            #endif

            return 0.0f;
        }

        // Check if the current TechTier exists in the map
        if (!UpgradeCreditCosts.Contains(TechTier))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("UpgradeCreditCost does not contain the current TechTier key.");
            #endif

            return 0.0f;
        }

        return UpgradeCreditCosts[TechTier];
    }

    // Returns the entire Downgrade Credits map
    const TMap<ETechTier, float>& GetDowngradeCredits() const
    {
        return DowngradeCreditCosts;
    }

    // Returns downgrade cost for a specific tech tier; logs error if key is not found.
    float GetDowngradeCreditByKey(ETechTier Key) const
    {
        if (!DowngradeCreditCosts.Contains(Key))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("DowngradeCreditsCost does not contain the key.");
            #endif

            return 0.0f;
        }

        #if DEV_DEBUG_MODE
        UE_LOG
        (
            LogTemp,
            Log,
            TEXT("Returning downgrade cost %.2f for key '%s'."),
            DowngradeCreditCosts[Key],
            *UEnum::GetValueAsString(Key)
        );
        #endif

        return DowngradeCreditCosts[Key];
    }

    // Returns the cost required to downgrade from the current tech tier.
    float RequiredDowngradeCredits() const
    {
        // Check if the DowngradeCreditsCost map is empty
        if (DowngradeCreditCosts.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("DowngradeCreditsCost map is empty.");
            #endif

            return 0.0f;
        }

        // Check if the current TechTier exists in the map
        if (!DowngradeCreditCosts.Contains(TechTier))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("DowngradeCreditsCost does not contain the current TechTier key.");
            #endif

            return 0.0f;
        }

        return DowngradeCreditCosts[TechTier];
    }

#pragma endregion

#pragma region Mutator

    // Sets the ability state to a new value and broadcasts change if different.
    void SetAbilityState(EAbilityState NewState)
    {
        // Update the ability state to the new value
        AbilityState = NewState;

        // Broadcast the state change to any bound listeners
        OnAbilityStateChanged.Broadcast(AbilityState);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("AbilityState set to %s and broadcasted."), *UEnum::GetValueAsString(AbilityState));
        #endif
    }

    // Sets the technology tier to a new value and broadcasts change if different.
    void SetTechTier(ETechTier NewTechTier)
    {
        // Update the tech tier to the new value
        TechTier = NewTechTier;

        // Broadcast the tech tier change to any bound listeners
        OnTechTierChanged.Broadcast(TechTier);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("TechTier set to %s and broadcasted."), *UEnum::GetValueAsString(TechTier));
        #endif
    }

    // Sets the current points to a new value within valid range and broadcasts change.
    void SetPoint(int8 NewPoint)
    {
        // Update the points to the new value
        Point = NewPoint;

        // Broadcast the points change to any bound listeners
        OnPointChanged.Broadcast(Point);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("Point set to %d and broadcasted."), Point);
        #endif
    }

    // Sets the maximum possible points to a new value and broadcasts the change.
    void SetMaxPoint(int8 NewMaxPoint)
    {
        // Update the max points to the new value
        MaxPoint = NewMaxPoint;

        // Broadcast the max points change to any bound listeners
        OnMaxPointChanged.Broadcast(MaxPoint);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("MaxPoints set to %d and broadcasted."), MaxPoint);
        #endif
    }

    // Sets the allocated points to a new value and broadcasts the change.
    void SetAllocatedPoint(int8 NewAllocatedPoint)
    {
        // Update the allocated points to the new value
        AllocatedPoint = NewAllocatedPoint;

        // Broadcast the allocated points change to any bound listeners
        OnAllocatedPointChanged.Broadcast(AllocatedPoint);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("AllocatedPoint set to %d and broadcasted."), AllocatedPoint);
        #endif
    }

    // Sets the reset point to a new value and broadcasts the change.
    void SetResetPoint(int8 NewResetPoint)
    {
        // Update the reset point to the new value 
        ResetPoint = NewResetPoint;

        // Broadcast the reset point change to any bound listeners
        OnResetPointChanged.Broadcast(ResetPoint);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("ResetPoint set to %d and broadcasted."), ResetPoint);
        #endif
    }

    // Sets the UpgradeCreditCost map to the provided new values.
    void SetUpgradeCredits(const TMap<ETechTier, float>& NewUpgradeCost)
    {
        UpgradeCreditCosts = NewUpgradeCost;


        #if DEV_DEBUG_MODE
        LOG_INFO("UpgradeCreditCost have been updated and broadcasted.");
        #endif
    }

    // Updates the credit value for an existing tech tier key only if the new value differs.
    void SetUpgradeCreditByKey(ETechTier Key, float CreditValue)
    {
        if (!UpgradeCreditCosts.Contains(Key))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set value for non-existent key.");
            #endif

            return;
        }

        if (FMath::IsNearlyEqual(UpgradeCreditCosts[Key], CreditValue))
        {
            #if DEV_DEBUG_MODE
            LOG_INFO("Value is unchanged. No update needed.");
            #endif

            return;
        }

        UpgradeCreditCosts[Key] = CreditValue;

        OnUpgradeCreditValueChanged.Broadcast(UpgradeCreditCosts[Key]);

        #if DEV_DEBUG_MODE
        UE_LOG
        (
            LogTemp,
            Log,
            TEXT("SetUpgradeCreditByKey: Updated credit to %.2f for key '%s'."), CreditValue, *UEnum::GetValueAsString(Key)
        );
        #endif
    }

    // Sets the DowngradeCreditsCost map to the provided new values.
    void SetDowngradeCredits(const TMap<ETechTier, float>& NewDowngradeCredits)
    {
        UpgradeCreditCosts = NewDowngradeCredits;


        #if DEV_DEBUG_MODE
        LOG_INFO("DowngradeCreditsCost has been updated and broadcasted.");
        #endif
    }

    // Updates the downgrade credit value for an existing tech tier key only if the new value differs.
    void SetDowngradeCreditByKey(ETechTier Key, float CreditValue)
    {
        if (!DowngradeCreditCosts.Contains(Key))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set downgrade value for a non-existent key.");
            #endif

            return;
        }

        if (FMath::IsNearlyEqual(DowngradeCreditCosts[Key], CreditValue))
        {
            #if DEV_DEBUG_MODE
            LOG_INFO("Downgrade value is unchanged. No update needed.");
            #endif

            return;
        }

        DowngradeCreditCosts[Key] = CreditValue;

        OnDowngradeCreditValueChanged.Broadcast(DowngradeCreditCosts[Key]);

        #if DEV_DEBUG_MODE
        UE_LOG
        (
            LogTemp,
            Log,
            TEXT("SetDowngradeCreditByKey: Updated downgrade credit to %.2f for key '%s'."),
            CreditValue,
            *UEnum::GetValueAsString(Key)
        );
        #endif
    }


#pragma endregion

#pragma region Lock/Unlock

    // Unlocks the ability by resetting its state and tech tier to default unlocked values.
    void UnlockAbility()
    {
        SetTechTier(ETechTier::Primitive);
        SetAbilityState(EAbilityState::Unlocked);
    }

    // Locks the ability by resetting its state and tech tier to default locked values.
    void LockAbility()
    {
        SetTechTier(ETechTier::Null);
        SetAbilityState(EAbilityState::Unlocked);
    }

    // Returns true if the ability is locked (TechTier is Null and state is Locked).
    bool AbilityLocked() const
    {
        return Point == 0 && AbilityState == EAbilityState::Locked && TechTier == ETechTier::Null;
    }

    // Returns true if the ability is unlocked (TechTier is above Null and state is Unlocked).
    bool AbilityUnLocked() const
    {
        return AbilityState == EAbilityState::Unlocked && TechTier > ETechTier::Null;
    }


#pragma endregion

#pragma region Reset

    // Resets points and allocated points to 0 and broadcasts the changes.
    void Reset()
    {
        // Reset points to 0
        SetPoint(0);

        // Store the current allocated points into ResetPoint before resetting
        SetResetPoint(AllocatedPoint);

        // Reset allocated points to 0
        SetAllocatedPoint(0);

        // Reset tech tier to Null (default state)
        SetTechTier(ETechTier::Null);

        // Reset ability state to Locked (default state)
        SetAbilityState(EAbilityState::Locked);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("Ability reset: Points, AllocatedPoints, TechTier, and State have been reset to default."));
        #endif
    }


#pragma endregion

#pragma region Increase/Decrease

    // Increases the current points by 1, ensuring it does not exceed MaxPoint or maximum TechTier.
    void IncreasePoint()
    {
        // Prevent increasing points if TechTier has reached or exceeded the maximum allowed tier (Quantum).
        if (TechTier >= ETechTier::Quantum)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("Cannot increase point: TechTier is already at or above the maximum allowed (Quantum).");
            #endif

            return;
        }

        // Prevent increasing points if current points have reached the maximum allowed points.
        if (Point >= MaxPoint)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("Cannot increase point: Current Point has reached MaxPoint.");
            #endif

            return;
        }

        // Automatically unlock the ability if it is currently locked.
        if (AbilityLocked())
        {
            UnlockAbility();

            #if DEV_DEBUG_MODE
            LOG_INFO("Ability was locked. Auto-unlocked before increasing point.");
            #endif
        }

        // Increase the point by 1 and apply the new value.
        int8 NewPoint = Point + 1;
        SetPoint(NewPoint);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("Point increased to %d."), NewPoint);
        #endif
    }


    // Decreases the current points by 1, ensuring it does not go below valid limits.
    void DecreasePoint()
    {
        if (TechTier <= ETechTier::Null || Point == 0)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("");
            #endif

            return;
        }

        // Prevent decrease if tech tier is above Primitive and point is at its minimum valid value (1)
        if (TechTier > ETechTier::Primitive && Point == 1)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Cannot decrease point below current tech tier downgrade (de-rank) required first.");
            #endif

            // TODO UI warning
            return;
        }

        // Calculate the new point value after decrement
        int8 NewPoint = Point - 1;

        // Update the point to the new value
        SetPoint(NewPoint);

        // If tech tier is Primitive and points have reached 0, lock the ability
        if (TechTier == ETechTier::Primitive && NewPoint == 0)
        {
            if (AbilityUnLocked())
            {
                LockAbility();

                #if DEV_DEBUG_MODE
                LOG_INFO("Ability locked as points decreased to 0 on Primitive tier.");
                #endif
            }
        }
    }

#pragma endregion

#pragma region Upgrade/Downgrade

    // Attempts to upgrade the tech tier if sufficient credit and conditions are met.
    void Upgrade(float InCredit)
    {
        // Block upgrade if already at max tier or ability is locked.
        if (TechTier >= ETechTier::Quantum || AbilityState == EAbilityState::Locked)
        {
            #if DEV_DEBUG_MODE
            UE_LOG
            (
                LogTemp,
                Error,
                TEXT("Cannot upgrade: Either already at max tech tier (Quantum) or ability is locked.")
            );
            #endif

            return;
        }

        if (Point < MaxPoint)
        {
            #if DEV_DEBUG_MODE 
            LOG_ERROR("Cannot upgrade: Ability point needs to be max point.");
            #endif

            return;
        }

        // Block upgrade if not enough credits are available.
        if (InCredit < RequiredUpgradeCredits())
        {
            #if DEV_DEBUG_MODE
            UE_LOG
            (
                LogTemp,
                Error,
                TEXT("Cannot upgrade: Insufficient credits. Required: %.2f, Provided: %.2f."),
                RequiredUpgradeCredits(),
                InCredit
            );
            #endif

            return;
        }

        // Upgrade to the next tech tier.
        ETechTier NextTechTier = static_cast<ETechTier>(static_cast<uint8>(TechTier) + 1);
        SetTechTier(NextTechTier);

        // Reset internal upgrade points after tier upgrade.
        SetPoint(0);

        // Log successful upgrade in dev mode.
        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("Tech tier upgraded to %s."), *UEnum::GetValueAsString(NextTechTier));
        #endif
    }


    // Attempts to downgrade the tech tier if sufficient credit and conditions are met.
    void Downgrade(float InCredit)
    {
        // If current tier is already locked/null, downgrade is invalid.
        if (TechTier == ETechTier::Null)
        {
            #if DEV_DEBUG_MODE
                UE_LOG( LogTemp, Warning, TEXT("Cannot downgrade: Ability is already locked (TechTier is Null)."));
            #endif

            return;
        }

        // Downgrade is not allowed if ability still has remaining points.
        if (Point > 0)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Cannot downgrade: Ability still has unspent points.");
            #endif
            return;
        }

        // If the ability is locked, we should not allow downgrade.
        if (AbilityLocked())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Cannot downgrade: Ability is currently locked.");
            #endif

            return;
        }

        // Prevent downgrade if insufficient downgrade credits.
        if (InCredit < RequiredDowngradeCredits())
        {
            #if DEV_DEBUG_MODE
            UE_LOG(
                LogTemp,
                Error,
                TEXT("Cannot downgrade: Insufficient credits. Required: %.2f, Provided: %.2f."),
                RequiredDowngradeCredits(),
                InCredit
            );
            #endif

            return;
        }

        // Determine the previous tier by decrementing current tier
        ETechTier PrevTechTier = static_cast<ETechTier>(static_cast<uint8>(TechTier) - 1);

        // If we've reached or gone below the null tier, lock the ability.
        if (PrevTechTier <= ETechTier::Null)
        {
            LockAbility();

            #if DEV_DEBUG_MODE
            LOG_ERROR("Downgrade reached lowest tier: Ability has been locked.");
            #endif

            return;
        }

        // Apply downgrade: update tech tier and reset points.
        SetTechTier(PrevTechTier);
        SetPoint(MaxPoint);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("Tech tier downgraded successfully to %s."), *UEnum::GetValueAsString(PrevTechTier));
        #endif
    }


#pragma endregion

};

#pragma endregion

#pragma endregion

#pragma region MovementAbility

UENUM(BlueprintType)
enum class EMovementAbilityType : uint8
{
    Null                          UMETA(DisplayName = "Select Mobility Ability Type"),
    Sprint                        UMETA(DisplayName = "Velocity Surge"),
    Jump                          UMETA(DisplayName = "Apex Bound"),
    DoubleJump                    UMETA(DisplayName = "Aerial Rebound"),
    CoyoteJump                    UMETA(DisplayName = "Second Wind"),
    Crouch                        UMETA(DisplayName = "Shadow Veil"),
    Prone                         UMETA(DisplayName = "Silent Crawl"),
    Roll                          UMETA(DisplayName = "Evasive Tumble"),
    Slide                         UMETA(DisplayName = "Swift Evasion Maneuver"),
    WallRun                       UMETA(DisplayName = "Vertical Chase"),
    VerticalWallRun               UMETA(DisplayName = "Skyward Ascent"),
    Hang                          UMETA(DisplayName = "Stealthy Lurk"),
    Dash                          UMETA(DisplayName = "Flash Surge"),
    Teleport                      UMETA(DisplayName = "Dimensional Drift"),
    Vault                         UMETA(DisplayName = "Seamless Overpass"),
    Mantle                        UMETA(DisplayName = "Ledge Grace"),
    Glide                         UMETA(DisplayName = "Wind's Embrace"),
    Swim                          UMETA(DisplayName = "Aquatic Flow"),
    Dive                          UMETA(DisplayName = "Abyssal Descent"),
    Hover                         UMETA(DisplayName = "Suspended Serenity"),
    Fly                           UMETA(DisplayName = "Skyborne Precision"),
    Max                           UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FMovementAbility
{
    GENERATED_BODY()

private:
    // Map holding individual movement abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    TMap<EMovementAbilityType, FAbilityModule> MovementAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FMovementAbility()
    : MovementAbilities()
    {
        // Initialize each movement type with a default ability module.
        for (uint8 i = static_cast<uint8>(EMovementAbilityType::Null) + 1; i < static_cast<uint8>(EMovementAbilityType::Max); i++)
        {
            EMovementAbilityType Type = static_cast<EMovementAbilityType>(i);
            MovementAbilities.Add(Type, FAbilityModule());
        }
    }


    bool operator==(FMovementAbility& Other) const
    {
        return AreMapsEqual(MovementAbilities, Other.MovementAbilities);
    }

    bool operator!=(FMovementAbility& Other) const
    {
        return !(*this == Other);
    }


    // Getter to access and modify MobilityAbilities
    TMap<EMovementAbilityType, FAbilityModule>& GetAbilities()
    {
        return MovementAbilities;
    }

    // Const getter for movement abilities.
    const TMap<EMovementAbilityType, FAbilityModule>& GetAbilities() const
    {
        return MovementAbilities;
    }

    // Setter to replace the entire MobilityAbilities map
    void SetAbilities(const TMap<EMovementAbilityType, FAbilityModule>& NewAbilities)
    {
        MovementAbilities = NewAbilities;
    }

    // Checks if the given movement type is valid and present in the ability map.
    bool ValidateAbilityByType(EMovementAbilityType Type) const
    {
        if (MovementAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: MovementAbilities map is empty.");
            #endif
            return false;
        }

        if (!MovementAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in MovementAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in MovementAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given movement type.
    void ResetAbilityByType(EMovementAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MovementAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given movement ability type.
    void IncreaseAbilityByType(EMovementAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MovementAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given movement ability type.
    void DecreaseAbilityByType(EMovementAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MovementAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified movement ability using provided credit.
    void UpgradeAbilityByType(EMovementAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MovementAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified movement ability using provided credit.
    void DowngradeAbilityByType(EMovementAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MovementAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }

};

#pragma endregion    

#pragma region MartialAbility

UENUM(BlueprintType)
enum class EMartialAbilityType : uint8
{
    Null                      UMETA(DisplayName = "Select Martial Ability"),
    ViperStrike               UMETA(DisplayName = "Viper Strike"),
    CycloneSpiralKick         UMETA(DisplayName = "Cyclone Spiral Kick"),
    ThunderousLegSweep        UMETA(DisplayName = "Thunderous Leg Sweep"),
    PhantomFootwork           UMETA(DisplayName = "Phantom Footwork"),
    DragonFist                UMETA(DisplayName = "Dragon Fist"),
    SerpentTwist              UMETA(DisplayName = "Serpent Twist"),
    PhoenixRising             UMETA(DisplayName = "Phoenix Rising"),
    ShadowStep                UMETA(DisplayName = "Shadow Step"),
    IronClawGrapple           UMETA(DisplayName = "Iron Claw Grapple"),
    MirageKick                UMETA(DisplayName = "Mirage Kick"),
    TempestCombo              UMETA(DisplayName = "Tempest Combo"),
    BerserkerCharge           UMETA(DisplayName = "Berserker Charge"),
    CelestialDancer           UMETA(DisplayName = "Celestial Dancer"),
    TitanSlam                 UMETA(DisplayName = "Titan Slam"),
    Max                       UMETA(Hidden)
}; 

USTRUCT(BlueprintType)
struct FMartialAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual martial abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<EMartialAbilityType, FAbilityModule> MartialAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FMartialAbility()
    : MartialAbilities()
    {
        // Initialize each martial type with a default ability module.
        for (uint8 i = static_cast<uint8>(EMartialAbilityType::Null) + 1; i < static_cast<uint8>(EMartialAbilityType::Max); i++)
        {
            EMartialAbilityType Type = static_cast<EMartialAbilityType>(i);
            MartialAbilities.Add(Type, FAbilityModule());
        }
    }


    bool operator==(FMartialAbility& Other) const
    {
        return AreMapsEqual(MartialAbilities, Other.MartialAbilities);
    }

    bool operator!=(FMartialAbility& Other) const
    {
        return !(*this == Other);
    }

    // Getter to access and modify MartialAbilities
    TMap<EMartialAbilityType, FAbilityModule>& GetAbilities()
    {
        return MartialAbilities;
    }

    // Const getter for martial abilities.
    const TMap<EMartialAbilityType, FAbilityModule>& GetAbilities() const
    {
        return MartialAbilities;
    }

    // Setter to replace the entire MartialAbilities map
    void SetAbilities(const TMap<EMartialAbilityType, FAbilityModule>& NewAbilities)
    {
        MartialAbilities = NewAbilities;
    }

    // Checks if the given martial ability type is valid and present in the ability map.
    bool ValidateAbilityByType(EMartialAbilityType Type) const
    {
        if (MartialAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: MartialAbilities map is empty.");
            #endif
            return false;
        }

        if (!MartialAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in MartialAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in MartialAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given martial ability type.
    void ResetAbilityByType(EMartialAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MartialAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given martial ability type.
    void IncreaseAbilityByKey(EMartialAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MartialAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given martial ability type.
    void DecreaseAbilityByType(EMartialAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MartialAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified martial ability using provided credit.
    void UpgradeAbilityByType(EMartialAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MartialAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified martial ability using provided credit.
    void DowngradeAbilityByType(EMartialAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MartialAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};

#pragma endregion      

#pragma region StealthAbility

UENUM(BlueprintType)
enum class EStealthAbilityType : uint8
{
    Null                     UMETA(DisplayName = "Select Stealth Ability"),
    Cloak                    UMETA(DisplayName = "Cloak"),
    SilentTakedown           UMETA(DisplayName = "Silent Takedown"),
    ShadowBlend              UMETA(DisplayName = "Shadow Blend"),
    StealthSprint            UMETA(DisplayName = "Stealth Sprint"),
    NoTrace                  UMETA(DisplayName = "No Trace"),
    SoundMaskingDevice       UMETA(DisplayName = "Sound Masking Device"),
    EMPShield                UMETA(DisplayName = "EMP Shield"),
    QuickEscape              UMETA(DisplayName = "Quick Escape"),
    InvisibilityCloak        UMETA(DisplayName = "Invisibility Cloak"),
    EnvironmentalCamouflage  UMETA(DisplayName = "Environmental Camouflage"),
    AcousticDampening        UMETA(DisplayName = "Acoustic Dampening"),
    PrecisionStrike          UMETA(DisplayName = "Precision Strike"),
    Max                      UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FStealthAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual stealth abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<EStealthAbilityType, FAbilityModule> StealthAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FStealthAbility()
    : StealthAbilities()
    {
        // Initialize each stealth type with a default ability module.
        for (uint8 i = static_cast<uint8>(EStealthAbilityType::Null) + 1; i < static_cast<uint8>(EStealthAbilityType::Max); i++)
        {
            EStealthAbilityType Type = static_cast<EStealthAbilityType>(i);
            StealthAbilities.Add(Type, FAbilityModule());
        }
    }

    // Getter to access and modify StealthAbilities
    TMap<EStealthAbilityType, FAbilityModule>& GetAbilities()
    {
        return StealthAbilities;
    }

    // Const getter for stealth abilities.
    const TMap<EStealthAbilityType, FAbilityModule>& GetAbilities() const
    {
        return StealthAbilities;
    }

    bool operator==(FStealthAbility& Other) const
    {
        return AreMapsEqual(StealthAbilities, Other.StealthAbilities);
    }

    bool operator!=(FStealthAbility& Other) const
    {
        return !(*this == Other);
    }

    // Setter to replace the entire StealthAbilities map
    void SetAbilities(const TMap<EStealthAbilityType, FAbilityModule>& NewAbilities)
    {
        StealthAbilities = NewAbilities;
    }

    // Checks if the given stealth ability type is valid and present in the ability map.
    bool ValidateAbilityByType(EStealthAbilityType Type) const
    {
        if (StealthAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: StealthAbilities map is empty.");
            #endif
            return false;
        }

        if (!StealthAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in StealthAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in StealthAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given stealth ability type.
    void ResetAbilityByType(EStealthAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = StealthAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given stealth ability type.
    void IncreaseAbilityByType(EStealthAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = StealthAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given stealth ability type.
    void DecreaseAbilityByType(EStealthAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = StealthAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified stealth ability using provided credit.
    void UpgradeAbilityByType(EStealthAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = StealthAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified stealth ability using provided credit.
    void DowngradeAbilityByType(EStealthAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = StealthAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};

#pragma endregion      

#pragma region CyberneticAbility

UENUM(BlueprintType)
enum class ECyberneticAbilityType : uint8
{
    Null                          UMETA(DisplayName = "Select Cybernetic Ability"),
    DataBreach                    UMETA(DisplayName = "Data Breach"),
    SignalJammer                  UMETA(DisplayName = "Signal Jammer"),
    RemoteOverride                UMETA(DisplayName = "Remote Override"),
    CodeInjection                 UMETA(DisplayName = "Code Injection"),
    CyberneticInterface           UMETA(DisplayName = "Cybernetic Interface"),
    FirewallBypass                UMETA(DisplayName = "Firewall Bypass"),
    SurveillanceDisable           UMETA(DisplayName = "Surveillance Disable"),
    AIManipulation                UMETA(DisplayName = "AI Manipulation"),
    NetworkSniffer                UMETA(DisplayName = "Network Sniffer"),
    DigitalGhost                  UMETA(DisplayName = "Digital Ghost"),
    EncryptionBreaker             UMETA(DisplayName = "Encryption Breaker"),
    RemoteSurveillance            UMETA(DisplayName = "Remote Surveillance"),
    DataMasking                   UMETA(DisplayName = "Data Masking"),
    BotnetControl                 UMETA(DisplayName = "Botnet Control"),
    TraceRoute                    UMETA(DisplayName = "Trace Route"),
    ProxyBypass                   UMETA(DisplayName = "Proxy Bypass"),
    MalwareDeployment             UMETA(DisplayName = "Malware Deployment"),
    DataCorruption                UMETA(DisplayName = "Data Corruption"),
    SocialEngineering             UMETA(DisplayName = "Social Engineering"),
    VehicleHacking                UMETA(DisplayName = "Vehicle Hacking"),
    DroneCommand                  UMETA(DisplayName = "Drone Command"),
    ExcavationSystemManipulation  UMETA(DisplayName = "Excavation System Manipulation"),
    TacticalDroneOverride         UMETA(DisplayName = "Tactical Drone Override"),
    RemoteVehicleAccess           UMETA(DisplayName = "Remote Vehicle Access"),
    AutomatedResourceGathering    UMETA(DisplayName = "Automated Resource Gathering"),
    ExplosiveDeviceHack           UMETA(DisplayName = "Explosive Device Hack"),
    NeuralOverride                UMETA(DisplayName = "Neural Override"),
    TacticalEMPStrike             UMETA(DisplayName = "Tactical EMP Strike"),
    DataExtractionProtocol        UMETA(DisplayName = "Data Extraction Protocol"),
    BiofeedbackManipulation       UMETA(DisplayName = "Biofeedback Manipulation"),
    Max                           UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FCyberneticAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual cybernetic abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<ECyberneticAbilityType, FAbilityModule> CyberneticAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FCyberneticAbility()
    : CyberneticAbilities()
    {
        // Initialize each cybernetic type with a default ability module.
        for (uint8 i = static_cast<uint8>(ECyberneticAbilityType::Null) + 1; i < static_cast<uint8>(ECyberneticAbilityType::Max); i++)
        {
            ECyberneticAbilityType Type = static_cast<ECyberneticAbilityType>(i);
            CyberneticAbilities.Add(Type, FAbilityModule());
        }
    }

    // Returns a modifiable reference to the CyberneticAbilities map.
    TMap<ECyberneticAbilityType, FAbilityModule>& GetAbilities()
    {
        return CyberneticAbilities;
    }

    // Const getter for cybernetic abilities.
    const TMap<ECyberneticAbilityType, FAbilityModule>& GetAbilities() const
    {
        return CyberneticAbilities;
    }

    bool operator==(FCyberneticAbility& Other) const
    {
        return AreMapsEqual(CyberneticAbilities, Other.CyberneticAbilities);
    }

    bool operator!=(FCyberneticAbility& Other) const
    {
        return !(*this == Other);
    }

    // Sets the entire CyberneticAbilities map with new values.
    void SetAbilities(const TMap<ECyberneticAbilityType, FAbilityModule>& NewAbilities)
    {
        CyberneticAbilities = NewAbilities;
    }

    // Checks if the given cybernetic ability type is valid and present in the ability map.
    bool ValidateAbilityByType(ECyberneticAbilityType Type) const
    {
        if (CyberneticAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: CyberneticAbilities map is empty.");
            #endif
            return false;
        }

        if (!CyberneticAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in CyberneticAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in CyberneticAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given cybernetic ability type.
    void ResetAbilityByType(ECyberneticAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = CyberneticAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given cybernetic ability type.
    void IncreaseAbilityByType(ECyberneticAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = CyberneticAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given cybernetic ability type.
    void DecreaseAbilityByType(ECyberneticAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = CyberneticAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified cybernetic ability using provided credit.
    void UpgradeAbilityByType(ECyberneticAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = CyberneticAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified cybernetic ability using provided credit.
    void DowngradeAbilityByType(ECyberneticAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = CyberneticAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};

#pragma endregion   

#pragma region SupportAbility

UENUM(BlueprintType)
enum class ESupportAbilityType : uint8
{
    Null                                  UMETA(DisplayName = "Select Support Ability"),
    AugmentedRealityTacticalInterface     UMETA(DisplayName = "Augmented Reality Tactical Interface"),
    AdaptiveCombatDroneDeployment         UMETA(DisplayName = "Adaptive Combat Drone Deployment"),
    AdvancedFieldMedicalSystems           UMETA(DisplayName = "Advanced Field Medical Systems"),
    TacticalResourceAllocationNetwork     UMETA(DisplayName = "Tactical Resource Allocation Network"),
    SmartEnvironmentalAnalysis            UMETA(DisplayName = "Smart Environmental Analysis"),
    TacticalHolographicProjection         UMETA(DisplayName = "Tactical Holographic Projection"),
    AutonomousSupplyDrop                  UMETA(DisplayName = "Autonomous Supply Drop"),
    CommunicationEnhancer                 UMETA(DisplayName = "Communication Enhancer"),
    PrecisionAirSupport                   UMETA(DisplayName = "Precision Air Support"),
    DynamicShieldingSystem                UMETA(DisplayName = "Dynamic Shielding System"),
    TacticalDataSynchronization           UMETA(DisplayName = "Tactical Data Synchronization"),
    RemoteSensorNetwork                   UMETA(DisplayName = "Remote Sensor Network"),
    BattlefieldAwarenessBoost             UMETA(DisplayName = "Battlefield Awareness Boost"),
    CollaborativeTacticalPlanning         UMETA(DisplayName = "Collaborative Tactical Planning"),
    MobileCommandCenter                   UMETA(DisplayName = "Mobile Command Center"),
    EnhancedTacticalAlgorithms            UMETA(DisplayName = "Enhanced Tactical Algorithms"),
    EnvironmentalShielding                UMETA(DisplayName = "Environmental Shielding"),
    HolographicDecoys                     UMETA(DisplayName = "Holographic Decoys"),
    ResourceGatheringAutomation           UMETA(DisplayName = "Resource Gathering Automation"),
    TacticalCommunicationRelay            UMETA(DisplayName = "Tactical Communication Relay"),
    NeuroAdaptiveTraining                 UMETA(DisplayName = "Neuro Adaptive Training"),
    CyberneticSupportFramework            UMETA(DisplayName = "Cybernetic Support Framework"),
    IntegratedSurveillanceNetwork         UMETA(DisplayName = "Integrated Surveillance Network"),
    InterdictionField                     UMETA(DisplayName = "Interdiction Field"),
    TacticalReinforcementSystem           UMETA(DisplayName = "Tactical Reinforcement System"),
    NanoMaterialResupply                  UMETA(DisplayName = "Nano Material Resupply"),
    BiometricThreatAssessment             UMETA(DisplayName = "Biometric Threat Assessment"),
    EnvironmentalAdaptationModule         UMETA(DisplayName = "Environmental Adaptation Module"),
    DecentralizedCommandProtocol          UMETA(DisplayName = "Decentralized Command Protocol"),
    ProximitySensorDeployment             UMETA(DisplayName = "Proximity Sensor Deployment"),
    RapidEvacuationProtocol               UMETA(DisplayName = "Rapid Evacuation Protocol"),
    TerrainManipulationSystem             UMETA(DisplayName = "Terrain Manipulation System"),
    ModularEquipmentUpgrade               UMETA(DisplayName = "Modular Equipment Upgrade"),
    Max                                   UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FSupportAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual support abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<ESupportAbilityType, FAbilityModule> SupportAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FSupportAbility()
    : SupportAbilities()
    {
        // Initialize each support type with a default ability module.
        for (uint8 i = static_cast<uint8>(ESupportAbilityType::Null) + 1; i < static_cast<uint8>(ESupportAbilityType::Max); i++)
        {
            ESupportAbilityType Type = static_cast<ESupportAbilityType>(i);
            SupportAbilities.Add(Type, FAbilityModule());
        }
    }

    // Returns a modifiable reference to the SupportAbilities map.
    TMap<ESupportAbilityType, FAbilityModule>& GetAbilities()
    {
        return SupportAbilities;
    }

    // Const getter for support abilities.
    const TMap<ESupportAbilityType, FAbilityModule>& GetAbilities() const
    {
        return SupportAbilities;
    }

    bool operator==(FSupportAbility& Other) const
    {
        return AreMapsEqual(SupportAbilities, Other.SupportAbilities);
    }

    bool operator!=(FSupportAbility& Other) const
    {
        return !(*this == Other);
    }

    // Sets the entire SupportAbilities map with new values.
    void SetAbilities(const TMap<ESupportAbilityType, FAbilityModule>& NewAbilities)
    {
        SupportAbilities = NewAbilities;
    }

    // Checks if the given support ability type is valid and present in the ability map.
    bool ValidateAbilityByType(ESupportAbilityType Type) const
    {
        if (SupportAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: SupportAbilities map is empty.");
            #endif
            return false;
        }

        if (!SupportAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in SupportAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in SupportAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given support ability type.
    void ResetAbilityByType(ESupportAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = SupportAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given support ability type.
    void IncreaseAbilityByType(ESupportAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = SupportAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given support ability type.
    void DecreaseAbilityByType(ESupportAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = SupportAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified support ability using provided credit.
    void UpgradeAbilityByType(ESupportAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = SupportAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified support ability using provided credit.
    void DowngradeAbilityByType(ESupportAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = SupportAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};

#pragma endregion     

#pragma region DefensiveAbility

UENUM(BlueprintType)
enum class EDefensiveAbilityType : uint8
{
    Null                                    UMETA(DisplayName = "Select Defensive Ability"),
    ReactiveArmorSystem                     UMETA(DisplayName = "Reactive Armor System"),
    EnergyDomeShield                        UMETA(DisplayName = "Energy Dome Shield"),
    CountermeasureDeployment                UMETA(DisplayName = "Countermeasure Deployment"),
    EnhancedEvasionProtocol                 UMETA(DisplayName = "Enhanced Evasion Protocol"),
    PersonalForceField                      UMETA(DisplayName = "Personal Force Field"),
    TacticalSmokeScreen                     UMETA(DisplayName = "Tactical Smoke Screen"),
    KineticBarrier                          UMETA(DisplayName = "Kinetic Barrier"),
    DamageAbsorptionMatrix                  UMETA(DisplayName = "Damage Absorption Matrix"),
    EnhancedTargetingCountermeasures        UMETA(DisplayName = "Enhanced Targeting Countermeasures"),
    ReflectiveArmor                         UMETA(DisplayName = "Reflective Armor"),
    EmergencyTeleportation                  UMETA(DisplayName = "Emergency Teleportation"),
    ReinforcedPositioning                   UMETA(DisplayName = "Reinforced Positioning"),
    TacticalBarrier                         UMETA(DisplayName = "Tactical Barrier"),
    AutoHealingShield                       UMETA(DisplayName = "Auto Healing Shield"),
    AreaDenialSystem                        UMETA(DisplayName = "Area Denial System"),
    ImpactReductionField                    UMETA(DisplayName = "Impact Reduction Field"),
    AdaptiveCamouflage                      UMETA(DisplayName = "Adaptive Camouflage"),
    DefensiveDroneFormation                 UMETA(DisplayName = "Defensive Drone Formation"),
    ShieldBash                              UMETA(DisplayName = "Shield Bash"),
    PerimeterDefenseSystem                  UMETA(DisplayName = "Perimeter Defense System"),
    EnhancedSituationalAwareness            UMETA(DisplayName = "Enhanced Situational Awareness"),
    TacticalRegrouping                      UMETA(DisplayName = "Tactical Regrouping"),
    Max                                     UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FDefensiveAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual defensive abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<EDefensiveAbilityType, FAbilityModule> DefensiveAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FDefensiveAbility()
        : DefensiveAbilities()
    {
        // Initialize each defensive type with a default ability module.
        for (uint8 i = static_cast<uint8>(EDefensiveAbilityType::Null) + 1; i < static_cast<uint8>(EDefensiveAbilityType::Max); i++)
        {
            EDefensiveAbilityType Type = static_cast<EDefensiveAbilityType>(i);
            DefensiveAbilities.Add(Type, FAbilityModule());
        }
    }

    // Returns a modifiable reference to the DefensiveAbilities map.
    TMap<EDefensiveAbilityType, FAbilityModule>& GetAbilities()
    {
        return DefensiveAbilities;
    }

    // Const getter for defensive abilities.
    const TMap<EDefensiveAbilityType, FAbilityModule>& GetAbilities() const
    {
        return DefensiveAbilities;
    }

    bool operator==(FDefensiveAbility& Other) const
    {
        return AreMapsEqual(DefensiveAbilities, Other.DefensiveAbilities);
    }

    bool operator!=(FDefensiveAbility& Other) const
    {
        return !(*this == Other);
    }

    // Sets the entire DefensiveAbilities map with new values.
    void SetAbilities(const TMap<EDefensiveAbilityType, FAbilityModule>& NewAbilities)
    {
        DefensiveAbilities = NewAbilities;
    }

    // Checks if the given defensive ability type is valid and present in the ability map.
    bool ValidateAbilityByType(EDefensiveAbilityType Type) const
    {
        if (DefensiveAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: DefensiveAbilities map is empty.");
            #endif
            return false;
        }

        if (!DefensiveAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in DefensiveAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in DefensiveAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given defensive ability type.
    void ResetAbilityByType(EDefensiveAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = DefensiveAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given defensive ability type.
    void IncreaseAbilityByType(EDefensiveAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = DefensiveAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given defensive ability type.
    void DecreaseAbilityByType(EDefensiveAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = DefensiveAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified defensive ability using provided credit.
    void UpgradeAbilityByType(EDefensiveAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = DefensiveAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified defensive ability using provided credit.
    void DowngradeAbilityByType(EDefensiveAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = DefensiveAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};

#pragma endregion    

#pragma region MarksmanAbility

UENUM(BlueprintType)
enum class EMarksmanAbilityType : uint8
{
    Null                                  UMETA(DisplayName = "Select Marksman Ability"),
    PrecisionAiming                       UMETA(DisplayName = "Precision Aiming"),
    LongRangeBallistics                   UMETA(DisplayName = "Long-Range Ballistics"),
    EnhancedScopeFunctionality            UMETA(DisplayName = "Enhanced Scope Functionality"),
    StealthMarking                        UMETA(DisplayName = "Stealth Marking"),
    SilenceRound                          UMETA(DisplayName = "Silence Round"),
    TargetAcquisitionSystem               UMETA(DisplayName = "Target Acquisition System"),
    CriticalHitMultiplier                 UMETA(DisplayName = "Critical Hit Multiplier"),
    BreachRound                           UMETA(DisplayName = "Breach Round"),
    WindAdjustmentModule                  UMETA(DisplayName = "Wind Adjustment Module"),
    TacticalRetreat                       UMETA(DisplayName = "Tactical Retreat"),
    PrecisionDrones                       UMETA(DisplayName = "Precision Drones"),
    MultiTargetFocus                      UMETA(DisplayName = "Multi-Target Focus"),
    LongRangeSustain                      UMETA(DisplayName = "Long Range Sustain"),
    EvasivePositioning                    UMETA(DisplayName = "Evasive Positioning"),
    ThermalVision                         UMETA(DisplayName = "Thermal Vision"),
    AdaptiveMarksman                      UMETA(DisplayName = "Adaptive Marksman"),
    SteadyBreath                          UMETA(DisplayName = "Steady Breath"),
    MarksmanshipTraining                  UMETA(DisplayName = "Marksmanship Training"),
    PrecisionStrike                       UMETA(DisplayName = "Precision Strike"),
    InfiltrationExpert                    UMETA(DisplayName = "Infiltration Expert"),
    Max                                   UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FMarksmanAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual marksman abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<EMarksmanAbilityType, FAbilityModule> MarksmanAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FMarksmanAbility()
    : MarksmanAbilities()
    {
        // Initialize each marksman type with a default ability module.
        for (uint8 i = static_cast<uint8>(EMarksmanAbilityType::Null) + 1; i < static_cast<uint8>(EMarksmanAbilityType::Max); i++)
        {
            EMarksmanAbilityType Type = static_cast<EMarksmanAbilityType>(i);
            MarksmanAbilities.Add(Type, FAbilityModule());
        }
    }

    // Returns a modifiable reference to the MarksmanAbilities map.
    TMap<EMarksmanAbilityType, FAbilityModule>& GetAbilities()
    {
        return MarksmanAbilities;
    }

    // Const getter for marksman abilities.
    const TMap<EMarksmanAbilityType, FAbilityModule>& GetAbilities() const
    {
        return MarksmanAbilities;
    }

    bool operator==(FMarksmanAbility& Other) const
    {
        return AreMapsEqual(MarksmanAbilities, Other.MarksmanAbilities);
    }

    bool operator!=(FMarksmanAbility& Other) const
    {
        return !(*this == Other);
    }

    // Sets the entire MarksmanAbilities map with new values.
    void SetAbilities(const TMap<EMarksmanAbilityType, FAbilityModule>& NewAbilities)
    {
        MarksmanAbilities = NewAbilities;
    }

    // Checks if the given marksman ability type is valid and present in the ability map.
    bool ValidateAbilityByType(EMarksmanAbilityType Type) const
    {
        if (MarksmanAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: MarksmanAbilities map is empty.");
            #endif
            return false;
        }

        if (!MarksmanAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in MarksmanAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in MarksmanAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given marksman ability type.
    void ResetAbilityByType(EMarksmanAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MarksmanAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given marksman ability type.
    void IncreaseAbilityByType(EMarksmanAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MarksmanAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given marksman ability type.
    void DecreaseAbilityByType(EMarksmanAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MarksmanAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified marksman ability using provided credit.
    void UpgradeAbilityByType(EMarksmanAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MarksmanAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified marksman ability using provided credit.
    void DowngradeAbilityByType(EMarksmanAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = MarksmanAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};


#pragma endregion

#pragma region ExplorationAbility

UENUM(BlueprintType)
enum class EExplorationAbilityType : uint8
{
    Null                        UMETA(DisplayName = "Select Exploration Abiltiy"),
    TerrainNavigator            UMETA(DisplayName = "Terrain Navigator"),
    CartographicInsight         UMETA(DisplayName = "Cartographic Insight"),
    EnvironmentalAwareness      UMETA(DisplayName = "Environmental Awareness"),
    StealthMovement             UMETA(DisplayName = "Stealth Movement"),
    SurvivalInstinct            UMETA(DisplayName = "Survival Instinct"),
    AnomalyDetector             UMETA(DisplayName = "Anomaly Detector"),
    AdaptiveScavenging          UMETA(DisplayName = "Adaptive Scavenging"),
    GeographicIntelligence      UMETA(DisplayName = "Geographic Intelligence"),
    EnhancedMobility            UMETA(DisplayName = "Enhanced Mobility"),
    PathfindingSpecialist       UMETA(DisplayName = "Pathfinding Specialist"),
    TerrainAlteration           UMETA(DisplayName = "Terrain Alteration"),
    EcoDetection                UMETA(DisplayName = "Eco-Detection"),
    HistoricalReconnaissance    UMETA(DisplayName = "Historical Reconnaissance"),
    BiomeExploration            UMETA(DisplayName = "Biome Exploration"),
    SignalAmplification         UMETA(DisplayName = "Signal Amplification"),
    UnderwaterNavigation        UMETA(DisplayName = "Underwater Navigation"),
    AstrobiologicalSurvey       UMETA(DisplayName = "Astrobiological Survey"),
    HazardousTerrainAwareness   UMETA(DisplayName = "Hazardous Terrain Awareness"),
    ResourceRecognition         UMETA(DisplayName = "Resource Recognition"),
    WildernessSurvival          UMETA(DisplayName = "Wilderness Survival"),
    CartographersPrecision      UMETA(DisplayName = "Cartographer's Precision"),
    AtmosphericAnalysis         UMETA(DisplayName = "Atmospheric Analysis"),
    Max                         UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FExplorationAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual exploration abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<EExplorationAbilityType, FAbilityModule> ExplorationAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FExplorationAbility()
    : ExplorationAbilities()
    {
        // Initialize each exploration type with a default ability module.
        for (uint8 i = static_cast<uint8>(EExplorationAbilityType::Null) + 1; i < static_cast<uint8>(EExplorationAbilityType::Max); i++)
        {
            EExplorationAbilityType Type = static_cast<EExplorationAbilityType>(i);
            ExplorationAbilities.Add(Type, FAbilityModule());
        }
    }

    // Returns a modifiable reference to the ExplorationAbilities map.
    TMap<EExplorationAbilityType, FAbilityModule>& GetAbilities()
    {
        return ExplorationAbilities;
    }

    // Const getter for exploration abilities.
    const TMap<EExplorationAbilityType, FAbilityModule>& GetAbilities() const
    {
        return ExplorationAbilities;
    }

    bool operator==(FExplorationAbility& Other) const
    {
        return AreMapsEqual(ExplorationAbilities, Other.ExplorationAbilities);
    }
     
    bool operator!=(FExplorationAbility& Other) const
    {
        return !(*this == Other);
    }

    // Sets the entire ExplorationAbilities map with new values.
    void SetAbilities(const TMap<EExplorationAbilityType, FAbilityModule>& NewAbilities)
    {
        ExplorationAbilities = NewAbilities;
    }

    // Checks if the given exploration ability type is valid and present in the ability map.
    bool ValidateAbilityByType(EExplorationAbilityType Type) const
    {
        if (ExplorationAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: ExplorationAbilities map is empty.");
            #endif
            return false;
        }

        if (!ExplorationAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in ExplorationAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in ExplorationAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given exploration ability type.
    void ResetAbilityByType(EExplorationAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExplorationAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given exploration ability type.
    void IncreaseAbilityByType(EExplorationAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExplorationAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given exploration ability type.
    void DecreaseAbilityByType(EExplorationAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExplorationAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified exploration ability using provided credit.
    void UpgradeAbilityByType(EExplorationAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExplorationAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified exploration ability using provided credit.
    void DowngradeAbilityByType(EExplorationAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExplorationAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};

#pragma endregion 

#pragma region ExcavationAbility

UENUM(BlueprintType)
enum class EExcavationAbilityType : uint8
{
    Null                           UMETA(DisplayName = "Select Excavation Ability"),
    PrecisionDigging               UMETA(DisplayName = "Precision Digging"),
    AdvancedSoilAnalysis           UMETA(DisplayName = "Advanced Soil Analysis"),
    ExcavationOptimization         UMETA(DisplayName = "Excavation Optimization"),
    ResourceIdentification         UMETA(DisplayName = "Resource Identification"),
    StructuralAssessment           UMETA(DisplayName = "Structural Assessment"),
    DeepEarthExploration           UMETA(DisplayName = "Deep Earth Exploration"),
    TerrainModification            UMETA(DisplayName = "Terrain Modification"),
    HazardousMaterialDetection     UMETA(DisplayName = "Hazardous Material Detection"),
    ManualExcavationExpertise      UMETA(DisplayName = "Manual Excavation Expertise"),
    AutomatedExcavationControl     UMETA(DisplayName = "Automated Excavation Control"),
    TrenchDesign                   UMETA(DisplayName = "Trench Design"),
    ArchaeologicalSurvey           UMETA(DisplayName = "Archaeological Survey"),
    LayeredExcavation              UMETA(DisplayName = "Layered Excavation"),
    GroundPenetratingRadarUse      UMETA(DisplayName = "Ground Penetrating Radar Use"),
    SiltAndSedimentManagement      UMETA(DisplayName = "Silt and Sediment Management"),
    EnvironmentalPreservation      UMETA(DisplayName = "Environmental Preservation"),
    ExcavationRiskAssessment       UMETA(DisplayName = "Excavation Risk Assessment"),
    AdaptiveExcavationStrategies   UMETA(DisplayName = "Adaptive Excavation Strategies"),
};

USTRUCT(BlueprintType)
struct FExcavationAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual excavation abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<EExcavationAbilityType, FAbilityModule> ExcavationAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FExcavationAbility()
    : ExcavationAbilities()
    {
        // Initialize each excavation type with a default ability module.
        for (uint8 i = static_cast<uint8>(EExcavationAbilityType::Null) + 1; i < static_cast<uint8>(EExcavationAbilityType::Max); i++)
        {
            EExcavationAbilityType Type = static_cast<EExcavationAbilityType>(i);
            ExcavationAbilities.Add(Type, FAbilityModule());
        }
    }

    // Returns a modifiable reference to the ExcavationAbilities map.
    TMap<EExcavationAbilityType, FAbilityModule>& GetAbilities()
    {
        return ExcavationAbilities;
    }

    // Const getter for excavation abilities.
    const TMap<EExcavationAbilityType, FAbilityModule>& GetAbilities() const
    {
        return ExcavationAbilities;
    }

    bool operator==(FExcavationAbility& Other) const
    {
        return AreMapsEqual(ExcavationAbilities, Other.ExcavationAbilities);
    }

    bool operator!=(FExcavationAbility& Other) const
    {
        return !(*this == Other);
    }

    // Sets the entire ExcavationAbilities map with new values.
    void SetAbilities(const TMap<EExcavationAbilityType, FAbilityModule>& NewAbilities)
    {
        ExcavationAbilities = NewAbilities;
    }

    // Checks if the given excavation ability type is valid and present in the ability map.
    bool ValidateAbilityByType(EExcavationAbilityType Type) const
    {
        if (ExcavationAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: ExcavationAbilities map is empty.");
            #endif
            return false;
        }

        if (!ExcavationAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in ExcavationAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in ExcavationAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given excavation ability type.
    void ResetAbilityByType(EExcavationAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExcavationAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given excavation ability type.
    void IncreaseAbilityByType(EExcavationAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExcavationAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given excavation ability type.
    void DecreaseAbilityByType(EExcavationAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExcavationAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified excavation ability using provided credit.
    void UpgradeAbilityByType(EExcavationAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExcavationAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified excavation ability using provided credit.
    void DowngradeAbilityByType(EExcavationAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = ExcavationAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};

#pragma endregion   

#pragma region TransactionAbility

UENUM(BlueprintType)
enum class ETransactionAbilityType : uint8
{
    Null                   UMETA(DisplayName = "Select Trade Ability"),
    BarterMaster           UMETA(DisplayName = "Barter Master"),
    ResourceHaggler        UMETA(DisplayName = "Resource Haggler"),
    ItemAppraisal          UMETA(DisplayName = "Item Appraisal"),
    QuickNegotiator        UMETA(DisplayName = "Quick Negotiator"),
    RareItemFinder         UMETA(DisplayName = "Rare Item Finder"),
    SupplySavant           UMETA(DisplayName = "Supply Savant"),
    TradeIntuition         UMETA(DisplayName = "Trade Intuition"),
    InfluentialDealer      UMETA(DisplayName = "Influential Dealer"),
    NegotiationTactician   UMETA(DisplayName = "Negotiation Tactician"),
    TradeNetwork           UMETA(DisplayName = "Trade Network"),
    FairTradeAdvocate      UMETA(DisplayName = "Fair Trade Advocate"),
    BargainHunter          UMETA(DisplayName = "Bargain Hunter"),
    MerchantKnowledge      UMETA(DisplayName = "Merchant Knowledge"),
    SupplyChainExpert      UMETA(DisplayName = "Supply Chain Expert"),
    TradePersuasion        UMETA(DisplayName = "Trade Persuasion"),
    ItemRestoration        UMETA(DisplayName = "Item Restoration"),
    FavorableConditions    UMETA(DisplayName = "Favorable Conditions"),
    MarketInsight          UMETA(DisplayName = "Market Insight"),
    RiskAssessment         UMETA(DisplayName = "Risk Assessment"),
    TacticalTrade          UMETA(DisplayName = "Tactical Trade"),
    TradeSpecialist        UMETA(DisplayName = "Trade Specialist"),
    CustomItemCreation     UMETA(DisplayName = "Custom Item Creation"),
    BulkTrade              UMETA(DisplayName = "Bulk Trade"),
    TimelyDeal             UMETA(DisplayName = "Timely Deal"),
    ResourceConversion     UMETA(DisplayName = "Resource Conversion"),
    StrategicPartnership   UMETA(DisplayName = "Strategic Partnership"),
    EthicalTrader          UMETA(DisplayName = "Ethical Trader"),
    Max                    UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FTransactionAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual transaction abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<ETransactionAbilityType, FAbilityModule> TransactionAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FTransactionAbility()
    : TransactionAbilities()
    {
        // Initialize each transaction type with a default ability module.
        for (uint8 i = static_cast<uint8>(ETransactionAbilityType::Null) + 1; i < static_cast<uint8>(ETransactionAbilityType::Max); i++)
        {
            ETransactionAbilityType Type = static_cast<ETransactionAbilityType>(i);
            TransactionAbilities.Add(Type, FAbilityModule());
        }
    }

    // Returns a modifiable reference to the TransactionAbilities map.
    TMap<ETransactionAbilityType, FAbilityModule>& GetAbilities()
    {
        return TransactionAbilities;
    }

    // Const getter for transaction abilities.
    const TMap<ETransactionAbilityType, FAbilityModule>& GetAbilities() const
    {
        return TransactionAbilities;
    }

    bool operator==(FTransactionAbility& Other) const
    {
        return AreMapsEqual(TransactionAbilities, Other.TransactionAbilities);
    }

    bool operator!=(FTransactionAbility& Other) const
    {
        return !(*this == Other);
    }

    // Sets the entire TransactionAbilities map with new values.
    void SetAbilities(const TMap<ETransactionAbilityType, FAbilityModule>& NewAbilities)
    {
        TransactionAbilities = NewAbilities;
    }

    // Checks if the given transaction ability type is valid and present in the ability map.
    bool ValidateAbilityByType(ETransactionAbilityType Type) const
    {
        if (TransactionAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: TransactionAbilities map is empty.");
            #endif
            return false;
        }

        if (!TransactionAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in TransactionAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in TransactionAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given transaction ability type.
    void ResetAbilityByType(ETransactionAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = TransactionAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given transaction ability type.
    void IncreaseAbilityByType(ETransactionAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = TransactionAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given transaction ability type.
    void DecreaseAbilityByType(ETransactionAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = TransactionAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified transaction ability using provided credit.
    void UpgradeAbilityByType(ETransactionAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = TransactionAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified transaction ability using provided credit.
    void DowngradeAbilityByType(ETransactionAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = TransactionAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};

#pragma endregion  

#pragma region AugmentAbility

UENUM(BlueprintType)
enum class EAugmentAbilityType : uint8
{
    Null                                   UMETA(DisplayName = "Select Passive Ability"),
    EnhancedStaminaRegeneration            UMETA(DisplayName = "Enhanced Stamina Regeneration"),
    DamageResistance                       UMETA(DisplayName = "Damage Resistance"),
    HealthRegeneration                     UMETA(DisplayName = "Health Regeneration"),
    EnvironmentalAdaptation                UMETA(DisplayName = "Environmental Adaptation"),
    TacticalAwareness                      UMETA(DisplayName = "Tactical Awareness"),
    QuickRecovery                          UMETA(DisplayName = "Quick Recovery"),
    EnhancedCriticalHitChance              UMETA(DisplayName = "Enhanced Critical Hit Chance"),
    WeaponProficiency                      UMETA(DisplayName = "Weapon Proficiency"),
    CrouchStability                        UMETA(DisplayName = "Crouch Stability"),
    FortifiedDefense                       UMETA(DisplayName = "Fortified Defense"),
    AgileMovement                          UMETA(DisplayName = "Agile Movement"),
    CombatMeditation                       UMETA(DisplayName = "Combat Meditation"),
    FortuneFinder                          UMETA(DisplayName = "Fortune Finder"),
    FearlessAdvancer                       UMETA(DisplayName = "Fearless Advancer"),
    TeamworkBond                           UMETA(DisplayName = "Teamwork Bond"),
    Resilience                             UMETA(DisplayName = "Resilience"),
    StealthyPresence                       UMETA(DisplayName = "Stealthy Presence"),
    ElementalAffinity                      UMETA(DisplayName = "Elemental Affinity"),
    QuickDodge                             UMETA(DisplayName = "Quick Dodge"),
    FearImmunity                           UMETA(DisplayName = "Fear Immunity"),
    ResourcefulSurvival                    UMETA(DisplayName = "Resourceful Survival"),
    ExpertTracker                          UMETA(DisplayName = "Expert Tracker"),
    BattleFocus                            UMETA(DisplayName = "Battle Focus"),
    Alertness                              UMETA(DisplayName = "Alertness"),
    SprintEfficiency                       UMETA(DisplayName = "Sprint Efficiency"),
    Coolheadedness                         UMETA(DisplayName = "Coolheadedness"),
    NaturalCamouflage                      UMETA(DisplayName = "Natural Camouflage"),
    GroupResilience                        UMETA(DisplayName = "Group Resilience"),
    CriticalFeedback                       UMETA(DisplayName = "Critical Feedback"),
    AdaptiveArmor                          UMETA(DisplayName = "Adaptive Armor"),
    EnhancedFocus                          UMETA(DisplayName = "Enhanced Focus"),
    EnergyConservation                     UMETA(DisplayName = "Energy Conservation"),
    EvasiveInstincts                       UMETA(DisplayName = "Evasive Instincts"),
    PerceptiveHunter                       UMETA(DisplayName = "Perceptive Hunter"),
    DefensivePosture                       UMETA(DisplayName = "Defensive Posture"),
    IntuitiveLeader                        UMETA(DisplayName = "Intuitive Leader"),
    EnhancedAgility                        UMETA(DisplayName = "Enhanced Agility"),
    Bloodlust                              UMETA(DisplayName = "Bloodlust"),
    UnyieldingSpirit                       UMETA(DisplayName = "Unyielding Spirit"),
    WeaponMastery                          UMETA(DisplayName = "Weapon Mastery"),
    CriticalEvade                          UMETA(DisplayName = "Critical Evade"),
    TacticalReinforcement                  UMETA(DisplayName = "Tactical Reinforcement"),
    SpeedyRecovery                         UMETA(DisplayName = "Speedy Recovery"),
    Max                                    UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FAugmentAbility
{
    GENERATED_BODY()

protected:
    // Map holding individual augment abilities by type.
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<EAugmentAbilityType, FAbilityModule> AugmentAbilities;

public:
    // Default constructor that initializes ability map with default modules.
    FAugmentAbility()
        : AugmentAbilities()
    {
        // Initialize each augment type with a default ability module.
        for (uint8 i = static_cast<uint8>(EAugmentAbilityType::Null) + 1; i < static_cast<uint8>(EAugmentAbilityType::Max); i++)
        {
            EAugmentAbilityType Type = static_cast<EAugmentAbilityType>(i);
            AugmentAbilities.Add(Type, FAbilityModule());
        }
    }

    // Returns a modifiable reference to the AugmentAbilities map.
    TMap<EAugmentAbilityType, FAbilityModule>& GetAbilities()
    {
        return AugmentAbilities;
    }

    // Const getter for augment abilities.
    const TMap<EAugmentAbilityType, FAbilityModule>& GetAbilities() const
    {
        return AugmentAbilities;
    }

    bool operator==(FAugmentAbility& Other) const
    {
        return AreMapsEqual(AugmentAbilities, Other.AugmentAbilities);
    }

    bool operator!=(FAugmentAbility& Other) const
    {
        return !(*this == Other);
    }

    // Sets the entire AugmentAbilities map with new values.
    void SetAbilities(const TMap<EAugmentAbilityType, FAbilityModule>& NewAbilities)
    {
        AugmentAbilities = NewAbilities;
    }

    // Checks if the given augment ability type is valid and present in the ability map.
    bool ValidateAbilityByType(EAugmentAbilityType Type) const
    {
        if (AugmentAbilities.IsEmpty())
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: AugmentAbilities map is empty.");
            #endif
            return false;
        }

        if (!AugmentAbilities.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Validation failed: Ability type not found in AugmentAbilities map.");
            #endif
            return false;
        }

        #if DEV_DEBUG_MODE
        LOG_INFO("Validation succeeded: Ability type exists in AugmentAbilities map.");
        #endif

        return true;
    }

    // Resets the ability module to its initial state for the given augment ability type.
    void ResetAbilityByType(EAugmentAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = AugmentAbilities[Type];
            Ability.Reset();
        }
    }

    // Increases the internal point value for the given augment ability type.
    void IncreaseAbilityByType(EAugmentAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = AugmentAbilities[Type];
            Ability.IncreasePoint();
        }
    }

    // Decreases the internal point value for the given augment ability type.
    void DecreaseAbilityByType(EAugmentAbilityType Type)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = AugmentAbilities[Type];
            Ability.DecreasePoint();
        }
    }

    // Attempts to upgrade the specified augment ability using provided credit.
    void UpgradeAbilityByType(EAugmentAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = AugmentAbilities[Type];
            Ability.Upgrade(InCredit);
        }
    }

    // Attempts to downgrade the specified augment ability using provided credit.
    void DowngradeAbilityByType(EAugmentAbilityType Type, float InCredit)
    {
        if (ValidateAbilityByType(Type))
        {
            FAbilityModule& Ability = AugmentAbilities[Type];
            Ability.Downgrade(InCredit);
        }
    }
};

 #pragma endregion      

#pragma region CharacterAbility

#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityPointChanged, int32, NewAbilityPoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaximumAbilityCapacityChanged, int32, NewMaximumCapacity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllocatedPointChanged, int32, NewAllocatedPoint);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResetedPointChanged, int32, NewResetedPoint);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMobilityAbilityChanged, const FMovementAbility&, NewMobilityAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMartialAbilityChanged, const FMartialAbility&, NewMartialAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStealthAbilityChanged, const FStealthAbility&, NewStealthAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCyberneticAbilityChanged, const FCyberneticAbility&, NewCyberneticAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupportAbilityChanged, const FSupportAbility&, NewSupportAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDefensiveAbilityChanged, const FDefensiveAbility&, NewDefensiveAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMarksmanAbilityChanged, const FMarksmanAbility&, NewMarksmanAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExplorationAbilityChanged, const FExplorationAbility&, NewExplorationAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExcavationAbilityChanged, const FExcavationAbility&, NewExcavationAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTransactionAbilityChanged, const FTransactionAbility&, NewTransactionAbility);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAugmentAbilityChanged, const FAugmentAbility&, NewAugmentAbility);

#pragma endregion

USTRUCT(BlueprintType)
struct FCharacterAbility
{
    GENERATED_BODY()

#pragma region DataEntry

private:
    // Ability points for the character
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    int32 AbilityPoint;

    // Maximum ability capacity for the character
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    int32 MaximumAbilityCapacity;

    // Allocated ability point for the character
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    int32 AllocatedPoint;

    // Resetted ability point for the character
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    int32 ResetedPoint;

    // Movement Ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FMovementAbility MovementAbility;

    // Martial Ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FMartialAbility MartialAbility;

    // Stealth Ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FStealthAbility StealthAbility;

    // Cybernetic Ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FCyberneticAbility CyberneticAbility;

    // Support Ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FSupportAbility SupportAbility;

    // Defensive Ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FDefensiveAbility DefensiveAbility;

    // Marksman ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FMarksmanAbility MarksmanAbility;

    // Exploration ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FExplorationAbility ExplorationAbility;

    // Excavation ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FExcavationAbility ExcavationAbility;

    // Transaction ability data
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FTransactionAbility TransactionAbility;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FAugmentAbility AugmentAbility;

#pragma endregion

#pragma region Delegate 

    // Delegate broadcast when AbilityPoint changes.
    UPROPERTY(BlueprintAssignable)
    FOnAbilityPointChanged OnAbilityPointChanged;

    // Delegate broadcast when MaximumAbilityCapacity changes.
    UPROPERTY(BlueprintAssignable)
    FOnMaximumAbilityCapacityChanged OnMaximumAbilityCapacityChanged;

    // Delegate broadcast when AllocatedPoint changes.
    UPROPERTY(BlueprintAssignable)
    FOnAllocatedPointChanged OnAllocatedPointChanged;

    // Delegate broadcast when ResetedPoint changes.
    UPROPERTY(BlueprintAssignable)
    FOnResetedPointChanged OnResetedPointChanged;

    // Delegate broadcast when MovementAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnMobilityAbilityChanged OnMobilityAbilityChanged;

    // Delegate broadcast when MartialAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnMartialAbilityChanged OnMartialAbilityChanged;

    // Delegate broadcast when StealthAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnStealthAbilityChanged OnStealthAbilityChanged;

    // Delegate broadcast when CyberneticAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnCyberneticAbilityChanged OnCyberneticAbilityChanged;

    // Delegate broadcast when SupportAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnSupportAbilityChanged OnSupportAbilityChanged;

    // Delegate broadcast when DefensiveAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnDefensiveAbilityChanged OnDefensiveAbilityChanged;

    // Delegate broadcast when MarksmanAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnMarksmanAbilityChanged OnMarksmanAbilityChanged;

    // Delegate broadcast when ExplorationAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnExplorationAbilityChanged OnExplorationAbilityChanged;

    // Delegate broadcast when ExcavationAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnExcavationAbilityChanged OnExcavationAbilityChanged;

    // Delegate broadcast when TransactionAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnTransactionAbilityChanged OnTransactionAbilityChanged;

    // Delegate broadcast when AugmentAbility data is updated.
    UPROPERTY(BlueprintAssignable)
    FOnAugmentAbilityChanged OnAugmentAbilityChanged;

#pragma endregion

#pragma region Constructor

public:
    // Constructor of character ability
    FCharacterAbility()
    : AbilityPoint(0)
    , MaximumAbilityCapacity(0)
    , AllocatedPoint(0)
    , ResetedPoint(0)
    , MovementAbility()
    , MartialAbility()
    , StealthAbility()
    , CyberneticAbility()
    , SupportAbility()
    , DefensiveAbility()
    , MarksmanAbility()
    , ExplorationAbility()
    , ExcavationAbility()
    , TransactionAbility()
    , AugmentAbility()
    {}

#pragma endregion

#pragma region Operator
public:
    // Equality operator for FCharacterAbility
    bool operator==(const FCharacterAbility& Other) const
    {
        return
            AbilityPoint            == Other.AbilityPoint           &&
            MaximumAbilityCapacity  == Other.MaximumAbilityCapacity &&
            AllocatedPoint          == Other.AllocatedPoint         &&
            ResetedPoint            == Other.ResetedPoint           &&

            AreMapsEqual(MovementAbility.GetAbilities(),    Other.MovementAbility.GetAbilities())       &&
            AreMapsEqual(StealthAbility.GetAbilities(),     Other.StealthAbility.GetAbilities())        &&
            AreMapsEqual(MartialAbility.GetAbilities(),     Other.MartialAbility.GetAbilities())        &&
            AreMapsEqual(CyberneticAbility.GetAbilities(),  Other.CyberneticAbility.GetAbilities())     &&
            AreMapsEqual(SupportAbility.GetAbilities(),     Other.SupportAbility.GetAbilities())        &&
            AreMapsEqual(DefensiveAbility.GetAbilities(),   Other.DefensiveAbility.GetAbilities())      &&
            AreMapsEqual(MarksmanAbility.GetAbilities(),    Other.MarksmanAbility.GetAbilities())       &&
            AreMapsEqual(ExplorationAbility.GetAbilities(), Other.ExplorationAbility.GetAbilities())    &&
            AreMapsEqual(ExcavationAbility.GetAbilities(),  Other.ExcavationAbility.GetAbilities())     &&
            AreMapsEqual(TransactionAbility.GetAbilities(), Other.TransactionAbility.GetAbilities())    &&
            AreMapsEqual(AugmentAbility.GetAbilities(),     Other.AugmentAbility.GetAbilities());
    }

    // Inequality operator for FCharacterAbility
    bool operator!=(const FCharacterAbility& Other) const
    {
        return !(*this == Other);
    }

#pragma endregion

#pragma region Accessor

public:

    int32 GetAbilityPoint() const
    {
        return AbilityPoint;
    }

    int32 GetMaximumAbilityCapacity() const
    {
        return MaximumAbilityCapacity;
    }

    int32 GetAllocatedPoint() const
    {
        return AllocatedPoint;
    }

    int32 GetResetedPoint() const
    {
        return ResetedPoint;
    }

    const FMovementAbility& GetMovementAbility() const
    {
        return MovementAbility;
    }

    const FMartialAbility& GetMartialAbility() const
    {
        return MartialAbility;
    }

    const FStealthAbility& GetStealthAbility() const
    {
        return StealthAbility;
    }

    const FCyberneticAbility& GetCyberneticAbility() const
    {
        return CyberneticAbility;
    }

    const FSupportAbility& GetSupportAbility() const
    {
        return SupportAbility;
    }

    const FDefensiveAbility& GetDefensiveAbility() const
    {
        return DefensiveAbility;
    }

    const FMarksmanAbility& GetMarksmanAbility() const
    {
        return MarksmanAbility;
    }

    const FExplorationAbility& GetExplorationAbility() const
    {
        return ExplorationAbility;
    }

    const FExcavationAbility& GetExcavationAbility() const
    {
        return ExcavationAbility;
    }

    const FTransactionAbility& GetTransactionAbility() const
    {
        return TransactionAbility;
    }

    const FAugmentAbility& GetAugmentAbility() const
    {
        return AugmentAbility;
    }

#pragma endregion

#pragma region Mutator

public:
    void SetAbilityPoints(int32 NewPoint)
    {
        if (NewPoint < 0)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Ability points cannot be negative.");
            #endif
            return;
        }

        if (AbilityPoint == NewPoint)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set AbilityPoint to the same value.");
            #endif
            return;
        }

        AbilityPoint = NewPoint;
        OnAbilityPointChanged.Broadcast(AbilityPoint);
    }

    void SetMaximumAbilityCapacity(int32 NewCapacity)
    {
        if (NewCapacity < 0)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Maximum ability capacity cannot be negative.");
            #endif
            return;
        }

        if (MaximumAbilityCapacity == NewCapacity)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set MaximumAbilityCapacity to the same value.");
            #endif
            return;
        }

        MaximumAbilityCapacity = NewCapacity;
        OnMaximumAbilityCapacityChanged.Broadcast(MaximumAbilityCapacity);
    }

    void SetAbilityPoints(int32 NewPoint)
    {
        if (NewPoint < 0)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Ability points cannot be negative.");
            #endif
            return;
        }

        if (AbilityPoint == NewPoint)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set AbilityPoint to the same value.");
            #endif
            return;
        }

        AbilityPoint = NewPoint;
        OnAbilityPointChanged.Broadcast(AbilityPoint);
    }

    void SetMaximumAbilityCapacity(int32 NewCapacity)
    {
        if (NewCapacity < 0)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Maximum ability capacity cannot be negative.");
            #endif
            return;
        }

        if (MaximumAbilityCapacity == NewCapacity)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set MaximumAbilityCapacity to the same value.");
            #endif
            return;
        }

        MaximumAbilityCapacity = NewCapacity;
        OnMaximumAbilityCapacityChanged.Broadcast(MaximumAbilityCapacity);
    }

    void SetAllocatedPoint(int32 NewAllocatedPoint)
    {
        if (NewAllocatedPoint < 0)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Allocated points cannot be negative.");
            #endif
            return;
        }

        if (AllocatedPoint == NewAllocatedPoint)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set AllocatedPoint to the same value.");
            #endif
            return;
        }

        AllocatedPoint = NewAllocatedPoint;
        OnAllocatedPointChanged.Broadcast(AllocatedPoint);
    }

    void SetResetedPoint(int32 NewResetedPoint)
    {
        if (NewResetedPoint < 0)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Reseted points cannot be negative.");
            #endif
            return;
        }

        if (ResetedPoint == NewResetedPoint)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set ResetedPoint to the same value.");
            #endif
            return;
        }

        ResetedPoint = NewResetedPoint;
        OnResetedPointChanged.Broadcast(ResetedPoint);
    }

    void SetMovementAbility(const FMovementAbility& NewAbility)
    {
        if (MovementAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set MovementAbility to the same value.");
            #endif
            return;
        }

        MovementAbility = NewAbility;
        OnMobilityAbilityChanged.Broadcast(MovementAbility);
    }

    void SetMartialAbility(const FMartialAbility& NewAbility)
    {
        if (MartialAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set MartialAbility to the same value.");
            #endif
            return;
        }

        MartialAbility = NewAbility;
        OnMartialAbilityChanged.Broadcast(MartialAbility);
    }

    void SetStealthAbility(const FStealthAbility& NewAbility)
    {
        if (StealthAbility == NewAbility)
        {
#if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set StealthAbility to the same value.");
#endif
            return;
        }

        StealthAbility = NewAbility;
        OnStealthAbilityChanged.Broadcast(StealthAbility);
    }

    void SetCyberneticAbility(const FCyberneticAbility& NewAbility)
    {
        if (CyberneticAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set CyberneticAbility to the same value.");
            #endif
            return;
        }

        CyberneticAbility = NewAbility;
        OnCyberneticAbilityChanged.Broadcast(CyberneticAbility);
    }

    void SetSupportAbility(const FSupportAbility& NewAbility)
    {
        if (SupportAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set SupportAbility to the same value.");
            #endif
            return;
        }

        SupportAbility = NewAbility;
        OnSupportAbilityChanged.Broadcast(SupportAbility);
    }

    void SetDefensiveAbility(const FDefensiveAbility& NewAbility)
    {
        if (DefensiveAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set DefensiveAbility to the same value.");
            #endif
            return;
        }

        DefensiveAbility = NewAbility;
        OnDefensiveAbilityChanged.Broadcast(DefensiveAbility);
    }

    void SetMarksmanAbility(const FMarksmanAbility& NewAbility)
    {
        if (MarksmanAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set MarksmanAbility to the same value.");
            #endif
            return;
        }

        MarksmanAbility = NewAbility;
        OnMarksmanAbilityChanged.Broadcast(MarksmanAbility);
    }

    void SetExplorationAbility(const FExplorationAbility& NewAbility)
    {
        if (ExplorationAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set ExplorationAbility to the same value.");
            #endif
            return;
        }

        ExplorationAbility = NewAbility;
        OnExplorationAbilityChanged.Broadcast(ExplorationAbility);
    }

    void SetExcavationAbility(const FExcavationAbility& NewAbility)
    {
        if (ExcavationAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set ExcavationAbility to the same value.");
            #endif
            return;
        }

        ExcavationAbility = NewAbility;
        OnExcavationAbilityChanged.Broadcast(ExcavationAbility);
    }

    void SetTransactionAbility(const FTransactionAbility& NewAbility)
    {
        if (TransactionAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set TransactionAbility to the same value.");
            #endif
            return;
        }

        TransactionAbility = NewAbility;
        OnTransactionAbilityChanged.Broadcast(TransactionAbility);
    }

    void SetAugmentAbility(const FAugmentAbility& NewAbility)
    {
        if (AugmentAbility == NewAbility)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set AugmentAbility to the same value.");
            #endif
            return;
        }

        AugmentAbility = NewAbility;
        OnAugmentAbilityChanged.Broadcast(AugmentAbility);
    }

#pragma endregion

#pragma region Utility

    template<typename AbilityData, typename AbilityType>
    void IncreaseAbilityPoint(AbilityData& Ability, AbilityType Type)
    {
        Ability.IncreaseAbilityByType(Type);
    }

    template<typename AbilityData, typename AbilityType>
    void DecreaseAbilityPoint(AbilityData& Ability, AbilityType Type)
    {
        Ability.DecreaseAbilityByType(Type);
    }

    template<typename AbilityData, typename AbilityType>
    void UpgradeAbility(AbilityData& Ability, AbilityType Type)
    {
        Ability.UpgradeAbilityByType(Type);
    }

    template<typename AbilityData, typename AbilityType>
    void DowngradeAbility(AbilityData& Ability, AbilityType Type)
    {
        Ability.DowngradeAbilityByType(Type);
    }
        

#pragma endregion

};

#pragma endregion


