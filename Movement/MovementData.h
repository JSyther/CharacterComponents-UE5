// Copyright © 2025 Reverse-A. All Rights Reserved.

#pragma once

#include "DevelopmentUtility\DiagnosticSystem.h"
#include "MovementState.h"
#include "MovementData.generated.h"

#pragma region ForwardDecleration

class UCurveFloat;
class USoundBase;
class UParticleSystem;

#pragma endregion

#pragma region MovementAttribute

#pragma region Delegate
/* ------------ MOVEMENT SPEED ------------ */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDesiredSpeedChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMinimumSpeedChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaximumSpeedChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpeedSmoothingRateChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAccelerationChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDecelerationChanged, float, NewValue);


/* ------------ GROUND CONTROL ------------ */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxStepHeightChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxWalkableSlopeAngleChanged, float, NewValue);

/* ------------ VERTICAL CONTROL ------------ */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpImpulseMinZChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpImpulseMaxZChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpImpulseMinXYChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpImpulseMaxXYChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJumpForceScalarChanged, float, NewValue);

/* ------------ AIR CONTROL ------------ */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAirAccelerationChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAirDecelerationChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAirControlRatioChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTerminalFallSpeedChanged, float, NewValue);

#pragma endregion

USTRUCT(BlueprintType)
struct FMovementAttribute
{
    GENERATED_BODY()

#pragma region Data-Entry

#pragma region MovementSpeed

private:
    // Character's target movement speed in units/sec
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float DesiredSpeed;

    // Minimum movement speed allowed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float MinimumSpeed;

    // Maximum movement speed allowed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float MaximumSpeed;

    // Interpolation rate to reach desired speed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float InterpolationSpeed;

    // Acceleration in units/sec²
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float Acceleration;

    // Deceleration in units/sec²
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float Deceleration;

#pragma endregion

#pragma region GroundControl

private:

    // Max vertical distance character can step over
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float MaxStepHeight;

    // Maximum slope angle in degrees the character can walk on
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float MaxWalkableSlopeAngle;

#pragma endregion

#pragma region VerticalControl

private:
    // Minimum vertical velocity for jump initiation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float JumpImpulseMinZ;

    // Maximum vertical velocity for jump initiation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float JumpImpulseMaxZ;

    // Minimum horizontal velocity during jump
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float JumpImpulseMinXY;

    // Maximum horizontal velocity during jump
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float JumpImpulseMaxXY;

    // Scalar multiplier to scale total jump force (affects trajectory arc)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float JumpForceScalar;

#pragma endregion

#pragma region AirControl

private:

    // Acceleration while airborne in units/sec²
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float AirAcceleration;

    // Deceleration while airborne in units/sec²
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float AirDeceleration;

    // Multiplier for how much lateral (horizontal) control is possible in the air [0-1]
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float AirControlRatio;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float TerminalFallSpeed;

#pragma endregion

#pragma endregion

#pragma region Delegate

#pragma region MovementSpeed

public:
    // Called when DesiredSpeed is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnDesiredSpeedChanged OnDesiredSpeedChanged;

    // Called when MinimumSpeed is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnMinimumSpeedChanged OnMinimumSpeedChanged;

    // Called when MaximumSpeed is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnMaximumSpeedChanged OnMaximumSpeedChanged;

    // Called when SpeedSmoothingRate is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnSpeedSmoothingRateChanged OnSpeedSmoothingRateChanged;

    // Called when Acceleration is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnAccelerationChanged OnAccelerationChanged;

    // Called when Deceleration is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnDecelerationChanged OnDecelerationChanged;

#pragma endregion

#pragma region GroundControl

public:
    // Called when MaxStepHeight is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnMaxStepHeightChanged OnMaxStepHeightChanged;

    // Called when MaxWalkableSlopeAngle is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnMaxWalkableSlopeAngleChanged OnMaxWalkableSlopeAngleChanged;

#pragma endregion

#pragma region VerticalControl

public:
    // Called when JumpImpulseMinZ is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnJumpImpulseMinZChanged OnJumpImpulseMinZChanged;

    // Called when JumpImpulseMaxZ is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnJumpImpulseMaxZChanged OnJumpImpulseMaxZChanged;

    // Called when JumpImpulseMinXY is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnJumpImpulseMinXYChanged OnJumpImpulseMinXYChanged;

    // Called when JumpImpulseMaxXY is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnJumpImpulseMaxXYChanged OnJumpImpulseMaxXYChanged;

    // Called when JumpForceScalar is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnJumpForceScalarChanged OnJumpForceScalarChanged;

#pragma endregion

#pragma region AirControl

public:

    // Called when AirAcceleration is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnAirAccelerationChanged OnAirAccelerationChanged;

    // Called when AirDeceleration is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnAirDecelerationChanged OnAirDecelerationChanged;

    // Called when AirControlRatio is modified
    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnAirControlRatioChanged OnAirControlRatioChanged;

    UPROPERTY(BlueprintAssignable, Category = "Movement|Events")
    FOnTerminalFallSpeedChanged OnTerminalFallSpeedChanged;

#pragma endregion

#pragma endregion

#pragma region Constructor

public:

    FMovementAttribute()
    : DesiredSpeed(0.f)
    , MinimumSpeed(0.f)
    , MaximumSpeed(0.f)
    , InterpolationSpeed(0.f)
    , Acceleration(0.f)
    , Deceleration(0.f)

    , MaxStepHeight(0.f)
    , MaxWalkableSlopeAngle(0.f)

    , AirAcceleration(0.f)
    , AirDeceleration(0.f)
    , AirControlRatio(0.f)
    , TerminalFallSpeed(0.f)

    , JumpImpulseMinZ(0.f)
    , JumpImpulseMaxZ(0.f)
    , JumpImpulseMinXY(0.f)
    , JumpImpulseMaxXY(0.f)
    , JumpForceScalar(0.f)
    {}

#pragma endregion

#pragma region Operator

    bool operator==(const FMovementAttribute& Other) const
    {
        return
            DesiredSpeed == Other.DesiredSpeed
            && MinimumSpeed == Other.MinimumSpeed
            && MaximumSpeed == Other.MaximumSpeed
            && InterpolationSpeed == Other.InterpolationSpeed
            && Acceleration == Other.Acceleration
            && Deceleration == Other.Deceleration

            && MaxStepHeight == Other.MaxStepHeight
            && MaxWalkableSlopeAngle == Other.MaxWalkableSlopeAngle

            && JumpImpulseMinZ == Other.JumpImpulseMinZ
            && JumpImpulseMaxZ == Other.JumpImpulseMaxZ
            && JumpImpulseMinXY == Other.JumpImpulseMinXY
            && JumpImpulseMaxXY == Other.JumpImpulseMaxXY
            && JumpForceScalar == Other.JumpForceScalar

            && AirAcceleration == Other.AirAcceleration
            && AirDeceleration == Other.AirDeceleration
            && AirControlRatio == Other.AirControlRatio;
    }

    bool operator!=(const FMovementAttribute& Other) const
    {
        return !(*this == Other);
    }

#pragma endregion

#pragma region Accessor

#pragma region MovementSpeed

    float GetDesiredSpeed() const { return DesiredSpeed; }
    float GetMinimumSpeed() const { return MinimumSpeed; }
    float GetMaximumSpeed() const { return MaximumSpeed; }
    float GetInterpolationSpeed() const { return InterpolationSpeed; }
    float GetGroundAcceleration() const { return Acceleration; }
    float GetGroundDeceleration() const { return Deceleration; }

#pragma endregion

#pragma region GroundControl

    float GetMaxStepHeight() const { return MaxStepHeight; }
    float GetMaxWalkableSlopeAngle() const { return MaxWalkableSlopeAngle; }

#pragma endregion

#pragma region Vertical Control 

    float GetJumpImpulseMinZ() const { return JumpImpulseMinZ; }
    float GetJumpImpulseMaxZ() const { return JumpImpulseMaxZ; }
    float GetJumpImpulseMinXY() const { return JumpImpulseMinXY; }
    float GetJumpImpulseMaxXY() const { return JumpImpulseMaxXY; }
    float GetJumpForceScalar() const { return JumpForceScalar; }

#pragma endregion

#pragma region AirControl

    float GetAirAcceleration() const { return AirAcceleration; }
    float GetAirDeceleration() const { return AirDeceleration; }
    float GetAirControlRatio() const { return AirControlRatio; }
    float GetTerminalFallSpeed() const { return TerminalFallSpeed; }

#pragma endregion

#pragma endregion

#pragma region Mutator

#pragma region MovementSpeed

    void SetDesiredSpeed(float InSpeed)
    {
        if (DesiredSpeed == InSpeed)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetDesiredSpeed called with the same value. No update performed.");
            #endif
            return;
        }

        if (InSpeed < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for DesiredSpeed.");
            #endif
            return;
        }

        DesiredSpeed = InSpeed;
        OnDesiredSpeedChanged.Broadcast(DesiredSpeed);
    }

    void SetMinimumSpeed(float InSpeed)
    {
        if (MinimumSpeed == InSpeed)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetMinimumSpeed called with the same value. No update performed.");
            #endif
            return;
        }

        if (InSpeed < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for MinimumSpeed.");
            #endif
            return;
        }

        MinimumSpeed = InSpeed;
        OnMinimumSpeedChanged.Broadcast(MinimumSpeed);
    }

    void SetMaximumSpeed(float InSpeed)
    {
        if (MaximumSpeed == InSpeed)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetMaximumSpeed called with the same value. No update performed.");
            #endif
            return;
        }

        if (InSpeed < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for MaximumSpeed.");
            #endif
            return;
        }

        MaximumSpeed = InSpeed;
        OnMaximumSpeedChanged.Broadcast(MaximumSpeed);
    }

    void SetInterpolationSpeed(float InRate)
    {
        if (InterpolationSpeed == InRate)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetSpeedSmoothingRate called with the same value. No update performed.");
            #endif
            return;
        }

        if (InRate < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for InterpolationSpeed.");
            #endif
            return;
        }

        InterpolationSpeed = InRate;
        OnSpeedSmoothingRateChanged.Broadcast(InterpolationSpeed);
    }

    void SetAcceleration(float InAccel)
    {
        if (Acceleration == InAccel)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetAcceleration called with the same value. No update performed.");
            #endif
            return;
        }

        if (InAccel < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for Acceleration.");
            #endif
            return;
        }

        Acceleration = InAccel;
        OnAccelerationChanged.Broadcast(Acceleration);
    }

    void SetDeceleration(float InDecel)
    {
        if (Deceleration == InDecel)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetGroundDeceleration called with the same value. No update performed.");
            #endif
            return;
        }

        if (InDecel < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for Deceleration.");
            #endif
            return;
        }

        Deceleration = InDecel;
        OnDecelerationChanged.Broadcast(Deceleration);
    }

#pragma endregion

#pragma region GroundControl 

    void SetMaxStepHeight(float InHeight)
    {
        if (MaxStepHeight == InHeight)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetMaxStepHeight called with the same value. No update performed.");
            #endif
            return;
        }

        if (InHeight < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for MaxStepHeight.");
            #endif
            return;
        }

        MaxStepHeight = InHeight;
        OnMaxStepHeightChanged.Broadcast(MaxStepHeight);
    }

    void SetMaxWalkableSlopeAngle(float InAngle)
    {
        if (MaxWalkableSlopeAngle == InAngle)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetMaxWalkableSlopeAngle called with the same value. No update performed.");
            #endif
            return;
        }

        if (InAngle < 0.f || InAngle > 90.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("MaxWalkableSlopeAngle must be between 0 and 90 degrees.");
            #endif
            return;
        }

        MaxWalkableSlopeAngle = InAngle;
        OnMaxWalkableSlopeAngleChanged.Broadcast(MaxWalkableSlopeAngle);
    }

#pragma endregion

