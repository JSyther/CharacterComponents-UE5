#pragma once

#include "Character/Data/CharacterData.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Network/NetworkManager.h"
#include "AdvanceMovementComponent.generated.h"

#pragma region ForwardDecleration

class ACharacterModule;
class UPlayerInputCache;

struct FSystemCore;

#pragma endregion

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AGEOFREVERSE_API UAdvanceMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()

#pragma region Constructor

public:
    UAdvanceMovementComponent();

#pragma endregion

#pragma region ClassCycle

protected:
	// Called when the game starts or when spawned
    virtual void BeginPlay() override;

	// Called every frame
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    // Initializes the advanced movement component.
    virtual void InitializeAdvanceMovementComponent();

#pragma endregion

#pragma region Network

private:
    ENetworkType NetworkType;

public:
    
    //bool Local() const
    //{
    //    return NetworkType == ENetworkType::Local;
    //}

    //bool Online() const
    //{
    //    return NetworkType == ENetworkType::Online;
    //}

#pragma endregion

#pragma region Utility
private:
    float DeltaSeconds();

#pragma endregion

#pragma region OwnerCharacter

private:
    // The owning character of this component.
    UPROPERTY()
    TObjectPtr<ACharacterModule> OwnerCharacter = nullptr;

public:
    /**
     * Returns the owning character, or nullptr if not set.
     */
    ACharacterModule* GetOwnerCharacter() const;

    /**
     * Sets the owning character, replacing any existing reference.
     * Passing nullptr clears the reference.
     */
    void SetOwnerCharacter(ACharacterModule* InOwnerCharacter);

#pragma endregion

#pragma region OwnerData

private:
    // Pointer to the owner data.
    FCharacterData* OwnerData = nullptr;

public:
    /**
     * Returns the current owner data pointer.
     * Caller should ensure validity.
     */
    FCharacterData* GetOwnerData() const;

    /**
     * Sets the owner data pointer.
     * Passing nullptr clears the reference.
     */
    void SetOwnerData(FCharacterData* InOwnerData);

private:
    FORCEINLINE ECharacterType GetOwnerType() const
    {
        return OwnerData->GetCharacterType();
    }

#pragma endregion

#pragma region OwnerAbility

private:
    // Pointer to the owner's ability structure.
    FCharacterAbility* OwnerAbility = nullptr;

public:
    /**
     * Sets the owner's ability structure.
     * @param InAbility - New ability data pointer. Must not be nullptr.
     */
    void SetOwnerAbility(FCharacterAbility* InAbility);

    /**
     * Gets the owner's ability structure.
     * @return Current ability pointer or nullptr if not set.
     */
    FCharacterAbility* GetOwnerAbility() const;

#pragma endregion

#pragma region OwnerAttribute

private:
    // Pointer to the owner's attribute structure.
    FCharacterAttribute* OwnerAttribute = nullptr;

public:
    /**
     * Sets the owner's attribute structure.
     * @param InAttribute - New attribute data pointer. Must not be nullptr.
     */
    void SetOwnerAttribute(FCharacterAttribute* InAttribute);

    /**
     * Gets the owner's attribute structure.
     * @return Current attribute pointer or nullptr if not set.
     */
    FCharacterAttribute* GetOwnerAttribute() const;

#pragma endregion

#pragma region OwnerLevel

private:
    // Pointer to the owner's level structure.
    FCharacterLevel* OwnerLevel = nullptr;

public:
    /**
     * Sets the owner's level structure.
     * @param InLevel - New level data pointer. Must not be nullptr.
     */
    void SetOwnerLevel(FCharacterLevel* InLevel);

    /**
     * Gets the owner's level structure.
     * @return Current level pointer or nullptr if not set.
     */
    FCharacterLevel* GetOwnerLevel() const;

#pragma endregion

#pragma region PlayerInputCache

private:
    /**
     * Cached player input object pointer.
     * Managed by Unreal's garbage collector via UPROPERTY.
     */
    UPROPERTY()
    TObjectPtr<UPlayerInputCache> PlayerInputCache = nullptr;

public:
    /**
     * Returns the cached PlayerInputCache UObject pointer.
     * Note: Caller should check for nullptr before use.
     */
    UPlayerInputCache* GetPlayerInputCache() const;

    /**
     * Sets or updates the cached PlayerInputCache UObject pointer.
     * @param NewPlayerInputCache The new PlayerInputCache pointer; can be nullptr to clear.
     */
    void SetPlayerInputCache(UPlayerInputCache* NewPlayerInputCache);