#pragma region VerticalControl 

    void SetJumpImpulseMinZ(float InVelocity)
    {
        if (JumpImpulseMinZ == InVelocity)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetJumpImpulseMinZ called with the same value. No update performed.");
            #endif
            return;
        }

        JumpImpulseMinZ = InVelocity;
        OnJumpImpulseMinZChanged.Broadcast(JumpImpulseMinZ);
    }

    void SetJumpImpulseMaxZ(float InVelocity)
    {
        if (JumpImpulseMaxZ == InVelocity)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetJumpImpulseMaxZ called with the same value. No update performed.");
            #endif
            return;
        }

        JumpImpulseMaxZ = InVelocity;
        OnJumpImpulseMaxZChanged.Broadcast(JumpImpulseMaxZ);
    }

    void SetJumpImpulseMinXY(float InVelocity)
    {
        if (JumpImpulseMinXY == InVelocity)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetJumpImpulseMinXY called with the same value. No update performed.");
            #endif
            return;
        }

        JumpImpulseMinXY = InVelocity;
        OnJumpImpulseMinXYChanged.Broadcast(JumpImpulseMinXY);
    }

    void SetJumpImpulseMaxXY(float InVelocity)
    {
        if (JumpImpulseMaxXY == InVelocity)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetJumpImpulseMaxXY called with the same value. No update performed.");
            #endif
            return;
        }

        JumpImpulseMaxXY = InVelocity;
        OnJumpImpulseMaxXYChanged.Broadcast(JumpImpulseMaxXY);
    }

    void SetJumpForceScalar(float InScalar)
    {
        if (JumpForceScalar == InScalar)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetJumpForceScalar called with the same value. No update performed.");
            #endif
            return;
        }

        if (InScalar < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for JumpForceScalar.");
            #endif
            return;
        }

        JumpForceScalar = InScalar;
        OnJumpForceScalarChanged.Broadcast(JumpForceScalar);
    }

#pragma endregion

#pragma region AirControl

    void SetAirAcceleration(float InAccel)
    {
        if (AirAcceleration == InAccel)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetAirAcceleration called with the same value. No update performed.");
            #endif
            return;
        }

        if (InAccel < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for AirAcceleration.");
            #endif
            return;
        }

        AirAcceleration = InAccel;
        OnAirAccelerationChanged.Broadcast(AirAcceleration);
    }

    void SetAirDeceleration(float InDecel)
    {
        if (AirDeceleration == InDecel)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetAirDeceleration called with the same value. No update performed.");
            #endif
            return;
        }

        if (InDecel < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for AirDeceleration.");
            #endif
            return;
        }

        AirDeceleration = InDecel;
        OnAirDecelerationChanged.Broadcast(AirDeceleration);
    }

    void SetAirControlRatio(float InRatio)
    {
        if (AirControlRatio == InRatio)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetAirControlRatio called with the same value. No update performed.");
            #endif
            return;
        }

        if (InRatio < 0.f || InRatio > 1.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("AirControlRatio must be between 0 and 1.");
            #endif
            return;
        }

        AirControlRatio = InRatio;
        OnAirControlRatioChanged.Broadcast(AirControlRatio);
    }

    void SetTerminalFallSpeed(float InSpeed)
    {
        if (TerminalFallSpeed == InSpeed)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetAirControlRatio called but TerminalFallSpeed is already set to the input value.");
            #endif
            return;
        }

        if (InSpeed < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("SetAirControlRatio failed: Input speed cannot be negative.");
            #endif
            return;
        }

        TerminalFallSpeed = InSpeed;
        OnTerminalFallSpeedChanged.Broadcast(TerminalFallSpeed);

        #if DEV_DEBUG_MODE
        LOG("TerminalFallSpeed successfully updated.");
        #endif
    }

#pragma endregion

#pragma endregion

};



#pragma endregion

#pragma region MovementProgress

#pragma region Delegate

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartLocationChanged, const FVector&, NewStartLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndLocationChanged, const FVector&, NewEndLocation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDurationChanged, float, NewDuration);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTotalTimeChanged, float, NewTotalTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTravelDistanceChanged, float, NewTravelDistance);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttemptCountChanged, uint32, NewAttemptCount);

#pragma endregion

USTRUCT(BlueprintType)
struct FMovementProgress
{
    GENERATED_BODY()

#pragma region DataEntry

private:

    /* ------------ TRAVEL DATA ------------ */
    // Starting location of the movement action
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FVector StartLocation;

    // Target location to reach during the movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FVector EndLocation;

    // Time it should take to complete the movement (in seconds)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float Duration;

    // Total time elapsed during movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float TotalTime;

    // Total distance from StartLocation to EndLocation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float TravelDistance;

    // Usage count of this movement type
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    int32  AttemptCount;

#pragma endregion

#pragma region Delegate

public:
    UPROPERTY(BlueprintAssignable)
    FOnStartLocationChanged OnStartLocationChanged;

    UPROPERTY(BlueprintAssignable)
    FOnEndLocationChanged OnEndLocationChanged;

    UPROPERTY(BlueprintAssignable)
    FOnDurationChanged OnDurationChanged;

    UPROPERTY(BlueprintAssignable)
    FOnTotalTimeChanged OnTotalTimeChanged;

    UPROPERTY(BlueprintAssignable)
    FOnTravelDistanceChanged OnTravelDistanceChanged;

    UPROPERTY(BlueprintAssignable)
    FOnAttemptCountChanged OnAttemptCountChanged;

#pragma endregion

#pragma region Constructor 

    FMovementProgress()
    : StartLocation(FVector::ZeroVector)
    , EndLocation(FVector::ZeroVector)
    , Duration(0.0f)
    , TotalTime(0.0f)
    , TravelDistance(0.0f)
    , AttemptCount(0)
    {}

#pragma endregion

#pragma region Operator

    FORCEINLINE bool operator==(const FMovementProgress& Other) const
    {
        return
            StartLocation == Other.StartLocation &&
            EndLocation == Other.EndLocation &&
            FMath::IsNearlyEqual(Duration, Other.Duration) &&
            FMath::IsNearlyEqual(TotalTime, Other.TotalTime) &&
            FMath::IsNearlyEqual(TravelDistance, Other.TravelDistance) &&
            AttemptCount == Other.AttemptCount;
    }

    FORCEINLINE bool operator!=(const FMovementProgress& Other) const
    {
        return !(*this == Other);
    }

#pragma endregion

#pragma region Accessor

    // Returns the starting location of the movement
    FORCEINLINE FVector GetStartLocation() const { return StartLocation; }

    // Returns the target location to reach
    FORCEINLINE FVector GetEndLocation() const { return EndLocation; }

    // Returns the total duration of the movement in seconds
    FORCEINLINE float GetDuration() const { return Duration; }

    // Returns the total time elapsed during the movement
    FORCEINLINE float GetTotalTime() const { return TotalTime; }

    // Returns the calculated distance from start to end
    FORCEINLINE float GetTravelDistance() const { return TravelDistance; }

    // Returns how many times this movement type has been attempted
    FORCEINLINE uint32 GetAttemptCount() const { return AttemptCount; }

#pragma endregion

#pragma region Mutator

    // Updates the start location if different and notifies listeners; logs a warning if unchanged
    void SetStartLocation(const FVector& InLocation)
    {
        if (StartLocation == InLocation)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetStartLocation called with the same value. No update performed.");
            #endif
            return;
        }

        StartLocation = InLocation;
        OnStartLocationChanged.Broadcast(StartLocation);
    }

    // Updates the end location if different and notifies listeners; logs a warning if unchanged
    void SetEndLocation(const FVector& InLocation)
    {
        if (EndLocation == InLocation)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetEndLocation called with the same value. No update performed.");
            #endif
            return;
        }

        EndLocation = InLocation;
        OnEndLocationChanged.Broadcast(EndLocation);
    }

    // Updates the duration if different and non-negative; logs error if negative input
    void SetDuration(float InDuration)
    {
        if (Duration == InDuration)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetDuration called with the same value. No update performed.");
            #endif

            return;
        }

        if (InDuration < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for Duration");
            #endif

            return;
        }

        Duration = InDuration;
        OnDurationChanged.Broadcast(Duration);
    }

    // Sets the total time if changed and non-negative; logs error and ignores if negative
    void SetTotalTime(float InTotalTime)
    {
        if (TotalTime == InTotalTime)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetTotalTime called with the same value. No update performed.");
            #endif

            return;
        }

        if (InTotalTime < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for TotalTime");
            #endif

            return;
        }

        TotalTime = InTotalTime;
        OnTotalTimeChanged.Broadcast(TotalTime);
    }

    // Sets the travel distance if changed and non-negative; logs error and ignores if negative
    void SetTravelDistance(float InDistance)
    {
        if (TravelDistance == InDistance)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetTravelDistance called with the same value. No update performed.");
            #endif

            return;
        }

        if (InDistance < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Negative value rejected for TravelDistance");
            #endif

            return;
        }

        TravelDistance = InDistance;
        OnTravelDistanceChanged.Broadcast(TravelDistance);
    }

    // Sets the attempt count if changed and non-zero; logs warnings or errors and ignores invalid inputs
    void SetAttemptCount(uint32 InCount)
    {
        if (AttemptCount == InCount)
        {
            #if DEV_DEBUG_MODE
            LOG_WARNING("SetAttemptCount called with the same value. No update performed.");
            #endif
            return;
        }

        // Example of a “negate” condition: reject zero or any invalid value here
        if (InCount == 0)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("AttemptCount cannot be zero.");
            #endif
            return;
        }

        AttemptCount = InCount;
        OnAttemptCountChanged.Broadcast(AttemptCount);
    }

#pragma endregion

#pragma region Update

    void UpdateDuration(float DeltaTime)
    {
        Duration += DeltaTime;
    }

    void UpdateTotalTime()
    {
        TotalTime += Duration;
    }

    void UpdateDistance(FVector StartVector, FVector EndVector)
    {
        TravelDistance = FVector::Dist(StartLocation, EndLocation);

    }

    void UpdateAttemptCount()
    {
        ++AttemptCount;
    }

#pragma endregion

};

#pragma endregion

#pragma region MovementFX

#pragma region Delegate

// AUDIO DELEGATES
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterSFXChanged, USoundBase*, NewEnterSFX);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveSFXChanged, USoundBase*, NewActiveSFX);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExitSFXChanged,  USoundBase*, NewExitSFX);
// VFX DELEGATES
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterVFXChanged, UParticleSystem*, NewEnterVFX);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActiveVFXChanged, UParticleSystem*, NewActiveVFX);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExitVFXChanged, UParticleSystem*, NewExitVFX);

#pragma endregion

USTRUCT(BlueprintType)
struct FMovementFX
{
    GENERATED_BODY()


#pragma region DataEntry

private:
    /* ------------ AUDIO ------------ */
    // Sound effect played once when the state or action starts (e.g., entering a movement mode)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USoundBase> EnterSFX = nullptr;

    // Sound effect that plays continuously or loops while the state or action is active
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USoundBase> ActiveSFX = nullptr;

    // Sound effect played once when the state or action ends (e.g., exiting a movement mode)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USoundBase> ExitSFX = nullptr;

    /* ------------ VISUALS ------------ */
    // Particle effect played once when the state or action starts (e.g., spawning effect)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UParticleSystem> EnterVFX = nullptr;

    // Particle effect that plays continuously or loops while the state or action is active
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UParticleSystem> ActiveVFX = nullptr;

    // Particle effect played once when the state or action ends (e.g., disappearing effect)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UParticleSystem> ExitVFX = nullptr;

#pragma endregion

#pragma region Delegate 

public:
    // AUDIO
    UPROPERTY(BlueprintAssignable, Category = "Audio|Delegates")
    FOnEnterSFXChanged OnEnterSFXChanged;

    UPROPERTY(BlueprintAssignable, Category = "Audio|Delegates")
    FOnActiveSFXChanged OnActiveSFXChanged;