#pragma endregion

#pragma region MovementData

private:
    /**
     * Movement data structure containing movement-related information.
     * Stored by value for simplicity and cache locality.
     * Ensure FCharacterMovement is cheap to copy/move.
     */
    FCharacterMovement MovementData;

public:
    /** Returns a mutable reference to the movement data */
    FORCEINLINE FCharacterMovement& GetMovementData();

    /** Returns a const reference to the movement data */
    FORCEINLINE const FCharacterMovement& GetMovementData() const;

    /** Sets the movement data by value (consider moving if large) */
    void SetMovementData(const FCharacterMovement& InMovement);


#pragma endregion




private:
    void SwitchMovement(EMovementType PreviousType, EMovementType CurrentType);
 

#pragma endregion

#pragma region Activate

private:
    TMap<EMovementType, TFunction<void()>> ActivateMovementHandlers;

    void InitializeActivateMovementHandlers();

    void Local_ActivateMovement(EMovementType Type);


    void ActivateIdle();            void ActivateWalk();          void ActivateRun();           void ActivateSprint();
    void ActivateCrouch();          void ActivateProne();         void ActivateCrawl();         void ActivateFall();
    void ActivateJump();            void ActivateSlide();         void ActivateRoll();          void ActivateWallRun();
    void ActivateVerticalWallRun(); void ActivateHang();          void ActivateDash();          void ActivateTeleport();
    void ActivateVault();           void ActivateMantle();        void ActivateGlide();         void ActivateSwim();
    void ActivateDive();            void ActivateHover();         void ActivateFly();           void ActivateGrappling();
    void ActivateZipline();

#pragma endregion


#pragma region Update

private:
    TMap<EMovementType, TFunction<void()>> UpdateMovementHandlers;

    void InitializeUpdateMovementHandlers();

    bool IsUpdateEnabled(EMovementType Type);

    void Local_UpdateMovement(EMovementType Type);

    void UpdateIdle();            void UpdateWalk();          void UpdateRun();           void UpdateSprint();
    void UpdateCrouch();          void UpdateProne();         void UpdateCrawl();         void UpdateFall();
    void UpdateJump();            void UpdateSlide();         void UpdateRoll();          void UpdateWallRun();
    void UpdateVerticalWallRun(); void UpdateHang();          void UpdateDash();          void UpdateTeleport();
    void UpdateVault();           void UpdateMantle();        void UpdateGlide();         void UpdateSwim();
    void UpdateDive();            void UpdateHover();         void UpdateFly();           void UpdateGrappling();
    void UpdateZipline();

#pragma endregion

#pragma region Deactivate

private:
    TMap<EMovementType, TFunction<void()>> DeactivateMovementHandlers;

    void InitializeDeactivateMovementHandlers();

    void Local_DeactivateMovement(EMovementType Type);

    void DeactivateIdle();      void DeactivateWalk();      void DeactivateRun();       void DeactivateSprint();
    void DeactivateCrouch();    void DeactivateProne();     void DeactivateCrawl();     void DeactivateFall();
    void DeactivateJump();      void DeactivateSlide();     void DeactivateRoll();      void DeactivateWallRun();
    void DeactivateHang();      void DeactivateDash();      void DeactivateTeleport();  void DeactivateVerticalWallRun();
    void DeactivateVault();     void DeactivateMantle();    void DeactivateGlide();     void DeactivateSwim();
    void DeactivateDive();      void DeactivateHover();     void DeactivateFly();       void DeactivateGrappling();
    void DeactivateZipline();

#pragma endregion





#pragma region CapsuleComponent

private:
    // The capsule component owned by this movement component (typically the character's collision capsule)
    UPROPERTY()
    TObjectPtr<UCapsuleComponent> OwnerCapsuleComponent;

    // Updates the capsule's height based on the current movement state (e.g. crouch, prone)
    void UpdateCapsuleHeight();

    // Smoothly interpolates the capsule height to a target value with a specified interpolation speed
    void InterpolateCapsuleHeight(float TargetHeight, float InterpSpeed);

public:
    // Sets the OwnerCapsuleComponent reference
    void SetOwnerCapsuleComponent(TObjectPtr<UCapsuleComponent> InComp);

    // Retrieves the current OwnerCapsuleComponent reference (returns nullptr if invalid)
    UCapsuleComponent* GetOwnerCapsuleComponent() const;

#pragma endregion

#pragma region Utility

private:
    bool bActivateDebug = true;

private:
    // Configuration constants
    float GroundOffset          = 10.f;
    float ForwardTraceDistance  = 100.0f;
    float MaximumWallHeight     = 1000.0f;

/* Speed */
    /* Interpolates movement speed towards a target speed at a given interpolation rate */
    void InterpolateMovementSpeed(float TargetSpeed, float InterpSpeed);

    // Returns the character's horizontal (XY plane) velocity magnitude.
    float HorizontalVelocitySize() const;

    // Returns the forward/backward movement input value.
    float LongitudinalMovementValue() const;

    // Returns the right/left movement input value.
    float LateralMovementValue() const;

/* Traces */
    float PerformWallHeightTrace();
    float GroundCheckTimer;
    float PerformGroundDistanceTrace();

/* Detection */
    /* Performs a trace check to detect a wall in front within the given distance */
    bool IsFrontWallDetected(float InTraceDistance);

    /* Detects if the character can hang from a ledge */
    bool DetectHang();

    // Checks if the character is currently overlapping water actors and updates swimming state. Returns true if in water.
    bool DetectWater();

#pragma endregion


#pragma region BasicMovement

private:
    // Current basic movement state of the character
    EBasicMovementState BasicMovementState;

public:
    // Returns the current basic movement state
    EBasicMovementState GetBasicMovement() const;

    // Sets the basic movement state to the provided new state
    void SetBasicMovement(EBasicMovementState NewState);

    // Checks if the current basic movement state matches the provided state
    bool IsBasicMovement(EBasicMovementState NewState) const;

private:
    // Switches the basic movement state internally without triggering external systems
    void SwitchBasicMovement(EBasicMovementState NewState);


#pragma region Idle

private:
    // Transition into Idle state, this function is called when the character becomes idle.
    void EnterIdle();

    // Transition out of Idle state, this function is called when leaving idle.
    void ExitIdle();

#pragma region Update

    // Handles the physics updates while the character is in the Idle state.
    void TickIdleMovement();

    void UpdateIdleDuration();
    void UpdateIdleTotalTime();
    void UpdateIdleStamina();

#pragma endregion

#pragma region Transition

    /* Idle Transitions = Walk, Run, Crouch, Prone, Crawl, Fall, Jump, Roll, Dash, Teleport, Swim*/

    /* Basic Mobility */
    void IdleToWalk();
	void IdleToRun();
	void IdleToCrouch();
	void IdleToProne();
	void IdleToCrawl();
	void IdleToFall();

    /* Special Mobility */
    void IdleToJump();
    void IdleToRoll();
    void IdleToDash();

    /* Advanced Mobility */
    void IdleToSwim();

#pragma endregion

#pragma endregion

#pragma region Walk

private:
    // Transition into Walk state, this function is called when the character starts walking.
    void EnterWalk();

    // Handles the physics updates while the character is walking.
    void TickWalkMovement();

    // Transition out of Walk state, this function is called when the character stops walking.
    void ExitWalk();

    void UpdateWalkDuration();
    void UpdateWalkTotalTime();
    void UpdateWalkTravelDistance();
    void UpdateWalkStamina();

#pragma region Transition

    /*Basic Mobility */
    void WalkToIdle();
    void WalkToRun();
    void WalkToSprint();
    void WalkToCrouch();
    void WalkToProne();
    void WalkToCrawl();
    void WalkToFall();

    /* Special Mobility */
    void WalkToJump();
    void WalkToRoll();
    void WalkToDash();

    /* Advanced Mobility */
    void WalkToVault();
    void WalkToSwim();

#pragma endregion

#pragma endregion

#pragma region Run
private:
    // Transition into Run state, this function is called when the character starts running.
    void EnterRun();

    // Handles the physics updates while the character is running.
    void TickRunMovement();

    // Transition out of Run state, this function is called when the character stops running.
    void ExitRun();


#pragma region Update

    void UpdateRunDuration();

    void UpdateRunStamina();

    void UpdateRunTotalTime();

    void UpdateRunTravelDistance();

#pragma endregion