    UPROPERTY(BlueprintAssignable, Category = "Audio|Delegates")
    FOnExitSFXChanged OnExitSFXChanged;

    // VFX
    UPROPERTY(BlueprintAssignable, Category = "VFX|Delegates")
    FOnEnterVFXChanged OnEnterVFXChanged;

    UPROPERTY(BlueprintAssignable, Category = "VFX|Delegates")
    FOnActiveVFXChanged OnActiveVFXChanged;

    UPROPERTY(BlueprintAssignable, Category = "VFX|Delegates")
    FOnExitVFXChanged OnExitVFXChanged;

#pragma endregion

#pragma region Constructor

public:
    FMovementFX()
    : EnterSFX(nullptr)
    , ActiveSFX(nullptr)
    , ExitSFX(nullptr)
    , EnterVFX(nullptr)
    , ActiveVFX(nullptr)
    , ExitVFX(nullptr)
    {}

#pragma endregion

#pragma region Operator
    
public:
    bool operator==(const FMovementFX& Other) const
    {
        return EnterSFX     == Other.EnterSFX
            && ActiveSFX    == Other.ActiveSFX
            && ExitSFX      == Other.ExitSFX
            && EnterVFX     == Other.EnterVFX
            && ActiveVFX    == Other.ActiveVFX
            && ExitVFX      == Other.ExitVFX;
    }

    bool operator!=(const FMovementFX& Other) const
    {
        return !(*this == Other);
    }

#pragma endregion

#pragma region Accessor

    // AUDIO
    FORCEINLINE TObjectPtr<USoundBase> GetEnterSFX() const { return EnterSFX; }
    FORCEINLINE TObjectPtr<USoundBase> GetActiveSFX() const { return ActiveSFX; }
    FORCEINLINE TObjectPtr<USoundBase> GetExitSFX() const { return ExitSFX; }

    // VISUALS
    FORCEINLINE TObjectPtr<UParticleSystem> GetEnterVFX() const { return EnterVFX; }
    FORCEINLINE TObjectPtr<UParticleSystem> GetActiveVFX() const { return ActiveVFX; }
    FORCEINLINE TObjectPtr<UParticleSystem> GetExitVFX() const { return ExitVFX; }

#pragma endregion 

#pragma region Mutator

    // AUDIO
    void SetEnterSFX(TObjectPtr<USoundBase> InEnterSFX)
    {
        EnterSFX = InEnterSFX;
        OnEnterSFXChanged.Broadcast(InEnterSFX);
    }

    void SetActiveSFX(TObjectPtr<USoundBase> InActiveSFX)
    {
        ActiveSFX = InActiveSFX;
        OnActiveSFXChanged.Broadcast(InActiveSFX);
    }

    void SetExitSFX(TObjectPtr<USoundBase> InExitSFX)
    {
        ExitSFX = InExitSFX;
        OnExitSFXChanged.Broadcast(InExitSFX);
    }

    // VISUALS
    void SetEnterVFX(TObjectPtr<UParticleSystem> InEnterVFX)
    {
        EnterVFX = InEnterVFX;
        OnEnterVFXChanged.Broadcast(InEnterVFX);
    }

    void SetActiveVFX(TObjectPtr<UParticleSystem> InActiveVFX)
    {
        ActiveVFX = InActiveVFX;
        OnActiveVFXChanged.Broadcast(InActiveVFX);
    }

    void SetExitVFX(TObjectPtr<UParticleSystem> InExitVFX)
    {
        ExitVFX = InExitVFX;
        OnExitVFXChanged.Broadcast(InExitVFX);
    }

#pragma endregion 

};

#pragma endregion

#pragma region MovementCost

#pragma region Delegate

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaCostChanged, float, NewStaminaCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnergyCostChanged, float, NewEnergyCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthCostChanged, float, NewHealthCost);

#pragma endregion

USTRUCT(BlueprintType)
struct FMovementCost
{
    GENERATED_BODY()

#pragma region Data-Entry

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float StaminaCost = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float EnergyCost = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    float HealthCost = 0.f;

#pragma endregion

#pragma region Delegate

public:
    // Cost | Delegates
    UPROPERTY(BlueprintAssignable)
    FOnStaminaCostChanged OnStaminaCostChanged;

    UPROPERTY(BlueprintAssignable)
    FOnEnergyCostChanged OnEnergyCostChanged;

    UPROPERTY(BlueprintAssignable)
    FOnHealthCostChanged OnHealthCostChanged;

#pragma endregion

#pragma region Constructor 

public:
    FMovementCost() = default;

#pragma endregion

#pragma region Operator

public:
    bool operator==(const FMovementCost& Other) const
    {
        return FMath::IsNearlyEqual(StaminaCost, Other.StaminaCost)
            && FMath::IsNearlyEqual(EnergyCost, Other.EnergyCost)
            && FMath::IsNearlyEqual(HealthCost, Other.HealthCost);
    }

    bool operator!=(const FMovementCost& Other) const
    {
        return !(*this == Other);
    }

#pragma endregion

#pragma region Accessor 

public:
    FORCEINLINE float GetStaminaCost() const { return StaminaCost; }
    FORCEINLINE float GetEnergyCost() const { return EnergyCost; }
    FORCEINLINE float GetHealthCost() const { return HealthCost; }

#pragma endregion

#pragma region Mutator

public:

    void SetStaminaCost(float InStaminaCost)
    {
        if (FMath::IsNearlyEqual(StaminaCost, InStaminaCost))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("SetStaminaCost: Value is identical to current.");
            #endif

            return;
        }

        if (InStaminaCost < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("SetStaminaCost: Negative value is not allowed.");
            #endif

            return;
        }

        StaminaCost = InStaminaCost;
        OnStaminaCostChanged.Broadcast(InStaminaCost);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("StaminaCost updated: %.2f"), InStaminaCost);
        #endif
    }

    void SetEnergyCost(float InEnergyCost)
    {
        if (FMath::IsNearlyEqual(EnergyCost, InEnergyCost))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("SetEnergyCost: Value is identical to current.");
            #endif
            return;
        }

        if (InEnergyCost < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("SetEnergyCost: Negative value is not allowed.");
            #endif
            return;
        }

        EnergyCost = InEnergyCost;
        OnEnergyCostChanged.Broadcast(InEnergyCost);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("EnergyCost updated: %.2f"), InEnergyCost);
        #endif
    }

    void SetHealthCost(float InHealthCost)
    {
        if (FMath::IsNearlyEqual(HealthCost, InHealthCost))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("SetHealthCost: Value is identical to current.");
            #endif
            return;
        }

        if (InHealthCost < 0.f)
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("SetHealthCost: Negative value is not allowed.");
            #endif
            return;
        }

        HealthCost = InHealthCost;
        OnHealthCostChanged.Broadcast(InHealthCost);

        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Log, TEXT("HealthCost updated: %.2f"), InHealthCost);
        #endif
    }

#pragma endregion

};

#pragma endregion

#pragma region MovementModule

#pragma region Delegate

// Phase & State
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementPhaseChanged, EMovementPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementStateChanged, EMovementState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementUpdateChanged, EMovementUpdate, NewUpdate);

// Physicss
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementAttributesChanged, const FMovementAttribute&, NewAttribute);

// Progress
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementProgressChanged, const FMovementProgress&, NewProgress);

// FX (SFX/VFX)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementFXChanged, const FMovementFX&, NewFX);

// Cost
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementCostChanged, const FMovementCost&, NewCost);

#pragma endregion

USTRUCT(BlueprintType)
struct FMovementModule
{
    GENERATED_BODY()

#pragma region DataEntry

private:
    // Current phase of movement logic (e.g., Locked, InProgress, Complete)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    EMovementPhase Phase;

    // Current movement state (e.g., Walk, Run, Crouch)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    EMovementState State;

    // Should this movement module update during tick?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    EMovementUpdate Update;

    // Controls the Physicsal parameters of movement such as speed, forces, damping, and gravity behavior.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FMovementAttribute MovementAttributes;

    // Tracks the current progress and runtime state of the movement
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FMovementProgress MovementProgress;

    // Holds audio-visual effect assets (SFX/VFX) associated with movement states (enter, active, exit)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FMovementFX MovementFX;

    // Defines attribute-related costs applied to the character when performing specific movement actions
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    FMovementCost MovementCost;

#pragma endregion

#pragma region Delegate

public:
    /* ------------ DELEGATES ------------ */

    // Called when movement phase changes
    UPROPERTY(BlueprintAssignable)
    FOnMovementPhaseChanged OnMovementPhaseChanged;

    // Called when movement state changes
    UPROPERTY(BlueprintAssignable)
    FOnMovementStateChanged OnMovementStateChanged;

    // Called when movement update mode is modified
    UPROPERTY(BlueprintAssignable)
    FOnMovementUpdateChanged OnMovementUpdateChanged;

    // Called when movement Physics attribute parameters are modified
    UPROPERTY(BlueprintAssignable)
    FOnMovementAttributesChanged OnMovementAttributesChanged;

    // Called when movement progress data is modified
    UPROPERTY(BlueprintAssignable)
    FOnMovementProgressChanged OnMovementProgressChanged;

    // Called when audio-visual effects for movement are modified
    UPROPERTY(BlueprintAssignable)
    FOnMovementFXChanged OnMovementFXChanged;

    // Called when movement cost parameters are modified
    UPROPERTY(BlueprintAssignable)
    FOnMovementCostChanged OnMovementCostChanged;

#pragma endregion

#pragma region Constructor

public:
    FMovementModule()
    : Phase(EMovementPhase::ReadyToAttempt)
    , State(EMovementState::Locked)   
    , Update(EMovementUpdate::Disabled) // default update state
    , MovementAttributes()
    , MovementProgress()
    , MovementFX()
    , MovementCost()
    {
        // Optional: Additional logic if needed
    }

#pragma endregion

#pragma region Operator

    bool operator==(const FMovementModule& Other) const
    {
        return
            Phase == Other.Phase &&
            State == Other.State &&
            Update == Other.Update &&
            MovementProgress == Other.MovementProgress &&
            MovementFX == Other.MovementFX &&
            MovementCost == Other.MovementCost;
    }

    bool operator!=(const FMovementModule& Other) const
    {
        return !(*this == Other);
    }

#pragma endregion

#pragma region Accessor 

    FORCEINLINE EMovementPhase GetPhase() const { return Phase; }
    FORCEINLINE EMovementState GetState() const { return State; }
    FORCEINLINE EMovementUpdate GetUpdate() const { return Update; }

    FORCEINLINE const FMovementAttribute& GetMovementAttributes() const { return MovementAttributes; }
    FORCEINLINE FMovementAttribute& GetMovementAttributes() { return MovementAttributes; }

    FORCEINLINE const FMovementProgress& GetMovementProgress() const { return MovementProgress; }
    FORCEINLINE FMovementProgress& GetMovementProgress() { return MovementProgress; }

    FORCEINLINE const FMovementFX& GetMovementFX() const { return MovementFX; }
    FORCEINLINE FMovementFX& GetMovementFX() { return MovementFX; }

    FORCEINLINE const FMovementCost& GetMovementCost() const { return MovementCost; }
    FORCEINLINE FMovementCost& GetMovementCost() { return MovementCost; }

#pragma endregion

#pragma region Mutator

    /* ------------ MUTATORS: PHASE & STATE ------------ */

    void SetMovementPhase(EMovementPhase InPhase)
    {
        if (Phase != InPhase)
        {
            Phase = InPhase;
            OnMovementPhaseChanged.Broadcast(Phase);
        }
    }

    void SetMovementState(EMovementState InState)
    {
        if (State != InState)
        {
            State = InState;
            OnMovementStateChanged.Broadcast(State);
        }
    }

    void SetMovementUpdate(EMovementUpdate InUpdate)
    {
        if (Update != InUpdate)
        {
            Update = InUpdate;
            OnMovementUpdateChanged.Broadcast(Update);
        }
    }


    /* ------------ MUTATORS: STRUCTS ------------ */

    void SetMovementPhysic(const FMovementAttribute& InPhysic)
    {
        if (!(MovementPhysic == InPhysic))
        {
            MovementPhysic = InPhysic;
            OnMovementPhysicsChanged.Broadcast(MovementPhysic);
        }
    }

    void SetMovementProgress(const FMovementProgress& InProgress)
    {
        if (!(MovementProgress == InProgress))
        {
            MovementProgress = InProgress;
            OnMovementProgressChanged.Broadcast(MovementProgress);
        }
    }

    void SetMovementFX(const FMovementFX& InFX)
    {
        if (!(MovementFX == InFX))
        {
            MovementFX = InFX;
            OnMovementFXChanged.Broadcast(MovementFX);
        }
    }

    void SetMovementCost(const FMovementCost& InCost)
    {
        if (!(MovementCost == InCost))
        {
            MovementCost = InCost;
            OnMovementCostChanged.Broadcast(MovementCost);
        }
    }

#pragma endregion

#pragma region Validate

    bool IsReadyToAttempt() const
    {
        return Phase == EMovementPhase::ReadyToAttempt;
    }

    bool IsInProgress() const
    {
        return Phase == EMovementPhase::InProgress;
    }

    bool IsComplete() const
    {
        return Phase == EMovementPhase::Complete;
    }

    bool UpdateEnabled() const
    {
        return Update == EMovementUpdate::Enabled;
    }

    bool UpdateDisabled() const
    {
        return Update == EMovementUpdate::Disabled;
    }

    bool Locked() const
    {
        return State == EMovementState::Locked;
    }

    bool Unlocked() const
    {
        return State == EMovementState::Unlocked;
    }
    
#pragma endregion

};

#pragma endregion

#pragma region MovementData

#pragma region Delegate

// Called when a MovementModule entry is updated in the map
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMovementModuleUpdated, EMovementType, MovementType, const FMovementModule&, Module);

// Declare a multicast delegate type that notifies movement type change.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMovementTypeChanged, EMovementType, PreviousType, EMovementType, NewType);

#pragma endregion

USTRUCT(BlueprintType)
struct FCharacterMovement
{
    GENERATED_BODY()

#pragma region Data-Entry

private:
    // A mapping of movement types to their respective movement module configurations
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
    TMap<EMovementType, FMovementModule> MovementModules;

    /**
     * The previous movement type the character was using before the last change.
     * Useful for detecting transitions or reverting to an earlier state.
     */
    EMovementType PreviousMovementType;

    /**
     * The current active movement type of the character.
     * Determines how movement logic is handled (e.g., walking, flying, swimming).
     */
    EMovementType CurrentMovementType;

#pragma endregion

#pragma region Delegate

public:
    // Notifies listeners when a movement module is updated
    UPROPERTY(BlueprintAssignable)
    FOnMovementModuleUpdated OnMovementModuleUpdated;

    UPROPERTY(BlueprintAssignable)
    FOnMovementTypeChanged OnMovementTypeChanged;

#pragma endregion

#pragma region Constructor

public:
    FCharacterMovement()
    : MovementModules()
    , PreviousMovementType(EMovementType::Null)
    , CurrentMovementType(EMovementType::Idle)
    {
        InitializeMovementTypes();
    }

#pragma endregion

#pragma region ModuleUtility

private:
    FMovementModule CreateModule
    (
        EMovementPhase Phase = EMovementPhase::Locked,
        EMovementState State = EMovementState::Off,
        EMovementUpdate Update = EMovementUpdate::Disabled,
        const FMovementAttribute& Physic,
        const FMovementProgress& Progress,
        const FMovementFX& FX,
        const FMovementCost& Cost
    )
    {
        FMovementModule Module;
        Module.SetPhase(Phase);
        Module.SetState(State);
        Module.SetUpdate(Update);
        Module.SetMovementPhysic(Physic);
        Module.SetMovementProgress(Progress);
        Module.SetMovementFX(FX);
        Module.SetMovementCost(Cost);
        return Module;
    }


    FORCEINLINE FMovementAttribute MakePhysic
    (
        float InDesiredSpeed = 0.0f, 
        float InMinSpeed = 0.0f, 
        float InMaxSpeed = 0.0f, 
        float InInterpSpeed = 0.0f,
        float InAcceleration = 0.0f, 
        float InDeceleration = 0.0f,

        float InMaxStepHeight = 0.0f,
        float InMaxWalkableSlopeAngle = 0.0f,

        float InJumpImpulseMinZ = 0.0f,
        float InJumpImpulseMaxZ = 0.0f,
        float InJumpImpulseMinXY = 0.0f,
        float InJumpImpulseMaxXY = 0.0f,
        float InJumpForceScalar = 0.0f,

        float InAirAcceleration = 0.0f, 
        float InAirDeceleration = 0.0f, 
        float InAirControlRatio = 0.0f, 
        float InTerminalFallSpeed = 0.0f
    )
    {
        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(InDesiredSpeed);
        Physics.SetMinimumSpeed(InMinSpeed);
        Physics.SetMaximumSpeed(InMaxSpeed);
        Physics.SetInterpolationSpeed(InInterpSpeed);
        Physics.SetAcceleration(InAcceleration);
        Physics.SetDeceleration(InDeceleration);

        Physics.SetMaxStepHeight(InMaxStepHeight);
        Physics.SetMaxWalkableSlopeAngle(InMaxWalkableSlopeAngle);


        Physics.SetJumpImpulseMinZ(InJumpImpulseMinZ);
        Physics.SetJumpImpulseMaxZ(InJumpImpulseMaxZ);
        Physics.SetJumpImpulseMinXY(InJumpImpulseMinXY);
        Physics.SetJumpImpulseMaxXY(InJumpImpulseMaxXY);
        Physics.SetJumpForceScalar(InJumpForceScalar);

        Physics.SetAirAcceleration(InAirAcceleration);
        Physics.SetAirDeceleration(InAirDeceleration);
        Physics.SetAirControlRatio(InAirControlRatio);

        Physics.SetTerminalFallSpeed(InTerminalFallSpeed);

        return Physics;
    }


    FORCEINLINE FMovementProgress MakeProgress
    (
        const FVector& InStartLocation = FVector::ZeroVector,
        const FVector& InEndLocation = FVector::ZeroVector,
        float InDuration = 0.0f,
        float InTotalTime = 0.0f,
        float InTravelDistance = 0.0f,
        int32 InAttemptCount = 0)
    {
        FMovementProgress Progress;

        Progress.SetStartLocation(InStartLocation);
        Progress.SetEndLocation(InEndLocation);
        Progress.SetDuration(InDuration);
        Progress.SetTotalTime(InTotalTime);
        Progress.SetTravelDistance(InTravelDistance);
        Progress.SetAttemptCount(InAttemptCount);

        return Progress;
    }

    FORCEINLINE FMovementFX MakeFX
    (
        TObjectPtr<USoundBase> InEnterSFX = nullptr,
        TObjectPtr<USoundBase> InActiveSFX = nullptr,
        TObjectPtr<USoundBase> InExitSFX = nullptr,
        TObjectPtr<UParticleSystem> InEnterVFX = nullptr,
        TObjectPtr<UParticleSystem> InActiveVFX = nullptr,
        TObjectPtr<UParticleSystem> InExitVFX = nullptr
    )
    {
        FMovementFX FX;

        FX.SetEnterSFX(InEnterSFX);
        FX.SetActiveSFX(InActiveSFX);
        FX.SetExitSFX(InExitSFX);

        FX.SetEnterVFX(InEnterVFX);
        FX.SetActiveVFX(InActiveVFX);
        FX.SetExitVFX(InExitVFX);

        return FX;
    }


    FORCEINLINE FMovementCost MakeCost
    (
        float InStamina = 0.0f, 
        float InEnergy = 0.0f, 
        float InHealth = 0.0f)
    {
        FMovementCost Cost;
        Cost.SetStaminaCost(InStamina);
        Cost.SetEnergyCost(InEnergy);
        Cost.SetHealthCost(InHealth);

        return Cost;
    }

#pragma endregion

#pragma region Initialize
private:
    void InitializeMovementTypes()
    {
        IdleModule();
        WalkModule();
        RunModule();
        SprintModule();
        CrouchModule();
        ProneModule();
        CrawlModule();
        FallModule();
        JumpModule();
        SlideModule();
        RollModule();
        WallRunModule();
        VerticalWallRunModule();
        HangModule();
        DashModule();
        TeleportModule();
        VaultModule();
        MantleModule();
        GlideModule();
        SwimModule();
        DiveModule();
        HoverModule();
        FlyModule();
        GrapplingModule();
        ZiplineModule();
    }