#pragma region Utility

    float PreviousVelocityY = 0.0f;
    void RunSpeedControl();

#pragma endregion

#pragma region Transition

    /* Basic Mobility */
    void RunToIdle();
    void RunToWalk();
    void RunToSprint();
    void RunToCrouch();
    void RunToProne();
    void RunToCrawl();
    void RunToFall();

    /* Special Mobility */
    void RunToJump();
    void RunToSlide();
    void RunToDash();
    
    /* Advance Mobility */
    void RunToVault();
    void RunToSwim();

#pragma endregion


#pragma endregion

#pragma region Sprint

private:
    // Transition into Sprint state, this function is called when the character starts sprinting.
    void EnterSprint();

    // Handles the physics updates while the character is sprinting.
    void TickSprintMovement();

    // Transition out of Sprint state, this function is called when the character stops sprinting.
    void ExitSprint();

    void UpdateSprintDuration();

    void UpdateSprintStamina();

    void UpdateSprintTotalTime();
    
    void UpdateSprintTravelDistance();

#pragma region Transition

    /* Basic Mobility */
    void SprintToIdle();
    void SprintToWalk();
    void SprintToRun();
    void SprintToProne();
    void SprintToCrawl();
    void SprintToFall();

    /* Special Mobility */
    void SprintToJump();
    void SprintToSlide();
	void SprintToRoll();
    void SprintToDash();

    /* Advance Mobility */
    void SprintToVault();
    void SprintToMantle();
    void SprintToSwim();


#pragma endregion

#pragma endregion

#pragma region Crawl

private:
    // Transition into Crawl state, this function is called when the character starts crawling.
    void EnterCrawl();

    // Handles the physics updates while the character is crawling.
    void TickCrawlMovement();

    // Transition out of Crawl state, this function is called when the character stops crawling.
    void ExitCrawl();

    void UpdateCrawlDuration();

    void UpdateCrawlStamina();

    void UpdateCrawlTotalTime();

    void UpdateCrawlTravelDistance();

#pragma region Transition

    void CrawlToIdle();
    void CrawlToCrouch();
    void CrawlToProne();
    void CrawlToFall();

#pragma endregion

#pragma endregion

#pragma region Crouch

private:
    // Transition into Crouch state, this function is called when the character starts crouching.
    void EnterCrouch();

    // Handles the physics updates while the character is crouching.
    void TickCrouchMovement();

    // Transition out of Crouch state, this function is called when the character stops crouching.
    void ExitCrouch();

#pragma region Update

    void UpdateCrouchStamina();
    void UpdateCrouchDuration();
    void UpdateCrouchTotalTime();
    void UpdateCrouchTravelDistance();
    
#pragma endregion

#pragma region Utility

    /* Performs a trace check to determine if the player can uncrouch */
    bool UnCrouchHeightValidation();

#pragma endregion

#pragma region Transition

    void CrouchToIdle();
    void CrouchToWalk();
    void CrouchToRun();
    void CrouchToJump();
    void CrouchToSlide();
    void CrouchToRoll();
    void CrouchToProne();
    void CrouchToCrawl();
    void CrouchToFall();

#pragma endregion

#pragma endregion

#pragma region Prone

private:
    // Transition into Prone state, this function is called when the character goes prone.
    void EnterProne();

    // Handles the physics updates while the character is prone.
    void TickProneMovement();

    // Transition out of Prone state, this function is called when the character stops being prone.
    void ExitProne();


#pragma region Update

    // The duration for which the character has been in the prone state, updated over time.
    void UpdateProneDuration();

    void UpdateProneTotalTime();

    void UpdateProneTravelDistance();

#pragma endregion

#pragma region Utility

    void ProneForwardThrust();

    bool CanProneThrustForward();

#pragma endregion

#pragma region Transition

    void ProneToIdle();
    void ProneToWalk();
    void ProneToRun();
    void ProneToRoll();
    void ProneToCrouch();
    void ProneToCrawl();
    void ProneToFall();

    void ProneToForwardThrust();

#pragma endregion


#pragma endregion

#pragma region Fall

private:
    // Transition into Fall state, this function is called when the character begins to fall.
    void EnterFall();

    // Handles the physics updates while the character is falling.
    void TickFallMovement();
    float PreviousZ;

    // Transition out of Fall state, this function is called when the character stops falling.
    void ExitFall();