    void IdleModule()
    {

        FMovementAttribute Physics;

        Physics.SetMaxWalkableSlopeAngle(45.0f);

        Physics.SetJumpImpulseMinZ(400.0f);
        Physics.SetJumpImpulseMaxZ(425.f);
        Physics.SetJumpImpulseMinXY(100.f);
        Physics.SetJumpImpulseMaxXY(125.0f);
        Physics.SetJumpForceScalar(1.0f);

        //-------------  IDLE EFFECTS -------------//

        FMovementFX FX;
        // TODO need to load sfx and vfx file path 
        FX.SetEnterSFX(nullptr);
        FX.SetActiveSFX(nullptr);
        FX.SetExitSFX(nullptr);

        FX.SetEnterVFX(nullptr);
        FX.SetActiveVFX(nullptr);
        FX.SetExitVFX(nullptr);


        //-------------  FINAL ADDITION -------------//
        MovementModules.Add
        (
            EMovementType::Idle,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),     
                FX,
                MakeCost()   
            )
        );
    }
    void WalkModule()
    {
        //-------------  WALK PhysicsS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(160.0f);               // Comfortable average walking speed (cm/s)
        Physics.SetMinimumSpeed(120.0f);               // Prevent very slow movement while walking
        Physics.SetMaximumSpeed(220.0f);               // Maximum walk speed limit
        Physics.SetInterpolationSpeed(6.0f);           // How quickly speed adjusts to input changes (higher = snappier)
        Physics.SetAcceleration(1400.0f);               // Moderate acceleration for walking
        Physics.SetDeceleration(1200.0f);               // Smooth deceleration when stopping walking

        Physics.SetMaxStepHeight(45.0f);                // Can step small obstacles (approx 45cm)
        Physics.SetMaxWalkableSlopeAngle(50.0f);        // Walkable slope angle limit (in degrees)

        // No jump impulse from walking state; jumping handled in JumpModule
        Physics.SetJumpImpulseMinZ(425.0f);             // min vertical jump impulse during jump state
        Physics.SetJumpImpulseMaxZ(450.0f);             // max vertical jump impulse during jump state
        Physics.SetJumpImpulseMinXY(125.0f);            // min horizontal jump impulse during jump state
        Physics.SetJumpImpulseMaxXY(150.0f);            // max horizontal jump impulse during jump state
        Physics.SetJumpForceScalar(1.0f);               // scalar for jump force during jump state

        // Air control parameters - allow some directional control while airborne after walking jump
        Physics.SetAirAcceleration(300.0f);             // Moderate air acceleration
        Physics.SetAirDeceleration(250.0f);             // Air deceleration to slow movement mid-air
        Physics.SetAirControlRatio(0.35f);              // Partial control in air (35% of ground control)


        //-------------  WALK EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                     // TODO: walking start sound
        FX.SetActiveSFX(nullptr);                    // TODO: footstep loop
        FX.SetExitSFX(nullptr);                      // TODO: stop walking sound

        FX.SetEnterVFX(nullptr);                     // TODO: maybe foot dust start
        FX.SetActiveVFX(nullptr);                    // TODO: looping walk trail?
        FX.SetExitVFX(nullptr);                      // TODO: light stop puff


        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Walk,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,          
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),                     
                FX,
                MakeCost(0.02f)                      
            )
        );
    }
    void RunModule()
    {
        //------------- RUN PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(400.0f);               // Comfortable average running speed (cm/s)
        Physics.SetMinimumSpeed(350.0f);               // Minimum running speed to avoid slowing too much
        Physics.SetMaximumSpeed(480.0f);               // Maximum run speed cap
        Physics.SetInterpolationSpeed(8.0f);           // How quickly speed adjusts to input changes (higher = more responsive)
        Physics.SetAcceleration(2200.0f);              // Faster acceleration for running
        Physics.SetDeceleration(2000.0f);              // Deceleration when stopping running, still smooth but quicker than walk

        Physics.SetMaxStepHeight(50.0f);               // Can step moderate obstacles (approx 50cm)
        Physics.SetMaxWalkableSlopeAngle(55.0f);       // Walkable slope angle limit increased for running

        // Jump impulse values relevant when running and jumping
        Physics.SetJumpImpulseMinZ(450.0f);            // Minimum vertical jump impulse for running jumps
        Physics.SetJumpImpulseMaxZ(500.0f);            // Maximum vertical jump impulse
        Physics.SetJumpImpulseMinXY(150.0f);           // Minimum horizontal jump impulse for running jumps
        Physics.SetJumpImpulseMaxXY(200.0f);           // Maximum horizontal jump impulse
        Physics.SetJumpForceScalar(1.2f);               // Slightly stronger jump force due to running momentum

        // Air control while running and jumping
        Physics.SetAirAcceleration(400.0f);            // Greater air acceleration for better control in air
        Physics.SetAirDeceleration(300.0f);            // Air deceleration to control momentum
        Physics.SetAirControlRatio(0.45f);             // Increased air control (45% of ground control)

        //------------- RUN EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: running start sound
        FX.SetActiveSFX(nullptr);                       // TODO: running footsteps loop
        FX.SetExitSFX(nullptr);                         // TODO: stop running sound

        FX.SetEnterVFX(nullptr);                        // TODO: dust burst at run start
        FX.SetActiveVFX(nullptr);                       // TODO: running trail or dust particles
        FX.SetExitVFX(nullptr);                         // TODO: small dust puff on stop

        //------------- FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Run,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.05f)                         // Higher stamina/resource cost for running
            )
        );
    }
    void SprintModule()
    {
        //------------- SPRINT PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(600.0f);               // High sprint speed (cm/s)
        Physics.SetMinimumSpeed(550.0f);               // Minimum sprint speed to avoid slowing down
        Physics.SetMaximumSpeed(700.0f);               // Max sprint speed cap
        Physics.SetInterpolationSpeed(10.0f);          // Very quick speed adjustment for responsiveness
        Physics.SetAcceleration(3500.0f);              // Fast acceleration for sprinting
        Physics.SetDeceleration(3000.0f);              // Deceleration when stopping sprint, brisk but controlled

        Physics.SetMaxStepHeight(55.0f);               // Able to step higher obstacles while sprinting
        Physics.SetMaxWalkableSlopeAngle(55.0f);       // Walkable slope angle limit for sprinting

        // Jump impulse boosted by sprint momentum
        Physics.SetJumpImpulseMinZ(480.0f);            // Min vertical jump impulse for sprint jumps
        Physics.SetJumpImpulseMaxZ(600.0f);            // Max vertical jump impulse
        Physics.SetJumpImpulseMinXY(200.0f);           // Min horizontal jump impulse for sprint jumps
        Physics.SetJumpImpulseMaxXY(300.0f);           // Max horizontal jump impulse
        Physics.SetJumpForceScalar(1.5f);               // Stronger jump force due to sprinting speed

        // Air control during sprint jump
        Physics.SetAirAcceleration(500.0f);            // High air acceleration for sprint jumps
        Physics.SetAirDeceleration(400.0f);            // Air deceleration
        Physics.SetAirControlRatio(0.6f);              // Higher air control ratio (60% of ground control)

        //------------- SPRINT EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: sprint start sound
        FX.SetActiveSFX(nullptr);                       // TODO: sprint footsteps loop
        FX.SetExitSFX(nullptr);                         // TODO: sprint stop sound

        FX.SetEnterVFX(nullptr);                        // TODO: dust burst on sprint start
        FX.SetActiveVFX(nullptr);                       // TODO: sprint trail effects
        FX.SetExitVFX(nullptr);                         // TODO: dust puff on sprint stop

        //------------- FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Sprint,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.1f)                          // Higher stamina/resource cost for sprinting
            )
        );
    }
    void CrouchModule()
    {
        //------------- CROUCH PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(75.0f);                // Slow crouch speed (cm/s)
        Physics.SetMinimumSpeed(50.0f);                // Minimum crouch speed
        Physics.SetMaximumSpeed(125.0f);               // Maximum crouch speed cap
        Physics.SetInterpolationSpeed(3.0f);           // Moderate speed interpolation for smoothness
        Physics.SetAcceleration(800.0f);               // Lower acceleration due to crouching
        Physics.SetDeceleration(600.0f);               // Smooth deceleration while crouching

        Physics.SetMaxStepHeight(30.0f);               // Lower step height due to crouch posture
        Physics.SetMaxWalkableSlopeAngle(45.0f);       // More limited slope handling when crouched

        // Jump impulses disabled during crouch
        Physics.SetJumpImpulseMinZ(350.0f);      // reduced vertical jump impulse while crouching
        Physics.SetJumpImpulseMaxZ(400.0f);      // max vertical jump impulse while crouching
        Physics.SetJumpImpulseMinXY(80.0f);      // reduced horizontal jump impulse while crouching
        Physics.SetJumpImpulseMaxXY(120.0f);     // max horizontal jump impulse while crouching
        Physics.SetJumpForceScalar(0.8f);        // lower jump force scalar due to crouched position


        // Limited air control since crouching is mostly grounded
        Physics.SetAirAcceleration(0.0f);      // less than idle, no air acceleration while crouching
        Physics.SetAirDeceleration(0.0f);      // no air deceleration during crouch
        Physics.SetAirControlRatio(0.0f);      // no air control allowed while crouching


        //------------- CROUCH EFFECTS -------------//
        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: crouch start sound
        FX.SetActiveSFX(nullptr);                       // TODO: soft footsteps sound while crouched
        FX.SetExitSFX(nullptr);                         // TODO: stand-up sound

        FX.SetEnterVFX(nullptr);                        // TODO: subtle dust or ground effects on crouch
        FX.SetActiveVFX(nullptr);                       // TODO: maybe faint shadow changes or effects while crouched
        FX.SetExitVFX(nullptr);                         // TODO: small effect when standing up

        //------------- FINAL ADDITION -------------//
        MovementModules.Add
        (
            EMovementType::Crouch,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.01f)                          // Minimal stamina/resource cost for crouching
            )
        );
    }
    void ProneModule()
    {
        //-------------  PRONE PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(50.0f);                // slow crawl speed while prone
        Physics.SetMinimumSpeed(40.0f);                // prevent zero-speed crawl
        Physics.SetMaximumSpeed(100.0f);               // max crawl limit
        Physics.SetInterpolationSpeed(3.0f);           // slower response to input
        Physics.SetAcceleration(600.0f);               // slow to pick up speed
        Physics.SetDeceleration(500.0f);               // gradual stop

        Physics.SetMaxStepHeight(15.0f);               // very low step capability
        Physics.SetMaxWalkableSlopeAngle(25.0f);       // restricted slope handling

        // Jump values with low sci-fi assistance (weak vertical hop)
        Physics.SetJumpImpulseMinZ(150.0f);            // light vertical lift
        Physics.SetJumpImpulseMaxZ(200.0f);            // small jump height
        Physics.SetJumpImpulseMinXY(60.0f);            // slight forward momentum
        Physics.SetJumpImpulseMaxXY(90.0f);            // moderate forward jump
        Physics.SetJumpForceScalar(0.35f);             // reduced jump scaling factor

        // Air control while prone (limited)
        Physics.SetAirAcceleration(120.0f);            // minor correction
        Physics.SetAirDeceleration(100.0f);            // reduced air drag
        Physics.SetAirControlRatio(0.2f);              // very limited control in air

        //-------------  PRONE EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                       // TODO: prone entry rustle
        FX.SetActiveSFX(nullptr);                      // TODO: prone crawl loop
        FX.SetExitSFX(nullptr);                        // TODO: stand up shuffle

        FX.SetEnterVFX(nullptr);                       // TODO: dust puff entry
        FX.SetActiveVFX(nullptr);                      // TODO: body drag trail?
        FX.SetExitVFX(nullptr);                        // TODO: exit puff effect

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Prone,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.015f)                       // slightly less stamina than crouch
            )
        );
    }
    void CrawlModule()
    {
        //-------------  CRAWL PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(35.0f);                // injured crawl pace
        Physics.SetMinimumSpeed(25.0f);                // slowest crawl before stuck
        Physics.SetMaximumSpeed(60.0f);                // crawl speed cap
        Physics.SetInterpolationSpeed(2.0f);           // slow input response
        Physics.SetAcceleration(400.0f);               // sluggish acceleration
        Physics.SetDeceleration(350.0f);               // lazy deceleration

        Physics.SetMaxStepHeight(10.0f);               // can barely step over anything
        Physics.SetMaxWalkableSlopeAngle(20.0f);       // very limited incline ability

        // Jump values with sci-fi assist (low jump possible)
        Physics.SetJumpImpulseMinZ(100.0f);            // weak vertical jump
        Physics.SetJumpImpulseMaxZ(160.0f);            // low peak jump height
        Physics.SetJumpImpulseMinXY(40.0f);            // slight forward leap
        Physics.SetJumpImpulseMaxXY(70.0f);            // minimal horizontal distance
        Physics.SetJumpForceScalar(0.25f);             // reduced jump force scale

        // Air movement while crawling (extremely limited)
        Physics.SetAirAcceleration(100.0f);            // tiny directional correction mid-air
        Physics.SetAirDeceleration(80.0f);             // limited air slowdown
        Physics.SetAirControlRatio(0.15f);             // minimal control

        //-------------  CRAWL EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                       // TODO: wounded crawl entry sound
        FX.SetActiveSFX(nullptr);                      // TODO: dragging loop
        FX.SetExitSFX(nullptr);                        // TODO: stop dragging

        FX.SetEnterVFX(nullptr);                       // TODO: dust + blood smear start
        FX.SetActiveVFX(nullptr);                      // TODO: dragging trail
        FX.SetExitVFX(nullptr);                        // TODO: smear fade

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Crawl,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.02f)                         // slightly more cost than prone
            )
        );
    }
    void FallModule()
    {
        //-------------  FALL PHYSICS -------------//

        FMovementAttribute Physics;

        // Air control parameters during fall
        Physics.SetAirAcceleration(600.0f);         // Moderate air acceleration for directional control
        Physics.SetAirDeceleration(400.0f);         // Air deceleration to slow lateral movement
        Physics.SetAirControlRatio(0.6f);           // Good air control (60% of ground control)
        Physics.SetTerminalFallSpeed(1600.0f);      // Terminal velocity during fall

        //-------------  FALL EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: start falling sound
        FX.SetActiveSFX(nullptr);                        // TODO: wind rush sound during fall
        FX.SetExitSFX(nullptr);                          // TODO: landing impact sound

        FX.SetEnterVFX(nullptr);                         // TODO: dust or wind effect start
        FX.SetActiveVFX(nullptr);                        // TODO: trail effects during fall
        FX.SetExitVFX(nullptr);                          // TODO: landing dust puff or impact effect

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Fall,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.0f)                           // No stamina cost during fall
            )
        );
    }
    void JumpModule()
    {
        //-------------  JUMP PHYSICS -------------//

        FMovementAttribute Physics;

        // for double jump and coyote jump ability
        Physics.SetJumpImpulseMinZ(450.0f);             // Vertical jump impulse minimum
        Physics.SetJumpImpulseMaxZ(520.0f);             // Vertical jump impulse maximum
        Physics.SetJumpImpulseMinXY(120.0f);            // Horizontal jump impulse minimum (forward push)
        Physics.SetJumpImpulseMaxXY(180.0f);            // Horizontal jump impulse maximum
        Physics.SetJumpForceScalar(1.0f);               // Normal jump force scalar

        Physics.SetAirAcceleration(400.0f);             // Air acceleration while airborne
        Physics.SetAirDeceleration(300.0f);             // Air deceleration
        Physics.SetAirControlRatio(0.5f);               // Partial control in air (50% of ground control)

        //-------------  JUMP EFFECTS -------------//
        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: jump start sound
        FX.SetActiveSFX(nullptr);                        // TODO: mid-air sound (optional)
        FX.SetExitSFX(nullptr);                          // TODO: landing sound

        FX.SetEnterVFX(nullptr);                         // TODO: jump launch effect
        FX.SetActiveVFX(nullptr);                        // TODO: airborne trail effect
        FX.SetExitVFX(nullptr);                          // TODO: landing dust or splash

        //-------------  FINAL ADDITION -------------//
        MovementModules.Add
        (
            EMovementType::Jump,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.04f)                           // stamina cost for jumping
            )
        );
    }
    void SlideModule()
    {
        //-------------  SLIDE PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(600.0f);                // faster sliding speed
        Physics.SetMinimumSpeed(500.0f);                // minimum slide speed to maintain momentum
        Physics.SetMaximumSpeed(800.0f);                // max speed cap for slide
        Physics.SetInterpolationSpeed(10.0f);           // very quick speed adjustments during slide
        Physics.SetAcceleration(3000.0f);               // strong acceleration at slide start
        Physics.SetDeceleration(2500.0f);               // rapid deceleration to stop slide

        Physics.SetMaxStepHeight(40.0f);                // handle small obstacles during slide
        Physics.SetMaxWalkableSlopeAngle(45.0f);        // slope handling while sliding

        // Jump impulse values for powerful sliding jump
        Physics.SetJumpImpulseMinZ(600.0f);             // strong vertical jump impulse
        Physics.SetJumpImpulseMaxZ(720.0f);             // max vertical jump impulse
        Physics.SetJumpImpulseMinXY(300.0f);            // powerful horizontal jump impulse
        Physics.SetJumpImpulseMaxXY(420.0f);            // max horizontal jump impulse
        Physics.SetJumpForceScalar(1.2f);               // enhanced jump force due to slide momentum

        Physics.SetAirAcceleration(600.0f);             // good air control during slide jump
        Physics.SetAirDeceleration(450.0f);
        Physics.SetAirControlRatio(0.7f);               // high air control
        Physics.SetTerminalFallSpeed(1600.0f);          // max fall speed

        //-------------  SLIDE EFFECTS -------------//
        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: slide start sound
        FX.SetActiveSFX(nullptr);                        // TODO: sliding sound loop
        FX.SetExitSFX(nullptr);                          // TODO: slide stop sound

        FX.SetEnterVFX(nullptr);                         // TODO: dust burst on slide start
        FX.SetActiveVFX(nullptr);                        // TODO: dust trail during slide
        FX.SetExitVFX(nullptr);                          // TODO: slide end puff

        //-------------  FINAL ADDITION -------------//
        MovementModules.Add
        (
            EMovementType::Slide,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.06f)                           // stamina cost for sliding
            )
        );
    }
    void RollModule()
    {
        //-------------  ROLL PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(500.0f);                // agile roll movement speed
        Physics.SetMinimumSpeed(400.0f);                // maintain momentum
        Physics.SetMaximumSpeed(700.0f);                // limit speed burst
        Physics.SetInterpolationSpeed(9.0f);            // rapid response to roll input
        Physics.SetAcceleration(2800.0f);               // quick burst forward
        Physics.SetDeceleration(2400.0f);               // stops after roll completes

        Physics.SetMaxStepHeight(35.0f);                // minor obstacle step
        Physics.SetMaxWalkableSlopeAngle(40.0f);        // roll usable on moderate slopes

        // Jump values - small hop or dodge vault allowed from roll
        Physics.SetJumpImpulseMinZ(420.0f);             // small hop possible during roll
        Physics.SetJumpImpulseMaxZ(520.0f);
        Physics.SetJumpImpulseMinXY(250.0f);            // forward carry during mid-roll jump
        Physics.SetJumpImpulseMaxXY(350.0f);
        Physics.SetJumpForceScalar(1.0f);               // regular jump force from roll

        Physics.SetAirAcceleration(400.0f);             // fair air control
        Physics.SetAirDeceleration(350.0f);
        Physics.SetAirControlRatio(0.55f);              // limited but useful air steering
        Physics.SetTerminalFallSpeed(1400.0f);          // default fall speed limit

        //-------------  ROLL EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: roll start sound
        FX.SetActiveSFX(nullptr);                        // TODO: rolling whoosh
        FX.SetExitSFX(nullptr);                          // TODO: roll stop thud

        FX.SetEnterVFX(nullptr);                         // TODO: blur trail or dust burst
        FX.SetActiveVFX(nullptr);                        // TODO: roll motion blur
        FX.SetExitVFX(nullptr);                          // TODO: dust end puff

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Roll,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.045f)                         // moderate stamina for rolling
            )
        );
    }
    void WallRunModule()
    {
        //-------------  WALLRUN PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(500.0f);                // consistent wall-run pace
        Physics.SetMinimumSpeed(450.0f);                // ensure forward momentum
        Physics.SetMaximumSpeed(620.0f);                // top limit for horizontal wall-run
        Physics.SetInterpolationSpeed(10.0f);           // very responsive while on wall
        Physics.SetAcceleration(2800.0f);               // burst movement along wall
        Physics.SetDeceleration(2600.0f);               // quick stop when detaching or failing

        Physics.SetMaxStepHeight(10.0f);                // negligible step height on wall
        Physics.SetMaxWalkableSlopeAngle(5.0f);         // nearly flat – wall is vertical

        // Jump from wall (wall-leap or transition)
        Physics.SetJumpImpulseMinZ(520.0f);             // upward launch from wall
        Physics.SetJumpImpulseMaxZ(580.0f);
        Physics.SetJumpImpulseMinXY(260.0f);            // strong lateral leap off wall
        Physics.SetJumpImpulseMaxXY(320.0f);
        Physics.SetJumpForceScalar(1.1f);               // enhanced push to clear the wall

        Physics.SetAirAcceleration(450.0f);             // good directional control mid-air
        Physics.SetAirDeceleration(350.0f);
        Physics.SetAirControlRatio(0.65f);              // above average air control
        Physics.SetTerminalFallSpeed(1000.0f);          // lower fall speed while exiting wall-run

        //-------------  WALLRUN EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: wall-grab sound
        FX.SetActiveSFX(nullptr);                       // TODO: wind rush or foot scraping
        FX.SetExitSFX(nullptr);                         // TODO: detach or jump-from-wall sound

        FX.SetEnterVFX(nullptr);                        // TODO: brief dust/spark on contact
        FX.SetActiveVFX(nullptr);                       // TODO: trail or blur during run
        FX.SetExitVFX(nullptr);                         // TODO: burst or pulse on exit

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::WallRun,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.06f)                         // moderate stamina for wallrun
            )
        );
    }
    void VerticalWallRunModule()
    {
        //-------------  VERTICAL WALLRUN PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(360.0f);                // upward climbing pace
        Physics.SetMinimumSpeed(300.0f);                // prevent stall
        Physics.SetMaximumSpeed(420.0f);                // capped vertical burst
        Physics.SetInterpolationSpeed(9.0f);            // quick height changes
        Physics.SetAcceleration(2500.0f);               // fast upward acceleration
        Physics.SetDeceleration(2300.0f);               // immediate response on stop/fall

        Physics.SetMaxStepHeight(5.0f);                 // irrelevant on vertical wall
        Physics.SetMaxWalkableSlopeAngle(0.0f);         // purely vertical surfaces only

        // Jumping *off* a vertical wall — backflip or side leap
        Physics.SetJumpImpulseMinZ(480.0f);             // moderate lift to push off
        Physics.SetJumpImpulseMaxZ(540.0f);
        Physics.SetJumpImpulseMinXY(220.0f);            // lateral push from wall
        Physics.SetJumpImpulseMaxXY(300.0f);
        Physics.SetJumpForceScalar(1.05f);              // slight boost to help arc off wall

        Physics.SetAirAcceleration(400.0f);             // agile mid-air correction
        Physics.SetAirDeceleration(320.0f);
        Physics.SetAirControlRatio(0.5f);               // fair control
        Physics.SetTerminalFallSpeed(900.0f);           // lower terminal to reduce fall penalty

        //-------------  VERTICAL WALLRUN EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: climbing grab or boost audio
        FX.SetActiveSFX(nullptr);                       // TODO: climbing sound loop
        FX.SetExitSFX(nullptr);                         // TODO: vault off wall or fall whoosh

        FX.SetEnterVFX(nullptr);                        // TODO: climbing sparks or surface flash
        FX.SetActiveVFX(nullptr);                       // TODO: vertical trail or air distortion
        FX.SetExitVFX(nullptr);                         // TODO: boost puff or dash streak

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::VerticalWallRun,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.08f)                         // higher cost for vertical gain
            )
        );
    }
    void HangModule()
    {
        //-------------  HANG PHYSICS -------------//

        FMovementAttribute Physics;

        // Allow jump *off* from hang (e.g., pull-up or wall push)
        Physics.SetJumpImpulseMinZ(420.0f);             // small vertical hop to pull up
        Physics.SetJumpImpulseMaxZ(480.0f);
        Physics.SetJumpImpulseMinXY(100.0f);            // light push-back
        Physics.SetJumpImpulseMaxXY(160.0f);
        Physics.SetJumpForceScalar(1.0f);               // standard impulse scaling

        // Air control after dropping or jumping from hang
        Physics.SetAirAcceleration(200.0f);             // light mid-air adjustment
        Physics.SetAirDeceleration(180.0f);
        Physics.SetAirControlRatio(0.25f);              // minimal influence
        Physics.SetTerminalFallSpeed(900.0f);           // moderate fall cap

        //-------------  HANG EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: grip or catch sound
        FX.SetActiveSFX(nullptr);                       // TODO: rope tension or hanging loop
        FX.SetExitSFX(nullptr);                         // TODO: drop or pull-up sound

        FX.SetEnterVFX(nullptr);                        // TODO: grab puff or sweat spark
        FX.SetActiveVFX(nullptr);                       // TODO: minimal ambient effect
        FX.SetExitVFX(nullptr);                         // TODO: jump flash or puff

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Hang,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.01f)                         // low stamina cost for static hang
            )
        );
    }
    void DashModule()
    {
        //-------------  DASH PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(1200.0f);               // fast dash speed
        Physics.SetMinimumSpeed(1000.0f);               // maintain minimum momentum
        Physics.SetMaximumSpeed(1400.0f);               // cap burst speed
        Physics.SetInterpolationSpeed(20.0f);           // snappy transition
        Physics.SetAcceleration(6000.0f);               // near-instant burst
        Physics.SetDeceleration(2000.0f);               // allow a bit of glide after dash

        Physics.SetMaxStepHeight(0.0f);                 // cannot step during dash
        Physics.SetMaxWalkableSlopeAngle(0.0f);         // dash ignores slopes

        // Optional: short hop if jump is pressed during dash
        Physics.SetJumpImpulseMinZ(320.0f);             // small dash-jump
        Physics.SetJumpImpulseMaxZ(380.0f);
        Physics.SetJumpImpulseMinXY(300.0f);            // forward-push carry
        Physics.SetJumpImpulseMaxXY(400.0f);
        Physics.SetJumpForceScalar(1.0f);               // use full force

        Physics.SetAirAcceleration(250.0f);             // light air steer after dash
        Physics.SetAirDeceleration(200.0f);
        Physics.SetAirControlRatio(0.20f);              // low control while airborne post-dash
        Physics.SetTerminalFallSpeed(1000.0f);          // prevent insane fall speeds

        //-------------  DASH EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: dash burst sound
        FX.SetActiveSFX(nullptr);                       // TODO: wind/speed loop
        FX.SetExitSFX(nullptr);                         // TODO: slide or stop sound

        FX.SetEnterVFX(nullptr);                        // TODO: burst visual
        FX.SetActiveVFX(nullptr);                       // TODO: motion blur or trail
        FX.SetExitVFX(nullptr);                         // TODO: decel puff or spark

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Dash,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.06f)                         // moderate stamina cost per dash
            )
        );
    }
    void TeleportModule()
    {
        //-------------  TELEPORT PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(0.0f);                   // no traditional movement
        Physics.SetMinimumSpeed(0.0f);
        Physics.SetMaximumSpeed(0.0f);
        Physics.SetInterpolationSpeed(0.0f);             // no smoothing needed
        Physics.SetAcceleration(0.0f);                   // no acceleration
        Physics.SetDeceleration(0.0f);                   // no deceleration

        Physics.SetMaxStepHeight(0.0f);                  // irrelevant
        Physics.SetMaxWalkableSlopeAngle(0.0f);

        Physics.SetJumpImpulseMinZ(0.0f);                // no jump
        Physics.SetJumpImpulseMaxZ(0.0f);
        Physics.SetJumpImpulseMinXY(0.0f);
        Physics.SetJumpImpulseMaxXY(0.0f);
        Physics.SetJumpForceScalar(0.0f);

        Physics.SetAirAcceleration(0.0f);                // no movement while teleporting
        Physics.SetAirDeceleration(0.0f);
        Physics.SetAirControlRatio(0.0f);
        Physics.SetTerminalFallSpeed(0.0f);

        //-------------  TELEPORT EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: teleport charge or sound cue
        FX.SetActiveSFX(nullptr);                        // TODO: warping hum, maybe looping
        FX.SetExitSFX(nullptr);                          // TODO: teleport re-materialization

        FX.SetEnterVFX(nullptr);                         // TODO: charge up glow
        FX.SetActiveVFX(nullptr);                        // TODO: dissolve / particles
        FX.SetExitVFX(nullptr);                          // TODO: reappear flash

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Teleport,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,               // no update needed, jump handled by logic
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.12f)                          // relatively high stamina cost for instant warp
            )
        );
    }
    void VaultModule()
    {
        //-------------  VAULT PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(420.0f);                 // Fast vault push forward
        Physics.SetMinimumSpeed(300.0f);                 // Maintain momentum
        Physics.SetMaximumSpeed(600.0f);                 // Cap vaulting burst
        Physics.SetInterpolationSpeed(12.0f);            // Quick transition into vaulting motion
        Physics.SetAcceleration(2200.0f);                // Strong burst to launch over
        Physics.SetDeceleration(1500.0f);                // Slows once vault motion ends

        Physics.SetMaxStepHeight(70.0f);                 // Slightly higher than walk; assumes obstacle top
        Physics.SetMaxWalkableSlopeAngle(60.0f);         // Vaulting is assisted; can go steeper

        // Impulse values — blend of jump & directional push
        Physics.SetJumpImpulseMinZ(260.0f);              // Small vertical lift
        Physics.SetJumpImpulseMaxZ(320.0f);
        Physics.SetJumpImpulseMinXY(300.0f);             // Forward launch during vault
        Physics.SetJumpImpulseMaxXY(480.0f);
        Physics.SetJumpForceScalar(1.15f);               // Stronger impulse than regular jump

        Physics.SetAirAcceleration(400.0f);              // Maintain some control mid-air
        Physics.SetAirDeceleration(300.0f);
        Physics.SetAirControlRatio(0.45f);               // Around half of ground control
        Physics.SetTerminalFallSpeed(1400.0f);           // Fast terminal velocity for drop after vault

        //-------------  VAULT EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: grunt or launch sound
        FX.SetActiveSFX(nullptr);                        // TODO: wind or motion
        FX.SetExitSFX(nullptr);                          // TODO: landing impact

        FX.SetEnterVFX(nullptr);                         // TODO: foot dust / motion blur
        FX.SetActiveVFX(nullptr);                        // TODO: trail effect
        FX.SetExitVFX(nullptr);                          // TODO: brief impact dust

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Vault,
            CreateModule
            (
                EMovementPhase::ReadyToAttempt,
                EMovementState::Off,
                EMovementUpdate::Disabled,               // Jump logic handles motion
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.04f)                          // Moderate cost, less than slide
            )
        );
    }
    void MantleModule()
    {
        //-------------  MANTLE PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(280.0f);                // steady climb speed over ledges
        Physics.SetMinimumSpeed(220.0f);                // prevent slow stalls during mantle
        Physics.SetMaximumSpeed(350.0f);                // cap max mantle speed
        Physics.SetInterpolationSpeed(7.0f);            // smooth speed changes for natural motion
        Physics.SetAcceleration(1800.0f);               // solid acceleration while climbing
        Physics.SetDeceleration(1500.0f);               // gradual deceleration to stop mantle

        Physics.SetMaxStepHeight(50.0f);                // can step ledges up to 50cm
        Physics.SetMaxWalkableSlopeAngle(40.0f);        // slope handling while mantling

        // Jump impulses usually disabled during mantle
        Physics.SetJumpImpulseMinZ(0.0f);
        Physics.SetJumpImpulseMaxZ(0.0f);
        Physics.SetJumpImpulseMinXY(0.0f);
        Physics.SetJumpImpulseMaxXY(0.0f);
        Physics.SetJumpForceScalar(0.0f);

        Physics.SetAirAcceleration(100.0f);             // minimal air control, if falling off mantle
        Physics.SetAirDeceleration(100.0f);
        Physics.SetAirControlRatio(0.15f);              // very limited air control
        Physics.SetTerminalFallSpeed(900.0f);           // lower fall speed for safety

        //-------------  MANTLE EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: grab ledge sound
        FX.SetActiveSFX(nullptr);                        // TODO: climbing motion sounds
        FX.SetExitSFX(nullptr);                          // TODO: landing or vault finish sound

        FX.SetEnterVFX(nullptr);                         // TODO: hand grip dust or sparkle
        FX.SetActiveVFX(nullptr);                        // TODO: motion blur or dust trail
        FX.SetExitVFX(nullptr);                          // TODO: final dust puff or jump-off effect

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Mantle,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.04f)                           // moderate stamina cost for mantle
            )
        );
    }
    void GlideModule()
    { 
        //-------------  GLIDE PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(600.0f);                // smooth forward glide speed
        Physics.SetMinimumSpeed(450.0f);                // prevent stalling mid-glide
        Physics.SetMaximumSpeed(750.0f);                // max controlled glide speed
        Physics.SetInterpolationSpeed(8.0f);            // responsive to input changes
        Physics.SetAcceleration(800.0f);                // gentle acceleration while gliding
        Physics.SetDeceleration(600.0f);                // smooth deceleration when stopping glide

        Physics.SetMaxStepHeight(0.0f);                 // no stepping during glide
        Physics.SetMaxWalkableSlopeAngle(0.0f);         // glide ignores slope

        // Jump impulse to allow pushing off / boost mid-glide
        Physics.SetJumpImpulseMinZ(150.0f);             // slight vertical boost while gliding
        Physics.SetJumpImpulseMaxZ(220.0f);
        Physics.SetJumpImpulseMinXY(250.0f);            // forward push to extend glide
        Physics.SetJumpImpulseMaxXY(320.0f);
        Physics.SetJumpForceScalar(1.0f);                // normal jump force scalar

        // Air control is primary during glide
        Physics.SetAirAcceleration(600.0f);             // good directional control mid-glide
        Physics.SetAirDeceleration(400.0f);
        Physics.SetAirControlRatio(0.8f);                // high control ratio to steer glide
        Physics.SetTerminalFallSpeed(350.0f);            // very slow descent (glide slows fall)

        //-------------  GLIDE EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: wind rush start sound
        FX.SetActiveSFX(nullptr);                        // TODO: sustained wind or air currents
        FX.SetExitSFX(nullptr);                          // TODO: glide stop sound

        FX.SetEnterVFX(nullptr);                         // TODO: subtle particle trails
        FX.SetActiveVFX(nullptr);                        // TODO: continuous trail / motion blur
        FX.SetExitVFX(nullptr);                          // TODO: fade out particle effect

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Glide,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.025f)                          // low stamina drain for gliding
            )
        );
    }
    void SwimModule()
    {
        //-------------  SWIM PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(300.0f);                // average swimming pace
        Physics.SetMinimumSpeed(200.0f);                // avoid sluggish underwater motion
        Physics.SetMaximumSpeed(450.0f);                // strong swim push max
        Physics.SetInterpolationSpeed(4.0f);            // slow speed transition in water
        Physics.SetAcceleration(900.0f);                // effortful water acceleration
        Physics.SetDeceleration(800.0f);                // smooth slowdown in water

        Physics.SetMaxStepHeight(0.0f);                 // no stepping in water
        Physics.SetMaxWalkableSlopeAngle(0.0f);         // no slope concern while swimming

        // Swim jump-like impulse — used for strokes or surfacing bursts
        Physics.SetJumpImpulseMinZ(180.0f);             // small upward burst
        Physics.SetJumpImpulseMaxZ(280.0f);             // strong upward swim push
        Physics.SetJumpImpulseMinXY(100.0f);            // horizontal swim boost
        Physics.SetJumpImpulseMaxXY(160.0f);            // stronger forward burst
        Physics.SetJumpForceScalar(1.0f);               // normal scale in water for impulse

        // Air control adapted to water resistance
        Physics.SetAirAcceleration(300.0f);             // limited directional swim push
        Physics.SetAirDeceleration(280.0f);             // gradual slow down
        Physics.SetAirControlRatio(0.4f);               // moderate control (lower than air)
        Physics.SetTerminalFallSpeed(400.0f);           // terminal descent if diving down

        //-------------  SWIM EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: splash in
        FX.SetActiveSFX(nullptr);                       // TODO: swimming loops
        FX.SetExitSFX(nullptr);                         // TODO: splash out / surfacing sound

        FX.SetEnterVFX(nullptr);                        // TODO: water splash particles
        FX.SetActiveVFX(nullptr);                       // TODO: bubbles / underwater trails
        FX.SetExitVFX(nullptr);                         // TODO: water drip or ripple effects

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Swim,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.03f)                          // higher stamina use due to effort
            )
        );
    }
    void DiveModule()
    {
        //-------------  DIVE PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(450.0f);                // swift forward motion while diving
        Physics.SetMinimumSpeed(300.0f);                // maintain momentum underwater
        Physics.SetMaximumSpeed(600.0f);                // aggressive underwater burst
        Physics.SetInterpolationSpeed(5.0f);            // medium transition speed
        Physics.SetAcceleration(1000.0f);               // quick thrust into dive
        Physics.SetDeceleration(900.0f);                // natural resistance slows us

        Physics.SetMaxStepHeight(0.0f);                 // no stepping
        Physics.SetMaxWalkableSlopeAngle(0.0f);         // irrelevant in water

        // Dive jump-like impulse — more forceful burst downward or forward
        Physics.SetJumpImpulseMinZ(-200.0f);            // negative = downward dive force
        Physics.SetJumpImpulseMaxZ(-400.0f);            // strong downward push
        Physics.SetJumpImpulseMinXY(200.0f);            // dive forward motion
        Physics.SetJumpImpulseMaxXY(300.0f);            // aggressive dive forward thrust
        Physics.SetJumpForceScalar(1.2f);               // slightly amplified for diving motion

        Physics.SetAirAcceleration(350.0f);             // directional adjustment during dive
        Physics.SetAirDeceleration(300.0f);             // underwater resistance
        Physics.SetAirControlRatio(0.3f);               // limited control during committed dive
        Physics.SetTerminalFallSpeed(500.0f);           // fast descent if dive is steep

        //-------------  DIVE EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: splash dive sound
        FX.SetActiveSFX(nullptr);                       // TODO: rushing water noise
        FX.SetExitSFX(nullptr);                         // TODO: transition surfacing sound

        FX.SetEnterVFX(nullptr);                        // TODO: heavy splash or water trail
        FX.SetActiveVFX(nullptr);                       // TODO: bubble trail / streak
        FX.SetExitVFX(nullptr);                         // TODO: surfacing ripple or foam

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Dive,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.035f)                         // diving consumes more stamina
            )
        );
    }
    void HoverModule()
    {
        //-------------  HOVER PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(200.0f);                // stable horizontal glide
        Physics.SetMinimumSpeed(150.0f);                // maintain hover motion
        Physics.SetMaximumSpeed(300.0f);                // allow forward thrust
        Physics.SetInterpolationSpeed(4.0f);            // smooth speed transition
        Physics.SetAcceleration(800.0f);                // controlled build-up
        Physics.SetDeceleration(750.0f);                // maintain graceful slowing

        Physics.SetMaxStepHeight(0.0f);                 // no stepping while hovering
        Physics.SetMaxWalkableSlopeAngle(0.0f);         // irrelevant

        // Hover initiation may use a lift-like jump impulse
        Physics.SetJumpImpulseMinZ(300.0f);             // vertical lift for stable hover
        Physics.SetJumpImpulseMaxZ(400.0f);             // stronger initial boost
        Physics.SetJumpImpulseMinXY(100.0f);            // slight forward kick
        Physics.SetJumpImpulseMaxXY(150.0f);            // boost while initiating hover
        Physics.SetJumpForceScalar(1.0f);               // normal jump force

        Physics.SetAirAcceleration(400.0f);             // high maneuverability
        Physics.SetAirDeceleration(350.0f);             // subtle control resistance
        Physics.SetAirControlRatio(0.9f);               // almost full directional control
        Physics.SetTerminalFallSpeed(300.0f);           // slow descent while hovering

        //-------------  HOVER EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                        // TODO: hover boot ignition or hum
        FX.SetActiveSFX(nullptr);                       // TODO: hovering loop sound
        FX.SetExitSFX(nullptr);                         // TODO: hover disengage pop or thud

        FX.SetEnterVFX(nullptr);                        // TODO: light upward particle trail
        FX.SetActiveVFX(nullptr);                       // TODO: faint glow or shimmer while hovering
        FX.SetExitVFX(nullptr);                         // TODO: spark/effect fadeout

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Hover,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.045f)                         // hovering is energy-intensive
            )
        );
    }
    void FlyModule()
    {
        //-------------  FLY PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(600.0f);                 // average controlled flight speed
        Physics.SetMinimumSpeed(400.0f);                 // avoid stall-like low movement
        Physics.SetMaximumSpeed(1200.0f);                // max afterburner or boost limit
        Physics.SetInterpolationSpeed(6.0f);             // responsive but smooth changes
        Physics.SetAcceleration(1800.0f);                // strong thrust response
        Physics.SetDeceleration(1500.0f);                // allow slowing quickly when needed

        Physics.SetMaxStepHeight(0.0f);                  // no stepping while flying
        Physics.SetMaxWalkableSlopeAngle(0.0f);          // N/A for flight

        // Flight state doesn't initiate via jump, but uses these values for sharp lift bursts
        Physics.SetJumpImpulseMinZ(600.0f);              // vertical lift burst
        Physics.SetJumpImpulseMaxZ(800.0f);              // aggressive vertical burst
        Physics.SetJumpImpulseMinXY(250.0f);             // forward momentum burst
        Physics.SetJumpImpulseMaxXY(400.0f);             // powerful directional boost
        Physics.SetJumpForceScalar(1.0f);                // standard force scale

        Physics.SetAirAcceleration(1600.0f);             // responsive 3D control
        Physics.SetAirDeceleration(1400.0f);             // smooth braking in air
        Physics.SetAirControlRatio(1.0f);                // full control in any direction
        Physics.SetTerminalFallSpeed(0.0f);              // no falling, constant hover/fly

        //-------------  FLY EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: engine ignition, jet burst
        FX.SetActiveSFX(nullptr);                        // TODO: wind/flight hum or loop
        FX.SetExitSFX(nullptr);                          // TODO: flight cut-off or descent

        FX.SetEnterVFX(nullptr);                         // TODO: ignition sparks or lift
        FX.SetActiveVFX(nullptr);                        // TODO: trail effect or motion blur
        FX.SetExitVFX(nullptr);                          // TODO: landing dust or fadeout

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Fly,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.07f)                           // high energy cost for sustained flight
            )
        );
    }
    void GrapplingModule()
    {
        //-------------  GRAPPLING PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(1000.0f);                // rapid traversal speed during grapple
        Physics.SetMinimumSpeed(800.0f);                 // maintain strong momentum
        Physics.SetMaximumSpeed(1600.0f);                // max grapple swing/zip limit
        Physics.SetInterpolationSpeed(10.0f);            // fast transition to grapple movement
        Physics.SetAcceleration(3000.0f);                // strong pull toward grapple point
        Physics.SetDeceleration(2500.0f);                // allow fast stop or cancel

        Physics.SetMaxStepHeight(0.0f);                  // N/A during grapple
        Physics.SetMaxWalkableSlopeAngle(0.0f);          // not grounded

        // Grapple launch or leap values for release movement
        Physics.SetJumpImpulseMinZ(500.0f);              // small upward launch upon detachment
        Physics.SetJumpImpulseMaxZ(720.0f);              // strong vertical pop-off
        Physics.SetJumpImpulseMinXY(500.0f);             // maintain horizontal swing on release
        Physics.SetJumpImpulseMaxXY(800.0f);             // launch away from grapple target
        Physics.SetJumpForceScalar(1.25f);               // increased force for dynamic exit

        Physics.SetAirAcceleration(1200.0f);             // mid-air control during grapple transitions
        Physics.SetAirDeceleration(900.0f);              // deceleration for adjusting angle
        Physics.SetAirControlRatio(0.75f);               // partial control while swinging
        Physics.SetTerminalFallSpeed(1800.0f);           // high limit to maintain high-speed drops

        //-------------  GRAPPLING EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                         // TODO: grapple launch sound
        FX.SetActiveSFX(nullptr);                        // TODO: grapple rope tension / swing loop
        FX.SetExitSFX(nullptr);                          // TODO: detach / swing-release burst

        FX.SetEnterVFX(nullptr);                         // TODO: rope or beam effect
        FX.SetActiveVFX(nullptr);                        // TODO: motion blur trail
        FX.SetExitVFX(nullptr);                          // TODO: spark or tether break

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Grappling,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.045f)                          // moderate cost per grapple use
            )
        );
    }
    void ZiplineModule()
    {
        //-------------  ZIPLINE PHYSICS -------------//

        FMovementAttribute Physics;

        Physics.SetDesiredSpeed(1200.0f);                 // steady zipline speed
        Physics.SetMinimumSpeed(1000.0f);                 // prevent slowing too much on zip
        Physics.SetMaximumSpeed(1600.0f);                 // zipline speed cap
        Physics.SetInterpolationSpeed(8.0f);              // smooth acceleration onto the zipline
        Physics.SetAcceleration(2500.0f);                 // quick ramp-up when entering
        Physics.SetDeceleration(2000.0f);                 // for manual disengage

        Physics.SetMaxStepHeight(0.0f);                   // grounded logic disabled
        Physics.SetMaxWalkableSlopeAngle(0.0f);           // not relevant

        // Jump impulse when releasing or jumping off the zipline
        Physics.SetJumpImpulseMinZ(420.0f);               // small vertical lift when leaping off
        Physics.SetJumpImpulseMaxZ(650.0f);               // max upward burst
        Physics.SetJumpImpulseMinXY(300.0f);              // forward leap minimum
        Physics.SetJumpImpulseMaxXY(700.0f);              // max horizontal leap from zipline
        Physics.SetJumpForceScalar(1.1f);                 // zipline jump boost

        // Air movement while releasing or jumping off
        Physics.SetAirAcceleration(800.0f);               // controlled leap arc
        Physics.SetAirDeceleration(700.0f);               // avoid excessive drift
        Physics.SetAirControlRatio(0.6f);                 // partial directional control
        Physics.SetTerminalFallSpeed(1600.0f);            // fairly fast terminal fall from zipline

        //-------------  ZIPLINE EFFECTS -------------//

        FMovementFX FX;
        FX.SetEnterSFX(nullptr);                          // TODO: zipline attach or launch
        FX.SetActiveSFX(nullptr);                         // TODO: zipline speed loop
        FX.SetExitSFX(nullptr);                           // TODO: detach burst sound

        FX.SetEnterVFX(nullptr);                          // TODO: spark or tether flash
        FX.SetActiveVFX(nullptr);                         // TODO: zip trail blur
        FX.SetExitVFX(nullptr);                           // TODO: break particle

        //-------------  FINAL ADDITION -------------//

        MovementModules.Add
        (
            EMovementType::Zipline,
            CreateModule
            (
                EMovementPhase::Locked,
                EMovementState::Off,
                EMovementUpdate::Disabled,
                Physics,
                MakeProgress(),
                FX,
                MakeCost(0.04f)                            // minor continuous stamina drain
            )
        );
    }