#pragma region Update

    void UpdateFallDamage();
    void UpdateFallDistance();
    void UpdateFallDuration();
    void UpdateFallTotalTime();

#pragma endregion

#pragma region Transition

    /* Basic Mobility */
    void FallToIdle();
    void FallToWalk();
    void FallToRun();
    void FallToCrouch();
    void FallToCrawl();

    /* Special Mobility */
    void FallToSlide();
    void FallToRoll();
    void FallToWallRun();
    void FallToVerticalWallRun();
    void FallToHang();
    void FallToJump();

    /* Advance Mobility */
    void FallToGlide();
    void FallToSwim();
    void FallToDive();
    void FallToHover();
    void FallToFly();

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region SpecialMobilityState

#pragma region Alias

    static constexpr ESpecialMovementState JumpMobility = ESpecialMovementState::Jump;
    static constexpr ESpecialMovementState SlideMobility = ESpecialMovementState::Slide;
    static constexpr ESpecialMovementState RollMobility = ESpecialMovementState::Roll;
    static constexpr ESpecialMovementState WallRunMobility = ESpecialMovementState::WallRun;
    static constexpr ESpecialMovementState VerticalWallRunMobility = ESpecialMovementState::VerticalWallRun;
    static constexpr ESpecialMovementState HangMobility = ESpecialMovementState::Hang;
    static constexpr ESpecialMovementState DashMobility = ESpecialMovementState::Dash;
    static constexpr ESpecialMovementState TeleportMobility = ESpecialMovementState::Teleport;

#pragma endregion

private:
    // Flag to determine if special mobility updates should be applied.
    bool bUpdateSpecialMobility;

    // Current special mobility state.
    ESpecialMovementState SpecialMobilityState;

public:
    // Gets the current special mobility state.
    ESpecialMovementState GetSpecialMobility() const;

    // Sets the special mobility state.
    void SetSpecialMobility(ESpecialMovementState NewSpecialMobility);

    // Checks if the current mobility state matches the given SpecialMobilityState state.
    bool IsSpecialMobility(ESpecialMovementState CheckSpecialMobility) const;

private:
    void SwitchSpecialMobilityState(ESpecialMovementState InSpecialMobility);

#pragma region Jump

private:
    void EnterJump();
    void TickJumpMovement();
    void ExitJump();

#pragma region Utility

    /* Checks if the jump height is valid based on the given distance */
    bool ValidJumpHeight(float Distance) const;

    float CalculateJumpZVelocity();

#pragma endregion

#pragma region Perform

    void PerformWallRunJump();
    void PerformVerticalWallRunJump();
    void PerformHangJump();
    void PerformCoyoteJump();

#pragma endregion

#pragma region Update

    void UpdateJumpDuration();
    void UpdateJumpTotalTime();
    void UpdateJumpTravelDistance();
    void UpdateJumpStamina();

#pragma endregion

#pragma region Transition

    /* Basic Mobility */
    void JumpToIdle();
    void JumpToWalk();
    void JumpToRun();

    /* Special Mobility */
    void JumpToMantle();
    void JumpToWallRun();
    void JumpToVerticalWallRun();
    void JumpToHang();
    void JumpToDash();

    /* Advanced Mobility */
    void JumpToGlide();
    void JumpToDive();
    void JumpToFall();

#pragma endregion

#pragma endregion

#pragma region Slide
private:
    void EnterSlide();
    void TickSlideMovement();
    void ExitSlide();

#pragma region Perform

    void PerformSlideMovement();

#pragma endregion

#pragma region Update

    void UpdateSlideDuration();
    void UpdateSlideTotalTime();
    void UpdateSlideStamina();
    void UpdateSlideTravelDistance();
    
#pragma endregion

#pragma region Transition

    /* Basic Mobility */
    void SlideToIdle();
    void SlideToWalk();
    void SlideToRun();
    void SlideToCrouch();
    void SlideToProne();
    void SlideToCrawl();
    void SlideToFall();

    /* Special Mobility */
    void SlideToJump();
    void SlideToRoll();
    void SlideToDash();

    /* Advanced Mobility */
    void SlideToSwim();
    void SlideToHover();
    void SlideToFly();

#pragma endregion


#pragma endregion

#pragma region Roll
private:
    void EnterRoll();
    void TickRollMovement();
    void ExitRoll();

#pragma region Update

    void UpdateRollStamina();
    void UpdateRollDuration();
    void UpdateRollTotalTime();
    void UpdateRollTravelDistance();

#pragma endregion

#pragma region Transition

    /* Basic Roll Transitions */
    void RollToIdle();
    void RollToWalk();
    void RollToRun();
    void RollToCrouch();
    void RollToProne();
    void RollToCrawl();
    void RollToFall();

    /* Special Roll Transitions */
    void RollToJump();
    void RollToSlide();
    void RollToDash();

#pragma endregion

#pragma endregion

#pragma region WallRun

private:
    void EnterWallRun();
    void TickWallRunMovement();
    void ExitWallRun();

#pragma region Update

    void UpdateWallRunStamina();

    void UpdateWallRunDuration();
    void UpdateWallRunTotalTime();
    void UpdateWallRunTravelDistance();
    
#pragma endregion

#pragma region Transition

    void WallRunToIdle();
    void WallRunToWalk();
    void WallRunToRun();

    void WallRunToFall();
    void WallRunToJump();
    void WallRunToEdgeJump();
    void WallRunToMantle();
    
#pragma endregion

#pragma region Utility

    bool DiagonalWallDetected();

    void PerformWallRunMovement();
    bool WallRunDetection();
    bool IsWallRunEdgeReached();
    bool IsWallRunPathBlocked();

#pragma endregion

#pragma endregion

#pragma region VerticalWallRun

private:
    void EnterVerticalWallRun();
    void TickVerticalWallRunMovement();
    void ExitVerticalWallRun();

#pragma region Perform

    void PerformVerticalWallRunMovement();

#pragma endregion

#pragma region Utility

    void VerticalWallRunReadyToAttemptTimerCompleted();

    bool VerticalWallRunDetection();

#pragma endregion   

#pragma region Update

    void UpdateVerticalWallRunStamina();

    void UpdateVerticalWallRunDuration();
    void UpdateVerticalWallRunTotalTime();
    void UpdateVerticalWallRunTravelDistance();

#pragma endregion

#pragma region Transition

    void VerticalWallRunToIdle();
    void VerticalWallRunToJump();
    void VerticalWallRunToFall();
    void VerticalWallRunToHang();
    void VerticalWallRunToMantle();

#pragma endregion

#pragma endregion

#pragma region Hang

#pragma region Classcycle

    void EnterHang();
    void TickHangMovement();
    void ExitHang();

#pragma endregion

#pragma region Perform  

	void PerformHangMovement();

#pragma endregion

#pragma region Utility

    void AdjustCapsuleHangLocation();

#pragma endregion

#pragma region Update

    void UpdateHangStamina();
    void UpdateHangDuration();
    void UpdateHangTotalTime();

#pragma endregion

#pragma region Transition

    void HangToJump();
    void HangToMantle();
    void HangToFall();

#pragma endregion

#pragma endregion

#pragma region Dash

private:
    void EnterDash();
    void TickDashMovement();
    void ExitDash();

#pragma region Update

    void UpdateDashStamina();
    void UpdateDashDuration();
    void UpdateDashTotalTime();
    void UpdateDashTravelDistance();

#pragma endregion

#pragma region Utility

    bool ValidDashRange(float Distance) const;

#pragma endregion

#pragma endregion

#pragma region Teleport

#pragma region Classcycle

private:
    void EnterTeleport();
    void TickTeleportMovement();
    void ExitTeleport();

#pragma endregion

#pragma region Utility

	bool TeleportDetection();

#pragma endregion

#pragma region Perform

	void PerformTeleportMovement();

#pragma endregion

#pragma region Update

	void UpdateTeleportEnergy();
	void UpdateTeleportDuration();
	void UpdateTeleportTotalTime();
	void UpdateTeleportTravelDistance();

#pragma endregion 

#pragma region Transition

	/* Basic Mobility */
	void TeleportToIdle();
    void TeleportToFall();
    void TeleportToCrawl();

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region AdvanceMobilityState


private:
    // Flag to determine if advanced mobility updates should be applied.
    bool bUpdateAdvanceMobility;

    // Current advanced mobility state.
    EAdvanceMovementState AdvanceMobilityState;