#pragma endregion

#pragma region Accessor

public:
    // Returns modifiable map of movement modules for non-const objects
    FORCEINLINE TMap<EMovementType, FMovementModule>& GetMovementModules()
    {
        return MovementModules;
    }

    // Returns read-only map of movement modules for const objects
    FORCEINLINE const TMap<EMovementType, FMovementModule>& GetMovementModules() const
    {
        return MovementModules;
    }

    // Gets the previous movement type of the character.
    FORCEINLINE EMovementType GetPreviousMovementType() const
    {
        return PreviousMovementType;
    }

    // Gets the current movement type of the character.
    FORCEINLINE EMovementType GetCurrentMovementType() const
    {
        return CurrentMovementType;
    }


#pragma endregion

#pragma region Mutator

public:

    // Updates the movement module for a given type if it exists, otherwise logs an error.
    void SetMovementModuleByType(EMovementType MovementType, const FMovementModule& InModule)
    {
        if (!MovementModules.Contains(MovementType))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Attempted to set MovementModule for invalid MovementType.");
            #endif

            return;
        }

        MovementModules[MovementType] = InModule;
        OnMovementModuleUpdated.Broadcast(MovementType, InModule);
    }

    // Sets a new movement type and broadcasts the change event.
    void SetMovementType(EMovementType NewType)
    {
        // Cache the current type before changing
        const EMovementType OldType = CurrentMovementType;

        // Update previous and current types
        SetPreviousMovementType(OldType);
        SetCurrentMovementType(NewType);

        // Notify listeners about the movement type change
        OnMovementTypeChanged.Broadcast(OldType, NewType);
    }


    // Sets the previous movement type of the character.
    void SetPreviousMovementType(EMovementType NewType)
    {
        PreviousMovementType = NewType;
    }

    // Sets the current movement type of the character.
    void SetCurrentMovementType(EMovementType NewType)
    {
        CurrentMovementType = NewType;
    }

#pragma endregion

#pragma region Utility

    bool UpdateByType(EMovementType Type)
    {
        if (!MovementModules.Contains(Type))
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("");
            #endif
            return;
        }

        if (!MovementModules[Type].IsInProgress())
        {
            return false;
        }

        return true;
    }

    // Checks if the character is in a specific previous movement type.
    bool IsPreviousMovementType(EMovementType TypeToCheck) const
    {
        return PreviousMovementType == TypeToCheck;
    }

    // Checks if the character is in a specific current movement type.
    bool IsCurrentMovementType(EMovementType TypeToCheck) const
    {
        return CurrentMovementType == TypeToCheck;
    }

#pragma endregion

};

#pragma endregion