public:
    // Gets the current advanced mobility state.
    EAdvanceMovementState GetAdvanceMobility() const;

    // Sets the advanced mobility state.
    void SetAdvanceMobility(EAdvanceMovementState NewAdvanceMobility);

    // Checks if the current mobility state matches the given AdvanceMobilityState state.
    bool IsAdvanceMobility(EAdvanceMovementState CheckAdvanceMobility) const;

private:
    void SwitchAdvanceMobilityState(EAdvanceMovementState InAdvanceMobility);

#pragma region Vault

    void EnterVault();
    void TickVaultMovement();
    void ExitVault();

#pragma region Perform

    void PerformVaultMovement();

#pragma endregion

#pragma region Update

    void UpdateVaultStamina();
    void UpdateVaultDuration();
    void UpdateVaultTotalTime();
    void UpdateVaultTravelDistance();

#pragma endregion

#pragma region Utility

    bool VaultCheck();

    bool VaultHeightDetection();

    bool VaultWitdhDetection();

    bool VaultCapsuleSizeHeightValidation();

#pragma endregion

#pragma endregion

#pragma region Mantle

#pragma region Lifecycle

    void EnterMantle();
    void TickMantleMovement();
    void ExitMantle();

#pragma endregion

#pragma region Perform

    void PerformMantleMovement();

#pragma endregion

#pragma region Update

    void UpdateMantleStamina();

    void UpdateMantleDuration();
    void UpdateMantleTotalTime();
    void UpdateMantleTravelDistance();

#pragma endregion

#pragma region Utility

    bool MantleDetection();

#pragma endregion

#pragma endregion

#pragma region Glide

#pragma region Lifecycle 

    void EnterGlide();
    void TickGlideMovement();
    void ExitGlide();

#pragma endregion

#pragma region Perform

    void PerformGlideMovement();

#pragma endregion

#pragma region Update

    void UpdateGlideDuration();
    void UpdateGlideTotalTime();
    void UpdateGlideTravelDistance();

#pragma endregion

#pragma region Utility

#pragma endregion

#pragma endregion

#pragma region Swim

#pragma region Lifecycle

    void EnterSwim();
    void TickSwimMovement();
    void ExitSwim();

#pragma endregion

#pragma region Perform

#pragma endregion

#pragma region Update

    void UpdateSwimDuration();

#pragma endregion

#pragma endregion

#pragma region Dive

    void EnterDive();
    void TickDiveMovement();
    void ExitDive();

    void UpdateDiveDuration();

#pragma endregion

#pragma region Hover

    void EnterHover();
    void TickHoverMovement();
    void ExitHover();

    void UpdateHoverDuration();

#pragma endregion

#pragma region Fly

    void EnterFly();
    void TickFlyMovement();
    void ExitFly();

    void UpdateFlyDuration();

#pragma endregion

#pragma region Grappling
private:
    void EnterGrappling();
    void TickGrapplingMovement();
    void ExitGrappling();

#pragma region Perform

    void PerformGraplingMovement();

#pragma endregion

#pragma region Update

    void UpdateGrapplingDuration();
    void UpdateGrapplingTotalTime();
    void UpdateGrapplingStamina();

#pragma endregion

#pragma region Transition

    /* Basic Mobility */
    void GrapplingToCrawl();
    void GrapplingToFall();

    /* Special Mobility */
    void GrapplingToJump();
    void GrapplingToDash();

    /* Advanced Mobility */
    void GrapplingToSwim();

#pragma endregion

#pragma region Utility

    bool DetectGrappling();

#pragma endregion

#pragma endregion

#pragma region Zipline

	void EnterZipline();
	void PhysZipline();
	void ExitZipline();

#pragma region Perform

	void PerformZiplineMovement();

#pragma endregion

#pragma region Update

	void UpdateZiplineDuration();
	void UpdateZiplineTotalTime();
	void UpdateZiplineStamina();
	void UpdateZiplineTravelDistance();

#pragma endregion

#pragma region Utility

	bool DetectZipline();

#pragma endregion

#pragma region Transtion

	void ZiplineToIdle();
	void ZiplineToWalk();
	void ZiplineToRun();
	void ZiplineToCrawl();
	void ZiplineToFall();

#pragma endregion

#pragma endregion

#pragma endregion



#pragma region Configuration

#pragma region SystemCore

private:
    FSystemCore* SystemCore = nullptr;

public:
    FSystemCore* GetSystemCore();

    void SetSystemCore(FSystemCore* InSystemCore);

#pragma endregion

#pragma endregion


};
