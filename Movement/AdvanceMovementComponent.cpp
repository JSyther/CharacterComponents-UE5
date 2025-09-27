
#include "Character/Component/Movement/AdvanceMovementComponent.h"
#include "Configuration/Game/Data/SystemCore.h"
#include "PlayerController/PlayerInputCache.h"
#include "Components/CapsuleComponent.h"

#pragma region Constructor 

 Constructor for UAdvanceMovementComponent
UAdvanceMovementComponent::UAdvanceMovementComponent()
{

}

#pragma endregion

#pragma region Class-Cycle


void UAdvanceMovementComponent::BeginPlay()
{
    Super::BeginPlay();
    InitializeAdvanceMovementComponent();
}

void UAdvanceMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    Local_UpdateMovement(MovementData.GetCurrentMovementType());
}

void UAdvanceMovementComponent::InitializeAdvanceMovementComponent()
{
    MaxAcceleration             = 2048.0f;  // High acceleration for air strafing
    AirControl                  = 0.85f;    // Allows sharp mid-air turns
    GroundFriction              = 3.0f;     // Smooth stopping on ground
    BrakingDecelerationWalking  = 0.0f;     // No slowdown while moving


    GravityScale                = 1.0f;
}

#pragma endregion

#pragma region Network

#pragma endregion

#pragma region Utility

float UAdvanceMovementComponent::DeltaSeconds()
{
    if (UWorld* World = GetWorld())
    {
        return World->GetDeltaSeconds();
    }

    return 0.0f;
}

#pragma endregion

#pragma region Owner


ACharacterModule* UAdvanceMovementComponent::GetOwnerCharacter() const
{
    if (OwnerCharacter != nullptr)
    {
        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Verbose, TEXT("OwnerCharacter is already valid."));
        #endif

        return OwnerCharacter.Get();
    }

    ACharacterModule* ResolvedOwner = Cast<ACharacterModule>(GetOwner());
    if (!ResolvedOwner)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("Failed to resolve owner as ACharacterModule");
        #endif

        return nullptr;
    }

    #if DEV_DEBUG_MODE
    LOG_INFO("OwnerCharacter was null. Resolved and cached from GetOwner().");
    #endif

     Lazily cache the result (safe to cast away const here)
    const_cast<UAdvanceMovementComponent*>(this)->OwnerCharacter = ResolvedOwner;
    return ResolvedOwner;
}



void UAdvanceMovementComponent::SetOwnerCharacter(ACharacterModule* InOwnerCharacter)
{
    OwnerCharacter = InOwnerCharacter; 

#if DEV_DEBUG_MODE
    if (OwnerCharacter == nullptr)
    {
        LOG_ERROR("OwnerCharacter is null after SetOwnerCharacter call!");
    }
    else
    {
        LOG_INFO("OwnerCharacter is not null after SetOwnerCharacter call.");
    }
#endif
}

#pragma endregion

#pragma region OwnerData

FCharacterData* UAdvanceMovementComponent::GetOwnerData() const
{
    return OwnerData;
}


void UAdvanceMovementComponent::SetOwnerData(FCharacterData* InOwnerData)
{
    if (InOwnerData == nullptr)
    {
#if DEV_DEBUG_MODE
        LOG_ERROR("Attempted to set OwnerData to nullptr, operation ignored.");
#endif
        return;
    }

    OwnerData = InOwnerData;

#if DEV_DEBUG_MODE
    LOG_INFO("OwnerData reference successfully updated.");
#endif
}



#pragma endregion

#pragma region OwnerAbility

void UAdvanceMovementComponent::UpdateCharacterAbility(FCharacterAbility* Ability)
{
    if (!Ability)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("");
        #endif
        return;
    }

    const FMovementAbility& MovementAbility = Ability->GetMovementAbility();
    auto& Modules = MovementData.GetMovementModules();

    const FAbilityModule* SprintModule = MovementAbility.GetAbilities().Find(EMovementAbilityType::Sprint);
    if (SprintModule && SprintModule->AbilityLocked())
    {
        if (FMovementModule* SprintMovement = Modules.Find(EMovementType::Sprint))
        {
            SprintMovement->SetPhase(EMovementPhase::ReadyToAttempt);
        }
        else
        {
            #if DEV_DEBUG_MODE
            LOG_ERROR("Sprint movement module not found.");
            #endif

        }
    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Jump))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::DoubleJump))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::CoyoteJump))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Crouch))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Prone))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Roll))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Slide))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::WallRun))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::VerticalWallRun))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Hang))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Dash))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Teleport))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Vault))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Mantle))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Glide))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Swim))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Dive))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Hover))
    {

    }

    if (MovementAbility.GetAbilities().Contains(EMovementAbilityType::Fly))
    {

    }

}

void UAdvanceMovementComponent::SetOwnerAbility(FCharacterAbility* InAbility)
{
    if (InAbility == nullptr)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("Attempted to set OwnerAbility to nullptr. Operation ignored.");
        #endif
        return;
    }

    OwnerAbility = InAbility;

    #if DEV_DEBUG_MODE
    LOG_INFO("OwnerAbility successfully updated.");
    #endif
}

FCharacterAbility* UAdvanceMovementComponent::GetOwnerAbility() const
{
    return OwnerAbility;
}


#pragma endregion

#pragma region CharacterAttribute

void UAdvanceMovementComponent::SetOwnerAttribute(FCharacterAttribute* InAttribute)
{
    if (InAttribute == nullptr)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("Attempted to set OwnerAttribute to nullptr. Operation ignored.");
        #endif
        return;
    }

    OwnerAttribute = InAttribute;

#if DEV_DEBUG_MODE
    LOG_INFO("OwnerAttribute successfully updated.");
#endif
}

FCharacterAttribute* UAdvanceMovementComponent::GetOwnerAttribute() const
{
    return OwnerAttribute;
}

#pragma endregion

#pragma region CharacterLevel

void UAdvanceMovementComponent::SetOwnerLevel(FCharacterLevel* InLevel)
{
    if (InLevel == nullptr)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("Attempted to set OwnerLevel to nullptr. Operation ignored.");
        #endif
        return;
    }

    OwnerLevel = InLevel;

#if DEV_DEBUG_MODE
    LOG_INFO("OwnerLevel successfully updated.");
#endif
}

FCharacterLevel* UAdvanceMovementComponent::GetOwnerLevel() const
{
    return OwnerLevel;
}

#pragma endregion

#pragma region PlayerInputCache

UPlayerInputCache* UAdvanceMovementComponent::GetPlayerInputCache() const
{
    return PlayerInputCache.Get();
}

void UAdvanceMovementComponent::SetPlayerInputCache(UPlayerInputCache* NewPlayerInputCache)
{
    PlayerInputCache = NewPlayerInputCache;

#if DEV_DEBUG_MODE
    if (PlayerInputCache == nullptr)
    {
        LOG_INFO("PlayerInputCache cleared (nullptr) in SetPlayerInputCache.");
    }
    else
    {
        LOG_INFO("PlayerInputCache updated.");
    }
#endif
}

#pragma endregion

#pragma region MovementData

FCharacterMovement& UAdvanceMovementComponent::GetMovementData()
{
    return MovementData;
}

const FCharacterMovement& UAdvanceMovementComponent::GetMovementData() const
{
    return MovementData;
}

void UAdvanceMovementComponent::SetMovementData(const FCharacterMovement& InMovement)
{
    MovementData = InMovement;
}

#pragma endregion

#pragma region Switch

void UAdvanceMovementComponent::SwitchMovement(EMovementType PreviousType, EMovementType CurrentType)
{
    switch (NetworkType)
    {
    case Local:
        Local_DeactivateMovement(PreviousType);
        Local_ActivateMovement(CurrentType);
        break;

    case Online:
        break;
    }
}

#pragma endregion

#pragma region Activate




void UAdvanceMovementComponent::InitializeActivateMovementHandlers()
{
    ActivateMovementHandlers.Add(Idle,                  [this]() { ActivateIdle(); });
    ActivateMovementHandlers.Add(Walk,                  [this]() { ActivateWalk(); });
    ActivateMovementHandlers.Add(Run,                   [this]() { ActivateRun(); });
    ActivateMovementHandlers.Add(Sprint,                [this]() { ActivateSprint(); });
    ActivateMovementHandlers.Add(EMovementType::Crouch, [this]() { ActivateCrouch(); });
    ActivateMovementHandlers.Add(Prone,                 [this]() { ActivateProne(); });
    ActivateMovementHandlers.Add(Crawl,                 [this]() { ActivateCrawl(); });
    ActivateMovementHandlers.Add(Fall,                  [this]() { ActivateFall(); });
    ActivateMovementHandlers.Add(Jump,                  [this]() { ActivateJump(); });
    ActivateMovementHandlers.Add(Slide,                 [this]() { ActivateSlide(); });
    ActivateMovementHandlers.Add(Roll,                  [this]() { ActivateRoll(); });
    ActivateMovementHandlers.Add(WallRun,               [this]() { ActivateWallRun(); });
    ActivateMovementHandlers.Add(VerticalWallRun,       [this]() { ActivateVerticalWallRun(); });
    ActivateMovementHandlers.Add(Hang,                  [this]() { ActivateHang(); });
    ActivateMovementHandlers.Add(Dash,                  [this]() { ActivateDash(); });
    ActivateMovementHandlers.Add(Teleport,              [this]() { ActivateTeleport(); });
    ActivateMovementHandlers.Add(Vault,                 [this]() { ActivateVault(); });
    ActivateMovementHandlers.Add(Mantle,                [this]() { ActivateMantle(); });
    ActivateMovementHandlers.Add(Glide,                 [this]() { ActivateGlide(); });
    ActivateMovementHandlers.Add(EMovementType::Swim,   [this]() { ActivateSwim(); });
    ActivateMovementHandlers.Add(Dive,                  [this]() { ActivateDive(); });
    ActivateMovementHandlers.Add(Hover,                 [this]() { ActivateHover(); });
    ActivateMovementHandlers.Add(Fly,                   [this]() { ActivateFly(); });
    ActivateMovementHandlers.Add(Grappling,             [this]() { ActivateGrappling(); });
    ActivateMovementHandlers.Add(Zipline,               [this]() { ActivateZipline(); });
}

void UAdvanceMovementComponent::ActivateIdle()
{
     Get a mutable reference to the module map
    TMap<EMovementType, FMovementModule>& Modules = MovementData.GetMovementModules();

     Try to find the Idle movement module
    FMovementModule* Module = Modules.Find(Idle);

     Validate the module and on it
    if (!Module || Module->Locked())
    {
        LOG_ERROR("Idle movement module is either missing or currently locked.");
        return;
    }

    const FMovementAttribute& Attribute = Module->GetMovementAttributes();
    FMovementProgress& Progress         = Module->GetMovementProgress();

    switch (NetworkType)
    {
    case ENetworkType::Local:
        switch (GetOwnerType())
        {
        case ECharacterType::Player:
            Progress.UpdateAttemptCount();
            Progress.UpdateDuration(DeltaSeconds());

            if (SystemCore->GetMovementConfiguration().InterpolateMovementSpeedDisabled())
            {
                MaxWalkSpeed = Attribute.GetDesiredSpeed();
            }

            Module->SetMovementPhase(InProgress);
            Module->SetMovementUpdate(Enabled);
            break;
        }
        
        break;
    }
}

void UAdvanceMovementComponent::Local_ActivateMovement(EMovementType Type)
{
    if (const TFunction<void()>* Handler = ActivateMovementHandlers.Find(Type))
    {
        (*Handler)();
    }
#if DEV_DEBUG_MODE
    else
    {
        LOG_ERROR("Failed to activate movement: No handler found for requested type.");
    }
#endif
}


void UAdvanceMovementComponent::ActivateWalk()
{
     TODO: Implement ActivateWalk logic
}

void UAdvanceMovementComponent::ActivateRun()
{
     TODO: Implement ActivateRun logic
}

void UAdvanceMovementComponent::ActivateSprint()
{
     TODO: Implement ActivateSprint logic
}

void UAdvanceMovementComponent::ActivateCrouch()
{
     TODO: Implement ActivateCrouch logic
}

void UAdvanceMovementComponent::ActivateProne()
{
     TODO: Implement ActivateProne logic
}

void UAdvanceMovementComponent::ActivateCrawl()
{
     TODO: Implement ActivateCrawl logic
}

void UAdvanceMovementComponent::ActivateFall()
{
     TODO: Implement ActivateFall logic
}

void UAdvanceMovementComponent::ActivateJump()
{
     TODO: Implement ActivateJump logic
}

void UAdvanceMovementComponent::ActivateSlide()
{
     TODO: Implement ActivateSlide logic
}

void UAdvanceMovementComponent::ActivateRoll()
{
     TODO: Implement ActivateRoll logic
}

void UAdvanceMovementComponent::ActivateWallRun()
{
     TODO: Implement ActivateWallRun logic
}

void UAdvanceMovementComponent::ActivateVerticalWallRun()
{
     TODO: Implement ActivateVerticalWallRun logic
}

void UAdvanceMovementComponent::ActivateHang()
{
     TODO: Implement ActivateHang logic
}

void UAdvanceMovementComponent::ActivateDash()
{
     TODO: Implement ActivateDash logic
}

void UAdvanceMovementComponent::ActivateTeleport()
{
     TODO: Implement ActivateTeleport logic
}

void UAdvanceMovementComponent::ActivateVault()
{
     TODO: Implement ActivateVault logic
}

void UAdvanceMovementComponent::ActivateMantle()
{
     TODO: Implement ActivateMantle logic
}

void UAdvanceMovementComponent::ActivateGlide()
{
     TODO: Implement ActivateGlide logic
}

void UAdvanceMovementComponent::ActivateSwim()
{
     TODO: Implement ActivateSwim logic
}

void UAdvanceMovementComponent::ActivateDive()
{
     TODO: Implement ActivateDive logic
}

void UAdvanceMovementComponent::ActivateHover()
{
     TODO: Implement ActivateHover logic
}

void UAdvanceMovementComponent::ActivateFly()
{
     TODO: Implement ActivateFly logic
}

void UAdvanceMovementComponent::ActivateGrappling()
{
     TODO: Implement ActivateGrappling logic
}

void UAdvanceMovementComponent::ActivateZipline()
{
     TODO: Implement ActivateZipline logic
}

#pragma endregion

#pragma region Update

void UAdvanceMovementComponent::InitializeUpdateMovementHandlers()
{
    UpdateMovementHandlers.Add(EMovementType::Idle, [this]() { UpdateIdle(); });
    UpdateMovementHandlers.Add(EMovementType::Walk, [this]() { UpdateWalk(); });
    UpdateMovementHandlers.Add(EMovementType::Run, [this]() { UpdateRun(); });
    UpdateMovementHandlers.Add(EMovementType::Sprint, [this]() { UpdateSprint(); });
    UpdateMovementHandlers.Add(EMovementType::Crouch, [this]() { UpdateCrouch(); });
    UpdateMovementHandlers.Add(EMovementType::Prone, [this]() { UpdateProne(); });
    UpdateMovementHandlers.Add(EMovementType::Crawl, [this]() { UpdateCrawl(); });
    UpdateMovementHandlers.Add(EMovementType::Fall, [this]() { UpdateFall(); });
    UpdateMovementHandlers.Add(EMovementType::Jump, [this]() { UpdateJump(); });
    UpdateMovementHandlers.Add(EMovementType::Slide, [this]() { UpdateSlide(); });
    UpdateMovementHandlers.Add(EMovementType::Roll, [this]() { UpdateRoll(); });
    UpdateMovementHandlers.Add(EMovementType::WallRun, [this]() { UpdateWallRun(); });
    UpdateMovementHandlers.Add(EMovementType::VerticalWallRun, [this]() { UpdateVerticalWallRun(); });
    UpdateMovementHandlers.Add(EMovementType::Hang, [this]() { UpdateHang(); });
    UpdateMovementHandlers.Add(EMovementType::Dash, [this]() { UpdateDash(); });
    UpdateMovementHandlers.Add(EMovementType::Teleport, [this]() { UpdateTeleport(); });
    UpdateMovementHandlers.Add(EMovementType::Vault, [this]() { UpdateVault(); });
    UpdateMovementHandlers.Add(EMovementType::Mantle, [this]() { UpdateMantle(); });
    UpdateMovementHandlers.Add(EMovementType::Glide, [this]() { UpdateGlide(); });
    UpdateMovementHandlers.Add(EMovementType::Swim, [this]() { UpdateSwim(); });
    UpdateMovementHandlers.Add(EMovementType::Dive, [this]() { UpdateDive(); });
    UpdateMovementHandlers.Add(EMovementType::Hover, [this]() { UpdateHover(); });
    UpdateMovementHandlers.Add(EMovementType::Fly, [this]() { UpdateFly(); });
    UpdateMovementHandlers.Add(EMovementType::Grappling, [this]() { UpdateGrappling(); });
    UpdateMovementHandlers.Add(EMovementType::Zipline, [this]() { UpdateZipline(); });
}


bool UAdvanceMovementComponent::IsUpdateEnabled(EMovementType Type)
{
    const TMap<EMovementType, FMovementModule>& Modules = MovementData.GetMovementModules();

    if (const FMovementModule* Module = Modules.Find(Type))
    {
        return Module->GetUpdate() == Enabled;
    }

#if DEV_DEBUG_MODE
    LOG_ERROR("IsMovementActive: MovementType not found in modules.");
#endif

    return false;
}

void UAdvanceMovementComponent::Local_UpdateMovement(EMovementType Type)
{
    if (const TFunction<void()>* Handler = UpdateMovementHandlers.Find(Type))
    {
        (*Handler)();
    }
#if DEV_DEBUG_MODE
    else
    {
        LOG_ERROR("");
    }
#endif
}

void UAdvanceMovementComponent::UpdateIdle()
{
     Get a mutable reference to the module map
    TMap<EMovementType, FMovementModule>& Modules = MovementData.GetMovementModules();

     Try to find the Idle movement module
    FMovementModule* Module = Modules.Find(EMovementType::Idle);

     Validate the module and update it
    if (!Module || Module->UpdateDisabled())
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("");
        #endif

        return;
    }

    const FMovementAttribute& Attribute = Module->GetMovementAttributes();
    FMovementProgress& Progress         = Module->GetMovementProgress(); 

    switch (GetOwnerType())
    {
    case ECharacterType::Player:
    {
        switch (NetworkType)
        {
        case ENetworkType::Local:

            if (Module->IsInProgress())
            {
                Progress.UpdateDuration(DeltaSeconds());

                if (SystemCore->GetMovementConfiguration().InterpolateMovementSpeedEnabled())
                {
                    MaxWalkSpeed = FMath::FInterpTo(MaxWalkSpeed, Attribute.GetDesiredSpeed(), DeltaSeconds(), Attribute.GetInterpolationSpeed());
                }

                if (OwnerData)
                {
                    OwnerData->GetCharacterAttribute().CharacterStat.RegenerateStamina(1);
                }


                if (PlayerInputCache && PlayerInputCache->AnyMovementInputActive())
                {
                    if (PlayerInputCache->InputWalkHeld() || PlayerInputCache->InputWalkPressed() || SystemCore->GetMovementConfiguration().WalkEnabled())
                    {
                        SwitchMovement(Walk);
                    }
                }
            }

        case ENetworkType::Online:

            break;
        }
        break;
    }


    case ECharacterType::AI:
    {
         TODO: Idle behavior for AI characters
        break;
    }

    default:
        break;
    }

}

void UAdvanceMovementComponent::UpdateIdle()
{
     TODO: Implement UpdateIdle logic
}

void UAdvanceMovementComponent::UpdateWalk()
{
     TODO: Implement UpdateWalk logic
}

void UAdvanceMovementComponent::UpdateRun()
{
     TODO: Implement UpdateRun logic
}

void UAdvanceMovementComponent::UpdateSprint()
{
     TODO: Implement UpdateSprint logic
}

void UAdvanceMovementComponent::UpdateCrouch()
{
     TODO: Implement UpdateCrouch logic
}

void UAdvanceMovementComponent::UpdateProne()
{
     TODO: Implement UpdateProne logic
}

void UAdvanceMovementComponent::UpdateCrawl()
{

}

void UAdvanceMovementComponent::UpdateFall()
{

}

void UAdvanceMovementComponent::UpdateJump()
{

}

void UAdvanceMovementComponent::UpdateSlide()
{

}

void UAdvanceMovementComponent::UpdateRoll()
{

}

void UAdvanceMovementComponent::UpdateWallRun()
{

}

void UAdvanceMovementComponent::UpdateVerticalWallRun()
{

}

void UAdvanceMovementComponent::UpdateHang()
{

}

void UAdvanceMovementComponent::UpdateDash()
{

}

void UAdvanceMovementComponent::UpdateTeleport()
{

}

void UAdvanceMovementComponent::UpdateVault()
{

}

void UAdvanceMovementComponent::UpdateMantle()
{

}

void UAdvanceMovementComponent::UpdateGlide()
{

}

void UAdvanceMovementComponent::UpdateSwim()
{

}

void UAdvanceMovementComponent::UpdateDive()
{

}

void UAdvanceMovementComponent::UpdateHover()
{

}

void UAdvanceMovementComponent::UpdateFly()
{

}

void UAdvanceMovementComponent::UpdateGrappling()
{

}

void UAdvanceMovementComponent::UpdateZipline()
{

}

#pragma endregion

#pragma region Deactivate

void UAdvanceMovementComponent::InitializeDeactivateMovementHandlers()
{
    DeactivateMovementHandlers.Add(EMovementType::Idle,             [this]() { DeactivateIdle(); });
    DeactivateMovementHandlers.Add(EMovementType::Walk,             [this]() { DeactivateWalk(); });
    DeactivateMovementHandlers.Add(EMovementType::Run,              [this]() { DeactivateRun(); });
    DeactivateMovementHandlers.Add(EMovementType::Sprint,           [this]() { DeactivateSprint(); });
    DeactivateMovementHandlers.Add(EMovementType::Crouch,           [this]() { DeactivateCrouch(); });
    DeactivateMovementHandlers.Add(EMovementType::Prone,            [this]() { DeactivateProne(); });
    DeactivateMovementHandlers.Add(EMovementType::Crawl,            [this]() { DeactivateCrawl(); });
    DeactivateMovementHandlers.Add(EMovementType::Fall,             [this]() { DeactivateFall(); });
    DeactivateMovementHandlers.Add(EMovementType::Jump,             [this]() { DeactivateJump(); });
    DeactivateMovementHandlers.Add(EMovementType::Slide,            [this]() { DeactivateSlide(); });
    DeactivateMovementHandlers.Add(EMovementType::Roll,             [this]() { DeactivateRoll(); });
    DeactivateMovementHandlers.Add(EMovementType::WallRun,          [this]() { DeactivateWallRun(); });
    DeactivateMovementHandlers.Add(EMovementType::VerticalWallRun,  [this]() { DeactivateVerticalWallRun(); });
    DeactivateMovementHandlers.Add(EMovementType::Hang,             [this]() { DeactivateHang(); });
    DeactivateMovementHandlers.Add(EMovementType::Dash,             [this]() { DeactivateDash(); });
    DeactivateMovementHandlers.Add(EMovementType::Teleport,         [this]() { DeactivateTeleport(); });
    DeactivateMovementHandlers.Add(EMovementType::Vault,            [this]() { DeactivateVault(); });
    DeactivateMovementHandlers.Add(EMovementType::Mantle,           [this]() { DeactivateMantle(); });
    DeactivateMovementHandlers.Add(EMovementType::Glide,            [this]() { DeactivateGlide(); });
    DeactivateMovementHandlers.Add(EMovementType::Swim,             [this]() { DeactivateSwim(); });
    DeactivateMovementHandlers.Add(EMovementType::Dive,             [this]() { DeactivateDive(); });
    DeactivateMovementHandlers.Add(EMovementType::Hover,            [this]() { DeactivateHover(); });
    DeactivateMovementHandlers.Add(EMovementType::Fly,              [this]() { DeactivateFly(); });
    DeactivateMovementHandlers.Add(EMovementType::Grappling,        [this]() { DeactivateGrappling(); });
    DeactivateMovementHandlers.Add(EMovementType::Zipline,          [this]() { DeactivateZipline(); });
}

void UAdvanceMovementComponent::Local_DeactivateMovement(EMovementType Type)
{
    if (const TFunction<void()>* Handler = DeactivateMovementHandlers.Find(Type))
    {
        (*Handler)();
    }
#if DEV_DEBUG_MODE
    else
    {
        LOG_ERROR("No handler found for the given MovementType.");
    }
#endif
}

void UAdvanceMovementComponent::DeactivateIdle()
{

}

void UAdvanceMovementComponent::DeactivateWalk()
{

}

void UAdvanceMovementComponent::DeactivateRun()
{

}

void UAdvanceMovementComponent::DeactivateSprint()
{

}

void UAdvanceMovementComponent::DeactivateCrouch()
{

}

void UAdvanceMovementComponent::DeactivateProne()
{

}

void UAdvanceMovementComponent::DeactivateCrawl()
{

}

void UAdvanceMovementComponent::DeactivateFall()
{
}

void UAdvanceMovementComponent::DeactivateJump()
{
}

void UAdvanceMovementComponent::DeactivateSlide()
{
}

void UAdvanceMovementComponent::DeactivateRoll()
{
}

void UAdvanceMovementComponent::DeactivateWallRun()
{
}

void UAdvanceMovementComponent::DeactivateVerticalWallRun()
{
}

void UAdvanceMovementComponent::DeactivateHang()
{
}

void UAdvanceMovementComponent::DeactivateDash()
{
}

void UAdvanceMovementComponent::DeactivateTeleport()
{
}

void UAdvanceMovementComponent::DeactivateVault()
{
}

void UAdvanceMovementComponent::DeactivateMantle()
{
}

void UAdvanceMovementComponent::DeactivateGlide()
{
}

void UAdvanceMovementComponent::DeactivateSwim()
{
}

void UAdvanceMovementComponent::DeactivateDive()
{
}

void UAdvanceMovementComponent::DeactivateHover()
{
}

void UAdvanceMovementComponent::DeactivateFly()
{
}

void UAdvanceMovementComponent::DeactivateGrappling()
{
}

void UAdvanceMovementComponent::DeactivateZipline()
{
}

#pragma endregion











#pragma region MovementState

void UAdvanceMovementComponent::SetMovementState(EMovementState NewMovementState)
{
    PreviousMovementState = CurrentMovementState;
    CurrentMovementState = NewMovementState;
}

EMovementState UAdvanceMovementComponent::GetCurrentMovementState() const
{
    return CurrentMovementState;
}

EMovementState UAdvanceMovementComponent::GetPreviousMovementState() const
{
    return PreviousMovementState;
}

void UAdvanceMovementComponent::SetCurrentMovementState(EMovementState NewState)
{
    if (CurrentMovementState != NewState)
    {
        CurrentMovementState = NewState;
        return;
    }

    #if DEV_DEBUG_MODE 
    LOG_WARNING("Already set to provided CurrentMovementState. No change applied.");
    #endif
}

void UAdvanceMovementComponent::SetPreviousMovementState(EMovementState NewState)
{
    if (PreviousMovementState != NewState)
    {
        PreviousMovementState = NewState;
        return;
    }

    #if DEV_DEBUG_MODE 
    LOG_WARNING("Already set to provided PreviousMovementState. No change applied.");
    #endif
}

bool UAdvanceMovementComponent::IsPreviousMovementState(EMovementState IsPreviousState) const
{
    return PreviousMovementState == IsPreviousState;
}

bool UAdvanceMovementComponent::IsCurrentMovementState(EMovementState IsMovementState) const
{
    return CurrentMovementState == IsMovementState;
}

#pragma endregion

#pragma region MovementSpeed

float UAdvanceMovementComponent::GetMaxWalkSpeed() const
{
    return MaxWalkSpeed;
}

void UAdvanceMovementComponent::SetMaxWalkSpeed(float NewSpeed)
{
    if (MaxWalkSpeed != NewSpeed)
    {
        MaxWalkSpeed = NewSpeed;

        #if DEV_DEBUG_MODE 
        LOG_INFO("MaxWalkSpeed updated successfully.");
        #endif

        return;
    }

    #if DEV_DEBUG_MODE
    LOG_WARNING("Already set to provided MaxWalkSpeed. No change applied.");
    #endif
}

#pragma endregion

#pragma region TickMovement

void UAdvanceMovementComponent::TickMovement()
{
    const auto CurrentType = MovementData.GetMovementType();
    const auto CurrentState = MovementData.GetMovementState();

    switch (CurrentType)
    {
    case EMovementType::Basic:
    {
        switch (CurrentState)
        {
        case EMovementState::Idle:      TickIdleMovement();     break;
        case EMovementState::Walk:      TickWalkMovement();     break;
        case EMovementState::Run:       TickRunMovement();      break;
        case EMovementState::Sprint:    TickSprintMovement();   break;
        case EMovementState::Crouch:    TickCrouchMovement();   break;
        case EMovementState::Prone:     TickProneMovement();    break;
        case EMovementState::Crawl:     TickCrawlMovement();    break;
        case EMovementState::Fall:      TickFallMovement();     break;

        default:
        #if DEV_DEBUG_MODE
        LOG_WARNING("TickMovement Basic: Unhandled movement state.");
        #endif
        break;
        }
        break;
    }

    case EMovementType::Special:
    {
        switch (CurrentState)
        {
        case EMovementState::Jump:              TickJumpMovement();             break;
        case EMovementState::Slide:             TickSlideMovement();            break;
        case EMovementState::Roll:              TickRollMovement();             break;
        case EMovementState::WallRun:           TickWallRunMovement();          break;
        case EMovementState::VerticalWallRun:   TickVerticalWallRunMovement();  break;
        case EMovementState::Hang:              TickHangMovement();             break;
        case EMovementState::Dash:              TickDashMovement();             break;
        case EMovementState::Teleport:          TickTeleportMovement();         break;

        default:
            #if DEV_DEBUG_MODE
            LOG_WARNING("TickMovement Special: Unhandled movement state.");
            #endif
            break;
        }
        break;
    }

    case EMovementType::Advance:
    {
        switch (CurrentState)
        {
        case EMovementState::Vault:     TickVaultMovement();        break;
        case EMovementState::Mantle:    TickMantleMovement();       break;
        case EMovementState::Glide:     TickGlideMovement();        break;
        case EMovementState::Swim:      TickSwimMovement();         break;
        case EMovementState::Dive:      TickDiveMovement();         break;
        case EMovementState::Hover:     TickHoverMovement();        break;
        case EMovementState::Fly:       TickFlyMovement();          break;
        case EMovementState::Grappling: TickGrapplingMovement();    break;

        default:
            #if DEV_DEBUG_MODE
            LOG_WARNING("TickMovement Advance: Unhandled movement state.");
            #endif
            break;
        }
        break;
    }

    case EMovementType::Null:
    case EMovementType::Max:

    default:
        #if DEV_DEBUG_MODE
        LOG_WARNING("TickMovement: Invalid or unhandled movement type.");
        #endif
        break;
    }
}

#pragma endregion

#pragma region CapsuleComponent

void UAdvanceMovementComponent::UpdateCapsuleHeight()
{
    float TargetHeight = 0;
    float BlendSpeed = 0;

    switch (MovementData.GetMovementState())
    {
        case EMovementState::Crouch:
            TargetHeight = Crouch->GetCapsuleHalfHeight();
            BlendSpeed = Crouch->GetCapsuleBlendSpeed();
            break;

        case EMovementState::Prone:
            TargetHeight = Prone->GetCapsuleHalfHeight();
            BlendSpeed = Prone->GetCapsuleBlendSpeed();
            break;

        case EMovementState::Crawl:
            TargetHeight = Crawl->GetCapsuleHalfHeight();
            BlendSpeed = Crawl->GetCapsuleBlendSpeed();
            break;

        case EMovementState::Slide:
            TargetHeight = Slide->GetCapsuleHalfHeight();
            BlendSpeed = Slide->GetCapsuleBlendSpeed();
            break;

        case EMovementState::Roll:
            // TODO: Roll Capsule Height
            LOG_TODO("Updating capsule height for roll is not prepared yet.!");

            // Early return since it's unimplemented
            return; 
    }

    // Apply interpolated height based on state
    InterpolateCapsuleHeight(TargetHeight, BlendSpeed); 
}

void UAdvanceMovementComponent::InterpolateCapsuleHeight(float TargetHeight, float InterpSpeed)
{
    if (!OwnerCapsuleComponent)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("OwnerCapsuleComponent is not valid.");
        #endif
        return;
    }

    if (!GetWorld())
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("WorldContext is nullptr.");
        #endif

        return;
    }

    // Cache delta time for this frame
    float DeltaTime = GetWorld()->GetDeltaSeconds(); 

    // Get current capsule half height
    float CurrentHeight = OwnerCapsuleComponent->GetScaledCapsuleHalfHeight(); 

    // Interpolate towards target
    float NewHeight = FMath::FInterpTo(CurrentHeight, TargetHeight, DeltaTime, InterpSpeed); 

    // Only update if there's a change
    if (!FMath::IsNearlyEqual(CurrentHeight, NewHeight)) 
    {
        // Apply the new interpolated height
        OwnerCapsuleComponent->SetCapsuleHalfHeight(NewHeight); 
    }
}

void UAdvanceMovementComponent::SetOwnerCapsuleComponent(TObjectPtr<UCapsuleComponent> InComp)
{
    if (!InComp)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("called with null Input component.");
        #endif
        return;
    }

    // Assign the new capsule component
    OwnerCapsuleComponent = InComp; 

    #if DEV_DEBUG_MODE
    LOG_INFO("OwnerCapsuleComponent has been set successfully.");
    #endif
}

UCapsuleComponent* UAdvanceMovementComponent::GetOwnerCapsuleComponent() const
{
    if (!OwnerCapsuleComponent)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("OwnerCapsuleComponent is not valid.");
        #endif
        return nullptr;
    }
    #if DEV_DEBUG_MODE
    LOG_INFO("OwnerCapsuleComponent returned successfully.!");
    #endif
    return OwnerCapsuleComponent;
}

#pragma endregion

#pragma region Utility

void UAdvanceMovementComponent::InterpolateMovementSpeed(float TargetSpeed, float InterpSpeed)
{
    // Early out if interpolation is disabled
    if (!SystemCore->GetMovementConfiguration().InterpolateMovementSpeedEnabled())
    {
        #if DEV_DEBUG_MODE 
        LOG_ERROR("InterpolateMovementSpeed called but interpolation is disabled in MovementConfiguration.");
        #endif 
        return;
    }

    const float DeltaTime = GetWorld()->GetDeltaSeconds(); // Cache DeltaTime
    const float CurrentSpeed = MaxWalkSpeed;

    // Only interpolate if current speed differs from target
    if (!FMath::IsNearlyEqual(CurrentSpeed, TargetSpeed))
    {
        MaxWalkSpeed = FMath::FInterpConstantTo(CurrentSpeed, TargetSpeed, DeltaTime, InterpSpeed);
    }
}

float UAdvanceMovementComponent::HorizontalVelocitySize() const
{
    FVector HorizontalVelocity = FVector(Velocity.X, Velocity.Y, 0.0f);

    return  HorizontalVelocity.Size();
}

float UAdvanceMovementComponent::LongitudinalMovementValue() const
{
    return FVector::DotProduct(GetLastInputVector(), GetOwner()->GetActorForwardVector());
}

float UAdvanceMovementComponent::LateralMovementValue() const
{
    return FVector::DotProduct(GetLastInputVector(), GetOwner()->GetActorRightVector());
}

float UAdvanceMovementComponent::PerformWallHeightTrace()
{
    // Early out if required components are missing
    if (!OwnerCapsuleComponent)
    {
        return -1.f;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return -1.f;
    }

    // Retrieve capsule properties and calculate trace start
    const float CapsuleHalfHeight = OwnerCapsuleComponent->GetScaledCapsuleHalfHeight();
    const FVector CapsuleLocation = OwnerCapsuleComponent->GetComponentLocation();
    const FVector ForwardVector = OwnerCapsuleComponent->GetForwardVector();

    const FVector TraceStart = CapsuleLocation - FVector(0.f, 0.f, CapsuleHalfHeight - GroundOffset);
    const FVector TraceEnd = TraceStart + ForwardVector * ForwardTraceDistance;

    // Prepare query parameters
    FCollisionQueryParams QueryParams;
    QueryParams.bTraceComplex = false;
    QueryParams.AddIgnoredActor(GetOwner());

    // Perform forward trace to detect wall base
    FHitResult ForwardHit;
    if (World->LineTraceSingleByChannel(ForwardHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
    {
        const FVector WallBase = ForwardHit.ImpactPoint;
        const FVector UpTraceEnd = WallBase + FVector(0.f, 0.f, MaximumWallHeight);

        // Perform upward trace from wall base to measure wall height
        FHitResult UpHit;
        if (World->LineTraceSingleByChannel(UpHit, WallBase, UpTraceEnd, ECC_Visibility, QueryParams))
        {
            return (UpHit.ImpactPoint - WallBase).Size();
        }

        // Return max wall height if upward trace does not hit
        return MaximumWallHeight;
    }

    // Return -1 if no wall is detected in front
    return -1.f;
}

float UAdvanceMovementComponent::PerformGroundDistanceTrace()
{
    if (!GetOwner() || !OwnerCapsuleComponent)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("OwnerCapsuleComponent or Owner invalid.");
        #endif
        return -1.0f;
    }

    const FVector CapsuleLocation = OwnerCapsuleComponent->GetComponentLocation();
    const float CapsuleHalfHeight = OwnerCapsuleComponent->GetUnscaledCapsuleHalfHeight();

    // Adjust start location slightly below capsule bottom to avoid self-collision
    const FVector StartLocation = CapsuleLocation - FVector(0.0f, 0.0f, CapsuleHalfHeight + 2.10f);
    const FVector EndLocation   = StartLocation - FVector(0.0f, 0.0f, 10000.0f);


    FHitResult GroundHit;
    FCollisionQueryParams QueryParams(FName(TEXT("GroundDistanceTrace")), false, GetOwner());
    QueryParams.AddIgnoredActor(GetOwner());
    QueryParams.AddIgnoredComponent(OwnerCapsuleComponent);

    const bool bHit = GetWorld()->LineTraceSingleByChannel(GroundHit, StartLocation, EndLocation, ECC_Visibility, QueryParams);


    #if DEV_DEBUG_MODE
    if (bActivateDebug)
    {
        DrawDebugLine(GetWorld(), StartLocation, EndLocation, bHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 2.0f);
    }
    #endif

    return bHit ? GroundHit.Distance : -1.0f;
}

bool UAdvanceMovementComponent::IsFrontWallDetected(float InTraceDistance)
{
    // Early out if essential components are missing
    if (!OwnerCapsuleComponent || !GetWorld())
    {
        return false;
    }

    // Get capsule location and forward direction
    const FVector CapsuleLocation   = OwnerCapsuleComponent->GetComponentLocation();
    const FVector ForwardVector     = OwnerCapsuleComponent->GetForwardVector();

    // Capsule dimensions
    const float CapsuleHalfHeight   = OwnerCapsuleComponent->GetScaledCapsuleHalfHeight();
    const float CapsuleRadius       = OwnerCapsuleComponent->GetScaledCapsuleRadius();

    // Trace parameters
    const float TraceDistance = InTraceDistance;
    FCollisionQueryParams TraceParams(FName(TEXT("FrontWallTrace")), false, GetOwner());
    TraceParams.AddIgnoredActor(GetOwner());
    TraceParams.AddIgnoredComponent(OwnerCapsuleComponent);
    TraceParams.bIgnoreTouches = true;

    // Collision channel: only detect static geometry
    const ECollisionChannel CollisionChannel = ECC_WorldStatic;

    // Define three trace start positions (mid, top, bottom)
    const FVector TraceStartMid     = CapsuleLocation + ForwardVector * CapsuleRadius;
    const FVector TraceStartTop     = TraceStartMid + FVector(0.0f, 0.0f, CapsuleHalfHeight * 0.9f);
    const FVector TraceStartBottom  = TraceStartMid - FVector(0.0f, 0.0f, CapsuleHalfHeight * 0.9f);

    // Define end points
    const FVector TraceEndMid       = TraceStartMid + ForwardVector * TraceDistance;
    const FVector TraceEndTop       = TraceStartTop + ForwardVector * TraceDistance;
    const FVector TraceEndBottom    = TraceStartBottom + ForwardVector * TraceDistance;

    // Perform traces
    FHitResult HitResultMid, HitResultTop, HitResultBottom;

    const bool bHitMid      = GetWorld()->LineTraceSingleByChannel(HitResultMid, TraceStartMid, TraceEndMid, CollisionChannel, TraceParams);
    const bool bHitTop      = GetWorld()->LineTraceSingleByChannel(HitResultTop, TraceStartTop, TraceEndTop, CollisionChannel, TraceParams);
    const bool bHitBottom   = GetWorld()->LineTraceSingleByChannel(HitResultBottom, TraceStartBottom, TraceEndBottom, CollisionChannel, TraceParams);

    #if DEV_DEBUG_MODE
    const bool bDebug = bActivateDebug;
    if (bDebug)
    {
        DrawDebugLine(GetWorld(), TraceStartMid, TraceEndMid, FColor::Red, false, 1.0f);
        DrawDebugLine(GetWorld(), TraceStartTop, TraceEndTop, FColor::Green, false, 1.0f);
        DrawDebugLine(GetWorld(), TraceStartBottom, TraceEndBottom, FColor::Blue, false, 1.0f);
    }
    #endif

    // Return true if any trace detects a static mesh (wall)
    return bHitMid || bHitTop || bHitBottom;
}

bool UAdvanceMovementComponent::DetectHang()
{
    if (!OwnerCapsuleComponent || !OwnerCharacter || !GetOwner())
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("Invalid OwnerCapsuleComponent, OwnerCharacter, or Owner detected.");
        #endif
        return false;
    }

    TObjectPtr<AActor> Owner = GetOwner();

    if (!Owner)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("Owner returned nullptr.");
        #endif
        return false;
    }

    const FVector CapsuleCenter     = OwnerCapsuleComponent->GetComponentLocation();
    const FVector CapsuleForward    = OwnerCapsuleComponent->GetForwardVector();
    const FVector UpVector          = OwnerCapsuleComponent->GetUpVector();
    const FVector DownVector        = -UpVector;

    const float CapsuleHalfHeight   = OwnerCapsuleComponent->GetUnscaledCapsuleHalfHeight();
    const float CapsuleRadius       = OwnerCapsuleComponent->GetUnscaledCapsuleRadius();
    const float TraceDistance       = 30.0f;

    if (IsCurrentMovementState(MovementStates::Fall))
    {
        const FVector HeadStart = CapsuleCenter + (UpVector * CapsuleHalfHeight);
        const FVector HeadEnd = HeadStart + (CapsuleForward * TraceDistance * 2.0f);

        #if DEV_DEBUG_MODE
        if (bActivateDebug)
        {
            DrawDebugLine(GetWorld(), HeadStart, HeadEnd, FColor::Red, true);
        }
        #endif

        FHitResult TopHit;
        FCollisionQueryParams TopQueryParams;
        TopQueryParams.AddIgnoredActor(Owner);
        TopQueryParams.AddIgnoredComponent(OwnerCapsuleComponent);
        TopQueryParams.bIgnoreTouches = true;


        const bool bTopHit = GetWorld()->LineTraceSingleByChannel(TopHit, HeadStart, HeadEnd, ECC_Visibility, TopQueryParams);

        if (!bTopHit)
        {
            const FVector CapsuleHitStart = CapsuleCenter + (UpVector * (CapsuleHalfHeight * 0.80f));
            const FVector CapsuleHitEnd = CapsuleHitStart + (CapsuleForward * TraceDistance);

            #if DEV_DEBUG_MODE
            if (bActivateDebug)
            {
                DrawDebugCapsule(GetWorld(), CapsuleHitEnd, CapsuleHalfHeight * 0.25f, CapsuleRadius * 0.50f, FQuat::Identity, FColor::Green, true);
            }
            #endif

            FHitResult CapsuleHit;
            FCollisionQueryParams CapsuleQueryParams;
            CapsuleQueryParams.AddIgnoredActor(Owner);
            CapsuleQueryParams.AddIgnoredComponent(OwnerCapsuleComponent);
            CapsuleQueryParams.bIgnoreTouches = true;

            const bool bCapsuleSweepHit = GetWorld()->SweepSingleByChannel(
                CapsuleHit,
                CapsuleHitStart,
                CapsuleHitEnd,
                FQuat::Identity,
                ECC_Visibility,
                FCollisionShape::MakeCapsule(CapsuleRadius * 0.50f, CapsuleHalfHeight * 0.25f),
                CapsuleQueryParams
            );

            if (bCapsuleSweepHit)
            {
                Hang->SetImpactPoint(CapsuleHit.ImpactPoint);
                Hang->SetImpactNormal(CapsuleHit.ImpactNormal);
                Hang->SetDirection(CapsuleHit.ImpactNormal);
                Hang->SetHangLocation(CapsuleHit.ImpactPoint);

                const FVector FeetHitStart = CapsuleCenter + (DownVector * (CapsuleHalfHeight * 0.80f));
                const FVector FeetHitEnd = FeetHitStart + (CapsuleForward * TraceDistance * 2.0f);

                #if DEV_DEBUG_MODE
                if (bActivateDebug)
                {
                    DrawDebugLine(GetWorld(), FeetHitStart, FeetHitEnd, FColor::Cyan, true);
                    DrawDebugPoint(GetWorld(), CapsuleHit.ImpactPoint, 10.0f, FColor::Orange, true);
                }
                #endif

                FHitResult FeetHit;
                FCollisionQueryParams FeetQueryParams;
                FeetQueryParams.AddIgnoredActor(Owner);
                FeetQueryParams.AddIgnoredComponent(OwnerCapsuleComponent);
                FeetQueryParams.bIgnoreTouches = true;


                const bool bFeetHit = GetWorld()->LineTraceSingleByChannel(FeetHit, FeetHitStart, FeetHitEnd, ECC_Visibility, FeetQueryParams);

                if (bFeetHit)
                {
                    LOG_INFO("Hang opportunity detected successfully (FallState).");
                    return true;
                }
            }
        }
    }
    else if (IsCurrentMovementState(MovementStates::Jump))
    {
        const FVector HeadHeightOffset = UpVector * (CapsuleHalfHeight * 0.8f);
        const FVector HeadTraceStart = CapsuleCenter + HeadHeightOffset;
        const FVector HeadTraceEnd = HeadTraceStart + (CapsuleForward * TraceDistance);

        const FVector CenterTraceStart = CapsuleCenter;
        const FVector CenterTraceEnd = CenterTraceStart + (CapsuleForward * TraceDistance);

        const FVector FootHeightOffset = DownVector * (CapsuleHalfHeight * 0.8f);
        const FVector FootTraceStart = CapsuleCenter + FootHeightOffset;
        const FVector FootTraceEnd = FootTraceStart + (CapsuleForward * TraceDistance);

        #if DEV_DEBUG_MODE
        if (bActivateDebug)
        {
            DrawDebugLine(GetWorld(), HeadTraceStart, HeadTraceEnd, FColor::Green, true, 1.0f, 0, 2.0f);
            DrawDebugLine(GetWorld(), CenterTraceStart, CenterTraceEnd, FColor::Green, true, 1.0f, 0, 2.0f);
            DrawDebugLine(GetWorld(), FootTraceStart, FootTraceEnd, FColor::Green, true, 1.0f, 0, 2.0f);
        }
        #endif

        FCollisionQueryParams TraceParams;
        TraceParams.AddIgnoredActor(Owner);
        TraceParams.AddIgnoredComponent(OwnerCapsuleComponent);
        TraceParams.bIgnoreTouches = true;

        FHitResult HeadHit, CenterHit, FootHit;

        const bool bHeadHit = GetWorld()->LineTraceSingleByChannel(HeadHit, HeadTraceStart, HeadTraceEnd, ECC_Visibility, TraceParams);
        const bool bCenterHit = GetWorld()->LineTraceSingleByChannel(CenterHit, CenterTraceStart, CenterTraceEnd, ECC_Visibility, TraceParams);
        const bool bFootHit = GetWorld()->LineTraceSingleByChannel(FootHit, FootTraceStart, FootTraceEnd, ECC_Visibility, TraceParams);

        if (bHeadHit)
        {
            Hang->SetImpactPoint(HeadHit.ImpactPoint);
            Hang->SetHangLocation(HeadHit.ImpactPoint);
            Hang->SetImpactNormal(HeadHit.ImpactNormal);
            Hang->SetDirection((-HeadHit.ImpactNormal).GetSafeNormal());
        }

        return !bHeadHit && bCenterHit && bFootHit;
    }
    else if (IsCurrentMovementState(MovementStates::VerticalWallRun))
    {
        const FVector HangTraceStart = CapsuleCenter + (UpVector * (CapsuleHalfHeight * 0.80f));
        const FVector HangTraceEnd = HangTraceStart + (CapsuleForward * 75.0f);

        FHitResult HangHit;
        FCollisionQueryParams HangTraceParams;
        HangTraceParams.AddIgnoredActor(Owner);
        HangTraceParams.AddIgnoredComponent(OwnerCapsuleComponent);
        HangTraceParams.bIgnoreTouches = true;

        const bool bDidHitHangSurface = GetWorld()->LineTraceSingleByChannel(HangHit, HangTraceStart, HangTraceEnd, ECC_Visibility, HangTraceParams);

        if (!bDidHitHangSurface)
        {
            LOG_INFO("Hang opportunity detected successfully (VerticalWallRunState).");
            return true;
        }
    }

    #if DEV_DEBUG_MODE
    LOG_ERROR("No valid hang opportunity detected in current movement state.");
    #endif

    return false;
}

bool UAdvanceMovementComponent::DetectWater()
{
    if (!GetOwner() || !OwnerCapsuleComponent)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("CheckForSwimming failed: Owner or CapsuleComponent is invalid.");
        #endif

        return false;
    }

    // Perform a simple capsule overlap check for any actors
    TArray<AActor*> OverlappingActors;
    OwnerCapsuleComponent->GetOverlappingActors(OverlappingActors);


    // Check for any actor with the "Water" tag
    for (AActor* Actor : OverlappingActors)
    {
        if (Actor && Actor->ActorHasTag("Water"))
        {
#if DEV_DEBUG_MODE
            LOG_INFO("Swimming detected via Actor Tag: Water.");
#endif
            return true;
        }
    }

    return false;
}


#pragma endregion

#pragma region BasicMovementState

EBasicMovementState UAdvanceMovementComponent::GetBasicMovement() const
{
    return BasicMovementState;
}

void UAdvanceMovementComponent::SetBasicMovement(EBasicMovementState NewBasicMobility)
{
    // If the new state is the same as the current state, log a debug message and exit.
    if (BasicMovementState == NewBasicMobility)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("SetBasicMovement called with same state: no change required.");
        #endif 
        return;
    }

    // Update the BasicMobility state and reset Special and Advance mobility states to Null.
    BasicMovementState      = NewBasicMobility;
    SpecialMobilityState    = ESpecialMovementState::Null;
    AdvanceMobilityState    = EAdvanceMovementState::Null;

    // Switch to the new basic movement state internally.
    SwitchBasicMovement(BasicMovementState);
}

bool UAdvanceMovementComponent::IsBasicMovement(EBasicMovementState CheckBasicMobility) const
{
    // Check if the current BasicMobility state matches the given state
    return BasicMovementState == CheckBasicMobility;
}

void UAdvanceMovementComponent::SwitchBasicMovement(EBasicMovementState InBasicMobility)
{
    switch (InBasicMobility)
    {

    case EBasicMovementState::Null:
        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Error, TEXT("BasicMovementState state set to Null. No movement logic will be executed. Verify if this is intentional."));
        #endif
        break;

    case EBasicMovementState::Idle:
        EnterIdle();
        break;

    case EBasicMovementState::Walk:
        EnterWalk();
        break;

    case EBasicMovementState::Run:
        EnterRun();
        break;

    case EBasicMovementState::Sprint:
        EnterSprint();
        break;

    case EBasicMovementState::Crouch:
        EnterCrouch();
        break;

    case EBasicMovementState::Prone:
        EnterProne();
        break;

    case EBasicMovementState::Crawl:
        EnterCrawl();
        break;

    case EBasicMovementState::Fall:
        EnterFall();
        break;

    default:
        #if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Error, TEXT("Unhandled BasicMovementState state: %s"), *UEnum::GetValueAsString(InBasicMobility));
        #endif
        break;
    }
}

#pragma region Idle

void UAdvanceMovementComponent::EnterIdle()
{
    SetMovementState(MovementStates::Idle);
    Idle->SetState(EIdleState::ReadyToAttempt);

    // Animation States
    SetLocomotionMode(ELocomotionMode::Ground);
    SetMovementAnimationState(EMovementAnimationState::Idle);
}

void UAdvanceMovementComponent::ExitIdle()
{
    Idle->SetState(EIdleState::Complete);
}

#pragma region Update

void UAdvanceMovementComponent::TickIdleMovement()
{
    if (Idle->TickDisabled())
    {
        #if DEV_DEBUG_MODE 
        LOG_ERROR("An unexpected idle state was encountered. Investigate for the root cause.");
        #endif 
        return;
    }

    if (Idle->IsReadyToAttempt())
    {
        Idle->SetState(EIdleState::InProgress);
    }

    if (Idle->IsInProgress())
    {
        SetMaxWalkSpeed(Idle->GetMovementSpeed());

        UpdateIdleDuration();
        UpdateIdleStamina();


        if (DetectWater())
        {
            IdleToSwim();
        }

        if (IsMovingOnGround())
        {
            /* Basic Mobility */
            IdleToWalk();
            IdleToRun();
            IdleToCrouch();
            IdleToProne();
            IdleToCrawl();

            /* Special Mobility */
            IdleToJump();
            IdleToRoll();
            IdleToDash();
        }
        else
        {
            IdleToFall();
        }

        IdleToSwim();

        if (IsPlayer())
        {
            UpdateIdleTotalTime();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::Idle);
            }
        }
        else if (IsAI())
        {

        }
    }
}

void UAdvanceMovementComponent::UpdateIdleDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = Idle->GetDuration();
    float NewDuration   = Duration + DeltaSecond;

    Idle->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateIdleTotalTime()
{
    float DeltaSecond       = GetWorld()->GetDeltaSeconds();
    float TotalTime         = Idle->GetTotalTime();
    float NewTotalTime      = TotalTime + DeltaSecond;

    Idle->SetTotalTime(NewTotalTime);
}

void UAdvanceMovementComponent::UpdateIdleStamina()
{
    float CharacterStamina      = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
    float CharacterMaxStamina   = CharacterData->CharacterAttribute.CharacterStat.GetMaxStamina();

    if (CharacterStamina <= CharacterMaxStamina)
    {
        CharacterData->CharacterAttribute.CharacterStat.RegenerateStamina(FIdleMovement::StaminaRegenModifier);
    }
}

#pragma endregion

#pragma region Transition

void UAdvanceMovementComponent::IdleToWalk()
{
    if (IsPlayer())
    {  
        if (SystemCore->GetPlayerMovementConfiguration().WalkEnabled() || (PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()))
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                ExitIdle();
                SetBasicMovement(WalkMovement);
                UE_LOG(LogTemp, Error, TEXT("IDLE TO WALK"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::IdleToRun()
{
    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                ExitIdle();
                SetBasicMovement(RunMovement);
                UE_LOG(LogTemp, Error, TEXT("IDLE TO RUN"));
                return;
            }
        }
    }
}


void UAdvanceMovementComponent::IdleToCrouch()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed())
        {
            if (CharacterData->CharacterAbility.CrouchAbilityUnlocked())
            {
                float CharacterStamina  = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                float CrouchStaminaCost = Crouch->GetStaminaCost();
                if (CharacterStamina >= CrouchStaminaCost)
                {
                    ExitIdle();
                    SetBasicMovement(CrouchMovement);
                    UE_LOG(LogTemp, Error, TEXT("IDLE TO CROUCH"));
                    return;
                }
                else
                {
                    LOG_TODO("Not enough stamina for Crouch");
                }
            }
        }
    }
}

void UAdvanceMovementComponent::IdleToProne()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputPronePressed() || PlayerInputCache->InputProneHeld())
        {
            if (CharacterData->CharacterAbility.ProneAbilityUnlocked())
            {
                float CharacterStamina = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                float ProneStaminaCost = Crouch->GetStaminaCost();

                if (CharacterStamina >= ProneStaminaCost)
                {
                    ExitIdle();
                    SetBasicMovement(ProneMovement);
                    UE_LOG(LogTemp, Error, TEXT("IDLE TO PRONE"));
                    return;
                }
                else
                {
                    LOG_TODO("Not enough stamina for prone");
                }
            }
        }
    }
}

void UAdvanceMovementComponent::IdleToCrawl()
{
    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitIdle();
        SetBasicMovement(CrawlMovement);
        UE_LOG(LogTemp, Error, TEXT("IDLE TO CRAWL"));
        return;
    }
}

void UAdvanceMovementComponent::IdleToFall()
{
    if (GroundDistance() >= 100.0f)
    {
        ExitIdle();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Error, TEXT("IDLE TO FALL"));
        return;
    }
}

void UAdvanceMovementComponent::IdleToJump()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpPressed())
        {            
            if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
            {
                float CharacterStamina = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                float JumpStaminaCost = Jump->GetIdleToJumpStaminaCost();

                if (CharacterStamina >= JumpStaminaCost)
                {
                    ExitIdle();
                    SetSpecialMobility(JumpMobility);
                    UE_LOG(LogTemp, Error, TEXT("IDLE TO JUMP"));
                    return;
                }
                else
                {
                    LOG_TODO("Not enough stamina for Jump");
                }
            }
        }
    }
}

void UAdvanceMovementComponent::IdleToRoll()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputRollPressed())
        {
            if (CharacterData->CharacterAbility.RollAbilityUnlocked())
            {
                float CharacterStamina = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                float RollStaminaCost  = Jump->GetIdleToJumpStaminaCost();

                if (CharacterStamina >= RollStaminaCost)
                {
                    ExitIdle();
                    SetSpecialMobility(RollMobility);
                    UE_LOG(LogTemp, Error, TEXT("IDLE TO ROLL"));
                    return;
                }
                else
                {
                    LOG_TODO("Not enough stamina for Roll");
                }
            }
        }
    }
}

void UAdvanceMovementComponent::IdleToDash()
{
    if (CharacterData->IsPlayer())
    {
        if (PlayerInputCache->InputDashPressed())
        {
            if (CharacterData->CharacterAbility.DashAbilityUnlocked() && ValidDashRange(Dash->GetMaximumDistance()))
            {
                float CharacterStamina = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                float DashStaminaCost  = Dash->GetStaminaCost();

                if (CharacterStamina >= DashStaminaCost)
                {
                    ExitIdle();
                    SetSpecialMobility(DashMobility);
                    UE_LOG(LogTemp, Error, TEXT("IDLE TO DASH"));
                    return;
                }
                else
                {
                    LOG_TODO("Not enough stamina for Dash");
                }
            }
        }
    }
}

void UAdvanceMovementComponent::IdleToSwim()
{
    if (CharacterData->IsPlayer())
    {
        if (CharacterData->GetCharacterAbility().CyberneticAbility SwimAbilityUnlocked())
        {
            // TODO: Idle To Swim
        }
    }
}

#pragma endregion

#pragma endregion

#pragma region Walk

void UAdvanceMovementComponent::EnterWalk()
{
    SetMovementState(WalkState);
    Walk->SetState(EWalkState::ReadyToAttempt);

    if (Walk->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Walk->SetStartLocation(CharacterOwner->GetActorLocation());

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::Walk);
            }
        }

        SetLocomotionMode(ELocomotionMode::Ground);
        SetMovementAnimationState(EMovementAnimationState::Movement);
    }
    UE_LOG(LogTemp, Error, TEXT("Enter Walk"));


}

void UAdvanceMovementComponent::TickWalkMovement()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (Walk->IsReadyToAttempt())
    {
        Walk->SetState(EWalkState::InProgress);
    }

    if (Walk->IsInProgress())
    {
        if (SystemCore.PlayerMovementConfiguration.InterpolateMovementSpeedEnabled())
        {
            InterpolateMovementSpeed
            (
                Walk->GetMaximumSpeed(),
                Walk->GetInterPolationSpeed()
            );
        }
        else
        {
            SetMovementSpeed(Walk->GetMaximumSpeed());
        }



        if (IsMovingOnGround())
        {
            UpdateWalkDuration();
            UpdateWalkStamina();

            if (IsPlayer())
            {
                UpdateWalkTotalTime();

                if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
                {
                    SetMovementCameraShakeState(EMovementCameraShakeState::Walk);
                }
            }

            /*Basic Mobility */
            WalkToIdle();
            WalkToRun();
            WalkToSprint();
            WalkToCrouch();
            WalkToProne();
            WalkToCrawl();

            /* Special Mobility */
            WalkToJump();
            WalkToRoll();
            WalkToDash();

            /* Advanced Mobility */
            WalkToVault();
            WalkToSwim();
        }
        else
        {
            WalkToFall();
        }
    }
}

void UAdvanceMovementComponent::ExitWalk()
{
    if (Walk->IsInProgress())
    {
        Walk->SetState(EWalkState::Complete);
    }

    if (Walk->IsComplete())
    {
        if (IsPlayer())
        {
            Walk->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateWalkTravelDistance();
        }
    }
}

void UAdvanceMovementComponent::UpdateWalkDuration()
{
    float DeltaSecond  = GetWorld()->GetDeltaSeconds();
    float WalkDuration = Walk->GetDuration();
    float NewDuration  = WalkDuration + DeltaSecond;

    Walk->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateWalkTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Walk->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaSecond;

    Walk->SetTotalTime(NewTotalTime);
}

void UAdvanceMovementComponent::UpdateWalkTravelDistance()
{
    FVector A   = Walk->GetStartLocation();
    FVector B   = Walk->GetEndLocation();

    float Distance  = FVector::Dist(A, B);

    float TravelDistance    = Walk->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    Walk->SetTravelDistance(NewTravelDistance);
}

void UAdvanceMovementComponent::UpdateWalkStamina()
{
    float Stamina       = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
    float MaxStamina    = CharacterData->CharacterAttribute.CharacterStat.GetMaxStamina();

    if (Stamina <= MaxStamina)
    {
        CharacterData->CharacterAttribute.CharacterStat.RegenerateStamina(FWalkMovement::StaminaRegenModifier);
    }
}

#pragma region Transition

void UAdvanceMovementComponent::WalkToIdle()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->MovementInputsInActive())
        {
            ExitWalk();
            SetBasicMovement(IdleMovement);
            UE_LOG(LogTemp, Error, TEXT("WALK TO IDLE"));
            return;
        }
    }
}

void UAdvanceMovementComponent::WalkToRun()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
		if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
		{         
            if (PlayerInputCache->AnyMovementInputActive())
            {
                ExitWalk();
                SetBasicMovement(RunMovement);
                UE_LOG(LogTemp, Error, TEXT("WALK TO RUN"));
                return;
            }
		}
	}
}

void UAdvanceMovementComponent::WalkToSprint()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputSprintPressed() || PlayerInputCache->InputSprintHeld())
        {   
            if (PlayerInputCache->InputMoveForwardPressed() || PlayerInputCache->InputMoveForwardHeld())
            {
                if (CharacterData->CharacterAbility.SprintAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.StaminaNotJustDepleted())
                    {
                        ExitWalk();
                        SetBasicMovement(SprintMovement);
                        UE_LOG(LogTemp, Error, TEXT("WALK TO SPRINT"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::WalkToCrouch()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed() || PlayerInputCache->InputCrouchHeld())
        {
            if (CharacterData->CharacterAbility.CrouchAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Crouch->GetStaminaCost())
                {
                    ExitWalk();
                    SetBasicMovement(CrouchMovement);
                    UE_LOG(LogTemp, Error, TEXT("WALK TO CROUCH"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::WalkToProne()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputPronePressed())
        {
            if (CharacterData->CharacterAbility.ProneAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Prone->GetStaminaCost())
                {
                    ExitWalk();
                    SetBasicMovement(ProneMovement);
                    UE_LOG(LogTemp, Error, TEXT("WALK TO PRONE"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::WalkToCrawl()
{
    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitWalk();
        SetBasicMovement(CrawlMovement);
        UE_LOG(LogTemp, Error, TEXT("WALK TO CRAWL"));
        return;
    }
}

void UAdvanceMovementComponent::WalkToFall()
{
    ExitWalk();
    SetBasicMovement(FallMovement);
    UE_LOG(LogTemp, Error, TEXT("IDLE TO FALL"));
    return;
}

void UAdvanceMovementComponent::WalkToJump()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpPressed())
        {
            if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetWalkToJumpStaminaCost())
                {
                    ExitWalk();
                    SetSpecialMobility(JumpMobility);
                    UE_LOG(LogTemp, Error, TEXT("WALK TO JUMP"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::WalkToRoll()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputRollPressed())
        {
            if (CharacterData->CharacterAbility.RollAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Roll->GetStaminaCost())
                {
                    ExitWalk();
                    SetSpecialMobility(RollMobility);
                    UE_LOG(LogTemp, Error, TEXT("WALK TO ROLL"));
                    return;
                }
            }
        }
    }
}


void UAdvanceMovementComponent::WalkToDash()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputDashPressed())
        {
            if (CharacterData->CharacterAbility.DashAbilityUnlocked() && ValidDashRange(Dash->GetMaximumDistance()))
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Dash->GetStaminaCost())
                {
                    ExitWalk();
                    SetSpecialMobility(ESpecialMovementState::Dash);
                    UE_LOG(LogTemp, Error, TEXT("WALK TO DASH"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::WalkToVault()
{
    if (Walk->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoVaultEnabled())
        {
            if (CharacterData->CharacterAbility.VaultAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Vault->GetStaminaCost())
                {
                    if (VaultCheck())
                    {
                        UE_LOG(LogTemp, Error, TEXT("Walk Vault Detected"));
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputVaultPressed() || PlayerInputCache->InputVaultHeld())
            {
                if (CharacterData->CharacterAbility.VaultAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Vault->GetStaminaCost())
                    {
                        if (VaultCheck())
                        {
                            UE_LOG(LogTemp, Error, TEXT("Walk Vault Detected"));
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::WalkToSwim()
{

}

#pragma endregion

#pragma endregion

#pragma region Run

void UAdvanceMovementComponent::EnterRun()
{
    SetMovementState(EMovementState::Run);
    Run->SetState(ERunState::ReadyToAttempt);

    if (Run->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Run->SetStartLocation(CharacterOwner->GetActorLocation());

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::Run);
            }
        }


        SetLocomotionMode(ELocomotionMode::Ground);
        SetMovementAnimationState(EMovementAnimationState::Movement);
    }
    UE_LOG(LogTemp, Error, TEXT("Enter Run"));
}

void UAdvanceMovementComponent::TickRunMovement()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (Run->IsReadyToAttempt())
    {
        Run->SetState(ERunState::InProgress);
    }

    if (Run->IsInProgress())
    {
        if (IsMovingOnGround())
        {        
            if (SystemCore.PlayerMovementConfiguration.InterpolateMovementSpeedEnabled())
            {
                float RunMaximumSpeed = Run->GetMaximumSpeed();
                float InterpolationSpeed = 0;

                if (HorizontalVelocitySize() < Run->GetMinimumSpeed())
                {
                    InterpolationSpeed = Run->GetInterpolationSpeed() * 3.0f;
                }
                else
                {
                    InterpolationSpeed = Run->GetInterpolationSpeed();
                }

                InterpolateMovementSpeed
                (
                    RunMaximumSpeed,
                    InterpolationSpeed
                );
            }
            else
            {
                SetMovementSpeed
                (
                    Run->GetMaximumSpeed()
                );
            }

            UpdateRunDuration();
            UpdateRunStamina();

            if (IsPlayer())
            {
                UpdateRunTotalTime();
            }

            RunSpeedControl();

            /* Basic Mobility */
            RunToIdle();
            RunToWalk();
            RunToSprint();
            RunToCrouch();
            RunToProne();
            RunToCrawl();

            /* Special Mobility */
            RunToJump();
            RunToSlide();
            RunToDash();

            /* Advance Mobility */
            RunToVault();
            RunToSwim();
        }
        else
        {
            RunToFall();
        }
    }
}

void UAdvanceMovementComponent::ExitRun()
{
    if (Run->IsInProgress())
    {
        Run->SetState(ERunState::Complete);
    }

    if (Run->IsComplete())
    {
        Run->SetEndLocation(CharacterOwner->GetActorLocation());
        UpdateRunTravelDistance();
    }
}

#pragma region Update

void UAdvanceMovementComponent::UpdateRunDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = Run->GetDuration();
    float NewDuration   = Duration + DeltaSecond;

    Run->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateRunStamina()
{
    if (HorizontalVelocitySize() <= Run->GetMaximumSpeed())
    {
        CharacterData->CharacterAttribute.CharacterStat.RegenerateStamina(FRunMovement::StaminaRegenModifier);
    }
}

void UAdvanceMovementComponent::UpdateRunTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Run->GetTotalTime();
    float NewTime       = TotalTime + DeltaSecond;

    Run->SetTotalTime(NewTime);
}

void UAdvanceMovementComponent::UpdateRunTravelDistance()
{
    FVector A = Run->GetStartLocation();
    FVector B = Run->GetEndLocation();

    float Distance          = FVector::Dist(A, B);
    float TravelDistance    = Run->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    Run->SetTravelDistance(NewTravelDistance);
}

#pragma endregion

void UAdvanceMovementComponent::RunSpeedControl()
{
    if (PlayerInputCache->InputMoveForwardInActive())
    {
        float CurrentVelocityY = GetOwner()->GetVelocity().Y; 

        if ((PreviousVelocityY > 0 && CurrentVelocityY < 0) || (PreviousVelocityY < 0 && CurrentVelocityY > 0))
        {
            SetMovementSpeed(Run->GetMinimumSpeed());
        }

        PreviousVelocityY = CurrentVelocityY;
    }
}

#pragma region Transition

void UAdvanceMovementComponent::RunToIdle()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->MovementInputsInActive())
        {   
            ExitRun();
            SetBasicMovement(IdleMovement);
            UE_LOG(LogTemp, Error, TEXT("RUN TO IDLE"));
            return;           
        }
    }
}

void UAdvanceMovementComponent::RunToWalk()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
		if ((PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()) || SystemCore.PlayerMovementConfiguration.WalkEnabled())
		{
			if (PlayerInputCache->AnyMovementInputActive())
			{
				ExitRun();
				SetBasicMovement(WalkMovement);
				UE_LOG(LogTemp, Error, TEXT("RUN TO WALK"));
				return;
			}
		}
    }
}

void UAdvanceMovementComponent::RunToSprint()
{
    if (Run->TickDisabled())
    {
        return;
    }


    if (IsPlayer())
    {
        if (PlayerInputCache->InputSprintPressed() || PlayerInputCache->InputSprintHeld())
        {
            if (PlayerInputCache->InputMoveForwardPressed() || PlayerInputCache->InputMoveForwardHeld())
            {
                if (CharacterData->CharacterAbility.SprintAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.StaminaNotJustDepleted() && CharacterData->CharacterAttribute.CharacterStat.GetStamina() > 0)
                    {
                        ExitRun();
                        SetBasicMovement(SprintMovement);
                        UE_LOG(LogTemp, Error, TEXT("RUN TO SPRINT"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RunToCrouch()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed())
        {
            if (CharacterData->CharacterAbility.CrouchAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Crouch->GetStaminaCost())
                {
                    ExitRun();
                    SetBasicMovement(CrouchMovement);
                    UE_LOG(LogTemp, Error, TEXT("RUN TO CROUCH"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RunToProne()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputPronePressed())
        {
            if (CharacterData->CharacterAbility.CrouchAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Prone->GetStaminaCost())
                {
                    ExitRun();
                    SetBasicMovement(ProneMovement);
                    UE_LOG(LogTemp, Error, TEXT("RUN TO PRONE"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RunToCrawl()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitRun();
        SetBasicMovement(CrawlMovement);
        UE_LOG(LogTemp, Error, TEXT("RUN TO CRAWL"));
        return;
    }
}

void UAdvanceMovementComponent::RunToFall()
{
    if (Run->TickDisabled())
    {
        return;
    }

    ExitRun();
    SetBasicMovement(FallMovement);
    UE_LOG(LogTemp, Error, TEXT("RUN TO FALL"));
    return;  
}

void UAdvanceMovementComponent::RunToJump()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpPressed())
        {
            if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetRunToJumpStaminaCost())
                {
                    ExitRun();
                    SetSpecialMobility(JumpMobility);
                    UE_LOG(LogTemp, Error, TEXT("RUN TO JUMP"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RunToSlide()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputSlidePressed())
        {
            if (CharacterData->CharacterAbility.SlideAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Slide->GetStaminaCost())
                {
                    ExitRun();
                    SetSpecialMobility(ESpecialMovementState::Slide);
                    UE_LOG(LogTemp, Error, TEXT("RUN TO JUMP"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RunToDash()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputDashPressed())
        {
            if (CharacterData->CharacterAbility.DashAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Dash->GetStaminaCost() * Dash->GetMaximumDistance())
                {
                    ExitRun();
                    SetSpecialMobility(ESpecialMovementState::Dash);
                    UE_LOG(LogTemp, Error, TEXT("RUN TO DASH"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RunToVault()
{
    if (Run->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoVaultEnabled())
        {
            if (CharacterData->CharacterAbility.VaultAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Vault->GetStaminaCost())
                {
                    if (VaultCheck())
                    {
                        ExitRun();
                        SetAdvanceMobility(EAdvanceMovementState::Vault);
                        UE_LOG(LogTemp, Error, TEXT("RUN TO VAULT"));
                        return;
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputVaultPressed() || PlayerInputCache->InputVaultHeld())
            {
                if (CharacterData->CharacterAbility.VaultAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() > Vault->GetStaminaCost())
                    {
                        if (VaultCheck())
                        {
                            ExitRun();
                            SetAdvanceMobility(EAdvanceMovementState::Vault);
                            UE_LOG(LogTemp, Error, TEXT("RUN TO VAULT"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RunToSwim()
{
    // TODO: Run to swim
}

#pragma endregion

#pragma endregion

#pragma region Sprint

void UAdvanceMovementComponent::EnterSprint()
{
	SetMovementState(SprintState);
    Sprint->SetState(ESprintState::ReadyToAttempt);

    if (Sprint->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Sprint->SetStartLocation(CharacterOwner->GetActorLocation());

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::Sprint);
            }
        }

        SetLocomotionMode(ELocomotionMode::Ground);
        SetMovementAnimationState(EMovementAnimationState::Movement);
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Sprint"));


}

void UAdvanceMovementComponent::TickSprintMovement()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (Sprint->IsReadyToAttempt())
    {
        Sprint->SetState(ESprintState::InProgress);
    }

    if (Sprint->IsInProgress())
    {
        if (IsMovingOnGround())
        {
            if (SystemCore.PlayerMovementConfiguration.InterpolateMovementSpeedEnabled())
            {
                float CurrentSpeed       = HorizontalVelocitySize();
                float SprintMinimumSpeed = Sprint->GetMinimumSpeed();
                float SprintMaximumSpeed = Sprint->GetMaximumSpeed();
                float InterpolationSpeed = 0;

                if (CurrentSpeed  < SprintMinimumSpeed / 2)
                {
                    InterpolationSpeed = Sprint->GetInterpolationSpeed() * 4.0f;
                }
                else if (CurrentSpeed < SprintMinimumSpeed)
                {
                    InterpolationSpeed = Sprint->GetInterpolationSpeed() * 2.0f;
                }
                else
                {
                    InterpolationSpeed = Sprint->GetInterpolationSpeed();
                }

                float RandomVariance = FMath::RandRange(-100.0f, 100.0f);
                float TargetSpeedWithVariance = FMath::Clamp(SprintMaximumSpeed + RandomVariance, SprintMinimumSpeed, SprintMaximumSpeed + 100.0f);

                InterpolateMovementSpeed
                (
                    TargetSpeedWithVariance,
                    InterpolationSpeed
                );
            }
            else
            {
                SetMovementSpeed(Sprint->GetMaximumSpeed());
            }

            UpdateSprintDuration();
            UpdateSprintStamina();

            if (IsPlayer())
            {
                UpdateSprintTotalTime();

                if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
                {
                    SetMovementCameraShakeState(EMovementCameraShakeState::Sprint);
                }
            }

            /* Basic Mobility */
            SprintToIdle();
            SprintToWalk();
            SprintToRun();
            SprintToProne();
            SprintToCrawl();

            /* Special Mobility */
            SprintToJump();
            SprintToSlide();
            SprintToRoll();
            SprintToDash();

            /* Advance Mobility */
            SprintToVault();
            SprintToMantle();
            SprintToSwim();
        }
        else
        {
            SprintToFall();
        }
    }
}

void UAdvanceMovementComponent::ExitSprint()
{
    if (Sprint->IsInProgress())
    {
        Sprint->SetState(ESprintState::Complete);
    }

    if (Sprint->IsComplete())
    {
        if (IsPlayer())
        {
            Sprint->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateSprintTravelDistance();
        }
    }
}

void UAdvanceMovementComponent::UpdateSprintDuration()
{
    float DeltaSecond       = GetWorld()->GetDeltaSeconds();
    float SprintDuration    = Sprint->GetDuration();
    float NewDuration       = DeltaSecond + SprintDuration;

    Sprint->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateSprintStamina()
{
    if (HorizontalVelocitySize() > Sprint->GetMinimumSpeed())
    {
        float CharacterStamina  = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
        float MaxStaminaCost    = Sprint->GetStaminaCost();
        float VelocityRatio     = FMath::Clamp(HorizontalVelocitySize() / Sprint->GetMaximumSpeed(), 0.0f, 1.0f);
        float StaminaCost       = MaxStaminaCost * VelocityRatio;
        float NewStamina        = FMath::Clamp(CharacterStamina - StaminaCost, 0.0f, CharacterData->CharacterAttribute.CharacterStat.GetStamina());

        CharacterData->CharacterAttribute.CharacterStat.SetStamina(NewStamina);
    }
    else
    {
        CharacterData->CharacterAttribute.CharacterStat.RegenerateStamina(FSprintMovement::SprintRegenModifier);
    }
}

void UAdvanceMovementComponent::UpdateSprintTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Sprint->GetTotalTime();
    float NewTime       = TotalTime + DeltaSecond;

    Sprint->SetTotalTime(NewTime);
}

void UAdvanceMovementComponent::UpdateSprintTravelDistance()
{
    FVector A       = Sprint->GetStartLocation();
    FVector B       = Sprint->GetEndLocation();
    float Distance  = FVector::Dist(A, B);

    float TravelDistance    = Sprint->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    Sprint->SetTravelDistance(NewTravelDistance);
}

#pragma region Transition

void UAdvanceMovementComponent::SprintToIdle()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->MovementInputsInActive())
        {
            ExitSprint();
            SetBasicMovement(IdleMovement);
            UE_LOG(LogTemp, Error, TEXT("SPRINT TO IDLE"));
            return;
        }
    }
}

void UAdvanceMovementComponent::SprintToWalk()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.SprintToggleEnabled())
        {
            if (SystemCore.PlayerMovementConfiguration.WalkEnabled() || (PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()))
            {
                if (PlayerInputCache->InputSprintPressed())
                {
                    ExitSprint();
                    SetBasicMovement(WalkMovement);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO WALK"));
                    return;
                }
            }
        }
        else
        { 
            if (SystemCore.PlayerMovementConfiguration.WalkEnabled() || (PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()))
            {
                if (PlayerInputCache->InputSprintReleased() || PlayerInputCache->InputSprintInActive())
                {
                    ExitSprint();
                    SetBasicMovement(WalkMovement);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO WALK"));
                    return;
                }
            }       
        }
    }
}

void UAdvanceMovementComponent::SprintToRun()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (CharacterData->CharacterAttribute.CharacterStat.StaminaJustDepleted())
    {
        ExitSprint();
        SetBasicMovement(RunMovement);
        UE_LOG(LogTemp, Error, TEXT("SPRINT TO RUN (STAMINA DEPLETED)"));
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputMoveBackwardPressed() || PlayerInputCache->InputMoveBackwardHeld())
        {
            ExitSprint();
            SetBasicMovement(RunMovement);
            UE_LOG(LogTemp, Error, TEXT("SPRINT TO RUN"));
            return;
        }

        if (SystemCore.PlayerMovementConfiguration.SprintToggleEnabled())
        {
            if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
            {
                if (PlayerInputCache->InputSprintPressed())
                {
                    ExitSprint();
                    SetBasicMovement(RunMovement);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO RUN"));
                    return;
                }
            }
        }
        else
        {
            if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
            {
                if (PlayerInputCache->InputSprintReleased() || PlayerInputCache->InputSprintInActive())
                {
                    ExitSprint();
                    SetBasicMovement(RunMovement);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO RUN"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SprintToProne()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputPronePressed())
        {
            if (CharacterData->CharacterAbility.ProneAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Prone->GetStaminaCost())
                {
                    ExitSprint();
                    SetBasicMovement(ProneMovement);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO PRONE"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SprintToCrawl()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitSprint();
        SetBasicMovement(CrawlMovement);
        UE_LOG(LogTemp, Error, TEXT("SPRINT TO CRAWL"));
        return;
    }
}

void UAdvanceMovementComponent::SprintToFall()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    ExitSprint();
    SetBasicMovement(FallMovement);
    UE_LOG(LogTemp, Error, TEXT("Sprint TO FALL"));
    return;
}

void UAdvanceMovementComponent::SprintToJump()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpPressed())
        {
            if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetSprintToJumpStaminaCost())
                {
                    ExitSprint();
                    SetSpecialMobility(JumpMobility);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO JUMP"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SprintToSlide()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        bool SlideInputsRequested =
        (PlayerInputCache->InputSlidePressed() || PlayerInputCache->InputSlideHeld()) ||
        (PlayerInputCache->InputCrouchPressed() || PlayerInputCache->InputCrouchHeld());

        if (SlideInputsRequested)
        {
            if (CharacterData->CharacterAbility.SlideAbilityUnlocked())
            {
                float CurrentStamina    = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                float StaminaCost       = Slide->GetStaminaCost();

                if (CurrentStamina >= StaminaCost)
                {
                    ExitSprint();
                    SetSpecialMobility(SlideMobility);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO SLIDE"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SprintToRoll()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputRollPressed())
        {
            if (CharacterData->CharacterAbility.RollAbilityUnlocked())
            {
                float CurrentStamina = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                float StaminaCost = Roll->GetStaminaCost();

                if (CurrentStamina >= StaminaCost)
                {
                    ExitSprint();
                    SetSpecialMobility(RollMobility);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO ROLL"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SprintToDash()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputDashPressed() || PlayerInputCache->InputDashHeld())
        {
            if (CharacterData->CharacterAbility.DashAbilityUnlocked() && ValidDashRange(Dash->GetMaximumDistance()))
            {
                float CurrentStamina = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                float StaminaCost = Dash->GetStaminaCost() * Dash->GetMaximumDistance();

                if (CurrentStamina >= StaminaCost)
                {
                    ExitSprint();
                    SetSpecialMobility(DashMobility);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO DASH"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SprintToVault()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (CharacterData->IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoVaultEnabled())
        {
            if (CharacterData->CharacterAbility.VaultAbilityUnlocked())
            {          
                if (VaultCheck())
                {
                    float Stamina = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                    float StaminaCost = Vault->GetStaminaCost();

                    if (Stamina >= StaminaCost)
                    {
                        ExitSprint();
                        SetAdvanceMobility(VaultMobility);
                        UE_LOG(LogTemp, Error, TEXT("SPRINT TO VAULT"));
                        return;
                    } 
                }               
            }
        }
        else
        {
            if (PlayerInputCache->InputVaultPressed() || PlayerInputCache->InputVaultHeld())
            {
                if (CharacterData->CharacterAbility.VaultAbilityUnlocked())
                {
                    float Stamina = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
                    float StaminaCost = Vault->GetStaminaCost();

                    if (Stamina >= StaminaCost)
                    {
                        if (VaultCheck())
                        {
                            ExitSprint();
                            SetAdvanceMobility(VaultMobility);
                            UE_LOG(LogTemp, Error, TEXT("SPRINT TO VAULT"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SprintToMantle()
{
    if (Sprint->TickDisabled())
    {
        return;
    }

    if (CharacterData->IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoMantlingEnabled())
        {
            if (CharacterData->CharacterAbility.MantleAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Mantle->GetStaminaCost())
                {
                    ExitSprint();
                    SetAdvanceMobility(EAdvanceMovementState::Mantle);
                    UE_LOG(LogTemp, Error, TEXT("SPRINT TO MANTLE"));
                    return;
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputMantlePressed() || PlayerInputCache->InputMantleHeld())
            {
                if (CharacterData->CharacterAbility.MantleAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Mantle->GetStaminaCost())
                    {
                        ExitSprint();
                        SetAdvanceMobility(EAdvanceMovementState::Mantle);
                        UE_LOG(LogTemp, Error, TEXT("SPRINT TO MANTLE"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SprintToSwim()
{
    // TODO: Sprint To Swim
}

#pragma endregion

#pragma endregion

#pragma region Crawl

void UAdvanceMovementComponent::EnterCrawl()
{
    SetMovementState(CrawlState);
    Crawl->SetState(ECrawlState::ReadyToAttempt);


    if (Crawl->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Crawl->SetStartLocation(CharacterOwner->GetActorLocation());

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::CrawlEnter);
            }
        }

        SetLocomotionMode(ELocomotionMode::Ground);
        SetMovementAnimationState(EMovementAnimationState::CrawlIdle);
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Crawl"));
}

void UAdvanceMovementComponent::TickCrawlMovement()
{
    if (Crawl->TickDisabled())
    {
        return;
    }
    
    if (Crawl->IsReadyToAttempt())
    {
        Crawl->SetState(ECrawlState::InProgress);
    }

    if (Crawl->IsInProgress())
    {
        if (IsMovingOnGround())
        {
   
            UpdateCrawlDuration();
            UpdateCrawlStamina();

            if (IsPlayer())
            {
                UpdateCrawlTotalTime();

                if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
                {
                    if (HorizontalVelocitySize() > 0)
                    {
                        SetMovementCameraShakeState(EMovementCameraShakeState::CrawlMovement);
                    }
                    else
                    {
                        SetMovementCameraShakeState(EMovementCameraShakeState::CrawlIdle);
                    }
                }

                // TODO: Do not forget to optimize it
                if (HorizontalVelocitySize() > 0)
                {
                    SetMovementAnimationState(EMovementAnimationState::CrawlMovement);
                }
                else
                {
                    SetMovementAnimationState(EMovementAnimationState::CrawlIdle);
                }

            }

            if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() > 0)
            {
                CrawlToIdle();
                CrawlToCrouch();
                CrawlToProne();
            }
        }
        else
        {
            CrawlToFall();
        }
    }
}

void UAdvanceMovementComponent::ExitCrawl()
{
    if (Crawl->IsInProgress())
    {
        Crawl->SetState(ECrawlState::Complete);
    }

    if (Crawl->IsComplete())
    {
        if (IsPlayer())
        {
            Crawl->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateCrawlTravelDistance();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::CrawlExit);
            }
        }
    }
}

#pragma region Update

void UAdvanceMovementComponent::UpdateCrawlDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = Crawl->GetDuration();
    float NewDuration   = Duration + DeltaSecond;

    Crawl->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateCrawlStamina()
{
    float Stamina = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
    float NewStamina;

    if (HorizontalVelocitySize() > 0)
    {
        if (Stamina > 0)
        {
            float StaminaCost   = Crawl->GetStaminaCost();
            NewStamina          = Stamina - StaminaCost;

            CharacterData->CharacterAttribute.CharacterStat.SetStamina(NewStamina);

            if (CharacterData->CharacterAttribute.CharacterStat.StaminaNotJustDepleted())
            {
                InterpolateMovementSpeed
                (
                    Crawl->GetMaximumSpeed(),
                    Crawl->GetInterpolationSpeed()
                );
            }
        }
    }
    else
    {
        float StaminaGain   = Crawl->GetStaminaGain();
        NewStamina    = Stamina + StaminaGain;
        CharacterData->CharacterAttribute.CharacterStat.SetStamina(NewStamina);

        SetMovementSpeed(0);
    }
}

void UAdvanceMovementComponent::UpdateCrawlTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Crawl->GetTotalTime();
    float NewTime       = TotalTime + DeltaSecond;

    Crawl->SetTotalTime(NewTime);
}

void UAdvanceMovementComponent::UpdateCrawlTravelDistance()
{
    FVector A               = Crawl->GetStartLocation();
    FVector B               = Crawl->GetEndLocation();
    float Distance          = FVector::Dist(A, B);

    float TravelDistance    = Crawl->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    Crawl->SetTravelDistance(NewTravelDistance);
}

#pragma endregion

#pragma region Transition

void UAdvanceMovementComponent::CrawlToIdle()
{
    if (CharacterData->IsPlayer())
    {
        if (PlayerInputCache->InputCrouchInActive() && PlayerInputCache->InputProneInActive() && PlayerInputCache->InputRollInActive())
        {
            ExitCrawl();
            SetBasicMovement(IdleMovement);
            UE_LOG(LogTemp, Error, TEXT("CRAWL TO IDLE"));
            return;
        }
    }
    else if (CharacterData->IsAI())
    {
        ExitCrawl();
        SetBasicMovement(IdleMovement);
        UE_LOG(LogTemp, Error, TEXT("CRAWL TO IDLE"));
        return;
    }
}

void UAdvanceMovementComponent::CrawlToCrouch()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed() || PlayerInputCache->InputCrouchHeld())
        {
            if (CharacterData->CharacterAbility.CrouchAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Crouch->GetStaminaCost())
                {
                    ExitCrawl();
                    SetBasicMovement(CrouchMovement);
                    UE_LOG(LogTemp, Error, TEXT("CRAWL TO CROUCH"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::CrawlToProne()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputPronePressed() ||PlayerInputCache->InputProneHeld())
        {
            if (CharacterData->CharacterAbility.ProneAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Prone->GetStaminaCost())
                {
                    ExitCrawl();
                    SetBasicMovement(ProneMovement);
                    UE_LOG(LogTemp, Error, TEXT("CRAWL TO PRONE"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::CrawlToFall()
{
    ExitCrawl();
    SetBasicMovement(FallMovement);
    UE_LOG(LogTemp, Error, TEXT("CRAWL TO FALL"));
    return;
}

#pragma endregion

#pragma endregion

#pragma region Crouch

void UAdvanceMovementComponent::EnterCrouch()
{
	SetMovementState(CrouchState);
    SetMovementCameraShakeState(EMovementCameraShakeState::CrouchEnter);

    Crouch->SetState(ECrouchState::ReadyToAttempt);

    if (Crouch->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            if (SystemCore.PlayerMovementConfiguration.InterpolateMovementSpeedDisabled())
            {
                SetMovementSpeed(Crouch->GetMaximumSpeed());
            }

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::CrouchEnter);
            }
        }

        Crouch->SetStartLocation(CharacterOwner->GetActorLocation());
        SetLocomotionMode(ELocomotionMode::Ground);
        SetMovementAnimationState(EMovementAnimationState::CrouchIdle);
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Crouch"));
}

void UAdvanceMovementComponent::TickCrouchMovement()
{
    if (Crouch->TickDisabled())
    {
        return;
    }

    if (Crouch->IsReadyToAttempt())
    {
        Crouch->SetState(ECrouchState::InProgress);
    }

    if (Crouch->IsInProgress())
    {
        if (IsMovingOnGround())
        {
            if (SystemCore.PlayerMovementConfiguration.InterpolateMovementSpeedEnabled())
            {
                if (IsPreviousMovementState(EMovementState::Slide))
                {
                    SetMovementSpeed(Crouch->GetMaximumSpeed());
                }
                else
                {
                    InterpolateMovementSpeed
                    (
                        Crouch->GetMaximumSpeed(),
                        Crouch->GetInterpolationSpeed()
                    );
                }
            }
            else
            {
                SetMovementSpeed(Crouch->GetMaximumSpeed());
            }

            UpdateCrouchDuration();

            if (IsPlayer())
            {
                UpdateCrouchTotalTime();

                if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
                {
                    if (HorizontalVelocitySize() > 0)
                    {
                        SetMovementCameraShakeState(EMovementCameraShakeState::CrouchMovement);
                        SetMovementAnimationState(EMovementAnimationState::CrouchMovement);
                    }
                    else
                    {
                        SetMovementCameraShakeState(EMovementCameraShakeState::CrouchIdle);
                        SetMovementAnimationState(EMovementAnimationState::CrouchIdle);
                    }
                }

                if (HorizontalVelocitySize() > 0)
                {
                    SetMovementAnimationState(EMovementAnimationState::CrouchMovement);
                }
                else
                {
                    SetMovementAnimationState(EMovementAnimationState::CrouchIdle);
                }
            }

            CrouchToIdle();
            CrouchToWalk();
            CrouchToRun();
            CrouchToJump();
            CrouchToSlide();
            CrouchToRoll();
            CrouchToProne();
            CrouchToCrawl();

            if (HorizontalVelocitySize() > 0)
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::CrouchMovement);
            }
            else
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::CrouchIdle);
            }
        }
        else
        {
            if (GroundDistance() >= 50.0f)
            {
                CrouchToFall();
            }
        }
    }


}

void UAdvanceMovementComponent::ExitCrouch()
{
    if (Crouch->IsInProgress())
    {
        Crouch->SetState(ECrouchState::Complete);
    }

    if (Crouch->IsComplete())
    {
        UpdateCrouchStamina();

        Crouch->SetEndLocation(CharacterOwner->GetActorLocation());
        UpdateCrouchTravelDistance();

        if (IsPlayer())
        {
            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::CrouchExit);
            }
        }
    }
}

#pragma region Update

void UAdvanceMovementComponent::UpdateCrouchStamina()
{
    float Stamina       = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
    float MaxStamina    = CharacterData->CharacterAttribute.CharacterStat.GetMaxStamina();
    float StaminaCost   = Crouch->GetStaminaCost();

    float NewStamina    = FMath::Clamp(Stamina - StaminaCost, 0.0f, MaxStamina);
    CharacterData->CharacterAttribute.CharacterStat.SetStamina(NewStamina);
}

void UAdvanceMovementComponent::UpdateCrouchDuration()
{
    float DeltaSecond       = GetWorld()->GetDeltaSeconds();
    float CrouchDuration    = Crouch->GetDuration();
    float NewDuration       = CrouchDuration + DeltaSecond;

    Crouch->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateCrouchTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Crouch->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaSecond;

    Crouch->SetTotalTime(NewTotalTime);
}

void UAdvanceMovementComponent::UpdateCrouchTravelDistance()
{
    FVector A               = Crouch->GetStartLocation();
    FVector B               = Crouch->GetEndLocation();

    float Distance          = FVector::Dist(A, B);
    float TravelDistance    = Crouch->GetTravelDistance();
    float NewDistance       = TravelDistance + Distance;

    Crouch->SetTravelDistance(NewDistance);
}


#pragma endregion

#pragma region Utility

bool UAdvanceMovementComponent::UnCrouchHeightValidation()
{

    float CapsuleHalfHeight = CharacterCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
    float CapsuleRadius     = CharacterCapsuleComponent()->GetUnscaledCapsuleRadius();

    FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight);

    FVector StartLocation = CharacterOwner->GetActorLocation();
    FVector EndLocation = StartLocation + FVector(0.0f, 0.0f, CapsuleHalfHeight * 2.0f); 

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);

    bool bCanUnCrouch = !GetWorld()->OverlapBlockingTestByChannel(EndLocation, FQuat::Identity, ECC_Pawn, CapsuleShape, QueryParams);


    bool bDebug = false;
    if (bDebug)
    {
        DrawDebugCapsule(GetWorld(), EndLocation, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, bCanUnCrouch ? FColor::Green : FColor::Red, false, 2.0f);
    }

    return bCanUnCrouch;
}

#pragma endregion

#pragma region Transtion

void UAdvanceMovementComponent::CrouchToIdle()
{
    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.CrouchToggleEnabled())
        {
            if (PlayerInputCache->InputCrouchPressed())
            {
                if (PlayerInputCache->MovementInputsInActive())
                {
                    if (UnCrouchHeightValidation())
                    {
                        ExitCrouch();
                        SetBasicMovement(IdleMovement);
                        UE_LOG(LogTemp, Error, TEXT("CROUCH TO IDLE"));
                        return;
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputCrouchReleased() || PlayerInputCache->InputCrouchInActive())
            {
                if (PlayerInputCache->MovementInputsInActive())
                {
                    if (UnCrouchHeightValidation())
                    {
                        ExitCrouch();
                        SetBasicMovement(IdleMovement);
                        UE_LOG(LogTemp, Error, TEXT("CROUCH TO IDLE"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::CrouchToWalk()
{
    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.CrouchToggleEnabled())
        {
            if (PlayerInputCache->InputCrouchPressed())
            {
                if (SystemCore.PlayerMovementConfiguration.WalkEnabled() || (PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()))
                {
                    if (PlayerInputCache->AnyMovementInputActive())
                    {
                        if (UnCrouchHeightValidation())
                        {
                            ExitCrouch();
                            SetBasicMovement(WalkMovement);
                            UE_LOG(LogTemp, Error, TEXT("CROUCH TO WALK"));
                            return;
                        }
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputCrouchReleased() || PlayerInputCache->InputCrouchInActive())
            {
                if (SystemCore.PlayerMovementConfiguration.WalkEnabled() || (PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()))
                {
                    if (PlayerInputCache->AnyMovementInputActive())
                    {
                        if (UnCrouchHeightValidation())
                        {
                            ExitCrouch();
                            SetBasicMovement(WalkMovement);
                            UE_LOG(LogTemp, Error, TEXT("CROUCH TO WALK"));
                            return;
                        }
                    }
                }
            }

        }
    }
}

void UAdvanceMovementComponent::CrouchToRun()
{
    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.CrouchToggleEnabled())
        {
            if (PlayerInputCache->InputCrouchPressed())
            {
                if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
                {
                    if (PlayerInputCache->AnyMovementInputActive())
                    {
                        if (UnCrouchHeightValidation())
                        {
                            ExitCrouch();
                            SetBasicMovement(RunMovement);
                            UE_LOG(LogTemp, Error, TEXT("CROUCH TO RUN"));
                            return;
                        }
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputCrouchReleased() || PlayerInputCache->InputCrouchInActive())
            {
                if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
                {
                    if (PlayerInputCache->AnyMovementInputActive())
                    {
                        if (UnCrouchHeightValidation())
                        {
                            ExitCrouch();
                            SetBasicMovement(RunMovement);
                            UE_LOG(LogTemp, Error, TEXT("CROUCH TO RUN"));
                            return;
                        }
                    }
                }
            }

        }
    }
}

void UAdvanceMovementComponent::CrouchToJump()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpPressed())
        {
            if (SystemCore.PlayerMovementConfiguration.IsJumpWhileCrouchedEnabled())
            {
                if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetCrouchToJumpStaminaCost())
                    {
                        ExitCrouch();
                        SetSpecialMobility(JumpMobility);
                        UE_LOG(LogTemp, Error, TEXT("Crouch to Jump"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::CrouchToSlide()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputSlidePressed())
        {
            if (CharacterData->CharacterAbility.SlideAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Slide->GetStaminaCost())
                {
                    ExitCrouch();
                    SetSpecialMobility(SlideMobility);
                    UE_LOG(LogTemp, Error, TEXT("Crouch to Jump"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::CrouchToRoll()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputRollPressed())
        {
            if (CharacterData->CharacterAbility.RollAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Roll->GetStaminaCost())
                {
                    ExitCrouch();
                    SetSpecialMobility(RollMobility);
                    UE_LOG(LogTemp, Error, TEXT("CROUCH TO ROLL"));
                    return;
                }
            }

        }
    }
}

void UAdvanceMovementComponent::CrouchToProne()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputProneHeld())
        {
            if (CharacterData->CharacterAbility.ProneAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Prone->GetStaminaCost())
                {
                    ExitCrouch();
                    SetBasicMovement(ProneMovement);
                    UE_LOG(LogTemp, Error, TEXT("CROUCH TO PRONE"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::CrouchToCrawl()
{
    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitCrouch();
        SetBasicMovement(CrawlMovement);
        UE_LOG(LogTemp, Error, TEXT("CROUCH TO CRAWL"));
        return;
    }
}

void UAdvanceMovementComponent::CrouchToFall()
{
    ExitCrouch();
    SetBasicMovement(FallMovement);
    UE_LOG(LogTemp, Error, TEXT("CROUCH TO FALL"));
    return;
}

#pragma endregion

#pragma endregion

#pragma region Prone

void UAdvanceMovementComponent::EnterProne()
{
	SetMovementState(EMovementState::Prone);
    Prone->SetState(EProneState::ReadyToAttempt);

    if (Prone->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Prone->SetStartLocation(CharacterOwner->GetActorLocation());

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::ProneEnter);
            }
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Prone"));
}

void UAdvanceMovementComponent::TickProneMovement()
{
    if (Prone->TickDisabled())
    {
        return;
    }

    if (Prone->IsReadyToAttempt())
    {
        Prone->SetState(EProneState::InProgress);
    }

    if (Prone->IsInProgress())
    {
        if (IsMovingOnGround())
        {
            if (SystemCore.PlayerMovementConfiguration.InterpolateMovementSpeedEnabled())
            {
                InterpolateMovementSpeed
                (
                    Prone->GetMaximumSpeed(),
                    Prone->GetInterpolationSpeed()
                );
            }
            else
            {
                SetMovementSpeed(Prone->GetMaximumSpeed());
            }

            UpdateProneDuration();

            if (IsPlayer())
            {
                UpdateProneTotalTime();

                if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
                {
                    if (HorizontalVelocitySize() > 0)
                    {
                        SetMovementCameraShakeState(EMovementCameraShakeState::ProneMovement);
                    }
                    else
                    {
                        SetMovementCameraShakeState(EMovementCameraShakeState::ProneIdle);
                    }
                }
            }

            ProneToIdle();
            ProneToWalk();
            ProneToRun();
            ProneToRoll();
            ProneToCrouch();
            ProneToCrawl();
            ProneToForwardThrust();


            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                if (HorizontalVelocitySize() > 0)
                {
                    SetMovementCameraShakeState(EMovementCameraShakeState::ProneMovement);
                }
                else
                {
                    SetMovementCameraShakeState(EMovementCameraShakeState::ProneIdle);
                }
            }
        }
        else
        {
            ProneToFall();
        }
    }
}

void UAdvanceMovementComponent::ExitProne()
{
    if (Prone->IsInProgress())
    {
        Prone->SetState(EProneState::Complete);
    }

    if (Prone->IsComplete())
    {
        if (IsPlayer())
        {
            Prone->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateProneTravelDistance();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::ProneExit);
            }
        }
    }
}

#pragma region Update

void UAdvanceMovementComponent::UpdateProneDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = Prone->GetDuration();
    float NewDuration   = DeltaSecond + Duration;

    Prone->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateProneTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Prone->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaSecond;

    Prone->SetDuration(NewTotalTime);
}

void UAdvanceMovementComponent::UpdateProneTravelDistance()
{
    FVector A = Prone->GetStartLocation();
    FVector B = Prone->GetEndLocation();

    float Distance          = FVector::Dist(A, B);

    float TravelDistance    = Prone->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    Prone->SetTravelDistance(NewTravelDistance);
}

#pragma endregion

#pragma region Utility

void UAdvanceMovementComponent::ProneForwardThrust()
{
    FVector StartLocation   = CharacterCapsuleComponent()->GetComponentLocation();

    FVector Forward         = CharacterCapsuleComponent()->GetForwardVector();
    FVector Upward          = CharacterCapsuleComponent()->GetUpVector();

    FVector ThrustForce     = (Forward * Prone->GetThrustAmount()) + (Upward * Prone->GetThrustAmount() * 0.25f);

    CharacterOwner->LaunchCharacter(ThrustForce, true, true);
}

bool UAdvanceMovementComponent::CanProneThrustForward()
{

    FVector StartLocation   = CharacterCapsuleComponent()->GetComponentLocation();
    FVector Forward         = CharacterCapsuleComponent()->GetForwardVector();

    float CheckDistance     = Prone->GetThrustAmount() * 1.5f; 

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);
    QueryParams.AddIgnoredComponent(CharacterCapsuleComponent());

    FVector EndLocation = StartLocation + (Forward * CheckDistance);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);

    return !bHit; 
}

#pragma endregion

#pragma region Transition

void UAdvanceMovementComponent::ProneToIdle()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputProneReleased() || PlayerInputCache->InputProneInActive())
        {
            if (PlayerInputCache->MovementInputsInActive())
            {
                ExitProne();
                SetBasicMovement(IdleMovement);
                UE_LOG(LogTemp, Error, TEXT("PRONE TO IDLE"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::ProneToWalk()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputProneReleased() || PlayerInputCache->InputProneInActive())
        {
            if (SystemCore.PlayerMovementConfiguration.WalkEnabled() || PlayerInputCache->InputWalkHeld())
            {
                if (PlayerInputCache->AnyMovementInputActive())
                {
                    ExitProne();
                    SetBasicMovement(WalkMovement);
                    UE_LOG(LogTemp, Error, TEXT("PRONE TO WALK"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::ProneToRun()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputProneReleased() || PlayerInputCache->InputProneInActive())
        {
            if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
            {
                if (PlayerInputCache->AnyMovementInputActive())
                {
                    ExitProne();
                    SetBasicMovement(RunMovement);
                    UE_LOG(LogTemp, Error, TEXT("PRONE TO RUN"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::ProneToRoll()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputRollPressed())
        {
            if (CharacterData->CharacterAbility.RollAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Roll->GetStaminaCost())
                {
                    ExitProne();
                    SetSpecialMobility(RollMobility);
                    UE_LOG(LogTemp, Error, TEXT("PRONE TO ROLL"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::ProneToCrouch()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed())
        {
            if (CharacterData->CharacterAbility.CrouchAbilityUnlocked())
            {
                ExitProne();
                SetBasicMovement(CrouchMovement);
                UE_LOG(LogTemp, Error, TEXT("PRONE TO CROUCH"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::ProneToCrawl()
{
    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitProne();
        SetBasicMovement(CrawlMovement);
        UE_LOG(LogTemp, Error, TEXT("PRONE TO CRAWL"));
        return;
    }
}

void UAdvanceMovementComponent::ProneToFall()
{
    ExitProne();
    SetBasicMovement(FallMovement);
    LOG_ERROR("PRONE TO FALL");
    return;
}

void UAdvanceMovementComponent::ProneToForwardThrust()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpPressed())
        {
            if (CharacterData->CharacterAbility.ProneAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Prone->GetStaminaCost() * 1.5f)
                {
                    if (CanProneThrustForward())
                    {
                        ProneForwardThrust();
                    }
                }
            }
        }
    }
}

#pragma endregion

#pragma endregion

#pragma region Fall

void UAdvanceMovementComponent::EnterFall()
{
	SetMovementState(FallState);
    Fall->SetState(EFallState::ReadyToAttempt);

    if (Fall->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Fall->SetStartLocation(CharacterOwner->GetActorLocation());
        }

        SetMovementAnimationState(EMovementAnimationState::Fall);
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Fall"));
}

void UAdvanceMovementComponent::TickFallMovement()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (Fall->IsReadyToAttempt())
    {
        Fall->SetState(EFallState::InProgress);
    }

    if (Fall->IsInProgress())
    {
        UpdateFallDuration();
        UpdateFallDistance();

        if (IsPlayer())
        {
            UpdateFallTotalTime();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::Fall);
            }
        }
        
        FallToVerticalWallRun();

        if (FMath::IsNearlyZero(GroundDistance(), 1.0f) && IsMovingOnGround())
        {
            FallToIdle();
            FallToWalk();
            FallToRun();
            FallToCrouch();
            FallToSlide();
            FallToRoll();
            FallToCrawl();
        }
        
        FallToJump();
        FallToHang();
    }
}

void UAdvanceMovementComponent::ExitFall()
{
    if (Fall->IsInProgress())
    {
        Fall->SetState(EFallState::Complete);
    }

    if (Fall->IsComplete())
    {
        if (IsPlayer())
        {
            //UpdateFallDamage();
            Fall->SetEndLocation(CharacterOwner->GetActorLocation());
        }
    }
}

#pragma region Update

void UAdvanceMovementComponent::UpdateFallDamage()
{
    float CurrentHealth = CharacterData->CharacterAttribute.CharacterStat.GetHealth();
    float FallDamage    = Fall->GetDamage();

    float NewHealth = CurrentHealth - FallDamage;
    CharacterData->CharacterAttribute.CharacterStat.SetHealth(NewHealth);
}

void UAdvanceMovementComponent::UpdateFallDistance()
{
    FVector A               = Fall->GetStartLocation();
    FVector B               = CharacterOwner->GetActorLocation(); 
    float TravelDistance    = Fall->GetTravelDistance();
    float Distance          = FVector::Dist(A, B);
    float NewDistance       = TravelDistance + Distance;

    Fall->SetDistance(NewDistance);
}

void UAdvanceMovementComponent::UpdateFallDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = Fall->GetDuration();
    float NewDuration   = Duration + DeltaSecond;
    Fall->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateFallTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Fall->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaSecond;

    Fall->SetTotalTime(NewTotalTime);
}

#pragma endregion

#pragma region Transition

void UAdvanceMovementComponent::FallToIdle()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->MovementInputsInActive() || HorizontalVelocitySize() <= 0)
        {
            ExitFall();
            SetBasicMovement(IdleMovement);
            UE_LOG(LogTemp, Error, TEXT("FALL TO IDLE"));
            return;
        }
    }
}

void UAdvanceMovementComponent::FallToWalk()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.WalkEnabled() || (PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()))
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                ExitFall();
                SetBasicMovement(WalkMovement);
                UE_LOG(LogTemp, Error, TEXT("FALL TO WALK"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::FallToRun()
{ 
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                ExitFall();
                SetBasicMovement(RunMovement);
                UE_LOG(LogTemp, Error, TEXT("FALL TO RUN"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::FallToCrouch()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed() || PlayerInputCache->InputCrouchHeld())
        {
            if (CharacterData->CharacterAbility.CrouchAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Crouch->GetStaminaCost())
                {
                    ExitFall();
                    SetBasicMovement(CrouchMovement);
                    UE_LOG(LogTemp, Error, TEXT("FALL TO CROUCH"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::FallToCrawl()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitFall();
        SetBasicMovement(CrawlMovement);
        UE_LOG(LogTemp, Error, TEXT("FALL TO CRAWL"));
        return;
    }
}

void UAdvanceMovementComponent::FallToSlide()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputSlidePressed() || PlayerInputCache->InputSlideHeld())
        {
            if (GroundDistance() <= 5.0f)
            {
                ExitFall();
                SetSpecialMobility(SlideMobility);
                UE_LOG(LogTemp, Error, TEXT("FALL TO SLIDE"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::FallToRoll()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputRollPressed() || PlayerInputCache->InputRollHeld())
        {
            if (GroundDistance() <= 5.0f)
            {
                ExitFall();
                SetSpecialMobility(RollMobility);
                UE_LOG(LogTemp, Error, TEXT("FALL TO ROLL"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::FallToWallRun()
{
    if (Fall->TickDisabled())
    {
        return;
    }
    if (IsPlayer())
    {
        if (PlayerInputCache->InputSprintReleased() || PlayerInputCache->InputSprintInActive())
        {
            return;
        }

        if (SystemCore.PlayerMovementConfiguration.AutoWallRunEnable())
        {
            if (DiagonalWallDetected())
            {
                ExitFall();
                SetSpecialMobility(WallRunMobility);
                UE_LOG(LogTemp, Error, TEXT("FALL TO WALLRUN"));
                return;
            }
        }
        else if (PlayerInputCache->InputJumpHeld())
        {
            if (DiagonalWallDetected())
            {
                ExitFall();
                SetSpecialMobility(WallRunMobility);
                UE_LOG(LogTemp, Error, TEXT("FALL TO WALLRUN"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::FallToVerticalWallRun()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpHeld() && PlayerInputCache->InputMoveForwardHeld())
        {
            if (CharacterData->CharacterAbility.VerticalWallRunAbilityUnlocked())
            {
                if (VerticalWallRun->CanVerticalWallRun())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= VerticalWallRun->GetStaminaCost())
                    {
                        if (VerticalWallRunDetection())
                        {
                            ExitFall();
                            SetSpecialMobility(VerticalWallRunMobility);
                            UE_LOG(LogTemp, Error, TEXT("FALL TO VERTICAL WALL RUN"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::FallToHang()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoHangEnabled())
        {
            if (CharacterData->CharacterAbility.HangAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Hang->GetStaminaCost())
                {
                    if (DetectHang())
                    {
                        ExitFall();
                        SetSpecialMobility(ESpecialMovementState::Hang);
                        UE_LOG(LogTemp, Error, TEXT("FALL TO HANG"));
                        return;
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputHangPressed() || PlayerInputCache->InputHangHeld())
            {
                if (CharacterData->CharacterAbility.HangAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Hang->GetStaminaCost())
                    {
                        if (DetectHang())
                        {
                            ExitFall();
                            SetSpecialMobility(ESpecialMovementState::Hang);
                            UE_LOG(LogTemp, Error, TEXT("FALL TO HANG"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::FallToJump()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPreviousMovementState(JumpState))
    {
        return;
    }

    if (IsPlayer())
    {
        if (CharacterData->CharacterAbility.JumpAbilityUnlocked() && CharacterData->CharacterAbility.CoyoteJumpAbilityUnlocked())
        {
            if (PlayerInputCache->InputJumpPressed())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() >= Jump->GetStaminaCost())
                {
                    if (Fall->GetDuration() < 1.0f)
                    {
                        ExitFall();
                        SetSpecialMobility(JumpMobility);
                        UE_LOG(LogTemp, Error, TEXT("FALL TO JUMP"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::FallToGlide()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoGlideEnabled())
        {
            if (CharacterData->CharacterAbility.GlideAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Glide->GetStaminaCost())
                {
                    if (GroundDistance() >= Glide->GetMinimumDistance())
                    {
                        ExitFall();
                        SetAdvanceMobility(GlideMobility);
                        UE_LOG(LogTemp, Error, TEXT("FALL TO HANG"));
                        return;
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputGlidePressed())
            {
                if (CharacterData->CharacterAbility.GlideAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Glide->GetStaminaCost())
                    {
                        if (GroundDistance() >= Glide->GetMinimumDistance())
                        {
                            ExitFall();
                            SetAdvanceMobility(GlideMobility);
                            UE_LOG(LogTemp, Error, TEXT("FALL TO HANG"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::FallToSwim()
{

}

void UAdvanceMovementComponent::FallToDive()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputDivePressed() || PlayerInputCache->InputDiveHeld())
        {
            if (CharacterData->CharacterAbility.DiveAbilityUnlocked())
            {
                if (Fall->GetDuration() >= 3.0f && GroundDistance() >= Dive->GetMinimumDistance())
                {
                    ExitFall();
                    SetAdvanceMobility(DiveMobility);
                    UE_LOG(LogTemp, Error, TEXT("FALL TO DIVE"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::FallToHover()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (CharacterData->CharacterAbility.HoverAbilityUnlocked())
        {
            // TODO: Fall To Hover
        }
    }
}

void UAdvanceMovementComponent::FallToFly()
{
    if (Fall->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (CharacterData->CharacterAbility.FlyAbilityUnlocked())
        {
            if (Fall->GetDuration() >= 3.0f && GroundDistance() >= Fly->GetMinimumDistance())
            {
                ExitFall();
                SetAdvanceMobility(FlyMobility);
                UE_LOG(LogTemp, Error, TEXT("FALL TO FLY"));
                return;
            }
        }
    }
}

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region SpecialMobilityState

ESpecialMovementState UAdvanceMovementComponent::GetSpecialMobility() const
{
    return SpecialMobilityState;
}

void UAdvanceMovementComponent::SetSpecialMobility(ESpecialMovementState NewSpecialMobility)
{
    // If the new state is the same as the current state, log a debug message and exit.
    if (SpecialMobilityState == NewSpecialMobility)
    {
#if DEV_DEBUG_MODE
        // Log a warning for attempting to set the same SpecialMobilityState state.
        UE_LOG(LogTemp, Error, TEXT("Attempted to set the same SpecialMobilityState state."));
#endif
        return;
    }

    // Update the SpecialMobilityState state and reset other mobility states.
    SpecialMobilityState = NewSpecialMobility;
    BasicMovementState   = EBasicMovementState::Null;
    AdvanceMobilityState = EAdvanceMovementState::Null;

    SwitchSpecialMobilityState(NewSpecialMobility);
}

bool UAdvanceMovementComponent::IsSpecialMobility(ESpecialMovementState CheckSpecialMobility) const
{
    // Check if the current SpecialMobilityState state matches the given state
    return SpecialMobilityState == CheckSpecialMobility;
}

void UAdvanceMovementComponent::SwitchSpecialMobilityState(ESpecialMovementState InSpecialMobility)
{
    switch (InSpecialMobility)
    {
    case ESpecialMovementState::Null:
#if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Warning, TEXT("SpecialMobilityState state set to Null. No special mobility actions will be executed. Ensure this is expected."));
#endif
        break;
    case ESpecialMovementState::Jump:
        EnterJump();
        break;

    case ESpecialMovementState::Slide:
        EnterSlide();
        break;

    case ESpecialMovementState::Roll:
        EnterRoll();
        break;

    case ESpecialMovementState::WallRun:
        EnterWallRun();
        break;

    case ESpecialMovementState::VerticalWallRun:
        EnterVerticalWallRun();
        break;

    case ESpecialMovementState::Hang:
        EnterHang();
        break;

    case ESpecialMovementState::Dash:
        EnterDash();
        break;

    case ESpecialMovementState::Teleport:
        EnterTeleport();
        break;
    default:
        break;
    }
}

#pragma region Jump

void UAdvanceMovementComponent::EnterJump()
{
    SetMovementState(JumpState);
    Jump->SetState(EJumpState::ReadyToAttempt);

    if (Jump->IsReadyToAttempt())
    {
        GroundCheckTimer = 0.0f;
        Jump->SetStartLocation(CharacterOwner->GetActorLocation());

        if (IsPlayer())
        {
            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::JumpEnter);
            }
        }
        UE_LOG(LogTemp, Error, TEXT("Enter Jump"));

        SetLocomotionMode(ELocomotionMode::Aerial);
        SetMovementAnimationState(EMovementAnimationState::JumpStart);
    }
}

void UAdvanceMovementComponent::TickJumpMovement()
{
    if (Jump->TickDisabled())
    {
        return;
    }

    if (Jump->IsReadyToAttempt())
    {
        if (IsPreviousMovementState(WallRunState))
        {
            PerformWallRunJump();
        }
        else if (IsPreviousMovementState(VerticalWallRunState))
        {
            PerformVerticalWallRunJump(); 
        }
        else if (IsPreviousMovementState(HangState))
        {
            PerformHangJump();
        }
        else if (IsPreviousMovementState(FallState))
        {
            PerformCoyoteJump();
        }
        else if(IsPreviousMovementState(SprintState))
        {
            const FVector ForwardLaunch = CharacterOwner->GetActorForwardVector() * 100.f; // tweak 200.0f as needed
            const FVector UpwardLaunch = FVector(0.0f, 0.0f, CalculateJumpZVelocity());

            const FVector LaunchVelocity = ForwardLaunch + UpwardLaunch;
            CharacterOwner->LaunchCharacter(LaunchVelocity, false, true);
        }
        else
        {
            CharacterOwner->LaunchCharacter(FVector(0.0f, 0.0f, CalculateJumpZVelocity()), false, true);
        }

        UpdateJumpStamina();

        Jump->SetState(EJumpState::InProgress);

        SetMovementAnimationState(EMovementAnimationState::JumpApex);
    }

    if (Jump->IsInProgress())
    {
        UpdateJumpDuration();

        if (IsPlayer())
        {
            UpdateJumpTotalTime();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::JumpLoop);
            }
        }

        float DeltaSecond = GetWorld()->GetDeltaSeconds();
        GroundCheckTimer += DeltaSecond;
        if (FMath::IsNearlyZero(GroundDistance(), 1.0f) && GroundCheckTimer >= 1.0f)
        {
            JumpToIdle();
            JumpToWalk();
            JumpToRun();
        }

        JumpToVerticalWallRun();
        JumpToMantle();

        if (Velocity.Z <= Fall->GetTransitionThreshold())
        {
            JumpToFall();
        }
        else
        {
            JumpToHang();
            JumpToWallRun();
        }
    }
}

void UAdvanceMovementComponent::ExitJump()
{
    if (Jump->IsInProgress())
    {
        Jump->SetState(EJumpState::Complete);
    }

    if (Jump->IsComplete())
    {
        GroundCheckTimer = 0.0f;

        if (IsPlayer())
        {
            Jump->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateJumpTravelDistance();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                if (IsMovingOnGround())
                {
                    SetMovementCameraShakeState(EMovementCameraShakeState::JumpLand);
                }
            }
        }

        SetMovementAnimationState(EMovementAnimationState::JumpEnd);
    }
}

#pragma region Update

void UAdvanceMovementComponent::UpdateJumpDuration()
{
    float DeltaSecond  = GetWorld()->GetDeltaSeconds();
    float Duration     = Jump->GetDuration();
    float NewDuration  = Duration + DeltaSecond;

    Jump->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateJumpTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Jump->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaSecond;

    Jump->SetTotalTime(NewTotalTime);
}

void UAdvanceMovementComponent::UpdateJumpTravelDistance()
{
    FVector A               = Jump->GetStartLocation();
    FVector B               = Jump->GetEndLocation();

    float Distance          = FVector::Dist(A, B);
    float TravelDistance    = Jump->GetTravelDistance();

    float NewTravelDistance = TravelDistance + Distance;

    Jump->SetTravelDistance(NewTravelDistance);
}

void UAdvanceMovementComponent::UpdateJumpStamina()
{
    float StaminaCost = 0.0f;

    switch (PreviousMovementState)
    {
    case EMovementState::Idle:
        StaminaCost = Jump->GetIdleToJumpStaminaCost();
        break;
    case EMovementState::Walk:
        StaminaCost = Jump->GetWalkToJumpStaminaCost();
        break;
    case EMovementState::Run:
        StaminaCost = Jump->GetRunToJumpStaminaCost();
        break;
    case EMovementState::Sprint:
        StaminaCost = Jump->GetSprintToJumpStaminaCost();
        break;
    case EMovementState::Crouch:
        StaminaCost = Jump->GetCrouchToJumpStaminaCost();
        break;
    case EMovementState::Slide:
        StaminaCost = Jump->GetSlideToJumpStaminaCost();
        break;
    case EMovementState::Roll:
        StaminaCost = Jump->GetRollToJumpStaminaCost();
        break;
    case EMovementState::WallRun:
        StaminaCost = Jump->GetWallRunToJumpStaminaCost();
        break;
    case EMovementState::VerticalWallRun:
        StaminaCost = Jump->GetVerticalWallRunToJumpStaminaCost();
        break;
    case EMovementState::Hang:
        StaminaCost = Jump->GetHangToJumpStaminaCost();
        break;
    case EMovementState::Dash:
        StaminaCost = Jump->GetDashToJumpStaminaCost();
        break;
    case EMovementState::Teleport:
        StaminaCost = Jump->GetTeleportToJumpStaminaCost();
        break;
    case EMovementState::Vault:
        StaminaCost = Jump->GetVaultToJumpStaminaCost();
        break;
    case EMovementState::Mantle:
        StaminaCost = Jump->GetMantleToJumpStaminaCost();
        break;
    case EMovementState::Glide:
        StaminaCost = Jump->GetGlideToJumpStaminaCost();
        break;
    case EMovementState::Swim:
        StaminaCost = Jump->GetSwimToJumpStaminaCost();
        break;
    case EMovementState::Hover:
        StaminaCost = Jump->GetHoverToJumpStaminaCost();
        break;
    case EMovementState::Fly:
        StaminaCost = Jump->GetFlyToJumpStaminaCost();
        break;
    default:
        break;
    }

    float Stamina     = CharacterData->CharacterAttribute.CharacterStat.GetStamina();
    float MaxStamina  = CharacterData->CharacterAttribute.CharacterStat.GetMaxStamina();
    float NewStamina  = FMath::Clamp(Stamina - StaminaCost, 0.0f, MaxStamina);

    CharacterData->CharacterAttribute.CharacterStat.SetStamina(NewStamina);
}

#pragma endregion

#pragma region Utility

bool UAdvanceMovementComponent::ValidJumpHeight(float Distance) const
{
    FVector CapsuleLocation = CharacterOwner->GetCapsuleComponent()->GetComponentLocation();
    FVector CapsuleTop = CapsuleLocation + FVector(0.0f, 0.0f, GetOwner()->GetSimpleCollisionHalfHeight());
    FVector TraceEnd = CapsuleTop + FVector(0.0f, 0.0f, Distance);

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());

    bool bHit = 
    GetWorld()->LineTraceSingleByChannel
    (
        HitResult,
        CapsuleTop,
        TraceEnd,
        ECC_Visibility,
        QueryParams
    );

    bool bDebug = false;

    if (bHit)
    {
        if (bDebug)
        {
            DrawDebugLine(GetWorld(), CapsuleTop, TraceEnd, FColor::Red, false, 2.0f, 0, 2.0f);
        }
    }
    else
    {
        if (bDebug)
        {
            DrawDebugLine(GetWorld(), CapsuleTop, TraceEnd, FColor::Green, false, 2.0f, 0, 2.0f);
        }
    }

    return !bHit;
}

float  UAdvanceMovementComponent::CalculateJumpZVelocity()
{
    float VelocityZ       = 0.0f;
    float CurrentVelocity = HorizontalVelocitySize();

    if (IsPreviousMovementState(IdleState))
    {
        VelocityZ = Jump->GetIdleJumpZVelocity() * 1.5f;
    }
    else if (IsPreviousMovementState(WalkState))
    {    
		float MinimumWalkSpeed = Walk->GetMinimumSpeed();
		float MaximumWalkSpeed = Walk->GetMaximumSpeed();

        float MinWalkJumpZ = Jump->GetMinWalkJumpZVelocity();
        float MaxWalkJumpZ = Jump->GetMaxWalkJumpZVelocity();

		VelocityZ = FMath::GetMappedRangeValueClamped
		(
			FVector2D(MinimumWalkSpeed, MaximumWalkSpeed),
			FVector2D(MinWalkJumpZ, MaxWalkJumpZ),
			CurrentVelocity
		);
    }
    else if (IsPreviousMovementState(RunState))
    {
        float MinimumRunSpeed = Run->GetMinimumSpeed();
        float MaximumRunSpeed = Run->GetMaximumSpeed();

		float MinRunJumpZ = Jump->GetMinRunJumpZVelocity();
		float MaxRunJumpZ = Jump->GetMaxRunJumpZVelocity();

        VelocityZ = FMath::GetMappedRangeValueClamped
        (
            FVector2D(MinimumRunSpeed, MaximumRunSpeed),
            FVector2D(MinRunJumpZ, MaxRunJumpZ),
            CurrentVelocity
        );

        VelocityZ += 100.0f;
    }
    else if (IsPreviousMovementState(SprintState))
    {
        float MinimumSprintSpeed = Sprint->GetMinimumSpeed();
        float MaximumSprintSpeed = Sprint->GetMaximumSpeed();

		float MinSprintJumpZ = Jump->GetMinSprintJumpZVelocity();
		float MaxSprintJumpZ = Jump->GetMaxSprintJumpZVelocity();

        VelocityZ = FMath::GetMappedRangeValueClamped
        (
            FVector2D(MinimumSprintSpeed, MaximumSprintSpeed),
            FVector2D(MinSprintJumpZ, MaxSprintJumpZ),
            CurrentVelocity
        );
    }
    else if (IsPreviousMovementState(CrouchState))
    {
        float MinimumCrouchSpeed = Crouch->GetMinimumSpeed();
        float MaximumCrouchSpeed = Crouch->GetMaximumSpeed();

		float MinCrouchJumpZ = Jump->GetMinCrouchJumpZVelocity();
		float MaxCrouchJumpZ = Jump->GetMaxCrouchJumpZVelocity();

        VelocityZ = FMath::GetMappedRangeValueClamped
        (
            FVector2D(MinimumCrouchSpeed, MaximumCrouchSpeed),
            FVector2D(MinCrouchJumpZ, MaxCrouchJumpZ),
            CurrentVelocity
        );
    }
    else if (IsPreviousMovementState(WallRunState))
    {
        float MinimumWallRunSpeed = WallRun->GetMinimumSpeed();
        float MaximumWallRunSpeed = WallRun->GetMaximumSpeed();

		float MinWallRunJumpZ = Jump->GetMinWallRunJumpZVelocity();


        VelocityZ = FMath::GetMappedRangeValueClamped
        (
            FVector2D(MinimumWallRunSpeed, MaximumWallRunSpeed),
            FVector2D(Jump->GetMinWallRunJumpZVelocity(), Jump->GetMaxWallRunJumpZVelocity()),
            CurrentVelocity
        );
    }
    else if (IsPreviousMovementState(VerticalWallRunState))
    {
        float MinimumVerticalWallRunSpeed = VerticalWallRun->GetMinimumSpeed();
        float MaximumVerticalWallRunSpeed = VerticalWallRun->GetMaximumSpeed();

        VelocityZ = FMath::GetMappedRangeValueClamped
        (
            FVector2D(MinimumVerticalWallRunSpeed, MaximumVerticalWallRunSpeed),
            FVector2D(Jump->GetMinVerticalWallRunJumpZVelocity(), Jump->GetMaxVerticalWallRunJumpZVelocity()),
            CurrentVelocity
        );
    }

    return VelocityZ;
}



#pragma endregion

#pragma region Perform

void UAdvanceMovementComponent::PerformWallRunJump()
{
    FVector WallNormal      = WallRun->GetImpactNormal();
    FVector ForwardVector   = CharacterCapsuleComponent()->GetForwardVector();
    FVector UpVector        = CharacterCapsuleComponent()->GetUpVector();
    FVector CurrentVelocity = CharacterOwner->GetVelocity();
    float VelocitySize      = CurrentVelocity.Size();

    const FVector WallPush      = WallNormal * WallRun->GetWallPushMultiplier();
    const FVector UpwardBoost   = UpVector * WallRun->GetUpwardBoostMultiplier();
    const FVector ForwardBoost  = ForwardVector * WallRun->GetForwardBoostMultiplier();
    const FVector JumpDirection = (WallPush + UpwardBoost + ForwardBoost).GetSafeNormal() * VelocitySize;

    FVector ForwardForce        = ForwardVector * VelocitySize; 
    FVector UpwardForce         = UpVector * FMath::Clamp(VelocitySize, 300.0f, Sprint->GetMaximumSpeed()) * WallRun->GetUpwardForceMultiplier();

	float MinimumUpwardForce    = WallRun->GetMinimumUpwardForce();
	float MaximumUpwardForce    = WallRun->GetMaximumUpwardForce();

	float MinimumForwardForce   = WallRun->GetMinimumForwardForce();
	float MaximumForwardForce   = WallRun->GetMaximumForwardForce();

    if (WallRun->GetDuration() > 0.25f)
    {
        if (UpwardForce.Size() >= MaximumUpwardForce)
        {
            UpwardForce = UpwardForce.GetSafeNormal() * MaximumUpwardForce;
        }
        else if (UpwardForce.Size() <= MinimumUpwardForce)
        {
            UpwardForce = UpwardForce.GetSafeNormal() * MinimumUpwardForce;
        }
    }
    else
    {
        UpwardForce = UpwardForce.GetSafeNormal() * 50.0f;
    }

	if (WallRun->GetDuration() > 0.15f)
	{
		if (ForwardForce.Size() >= MaximumForwardForce)
		{
			ForwardForce = ForwardForce.GetSafeNormal() * MaximumForwardForce;
		}
		else if (ForwardForce.Size() <= MinimumForwardForce)
		{
			ForwardForce = ForwardForce.GetSafeNormal() * MinimumForwardForce;
		}
	}
	else
	{
		ForwardForce = ForwardForce.GetSafeNormal() * MaximumForwardForce * 0.25f;
	}

    // Launch character
    CharacterOwner->LaunchCharacter(JumpDirection + ForwardForce + UpwardForce, true, true);
}

void UAdvanceMovementComponent::PerformVerticalWallRunJump()
{
    FVector ForwardVector = CharacterCapsuleComponent()->GetForwardVector();

    float VerticalJumpImpulse = 600.0f;
    float BackwardPushImpulse = 600.0f;

    FVector LaunchVelocity = FVector::ZeroVector;
    LaunchVelocity += FVector::UpVector * VerticalJumpImpulse;
    LaunchVelocity -= ForwardVector * BackwardPushImpulse;

    CharacterOwner->LaunchCharacter(LaunchVelocity, true, true);

    // Flip the character to face the opposite direction
    FRotator CurrentRotation = CharacterOwner->GetActorRotation();
    FRotator NewRotation = CurrentRotation + FRotator(0.f, 180.f, 0.f);
    CharacterOwner->SetActorRotation(NewRotation);
}


void UAdvanceMovementComponent::PerformHangJump()
{
    FVector UpwardImpulse = FVector(0.0f, 0.0f, 200.0f);
    FVector BackwardImpulse = -CharacterOwner->GetActorForwardVector() * 400.0f;

    FVector LaunchVelocity = UpwardImpulse + BackwardImpulse;

    FRotator CurrentRotation = CharacterOwner->GetActorRotation();
    FRotator NewRotation = FRotator(CurrentRotation.Pitch, FRotator::ClampAxis(CurrentRotation.Yaw + 180.0f), CurrentRotation.Roll);

    CharacterOwner->bUseControllerRotationYaw = false;
    CharacterOwner->SetActorRotation(NewRotation);

    if (CharacterOwner->GetMesh())
    {
        CharacterOwner->GetMesh()->SetWorldRotation(NewRotation);
    }

    CharacterOwner->LaunchCharacter(LaunchVelocity, true, true);
}

void UAdvanceMovementComponent::PerformCoyoteJump()
{
    LOG_INFO("CoyoteJump");

    const float CoyoteJumpImpulse = 420.0f;

    FVector LaunchVelocity = FVector::UpVector * CoyoteJumpImpulse;

    FVector CurrentVelocity = CharacterOwner->GetVelocity();
    LaunchVelocity.X = CurrentVelocity.X;
    LaunchVelocity.Y = CurrentVelocity.Y;

    CharacterOwner->LaunchCharacter(LaunchVelocity, true, true);
}

#pragma endregion

#pragma region Transition

void UAdvanceMovementComponent::JumpToIdle()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->MovementInputsInActive())
        {
            ExitJump();
            SetBasicMovement(IdleMovement);
            UE_LOG(LogTemp, Error, TEXT("JUMP TO IDLE"));
            return;
        }
    }
}

void UAdvanceMovementComponent::JumpToWalk()
{
    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.WalkEnabled() || (PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()))
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                ExitJump();
                SetBasicMovement(WalkMovement);
                UE_LOG(LogTemp, Error, TEXT("JUMP TO WALK"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::JumpToRun()
{
    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                ExitJump();
                SetBasicMovement(RunMovement);
                UE_LOG(LogTemp, Error, TEXT("JUMP TO RUN"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::JumpToMantle()
{
    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoMantlingEnabled())
        {
            if (CharacterData->CharacterAbility.MantleAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Mantle->GetStaminaCost())
                {
                    if (MantleDetection())
                    {
                        ExitJump();
                        SetAdvanceMobility(EAdvanceMovementState::Mantle);
                        UE_LOG(LogTemp, Error, TEXT("JUMP TO MANTLE"));
                        return;
                    }
                }
            }
        }
        else if (PlayerInputCache->InputJumpPressed() || PlayerInputCache->InputJumpHeld())
        {
            if (PlayerInputCache->InputMoveForwardPressed() || PlayerInputCache->InputMoveForwardHeld())
            {
                if (CharacterData->CharacterAbility.MantleAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Mantle->GetStaminaCost())
                    {
                        if (MantleDetection())
                        {
                            ExitJump();
                            SetAdvanceMobility(EAdvanceMovementState::Mantle);
                            UE_LOG(LogTemp, Error, TEXT("JUMP TO MANTLE"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::JumpToWallRun()
{
    if (Jump->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputMoveBackwardPressed() || PlayerInputCache->InputMoveBackwardHeld())
        {
            return;
        }

        if (SystemCore.PlayerMovementConfiguration.AutoWallRunEnable())
        {
            if (CharacterData->CharacterAbility.WallRunAbilityUnlocked())
            {
                if (WallRunDetection())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= WallRun->GetStaminaCost())
                    {
                        ExitJump();
                        SetSpecialMobility(WallRunMobility);
                        UE_LOG(LogTemp, Error, TEXT("JUMP TO WALL RUN"));
                        return;
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputJumpHeld() && (PlayerInputCache->InputSprintHeld() || PlayerInputCache->InputSprintPressed()))
            {
                if (CharacterData->CharacterAbility.WallRunAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= 0.0f)
                    {
                        if (WallRunDetection())
                        {
                            ExitJump();
                            SetSpecialMobility(WallRunMobility);
                            UE_LOG(LogTemp, Error, TEXT("JUMP TO WALL RUN"));
                            return;
                        }           
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::JumpToVerticalWallRun()
{
	if (Jump->TickDisabled())
	{
		return;
	}   

    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpHeld() && PlayerInputCache->InputMoveForwardHeld())
        {
            if (CharacterData->CharacterAbility.VerticalWallRunAbilityUnlocked())
            {
                if (VerticalWallRun->CanVerticalWallRun())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= VerticalWallRun->GetStaminaCost())
                    {
                        if (VerticalWallRunDetection())
                        {
                            ExitJump();
                            SetSpecialMobility(VerticalWallRunMobility);
                            UE_LOG(LogTemp, Error, TEXT("JUMP TO VERTICAL WALL RUN"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::JumpToHang()
{
    if (Jump->TickDisabled())
    {
        return;
    }

    if (CharacterData->IsPlayer())
    {
        if (PlayerInputCache->InputHangPressed() || PlayerInputCache->InputHangHeld())
        {
            if (CharacterData->CharacterAbility.HangAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Hang->GetStaminaCost())
                {
                    if (DetectHang())
                    {
                        ExitJump();
                        SetSpecialMobility(HangMobility);
                        UE_LOG(LogTemp, Error, TEXT("JUMP TO HANG"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::JumpToDash()
{
    if (Jump->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputDashPressed())
        {
            if (CharacterData->CharacterAbility.DashAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Dash->GetStaminaCost())
                {
                    ExitJump();
                    SetSpecialMobility(SlideMobility);
                    UE_LOG(LogTemp, Error, TEXT("JUMP TO DASH"));
                    return;
                }
            }
        }
    }
    else if (IsAI())
    {

    }
}

void UAdvanceMovementComponent::JumpToGlide()
{
    if (Jump->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoGlideEnabled())
        {
            if (CharacterData->CharacterAbility.GlideAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Glide->GetStaminaCost())
                {
                    bool ValidDistance  = GroundDistance() >= Glide->GetMinimumDistance();
                    bool ValidVelocityZ = CharacterOwner->GetVelocity().Z <= 0.0f;

                    if (ValidDistance && ValidVelocityZ)
                    {
                        ExitJump();
                        SetAdvanceMobility(GlideMobility);
                        UE_LOG(LogTemp, Error, TEXT("JUMP TO GLIDE"));
                        return;
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputGlideHeld())
            {
                if (CharacterData->CharacterAbility.GlideAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Glide->GetStaminaCost())
                    {
                        bool ValidDistance  = GroundDistance() >= Glide->GetMinimumDistance();
                        bool ValidVelocityZ = CharacterOwner->GetVelocity().Z <= 0.0f;

                        if (ValidDistance && ValidVelocityZ)
                        {
                            ExitJump();
                            SetAdvanceMobility(GlideMobility);
                            UE_LOG(LogTemp, Error, TEXT("JUMP TO GLIDE"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::JumpToDive()
{
    if (Jump->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputDivePressed())
        {
            if (CharacterData->CharacterAbility.DiveAbilityUnlocked())
            {
                bool ValidDistance = GroundDistance() >= Glide->GetMinimumDistance();

                if (ValidDistance)
                {
                    ExitJump();
                    SetAdvanceMobility(DiveMobility);
                    UE_LOG(LogTemp, Error, TEXT("JUMP TO DIVE"));
                    return;
                }         
            }
        }
    }
}

void UAdvanceMovementComponent::JumpToFall()
{
    if (Jump->TickDisabled())
    {
        return;
    }

    ExitJump();
    SetBasicMovement(FallMovement);
    UE_LOG(LogTemp, Error, TEXT("JUMP TO FALL"));
    return;
}

#pragma endregion

#pragma endregion

#pragma region Slide

void UAdvanceMovementComponent::EnterSlide()
{
	SetMovementState(SlideState);
    Slide->SetState(ESlideState::ReadyToAttempt);

    if (Slide->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Slide->SetStartLocation(CharacterOwner->GetActorLocation());

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::SlideEnter);
            }
        }
    }
    UE_LOG(LogTemp, Error, TEXT("Enter Slide"));
}

void UAdvanceMovementComponent::TickSlideMovement()
{
    if (Slide->TickDisabled())
    {
        return;
    }

    if (Slide->IsReadyToAttempt())
    {
        Slide->SetState(ESlideState::InProgress);
        SetMovementCameraShakeState(EMovementCameraShakeState::SlideLoop);
    }

    if (Slide->IsInProgress())
    {
        UpdateSlideDuration();

        if (IsPlayer())
        {
            UpdateSlideTotalTime();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::SlideLoop);
            }
        }

        
        UpdateSlideStamina();
        PerformSlideMovement();

        if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() <= 0)
        {
            if (IsFalling() && GroundDistance() > 50.0f)
            {
                SlideToFall();
            }
            else
            {
                SlideToIdle();
            }
        }
        else if (Slide->IsSlideCompleted())
        {
            SlideToCrouch();
        }


        //if (Slide->IsSlideCompleted() || )
        //{
        //    SlideToRoll();
        //    SlideToIdle();
        //    SlideToWalk();
        //    SlideToRun();
        //}
       
        //if(IsFalling())
        //{
        //    SlideToFall();
        //}

        //SlideToCrawl();
        //SlideToSwim();
    }
}

void UAdvanceMovementComponent::ExitSlide()
{
    if (Slide->IsInProgress())
    {
        Slide->SetState(ESlideState::Complete);
        Slide->SetEndLocation(CharacterOwner->GetActorLocation());
    }

    if (Slide->IsComplete())
    {
        if (IsPlayer())
        {
            UpdateSlideTravelDistance();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::SlideExit);
            }
        }
    }

}

#pragma region Perform

void UAdvanceMovementComponent::PerformSlideMovement()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float GravityForce  = GetGravityZ();
    float GravityFactor = 0.50f;

    static float SlideTimeElapsed = 0.0f;
    static FVector SlideDirection;

    float SlideDuration = 1.0f;
    float MaxSlideSpeed = Slide->GetMaximumSpeed();
    float MinSlideSpeed = Slide->GetMinimumSpeed();

    FVector CurrentVelocity = CharacterOwner->GetVelocity();

    // Store initial slide direction once
    if (SlideTimeElapsed == 0.0f)
    {
        SlideDirection = CurrentVelocity.GetSafeNormal();
    }

    float InputYaw = 0.0f;
    float InputPitch = 0.0f;


    if (IsPlayer())
    {
        if (TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetController()))
        {
            PlayerController->GetInputMouseDelta(InputYaw, InputPitch);
        }
    }

    // Apply yaw rotation to SlideDirection
    if (!FMath::IsNearlyZero(InputYaw))
    {
        FRotator RotationDelta(0.0f, InputYaw * 2.0f, 0.0f); // Adjust rotation speed
        SlideDirection = RotationDelta.RotateVector(SlideDirection);
    }

    // Calculate interpolation factor
    float Alpha = FMath::Clamp(SlideTimeElapsed / SlideDuration, 0.0f, 1.0f);

    // Adjust speed: Increase in the first half, decrease in the second
    float SlideSpeed;
    if (SlideTimeElapsed < SlideDuration / 2)
    {
        SlideSpeed = FMath::Lerp(CurrentVelocity.Size(), MaxSlideSpeed, Alpha);
    }
    else
    {
        SlideSpeed = FMath::Lerp(MaxSlideSpeed, MinSlideSpeed, Alpha);
    }

    // Stop movement if velocity is too low
    if (SlideSpeed <= MinSlideSpeed)
    {
        Slide->SetSlideComplete(true);
        SlideTimeElapsed = 0.0f;
        CharacterOwner->GetCharacterMovement()->Velocity = FVector::ZeroVector;
        return;
    }

    // Apply new velocity with rotation
    FVector NewVelocity = SlideDirection.GetSafeNormal() * SlideSpeed;
    NewVelocity.Z += (GravityForce * GravityFactor) * DeltaSecond;

    CharacterOwner->LaunchCharacter(NewVelocity, true, true);

    SlideTimeElapsed += DeltaSecond;
}

#pragma endregion

#pragma region Update

void UAdvanceMovementComponent::UpdateSlideDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = Slide->GetDuration();
    float NewDuration   = Duration + DeltaSecond;

    Slide->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateSlideTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Slide->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaSecond;

    Slide->SetTotalTime(NewTotalTime);
}

void UAdvanceMovementComponent::UpdateSlideStamina()
{
    CharacterData->CharacterAttribute.CharacterStat.ApplyStaminaCost
    (
        Slide->GetStaminaCost()
    );
}

void UAdvanceMovementComponent::UpdateSlideTravelDistance()
{
    FVector A               = Slide->GetStartLocation();
    FVector B               = Slide->GetEndLocation();

    float Distance          = FVector::Dist(A, B);
    float TravelDistance    = Slide->GetTravelDistance();
    float NewDistance       = TravelDistance + Distance;

    Slide->SetTravelDistance(NewDistance);
}

#pragma endregion

#pragma region Transition

void UAdvanceMovementComponent::SlideToIdle()
{
    if (Slide->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed() || PlayerInputCache->InputCrouchHeld())
        {
            return;
        }

        if (PlayerInputCache->InputSlidePressed() || PlayerInputCache->InputSlideHeld())
        {
            return;
        }

        if (PlayerInputCache->MovementInputsInActive())
        {
            ExitSlide();
            SetBasicMovement(IdleMovement);
            UE_LOG(LogTemp, Error, TEXT("SLIDE TO IDLE"));
            return;
        }
    }
}

void UAdvanceMovementComponent::SlideToWalk()
{
    if (Slide->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld())
        {
            if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() <= 0 || Slide->IsSlideCompleted())
            {
                if (PlayerInputCache->AnyMovementInputActive())
                {
                    ExitSlide();
                    SetBasicMovement(WalkMovement);
                    UE_LOG(LogTemp, Error, TEXT("SLIDE TO WALK"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SlideToRun()
{
    if (Slide->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputWalkInActive() && SystemCore.PlayerMovementConfiguration.WalkDisabled())
        {
            if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() <= 0 || Slide->IsSlideCompleted())
            {
                if (PlayerInputCache->AnyMovementInputActive())
                {
                    ExitSlide();
                    SetBasicMovement(RunMovement);
                    UE_LOG(LogTemp, Error, TEXT("SLIDE TO RUN"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SlideToCrouch()
{
    if (Slide->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed() || PlayerInputCache->InputCrouchHeld())
        {
            if (CharacterData->CharacterAbility.CrouchAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Crouch->GetStaminaCost())
                {
                    ExitSlide();
                    SetBasicMovement(CrouchMovement);
                    UE_LOG(LogTemp, Error, TEXT("SLIDE TO Crouch"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SlideToProne()
{
    if (Slide->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputPronePressed() || PlayerInputCache->InputPronePressed())
        {
            if (CharacterData->CharacterAbility.ProneAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Crouch->GetStaminaCost())
                {
                    if (Slide->IsSlideCompleted())
                    {
                        ExitSlide();
                        SetBasicMovement(ProneMovement);
                        UE_LOG(LogTemp, Error, TEXT("SLIDE TO PRONE"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SlideToCrawl()
{
    if (Slide->TickDisabled())
    {
        return;
    }

    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitSlide();
        SetBasicMovement(CrawlMovement);
        UE_LOG(LogTemp, Error, TEXT("SLIDE TO CRAWL"));
        return;
    }
}

void UAdvanceMovementComponent::SlideToFall()
{
    if (Slide->TickDisabled())
    {
        return;
    }

    if (GroundDistance() >= 100.0f)
    {
        ExitSlide();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Error, TEXT("SLIDE TO FALL"));
        return;
    }
}

void UAdvanceMovementComponent::SlideToJump()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpPressed() || PlayerInputCache->InputJumpHeld())
        {
            if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetSlideToJumpStaminaCost())
                {
                    ExitSlide();
                    SetSpecialMobility(JumpMobility);
                    UE_LOG(LogTemp, Error, TEXT("SLIDE TO JUMP"));
                    return;
                }
            }
        } 
    }
}

void UAdvanceMovementComponent::SlideToRoll()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputRollPressed() || PlayerInputCache->InputRollHeld())
        {
            if (CharacterData->CharacterAbility.RollAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Roll->GetStaminaCost())
                {
                    ExitSlide();
                    SetSpecialMobility(RollMobility);
                    UE_LOG(LogTemp, Error, TEXT("SLIDE TO ROLL"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::SlideToDash()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputDashPressed() || PlayerInputCache->InputDashHeld())
        {          
            if (CharacterData->CharacterAbility.DashAbilityUnlocked() && ValidDashRange(Dash->GetMaximumDistance()))
            {
                if (Slide->GetDuration() >= Slide->GetNextActionCooldown())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Dash->GetStaminaCost())
                    {
                        ExitSlide();
                        SetSpecialMobility(DashMobility);
                        UE_LOG(LogTemp, Error, TEXT("SLIDE TO DASH"));
                        return;
                    }
                } 
            }
        }
    }
}

void UAdvanceMovementComponent::SlideToSwim()
{
    // TODO: Slide to swim
}

void UAdvanceMovementComponent::SlideToHover()
{
    // TODO: Slide to Hover
}

void UAdvanceMovementComponent::SlideToFly()
{
    // TODO: Slide to fly
}

#pragma endregion

#pragma endregion

#pragma region Roll

void UAdvanceMovementComponent::EnterRoll()
{
    SetMovementState(RollState);
    Roll->SetState(ERollState::ReadyToAttempt);

    if (Roll->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Roll->SetStartLocation(CharacterOwner->GetActorLocation());

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::RollEnter);
            }
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Roll"));
}

void UAdvanceMovementComponent::TickRollMovement()
{
    if (Roll->TickDisabled())
    {
        return;
    }

    if (Roll->IsReadyToAttempt())
    {
        Roll->SetState(ERollState::InProgress);
        SetMovementCameraShakeState(EMovementCameraShakeState::RollLoop);
    }
       
    if (Roll->IsInProgress())
    {
        UpdateRollDuration();

        if (IsPlayer())
        {
            UpdateRollTotalTime();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::RollLoop);
            }
        }
    }
}

void UAdvanceMovementComponent::ExitRoll()
{
    if (Roll->IsInProgress())
    {
        Roll->SetState(ERollState::Complete);
        SetMovementCameraShakeState(EMovementCameraShakeState::RollExit);
    }

    if (Roll->IsComplete())
    {
        if (IsPlayer())
        {
            Roll->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateRollTravelDistance();
        }
    }
}

#pragma region Update 

void UAdvanceMovementComponent::UpdateRollStamina()
{
    CharacterData->CharacterAttribute.CharacterStat.ApplyStaminaCost
    (
        Roll->GetStaminaCost()
    );
}

void UAdvanceMovementComponent::UpdateRollDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = Roll->GetDuration();
    float NewDuration   = Duration + DeltaSecond;

    Roll->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateRollTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Roll->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaSecond;

    Roll->SetTotalTime(NewTotalTime); 
}

void UAdvanceMovementComponent::UpdateRollTravelDistance()
{
    FVector A               = Roll->GetStartLocation();
    FVector B               = Roll->GetEndLocation();

    float Distance          = FVector::Dist(A, B);
    float TravelDistance    = Roll->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    Slide->SetTravelDistance(NewTravelDistance);
}

void UAdvanceMovementComponent::RollToIdle()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->MovementInputsInActive())
        {
            if (Roll->IsRollCompleted())
            {
                ExitRoll();
                SetBasicMovement(IdleMovement);
                UE_LOG(LogTemp, Error, TEXT("ROLL TO IDLE"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::RollToWalk()
{
    if (IsPlayer())
    {
        if ((PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()) || SystemCore.PlayerMovementConfiguration.WalkEnabled())
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                if (Roll->IsRollCompleted())
                {
                    ExitRoll();
                    SetBasicMovement(WalkMovement);
                    UE_LOG(LogTemp, Error, TEXT("ROLL TO WALK"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RollToRun()
{
    if (IsPlayer())
    {
        if ((SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive()))
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                if (Roll->IsRollCompleted())
                {
                    ExitRoll();
                    SetBasicMovement(RunMovement);
                    UE_LOG(LogTemp, Error, TEXT("ROLL TO RUN"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RollToCrouch()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed() || PlayerInputCache->InputCrouchHeld())
        {
            if (CharacterData->CharacterAbility.CrouchAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Roll->GetStaminaCost())
                {
                    if (Roll->IsRollCompleted())
                    {
                        ExitRoll();
                        SetBasicMovement(CrouchMovement);
                        UE_LOG(LogTemp, Error, TEXT("ROLL TO CROUCH"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RollToProne()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputPronePressed() || PlayerInputCache->InputProneHeld())
        {
            if (CharacterData->CharacterAbility.ProneAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Roll->GetStaminaCost())
                {
                    if (Roll->IsRollCompleted())
                    {
                        ExitRoll();
                        SetBasicMovement(ProneMovement);
                        UE_LOG(LogTemp, Error, TEXT("ROLL TO PRONE"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RollToCrawl()
{
    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitRoll();
        SetBasicMovement(CrawlMovement);
        UE_LOG(LogTemp, Error, TEXT("IDLE TO CRAWL"));
        return;
    }
}

void UAdvanceMovementComponent::RollToFall()
{
    if (!IsMovingOnGround())
    {
        ExitIdle();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Error, TEXT("IDLE TO FALL"));
        return;
    }
}

void UAdvanceMovementComponent::RollToJump()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpPressed() || PlayerInputCache->InputJumpHeld())
        {
            if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetRollToJumpStaminaCost())
                {
                    if (Roll->IsRollCompleted())
                    {
                        ExitRoll();
                        SetSpecialMobility(JumpMobility);
                        UE_LOG(LogTemp, Error, TEXT("ROLL TO JUMP"));
                        return;
                    }  
                }
            }
        }
    }
}

void UAdvanceMovementComponent::RollToSlide()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputSlidePressed() || PlayerInputCache->InputSlideHeld())
        {
            if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetStaminaCost())
                {
                    if (Roll->IsRollCompleted())
                    {
                        ExitRoll();
                        SetSpecialMobility(JumpMobility);
                        UE_LOG(LogTemp, Error, TEXT("ROLL TO SLIDE"));
                        return;
                    }
                }
            }
        }       
    }
}

void UAdvanceMovementComponent::RollToDash()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputDashPressed() || PlayerInputCache->InputDashHeld())
        {
            if (CharacterData->CharacterAbility.DashAbilityUnlocked() && ValidDashRange(Dash->GetMaximumDistance()))
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Dash->GetStaminaCost())
                {
                    if (Roll->IsRollCompleted())
                    {
                        ExitRoll();
                        SetSpecialMobility(DashMobility);
                        LOG_ERROR("ROLL TO DASH");
                        return;
                    }
                }
            }
        }
    }
}

#pragma endregion

#pragma endregion

#pragma region WallRun

void UAdvanceMovementComponent::EnterWallRun()
{
    SetMovementState(WallRunState);

    WallRun->SetState(EWallRunState::ReadyToAttempt);

    if (WallRun->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            WallRun->SetStartLocation(CharacterOwner->GetActorLocation());
            SetMovementSpeed(WallRun->GetInitialSpeed());

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                if (WallRun->IsWallRunSideLeft())
                {
                    SetMovementCameraShakeState(EMovementCameraShakeState::WallRunLeft);
                }
                else if (WallRun->IsWallRunSideRight())
                {
                    SetMovementCameraShakeState(EMovementCameraShakeState::WallRunRight);
                }
            }
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Enter WallRun"));
}

void UAdvanceMovementComponent::TickWallRunMovement()
{
    if (WallRun->TickDisabled())
    {
        return;
    }

    if (WallRun->IsReadyToAttempt())
    {
        WallRun->SetState(EWallRunState::InProgress);
    }

    if (WallRun->IsInProgress())
    {
        UpdateWallRunDuration();
        UpdateWallRunStamina();

        PerformWallRunMovement();

        WallRunToJump();
        WallRunToMantle();

        if (WallRun->TickDisabled())
        {
            return;
        }
        if (IsMovingOnGround())
        {
            WallRunToIdle();
            WallRunToWalk();
            WallRunToRun();
        }
        else
        {
            WallRunToFall();
        }

        if (IsPlayer())
        {
            UpdateWallRunTotalTime();
        }
    }
}

void UAdvanceMovementComponent::ExitWallRun()
{
    if (WallRun->IsInProgress())
    {
        SetMovementMode(MOVE_Walking);
        WallRun->SetState(EWallRunState::Complete);
    }

    if (WallRun->IsComplete())
    {
        if (IsPlayer())
        {
            WallRun->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateWallRunTravelDistance();
        }
    }
}

#pragma region Update

void UAdvanceMovementComponent::UpdateWallRunStamina()
{
    CharacterData->CharacterAttribute.CharacterStat.ApplyStaminaCost
    (
        WallRun->GetStaminaCost()
    );
}

void UAdvanceMovementComponent::UpdateWallRunDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = WallRun->GetDuration();
    float NewDuration   = Duration + DeltaSecond;

    WallRun->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateWallRunTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = WallRun->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaSecond;

    WallRun->SetTotalTime(NewTotalTime);
}

void UAdvanceMovementComponent::UpdateWallRunTravelDistance()
{
    FVector A = WallRun->GetStartLocation();
    FVector B = WallRun->GetEndLocation();

    float Distance          = FVector::Dist(A, B);
    float TravelDistance    = WallRun->GetTotalTravelDistance();
    float NewDistance       = TravelDistance + Distance;

    WallRun->SetTravelDistance(NewDistance);
}

#pragma endregion

#pragma region Transition

void UAdvanceMovementComponent::WallRunToIdle()
{
    if (WallRun->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->MovementInputsInActive())
        {
            ExitWallRun();
            SetBasicMovement(IdleMovement);
            UE_LOG(LogTemp, Error, TEXT("WALLRUN TO IDLE"));
            return;
        }
    }
}

void UAdvanceMovementComponent::WallRunToWalk()
{
    if (WallRun->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if ((PlayerInputCache->InputWalkPressed() || PlayerInputCache->InputWalkHeld()) || SystemCore.PlayerMovementConfiguration.WalkEnabled())
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                ExitWallRun();
                SetBasicMovement(WalkMovement);
                UE_LOG(LogTemp, Error, TEXT("WALLRUN TO WALK"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::WallRunToRun()
{
    if (WallRun->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.WalkDisabled() && PlayerInputCache->InputWalkInActive())
        {
            if (PlayerInputCache->AnyMovementInputActive())
            {
                ExitWallRun();
                SetBasicMovement(RunMovement);
                UE_LOG(LogTemp, Error, TEXT("WALLRUN TO RUN"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::WallRunToFall()
{
    if (WallRun->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        bool FallInputRequest =
        (PlayerInputCache->InputCrouchPressed() || PlayerInputCache->InputCrouchHeld()) ||
        (PlayerInputCache->InputPronePressed() || PlayerInputCache->InputProneHeld()) ||
        (PlayerInputCache->InputMoveBackwardPressed() || PlayerInputCache->InputMoveBackwardHeld());

        if (FallInputRequest)
        {
            ExitWallRun();
            SetBasicMovement(FallMovement);
            UE_LOG(LogTemp, Error, TEXT("WALL-RUN TO FALL"));
            return;
        }
    }

    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() <= 0.0f)
    {
        ExitWallRun();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Error, TEXT("WALL-RUN TO FALL(Stamina is depleted)"));
        return;
    }

    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0.0f)
    {
        if (GroundDistance() >= 100.0f)
        {
            ExitWallRun();
            SetBasicMovement(FallMovement);
            UE_LOG(LogTemp, Error, TEXT("WALL-RUN TO FALL(Health is depleted)"));
            return;
        }
    }

    if (IsWallRunEdgeReached())
    {
        ExitWallRun();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Error, TEXT("IsWallRunEdgeReached"));
        return;
    }

    if (WallRun->IsWallRunCompleted())
    {
        ExitWallRun();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Error, TEXT("IsWallRunCompleted"));
        return;
    }
}

void UAdvanceMovementComponent::WallRunToJump()
{
    if (WallRun->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoWallRunEnable())
        {
            if (PlayerInputCache->InputJumpPressed())
            {
                UE_LOG(LogTemp, Error, TEXT("InputJumpPressed"));
                if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetStaminaCost())
                    {
                        ExitWallRun();
                        SetSpecialMobility(JumpMobility);
                        UE_LOG(LogTemp, Error, TEXT("WALL-RUN TO JUMP"));
                        return;
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputJumpReleased())
            {
                if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetStaminaCost())
                    {
                        ExitWallRun();
                        SetSpecialMobility(JumpMobility);
                        UE_LOG(LogTemp, Error, TEXT("WALL-RUN TO JUMP"));
                        return;
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::WallRunToEdgeJump()
{
    if (WallRun->TickDisabled())
    {
        return;
    }

    if (IsWallRunEdgeReached())
    {
        if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() <= Jump->GetStaminaCost())
        {
            EWallRunSide WallSide = WallRun->GetWallRunSide();
            FVector JumpDirection = CharacterOwner->GetActorForwardVector() * HorizontalVelocitySize();

            if (WallSide == EWallRunSide::Left)
            {
                JumpDirection += CharacterOwner->GetActorRightVector() * (HorizontalVelocitySize() * 0.75f);
            }
            else if (WallSide == EWallRunSide::Right)
            {
                JumpDirection -= CharacterOwner->GetActorRightVector() * (HorizontalVelocitySize() * 0.75f);
            }

            JumpDirection.Z = HorizontalVelocitySize();
            CharacterOwner->LaunchCharacter(JumpDirection, true, true);
        }
    }
}

void UAdvanceMovementComponent::WallRunToMantle()
{
    if (WallRun->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoMantlingEnabled())
        {
            if (CharacterData->CharacterAbility.MantleAbilityUnlocked())
            {
                if (MantleDetection())
                {
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Mantle->GetStaminaCost())
                    {
                        ExitWallRun();
                        SetAdvanceMobility(MantleMobility);
                        UE_LOG(LogTemp, Error, TEXT("WALL-RUN TO MANTLE"));
                        return;
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputSprintPressed() || PlayerInputCache->InputSprintHeld())
            {
                if (CharacterData->CharacterAbility.MantleAbilityUnlocked())
                {
                    if (MantleDetection())
                    {
                        if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Mantle->GetStaminaCost())
                        {
                            ExitWallRun();
                            SetAdvanceMobility(MantleMobility);
                            UE_LOG(LogTemp, Error, TEXT("WALL-RUN TO JUMP"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

#pragma endregion

#pragma region Utility

bool UAdvanceMovementComponent::DiagonalWallDetected()
{
    /* Capsule Properties */
    FVector CapsuleCenter = CharacterOwner->GetCapsuleComponent()->GetComponentLocation();
    float CapsuleHalfHeight = CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
    float CapsuleRadius = CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleRadius();

    /* Directional Vectors */
    FVector ForwardVector = CharacterOwner->GetCapsuleComponent()->GetForwardVector();
    FVector RightVector = CharacterOwner->GetCapsuleComponent()->GetRightVector();

    /* Left Side */
    FVector LeftFootLocation = (CapsuleCenter - FVector(0.0f, 0.0f, CapsuleHalfHeight)) - (RightVector * CapsuleRadius);
    FVector LeftShoulderLocation = (CapsuleCenter + FVector(0.0f, 0.0f, CapsuleHalfHeight * 0.5f)) - (RightVector * CapsuleRadius);

    /* Right Side */
    FVector RightFootLocation = (CapsuleCenter - FVector(0.0f, 0.0f, CapsuleHalfHeight)) + (RightVector * CapsuleRadius);
    FVector RightShoulderLocation = (CapsuleCenter + FVector(0.0f, 0.0f, CapsuleHalfHeight * 0.5f)) + (RightVector * CapsuleRadius);

    /* Calculate 45-degree rotated direction vectors */
    FVector DiagonalForwardRight = ForwardVector.RotateAngleAxis(45.0f, FVector(0.0f, 0.0f, 1.0f)); // +45° from forward
    FVector DiagonalForwardLeft = ForwardVector.RotateAngleAxis(-45.0f, FVector(0.0f, 0.0f, 1.0f)); // -45° from forward

    /* Line trace distance */
    float TraceDistance = 50.0f;

    /* Hit results */
    FHitResult LeftFootHit, LeftShoulderHit, RightFootHit, RightShoulderHit;
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(CharacterOwner);

    /* Perform Line Traces */
    bool bLeftFootHit = GetWorld()->LineTraceSingleByChannel(LeftFootHit, LeftFootLocation, LeftFootLocation + (DiagonalForwardLeft * TraceDistance), ECC_Visibility, TraceParams);

    bool bLeftShoulderHit = GetWorld()->LineTraceSingleByChannel(LeftShoulderHit, LeftShoulderLocation, LeftShoulderLocation + (DiagonalForwardLeft * TraceDistance), ECC_Visibility, TraceParams);
    bool bRightFootHit = GetWorld()->LineTraceSingleByChannel(RightFootHit, RightFootLocation, RightFootLocation + (DiagonalForwardRight * TraceDistance), ECC_Visibility, TraceParams);
    bool bRightShoulderHit = GetWorld()->LineTraceSingleByChannel(RightShoulderHit, RightShoulderLocation, RightShoulderLocation + (DiagonalForwardRight * TraceDistance), ECC_Visibility, TraceParams);


    bool bDebug = false;
    if (bDebug)
    {
        /* Debug Line Drawing */
        DrawDebugLine(GetWorld(), LeftFootLocation, LeftFootLocation + (DiagonalForwardLeft * TraceDistance), FColor::Red, false, 10.0f, 0, 2.0f);
        DrawDebugLine(GetWorld(), RightFootLocation, RightFootLocation + (DiagonalForwardRight * TraceDistance), FColor::Green, false, 10.0f, 0, 2.0f);
        DrawDebugLine(GetWorld(), LeftShoulderLocation, LeftShoulderLocation + (DiagonalForwardLeft * TraceDistance), FColor::Blue, false, 10.0f, 0, 2.0f);
        DrawDebugLine(GetWorld(), RightShoulderLocation, RightShoulderLocation + (DiagonalForwardRight * TraceDistance), FColor::Yellow, false, 10.0f, 0, 2.0f);
    }

    return (bLeftFootHit && bLeftShoulderHit) || (bRightFootHit && bRightShoulderHit);
}

void UAdvanceMovementComponent::PerformWallRunMovement()
{
    if (WallRun->TickDisabled())
    {
        return;
    }

    FVector Normal = WallRun->GetImpactNormal();
    FVector ForwardDirection = FVector::CrossProduct(FVector::UpVector, Normal);

    if (WallRun->GetWallRunSide() == EWallRunSide::Left)
    {
        ForwardDirection *= -1.0f;
    }

    FRotator NewRotation = FRotationMatrix::MakeFromX(ForwardDirection).Rotator();
    CharacterCapsuleComponent()->SetWorldRotation(NewRotation);

    float DeltaTime              = GetWorld()->GetDeltaSeconds();
    float CurrentSpeed           = Velocity.Size();
    float MinimumSpeed           = WallRun->GetMinimumSpeed();
    float MaximumSpeed           = WallRun->GetMaximumSpeed();
	float AdditionalBoostSpeed   = WallRun->GetAdditionalBoostSpeed();

    static float InitialSpeed       = WallRun->GetInitialSpeed();
    static float SpeedScalingFactor = (CurrentSpeed / 10.0f);
    float SpeedBoost = 10.0f;

    float AdjustedTargetSpeed;
    if (PlayerInputCache->InputSprintHeld() && WallRun->GetDuration() >= 0.25f)
    {
        AdjustedTargetSpeed = FMath::Clamp((InitialSpeed + SpeedScalingFactor) + SpeedBoost, MinimumSpeed, MaximumSpeed);
    }
    else
    {
        AdjustedTargetSpeed = FMath::Clamp((InitialSpeed + SpeedScalingFactor) + SpeedBoost, MinimumSpeed, MaximumSpeed + AdditionalBoostSpeed);
    }


    float InterpolationSpeed = WallRun->GetInterpolationSpeed();
    MaxWalkSpeed             = FMath::FInterpTo(MaxWalkSpeed, AdjustedTargetSpeed, DeltaTime, InterpolationSpeed);

    FVector CurrentLocation  = CharacterCapsuleComponent()->GetComponentLocation();
    FVector NewLocation      = CurrentLocation;

    float Duration           = WallRun->GetDuration();
    float MaximumDuration    = WallRun->GetMaximumDuration();

    if (Duration < (MaximumDuration / 2))
    {
        float LiftForce = WallRun->GetLiftForce();

        NewLocation += ForwardDirection * MaxWalkSpeed * DeltaTime;
        NewLocation.Z += LiftForce;
    }
    else if(Duration > (MaximumDuration / 2) && Duration < MaximumDuration)
    {
        float DescentSpeed = FMath::Clamp(Duration - 1.5f, 0.0f, 1.0f) * 50.0f;
        NewLocation += ForwardDirection * MaxWalkSpeed * DeltaTime;
        NewLocation -= FVector::UpVector * DescentSpeed * DeltaTime;
    }
    else if(Duration >= MaximumDuration)
    {
        WallRun->SetWallRunCompleted(true);
    }

    float Friction = WallRun->GetFriction();
    float Gravity = WallRun->GetGravity();

    float DecelerationMultiplier = 0.50f;
    MaxWalkSpeed -= (Friction + Gravity) * DecelerationMultiplier;

    CharacterCapsuleComponent()->SetWorldLocation(NewLocation);
}

bool UAdvanceMovementComponent::WallRunDetection()
{
    FVector CapsuleLocation = CharacterCapsuleComponent()->GetComponentLocation();
    FVector ForwardVector   = CharacterCapsuleComponent()->GetForwardVector();
    FVector RightVector     = CharacterCapsuleComponent()->GetRightVector();
    FVector LeftVector      = -RightVector;
    FVector UpVector        = CharacterCapsuleComponent()->GetUpVector();

    float TraceDistance     = WallRun->GetDetectDistance();  

    float CapsuleHalfHeight = CharacterCapsuleComponent()->GetScaledCapsuleHalfHeight();
    float CapsuleRadius     = CharacterCapsuleComponent()->GetScaledCapsuleRadius();

    // Line trace positions (Feet, Mid, Head)
    FVector FeetLocation    = CapsuleLocation - (UpVector * (CapsuleHalfHeight * 0.7f));
    FVector MidLocation     = CapsuleLocation;
    FVector HeadLocation    = CapsuleLocation + (UpVector * (CapsuleHalfHeight * 0.7f));

    // Offsets for Left & Right traces
    float SideOffset        = CapsuleRadius; 
    FVector LeftOffset      = -RightVector * SideOffset;
    FVector RightOffset     = RightVector * SideOffset;

    FVector DiagonalOffsetLeft  = ForwardVector + LeftOffset.GetSafeNormal();
    FVector DiagonalOffsetRight = ForwardVector + RightOffset.GetSafeNormal();

    // Start and End locations for traces

    int TraceAmount = 6;
    /* Left */
    FVector TraceStartLeft[] = 
    {
        FeetLocation    + LeftOffset, 
        MidLocation     + LeftOffset, 
        HeadLocation    + LeftOffset,
        FeetLocation    + LeftOffset,
		MidLocation     + LeftOffset,
		HeadLocation    + LeftOffset
    };

    FVector TraceEndLeft[] =
    {
        TraceStartLeft[0] + (DiagonalOffsetLeft * TraceDistance),
        TraceStartLeft[1] + (DiagonalOffsetLeft * TraceDistance),
        TraceStartLeft[2] + (DiagonalOffsetLeft * TraceDistance),
		TraceStartLeft[3] + (LeftVector * TraceDistance),
		TraceStartLeft[4] + (LeftVector * TraceDistance),
		TraceStartLeft[5] + (LeftVector * TraceDistance)
    };

    /* Right */
    FVector TraceStartRight[] = 
    {
        FeetLocation    + RightOffset, 
        MidLocation     + RightOffset,
        HeadLocation    + RightOffset,
		FeetLocation    + RightOffset,
		MidLocation     + RightOffset,
		HeadLocation    + RightOffset
    };

    FVector TraceEndRight[] = 
    {
        TraceStartRight[0] + (DiagonalOffsetRight * TraceDistance),
        TraceStartRight[1] + (DiagonalOffsetRight * TraceDistance),
        TraceStartRight[2] + (DiagonalOffsetRight * TraceDistance),
		TraceStartRight[3] + (RightVector * TraceDistance),
		TraceStartRight[4] + (RightVector * TraceDistance),
		TraceStartRight[5] + (RightVector * TraceDistance)
    };

    FHitResult HitLeft[6], HitRight[6];
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(GetOwner());

    bool LeftHit = true, RightHit = true;


    for (int i = 0; i < TraceAmount; i++)
    {
        bool TraceHitLeft =
        GetWorld()->LineTraceSingleByChannel
        (
            HitLeft[i],
            TraceStartLeft[i],
            TraceEndLeft[i],
            ECC_Visibility,
            QueryParams
        );

        bool TraceHitRight = GetWorld()->LineTraceSingleByChannel
        (
            HitRight[i],
            TraceStartRight[i],
            TraceEndRight[i],
            ECC_Visibility,
            QueryParams
        );

        bool bDebug = false;
        if (bDebug)
        {
            FColor LeftColor    = TraceHitLeft ? FColor::Green : FColor::Red;
            FColor RightColor   = TraceHitRight ? FColor::Green : FColor::Red;

            DrawDebugLine(GetWorld(), TraceStartLeft[i], TraceEndLeft[i], LeftColor, true, 1.0f, 0, 2.0f);
            DrawDebugLine(GetWorld(), TraceStartRight[i], TraceEndRight[i], RightColor, true, 1.0f, 0, 2.0f);
        }


        if (TraceHitLeft == false)
        {
            LeftHit = false;
        }

        if (TraceHitRight == false)
        {
            RightHit = false;
        }
    }

    if (LeftHit)
    {
        WallRun->SetWallRunSide(EWallRunSide::Left);
        WallRun->SetImpactNormal(HitLeft[1].ImpactNormal);
        WallRun->SetImpactPoint(HitLeft[1].ImpactPoint);
        return true;
    }
    else if (RightHit)
    {
        WallRun->SetWallRunSide(EWallRunSide::Right);
        WallRun->SetImpactNormal(HitRight[1].ImpactNormal);
        WallRun->SetImpactPoint(HitRight[1].ImpactPoint);
        return true;
    }

    return false;
}

bool UAdvanceMovementComponent::IsWallRunEdgeReached()
{
    if (WallRun->TickDisabled())
    {
        return false;
    }

    float CapsuleHalfHeight = CharacterCapsuleComponent()->GetScaledCapsuleHalfHeight();
    FVector RightVector     = CharacterCapsuleComponent()->GetRightVector();


    FVector TraceStart      = CharacterCapsuleComponent()->GetComponentLocation() - FVector(0.0f, 0.0f, CapsuleHalfHeight - 10.0f);

    FVector TraceDirection  = WallRun->IsWallRunSideRight() ? RightVector : -RightVector;
    FVector TraceEnd        = TraceStart + (TraceDirection * 75.0f); 

    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);
    QueryParams.AddIgnoredComponent(CharacterCapsuleComponent());

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, QueryParams);

    bool bDebug = false;
    if (bDebug)
    {
        // Draw a red line from TraceStart to TraceEnd to visualize the trace
        DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, true, 1.0f, 0, 1.0f);
    }

    return !bHit;
}

bool UAdvanceMovementComponent::IsWallRunPathBlocked()
{
    if (WallRun->TickDisabled())
    {
        return false;
    }

    float CapsuleRadius = CharacterCapsuleComponent()->GetScaledCapsuleRadius() * 0.8f;
    float CapsuleHalfHeight = CharacterCapsuleComponent()->GetScaledCapsuleHalfHeight() * 0.8f;

    FVector ForwardVector = CharacterCapsuleComponent()->GetForwardVector();
    FVector TraceStart = CharacterCapsuleComponent()->GetComponentLocation();

    float ForwardDistance = 75.0f;

    FVector TraceEnd = TraceStart + (ForwardVector * ForwardDistance);

    // Collision parameters
    FHitResult HitResult;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);
    QueryParams.AddIgnoredComponent(CharacterCapsuleComponent());

    // Perform capsule trace
    bool bHit = GetWorld()->SweepSingleByChannel
    (
        HitResult,
        TraceStart,
        TraceEnd,
        FQuat::Identity,
        ECC_Visibility, 
        FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
        QueryParams
    );

    return bHit; 
}

#pragma endregion

#pragma endregion

#pragma region VerticalWallRun

void UAdvanceMovementComponent::EnterVerticalWallRun()
{
    SetMovementState(VerticalWallRunState);
    VerticalWallRun->SetState(EVerticalWallRunState::ReadyToAttempt);

    if (VerticalWallRun->IsReadyToAttempt())
    {
        VerticalWallRun->SetEntryVelocity(Velocity);
        VerticalWallRun->SetCanVerticalWallRun(false);

        StopMovementImmediately();
        Velocity = FVector::ZeroVector;

        if (IsPreviousMovementState(FallState))
        {
            FVector WallNormal = VerticalWallRun->GetWallNormal();
            FRotator LookAtWallRotation = (-WallNormal).Rotation();
            CharacterOwner->SetActorRotation(LookAtWallRotation);
            if (CharacterOwner->GetMesh())
            {
                CharacterOwner->GetMesh()->SetWorldRotation(LookAtWallRotation);
            }
        }

        if (IsPlayer())
        {
            VerticalWallRun->SetStartLocation(CharacterOwner->GetActorLocation());
            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::VerticalWallRunEnter);
            }
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Vertical WallRun"));
}

void UAdvanceMovementComponent::TickVerticalWallRunMovement()
{
    if (VerticalWallRun->TickDisabled())
    {
        return;
    }

    if (VerticalWallRun->IsReadyToAttempt())
    {
        VerticalWallRun->SetState(EVerticalWallRunState::InProgress);

        if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
        {
            SetMovementCameraShakeState(EMovementCameraShakeState::VerticalWallRunLoop);
        }
    }

    if (VerticalWallRun->IsInProgress())
    {
        UpdateVerticalWallRunDuration();
        UpdateVerticalWallRunStamina();
        PerformVerticalWallRunMovement();

        VerticalWallRunToHang();
        VerticalWallRunToMantle();
        VerticalWallRunToFall();
        VerticalWallRunToJump();

        if (IsPlayer())
        {
            UpdateVerticalWallRunTotalTime();
        }
    }
}

void UAdvanceMovementComponent::ExitVerticalWallRun()
{
    if (VerticalWallRun->IsInProgress())
    {
        VerticalWallRun->SetState(EVerticalWallRunState::Complete);
    }

    if (VerticalWallRun->IsComplete())
    {
        if (IsPlayer())
        {
            VerticalWallRun->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateVerticalWallRunTravelDistance();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::VerticalWallRunExit);
            }
        }

        FTimerHandle& TimerHandle = const_cast<FTimerHandle&>(VerticalWallRun->GetReadyToAttemptTimerHandle());

        GetWorld()->GetTimerManager().SetTimer
        (
            TimerHandle,
            this,
            &UAdvanceMovementComponent::VerticalWallRunReadyToAttemptTimerCompleted,
            VerticalWallRun->GetCanVerticalWallRunDelay(),
            false
        );
    }
}

#pragma region Perform

void UAdvanceMovementComponent::PerformVerticalWallRunMovement()
{
    // Get the upward direction
    FVector LaunchDirection = FVector::UpVector;

    // Optional: add a bit of forward push away from the wall
    const FVector WallForwardBoost = -VerticalWallRun->GetWallNormal() * 0.2f; // Adjust 0.2f as needed
    LaunchDirection += WallForwardBoost;

    // Normalize to prevent too large a boost
    LaunchDirection.Normalize();

    float ClimbSpeed = VerticalWallRun->GetClimbSpeed();
    float ClimbBoost = 1; 

    bool InputBoostRequest = PlayerInputCache->InputSprintPressed() || PlayerInputCache->InputSprintHeld();
    if (InputBoostRequest)
    {
        ClimbBoost += VerticalWallRun->GetClimbBoost();
    }

    FVector LaunchVelocity = LaunchDirection * ClimbSpeed * ClimbBoost;

    // Launch the character (don't override X/Y movement if you want air control)
    CharacterOwner->LaunchCharacter(LaunchVelocity, true, true);
}

#pragma endregion

#pragma region Utility

void UAdvanceMovementComponent::VerticalWallRunReadyToAttemptTimerCompleted()
{
    UE_LOG(LogTemp, Error, TEXT("VerticalWallRunReadyToAttemptTimerCompleted"));
    VerticalWallRun->SetCanVerticalWallRun(true);
}

bool UAdvanceMovementComponent::VerticalWallRunDetection()
{
    const bool bDebug = false;

    float CapsuleHalfHeight     = CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
    float CapsuleRadius         = CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleRadius();
    float TraceDistance         = VerticalWallRun->GetTraceDistance();
    float UpperCheckHeight      = 75.0f;

    FVector StartLocation = CharacterOwner->GetActorLocation();
    FVector ForwardVector = CharacterOwner->GetActorForwardVector();
    FVector EndLocation   = StartLocation + (ForwardVector * TraceDistance);

    FHitResult VerticalWallRunHit;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);

    // 1. Capsule trace forward to detect a wall
    bool bWallHit = GetWorld()->SweepSingleByChannel(
        VerticalWallRunHit,
        StartLocation,
        EndLocation,
        FQuat::Identity,
        ECC_Visibility,
        FCollisionShape::MakeCapsule(CapsuleRadius * 0.80f, CapsuleHalfHeight * 0.80f),
        QueryParams
    );

    if (bDebug)
    {
        DrawDebugCapsule(GetWorld(), EndLocation, CapsuleHalfHeight, CapsuleRadius, FQuat::Identity, FColor::Cyan, false, 2.0f, 0, 1.0f);
    }

    if (!bWallHit || !VerticalWallRunHit.bBlockingHit)
    {
        return false;
    }

    // 2. Line trace from ABOVE capsule forward to check vertical space for wall run
    FVector UpperStart = StartLocation + FVector(0.0f, 0.0f, CapsuleHalfHeight + UpperCheckHeight);
    FVector UpperEnd = UpperStart + (ForwardVector * TraceDistance);

    FHitResult UpperHit;
    bool bUpperHit = GetWorld()->LineTraceSingleByChannel(UpperHit, UpperStart, UpperEnd, ECC_Visibility, QueryParams);

    if (bDebug)
    {
        DrawDebugLine(GetWorld(), UpperStart, UpperEnd, bUpperHit ? FColor::Red : FColor::Green, false, 2.0f, 0, 2.0f);
    }

    if (bUpperHit && UpperHit.bBlockingHit)
    {
        FVector WallNormal = VerticalWallRunHit.ImpactNormal;
        VerticalWallRun->SetImpactPoint(VerticalWallRunHit.ImpactPoint);
        VerticalWallRun->SetWallNormal(WallNormal);

        FVector WallRight = FVector::CrossProduct(WallNormal, FVector::UpVector).GetSafeNormal();
        FVector WallUp = FVector::CrossProduct(WallRight, WallNormal).GetSafeNormal();
        VerticalWallRun->SetWallRunDirection(WallUp);


        return true;
    }

    return false;
}


#pragma endregion

#pragma region Update

void UAdvanceMovementComponent::UpdateVerticalWallRunStamina()
{
    float StaminaMultiplier = 1.0f;
    if (PlayerInputCache->InputSprintPressed() || PlayerInputCache->InputSprintHeld())
    {
        StaminaMultiplier = 1.5f;
    }

    CharacterData->CharacterAttribute.CharacterStat.ApplyStaminaCost
    (
        VerticalWallRun->GetStaminaCost() * StaminaMultiplier
    );
}


void UAdvanceMovementComponent::UpdateVerticalWallRunDuration()
{
    float DeltaSeconds  = GetWorld()->GetDeltaSeconds();
    float Duration      = VerticalWallRun->GetDuration();
    float NewDuration   = Duration + DeltaSeconds;

    VerticalWallRun->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateVerticalWallRunTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = VerticalWallRun->GetTotalTime();
    float NewTime       = TotalTime + DeltaSecond;

    VerticalWallRun->SetTotalTime(NewTime);
}

void UAdvanceMovementComponent::UpdateVerticalWallRunTravelDistance()
{
    FVector A               = VerticalWallRun->GetStartLocation();
    FVector B               = VerticalWallRun->GetEndLocation();

    float Distance          = FVector::Dist(A, B);
    float TravelDistance    = VerticalWallRun->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    VerticalWallRun->SetTravelDistance(NewTravelDistance);
}

#pragma endregion 

#pragma region Transition

void UAdvanceMovementComponent::VerticalWallRunToIdle()
{
    if (VerticalWallRun->TickDisabled())
    {
        return;
    }

    if (GroundDistance() <= 20.0f)
    {
        ExitVerticalWallRun();
        SetBasicMovement(IdleMovement);
        UE_LOG(LogTemp, Error, TEXT("VERTICAL WALL-RUN TO IDLE"));
        return;
    }
}

void UAdvanceMovementComponent::VerticalWallRunToJump()
{
    if (VerticalWallRun->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpReleased() || PlayerInputCache->InputJumpInActive())
        {
            if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetVerticalWallRunToJumpStaminaCost())
                {
                    ExitVerticalWallRun();
                    SetSpecialMobility(JumpMobility);
                    UE_LOG(LogTemp, Error, TEXT("VERTICAL WALL-RUN TO JUMP"));
                    return;
                }
            }
        }
    }
}

void UAdvanceMovementComponent::VerticalWallRunToFall()
{
    if (VerticalWallRun->TickDisabled())
    {
        return;
    }

    // Define start and end positions for forward check
    FVector CapsuleCenter = CharacterCapsuleComponent()->GetComponentLocation();
    FVector ForwardVector = CharacterCapsuleComponent()->GetForwardVector();
    FVector Start = CapsuleCenter;
    FVector End = Start + (ForwardVector * 75.0f);

    // Perform capsule trace using reduced size (80%) to check if still touching the wall
    float CapsuleRadius = CharacterCapsuleComponent()->GetScaledCapsuleRadius() * 0.80f;
    float CapsuleHalfHeight = CharacterCapsuleComponent()->GetScaledCapsuleHalfHeight() * 0.80f;

    FHitResult WallHit;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);

    bool bIsStillTouchingWall = GetWorld()->SweepSingleByChannel
    (
        WallHit,
        Start,
        End,
        FQuat::Identity,
        ECC_Visibility,
        FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
        QueryParams
    );

    if (!bIsStillTouchingWall)
    {
        ExitVerticalWallRun();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Warning, TEXT("NO WALL DETECTED — VERTICAL WALL-RUN TO FALL"));
        return;
    }


    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() <= 0 || VerticalWallRun->GetDuration() >= 2.0f)
    {
        ExitVerticalWallRun();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Error, TEXT("VERTICAL WALL-RUN TO FALL"));
        return;
    }

    if (IsPlayer())
    {
        bool FallInputRequest =
            PlayerInputCache->InputCrouchPressed() ||
            PlayerInputCache->InputCrouchHeld() ||
            PlayerInputCache->InputSlidePressed() ||
            PlayerInputCache->InputSlideHeld() ||
            PlayerInputCache->InputMoveBackwardPressed() ||
            PlayerInputCache->InputMoveBackwardHeld() ||

            (PlayerInputCache->InputMoveForwardReleased() || PlayerInputCache->InputMoveForwardInActive())
            &&
            (PlayerInputCache->InputJumpReleased() || PlayerInputCache->InputJumpInActive());
            

        if (FallInputRequest)
        {
            ExitVerticalWallRun();
            SetSpecialMobility(JumpMobility);
            UE_LOG(LogTemp, Error, TEXT("VERTICAL WALL-RUN TO JUMP"));
            return;
        }
    }
}

void UAdvanceMovementComponent::VerticalWallRunToHang()
{
    if (VerticalWallRun->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (SystemCore.PlayerMovementConfiguration.AutoMantlingEnabled())
        {
            if (CharacterData->CharacterAbility.HangAbilityUnlocked())
            {
                if (DetectHang())
                {            
                    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Hang->GetStaminaCost())
                    {
                        ExitVerticalWallRun();
                        SetSpecialMobility(HangMobility);
                        UE_LOG(LogTemp, Error, TEXT("VERTICAL WALL-RUN TO HANG"));
                        return;
                    }                   
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputHangPressed() || PlayerInputCache->InputHangHeld())
            {
                if (DetectHang())
                {
                    if (CharacterData->CharacterAbility.HangAbilityUnlocked())
                    {
                        if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Hang->GetStaminaCost())
                        {
                            ExitVerticalWallRun();
                            SetSpecialMobility(HangMobility);
                            UE_LOG(LogTemp, Error, TEXT("VERTICAL WALL-RUN TO HANG"));
                            return;
                        }
                    }
                }
            }
        }
    }
}

void UAdvanceMovementComponent::VerticalWallRunToMantle()
{
    if (VerticalWallRun->TickDisabled())
    {
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputHangPressed() || PlayerInputCache->InputHangHeld())
        {
            return;
        }

        if (SystemCore.PlayerMovementConfiguration.AutoHangEnabled())
        {
            return;
        }

        if (SystemCore.PlayerMovementConfiguration.AutoMantlingEnabled())
        {
            if (PlayerInputCache->InputSprintHeld() || PlayerInputCache->InputJumpHeld())
            {
                if (MantleDetection())
                {
                    if (CharacterData->CharacterAbility.MantleAbilityUnlocked())
                    {
                        if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Mantle->GetStaminaCost())
                        {
                            ExitVerticalWallRun();
                            SetAdvanceMobility(MantleMobility);
                            UE_LOG(LogTemp, Error, TEXT("VERTICAL WALL-RUN TO MANTLE"));
                            return;
                        }
                    }
                }
            }
        }
        else
        {
            if (PlayerInputCache->InputSprintHeld() || PlayerInputCache->InputJumpHeld())
            {
                if (MantleDetection())
                {
                    if (CharacterData->CharacterAbility.MantleAbilityUnlocked())
                    {
                        if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Mantle->GetStaminaCost())
                        {
                            ExitVerticalWallRun();
                            SetAdvanceMobility(MantleMobility);
                            UE_LOG(LogTemp, Error, TEXT("VERTICAL WALL-RUN TO MANTLE"));
                            return;
                        }
                    }
                }
            }
        }
    }
}
#pragma endregion 

#pragma endregion

#pragma region Hang

void UAdvanceMovementComponent::EnterHang()
{
	SetMovementState(HangState);
	Hang->SetState(EHangState::ReadyToAttempt);

    if (Hang->IsReadyToAttempt())
    {
        GravityScale = Hang->GetGravityScale();
        Velocity     = FVector::ZeroVector;
        SetMovementMode(MOVE_Flying);

        CharacterOwner->bUseControllerRotationYaw = false;
        bOrientRotationToMovement = false;
        StopMovementImmediately();

        if (IsPlayer())
        {
            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::HangEnter);
            }
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Hang"));
}

void UAdvanceMovementComponent::TickHangMovement()
{
    if (Hang->TickDisabled())
    {
        return;
    }

    if (Hang->IsReadyToAttempt())
    {
        Hang->SetState(EHangState::InProgress);
    }

    if (Hang->IsInProgress())
    {
		/* Updates */
        UpdateHangDuration();
        UpdateHangStamina();

        if (IsPlayer())
        {
            UpdateHangTotalTime();
        }


        /* Performs */
        PerformHangMovement();

        /* Transitions */
        HangToJump();
        HangToMantle();
        HangToFall();


        AdjustCapsuleHangLocation();
    }
}

void UAdvanceMovementComponent::ExitHang()
{
    if (Hang->IsInProgress())
    {
        Hang->SetState(EHangState::Complete);
    }

    if (Hang->IsComplete())
    {
        CharacterOwner->bUseControllerRotationYaw = true;
        bOrientRotationToMovement = true;

        SetMovementMode(MOVE_Falling);
        GravityScale = 1.0f;

        if (IsPlayer())
        {
            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::HangExit);
            }
        }
    }
}

#pragma region Perform

void UAdvanceMovementComponent::PerformHangMovement()
{
    if (IsPreviousMovementState(JumpState))
    {
        LOG_INFO("Player was previously in Jump state.");
    }
    else if (IsPreviousMovementState(FallState))
    {
        LOG_INFO("Player was previously in Fall state.");
    }
    else if (IsPreviousMovementState(VerticalWallRunState))
    {
        LOG_INFO("Player was previously in Vertical Wall Run state.");
    }
    else if (IsPreviousMovementState(WallRunState))
    {
        LOG_INFO("Player was previously in Wall Run state.");
    }

    FVector MovementOffset  = FVector::ZeroVector;
    FVector WallNormal      = Hang->GetImpactNormal();
    FVector WallRightVector = FVector::CrossProduct(WallNormal, FVector::UpVector).GetSafeNormal();
    float HorizontalSpeed   = Hang->GetHorizontalSpeed();
    float DeltaTime         = GetWorld()->GetDeltaSeconds();


    if (IsPlayer())
    {
        bool PlayerInputRequestLeft = PlayerInputCache->InputMoveLeftPressed() || PlayerInputCache->InputMoveLeftHeld();
        bool PlayerInputRequestRight = PlayerInputCache->InputMoveRightPressed() || PlayerInputCache->InputMoveRightHeld();

        if (PlayerInputRequestLeft)
        {
            MovementOffset = -WallRightVector * HorizontalSpeed * DeltaTime;

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::HangMovementLeft);
            }
        }
        else if (PlayerInputRequestRight)
        {
            MovementOffset = WallRightVector * HorizontalSpeed * DeltaTime;

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::HangMovementRight);
            }
        }
    }
    else if (IsAI())
    {

    }

    //// Get current capsule location and wall data 
    //FVector CurrentLocation = CharacterCapsuleComponent()->GetComponentLocation();
    //FVector WallNormal      = Hang->GetImpactNormal();
    //FVector WallRightVector = FVector::CrossProduct(WallNormal, FVector::UpVector).GetSafeNormal();
    //float DeltaTime         = GetWorld()->GetDeltaSeconds();
    //float HorizontalSpeed   = Hang->GetHorizontalSpeed();

    //FRotator TargetRotation     = WallNormal.ToOrientationRotator();
    //TargetRotation.Pitch        = 0.0f;
    //TargetRotation.Roll         = 0.0f;

    //if (IsPreviousMovementState(VerticalWallRunState))
    //{
    //    CharacterCapsuleComponent()->SetWorldLocation(CurrentLocation);
    //}
    //else
    //{
    //    CharacterCapsuleComponent()->SetWorldRotation(TargetRotation);
    //    CharacterCapsuleComponent()->SetWorldLocation(CurrentLocation);
    //}

  //  if (IsPlayer())
  //  {
		//FRotator ControlRotation = PlayerCharacterController->GetControlRotation();

  //      float WallYaw = (-WallNormal).ToOrientationRotator().Yaw;

  //      float YawMin = WallYaw - 90.0f;
  //      float YawMax = WallYaw + 90.0f;

  //      ControlRotation.Yaw = FMath::ClampAngle(ControlRotation.Yaw, YawMin, YawMax);
  //      ControlRotation.Pitch = FMath::ClampAngle(ControlRotation.Pitch, -60.0f, 60.0f); // limit look up/down

  //      PlayerCharacterController->SetControlRotation(ControlRotation);
  //  }

  //  // --- Step 3: Handle movement input only left/right along the wall ---
  //  FVector MovementOffset = FVector::ZeroVector;

  //  if (PlayerInputCache->InputMoveLeftPressed() || PlayerInputCache->InputMoveLeftHeld())
  //  {
  //      MovementOffset = -WallRightVector * HorizontalSpeed * DeltaTime;
  //  }
  //  else if (PlayerInputCache->InputMoveRightPressed() || PlayerInputCache->InputMoveRightHeld())
  //  {
  //      MovementOffset = WallRightVector * HorizontalSpeed * DeltaTime;
  //  }

  //  // Apply movement
  //  CharacterCapsuleComponent()->SetWorldLocation(CurrentLocation + MovementOffset);

}

bool bCapsuleReachedHangLocation = false;

void UAdvanceMovementComponent::AdjustCapsuleHangLocation()
{
    FVector HangPoint       = Hang->GetImpactPoint();
    FVector CapsuleLocation = CharacterCapsuleComponent()->GetComponentLocation();
    float CapsuleHalfHeight = CharacterCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
    FVector TargetLocation  = FVector(CapsuleLocation.X, CapsuleLocation.Y, HangPoint.Z - (CapsuleHalfHeight - 0.200f));

    if (!CapsuleLocation.Equals(TargetLocation, 0.01f))
    {
        float DeltaSecond = GetWorld()->GetDeltaSeconds();
        float InterpSpeed   = 10.0f; 
        FVector NewLocation = FMath::VInterpTo(CapsuleLocation, TargetLocation, DeltaSecond, InterpSpeed);
        CharacterOwner->SetActorLocation(NewLocation);
        bCapsuleReachedHangLocation = false;
    }
    else
    {
        bCapsuleReachedHangLocation = true;
    }
}


#pragma endregion

#pragma region Update

void UAdvanceMovementComponent::UpdateHangStamina()
{
    CharacterData->CharacterAttribute.CharacterStat.ApplyStaminaCost
    (
        Hang->GetStaminaCost()
    );
}

void UAdvanceMovementComponent::UpdateHangDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = Hang->GetDuration();
    float NewDuration   = Duration + DeltaSecond;

    Hang->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateHangTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Hang->GetTotalTime();
    float NewTime       = TotalTime + DeltaSecond;

    Hang->SetTotalTime(NewTime);
}

#pragma endregion

#pragma region Transition

void UAdvanceMovementComponent::HangToJump()
{
    if (IsPlayer())
    {
        if (PlayerInputCache->InputJumpPressed())
        {
            if (CharacterData->CharacterAbility.JumpAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Jump->GetHangToJumpStaminaCost())
                {
                    ExitHang();
                    SetSpecialMobility(JumpMobility);
                    UE_LOG(LogTemp, Error, TEXT("HANG TO JUMP"));
                    return;
                }
            }
            else
            {
                ExitHang();
                SetBasicMovement(FallMovement);
                UE_LOG(LogTemp, Error, TEXT("HANG TO FALL"));
                return;
            }
        }
    }
}

void UAdvanceMovementComponent::HangToMantle()
{
	if (IsPlayer())
	{
		if (PlayerInputCache->InputHangReleased() || PlayerInputCache->InputJumpReleased())
		{
            if (CharacterData->CharacterAbility.MantleAbilityUnlocked())
            {
                if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() >= Mantle->GetStaminaCost())
                {
                    ExitHang();
                    SetAdvanceMobility(MantleMobility);
                    UE_LOG(LogTemp, Error, TEXT("HANG TO MANTLE"));
                    return;
                }
            }
		}
	}
}

void UAdvanceMovementComponent::HangToFall()
{
    if (CharacterData->CharacterAttribute.CharacterStat.GetStamina() <= 0)
    {
        ExitHang();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Error, TEXT("HANG TO FALL"));
        return;
    }

    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
        ExitHang();
        SetBasicMovement(FallMovement);
        UE_LOG(LogTemp, Error, TEXT("HANG TO FALL"));
        return;
    }

    if (IsPlayer())
    {
        if (PlayerInputCache->InputCrouchPressed() || PlayerInputCache->InputCrouchHeld())
        {
            ExitHang();
            SetBasicMovement(FallMovement);
            UE_LOG(LogTemp, Error, TEXT("HANG TO FALL"));
            return;
        }

        if (PlayerInputCache->InputPronePressed() || PlayerInputCache->InputProneHeld())
        {
            ExitHang();
            SetBasicMovement(FallMovement);
            UE_LOG(LogTemp, Error, TEXT("HANG TO FALL"));
            return;
        }

		if (PlayerInputCache->InputMoveBackwardPressed() || PlayerInputCache->InputMoveBackwardHeld())
		{
			ExitHang();
			SetBasicMovement(FallMovement);
			UE_LOG(LogTemp, Error, TEXT("HANG TO FALL"));
			return;
		}
    }
}

#pragma endregion

#pragma endregion

#pragma region Dash

void UAdvanceMovementComponent::EnterDash()
{
	SetMovementState(DashState);
    Dash->SetState(EDashState::ReadyToAttempt);

    if (Dash->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Dash->SetStartLocation(CharacterOwner->GetActorLocation());
            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::DashEnter);
            }
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Dash"));
}

void UAdvanceMovementComponent::TickDashMovement()
{
    if (Dash->TickDisabled())
    {
        return;
    }

    if (Dash->IsReadyToAttempt())
    {
        Dash->SetState(EDashState::InProgress);

        if (IsPlayer())
        {
            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::DashLoop);
            }
        }
    }

    if (Dash->IsInProgress())
    {
        if (IsPlayer())
        {
            UpdateDashTotalTime();
        }
        UpdateDashDuration();
    }
}

void UAdvanceMovementComponent::ExitDash()
{
    if (Dash->IsInProgress())
    {
        Dash->SetState(EDashState::Complete);
    }

    if (Dash->IsComplete())
    {
        if (IsPlayer())
        {
            Dash->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateDashTravelDistance();

            if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
            {
                SetMovementCameraShakeState(EMovementCameraShakeState::DashExit);
            }
        }
    }
}

#pragma region Update

void UAdvanceMovementComponent::UpdateDashStamina()
{
    CharacterData->CharacterAttribute.CharacterStat.ApplyStaminaCost
    (
        Dash->GetStaminaCost()
    );
}

void UAdvanceMovementComponent::UpdateDashDuration()
{
    float DeltaSecond = GetWorld()->GetDeltaSeconds();
    float Duration = Dash->GetDuration();
    float NewDuration = Duration + DeltaSecond;

    Dash->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateDashTotalTime()
{
    float DeltaSecond = GetWorld()->GetDeltaSeconds();
    float TotalTime = Hang->GetTotalTime();
    float NewTime = TotalTime + DeltaSecond;

    Dash->SetTotalTime(NewTime);
}

void UAdvanceMovementComponent::UpdateDashTravelDistance()
{
    FVector A = Dash->GetStartLocation();
    FVector B = Dash->GetEndLocation();

    float Distance = FVector::Dist(A, B);

    float TravelDistance = Dash->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    Dash->SetTravelDistance(NewTravelDistance);
}

#pragma endregion

#pragma region Utility

bool UAdvanceMovementComponent::ValidDashRange(float Distance) const
{
    if (CharacterOwner == nullptr)
    {
		LOG_ERROR("CharacterOwner is null in ValidDashRange");
		return false;
    }

	// Get the capsule component
    TObjectPtr<UCapsuleComponent> Capsule = CharacterOwner->GetCapsuleComponent();
	if (Capsule == nullptr)
	{
		LOG_ERROR("Capsule component is null in ValidDashRange");
		return false;
	}

	// Get capsule location and dimensions
    FVector CapsuleLocation = Capsule->GetComponentLocation();
    float HalfCapsuleHeight = Capsule->GetScaledCapsuleHalfHeight() * 0.5f;
    float CapsuleRadius = Capsule->GetScaledCapsuleRadius();


    // Define trace start and end points
    FVector TraceStart = CapsuleLocation;
    FVector TraceEnd = TraceStart + (CharacterOwner->GetActorForwardVector() * Distance);

    // Capsule trace parameters
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);


    // Perform capsule trace with half height
    FHitResult HitResult;
    bool bHit = GetWorld()->SweepSingleByChannel
    (
        HitResult,
        TraceStart,
        TraceEnd,
        FQuat::Identity,
        ECC_Visibility,
        FCollisionShape::MakeCapsule(CapsuleRadius, HalfCapsuleHeight),
        QueryParams
    );

    FColor CapsuleColor = bHit ? FColor::Red : FColor::Green;

	// Draw debug capsule for visualization
    bool bDebug = false;
    if (bDebug)
    {
        // Draw start capsule
        DrawDebugCapsule
        (
            GetWorld(),
            TraceStart,
            HalfCapsuleHeight,
            CapsuleRadius,
            FQuat::Identity,
            CapsuleColor,
            false,
            2.0f // Debug duration
        );

        // Draw end capsule
        DrawDebugCapsule
        (
            GetWorld(),
            TraceEnd,
            HalfCapsuleHeight,
            CapsuleRadius,
            FQuat::Identity,
            CapsuleColor,
            false,
            2.0f
        );
    }

    // Dash is valid if no obstacle is hit
    return !bHit;
}

#pragma endregion

#pragma endregion

#pragma region Teleport

void UAdvanceMovementComponent::EnterTeleport()
{
	SetMovementState(EMovementState::Teleport);
	Teleport->SetState(ETeleportState::ReadyToAttempt);

	if (Teleport->IsReadyToAttempt())
	{
		if (IsPlayer())
		{
			Teleport->SetStartLocation(CharacterOwner->GetActorLocation());

			if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
			{
				SetMovementCameraShakeState(EMovementCameraShakeState::TeleportStart);
			}
		}

        Teleport->SetReachedTargetLocation(false);
	}

    UE_LOG(LogTemp, Error, TEXT("Enter Teleport"));
}

void UAdvanceMovementComponent::TickTeleportMovement()
{
	if (Teleport->TickDisabled())
	{
		return;
	}

	if (Teleport->IsReadyToAttempt())
	{
		Teleport->SetState(ETeleportState::InProgress);

		if (IsPlayer())
		{
			if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
			{
				SetMovementCameraShakeState(EMovementCameraShakeState::TeleportLoop);
			}
		}
	}

	if (Teleport->IsInProgress())
	{
        UpdateTeleportEnergy();
		UpdateTeleportDuration();
		PerformTeleportMovement();
        TeleportToCrawl();

		if (Teleport->IsReachedTargetLocation())
		{
			if (GroundDistance() >= 10.0f)
            {
                TeleportToFall();
			}
            else
            {
                TeleportToIdle();
            }
		}

        if (IsPlayer())
        {
            UpdateTeleportTotalTime();
        }
	}
}

void UAdvanceMovementComponent::ExitTeleport()
{
	if (Teleport->IsInProgress())
	{
		Teleport->SetState(ETeleportState::Complete);
	}

	if (Teleport->IsComplete())
	{
        Teleport->SetEndLocation(CharacterOwner->GetActorLocation());

		if (IsPlayer())
		{
            UpdateTeleportTravelDistance();

			if (SystemCore.PlayerMovementConfiguration.IsDynamicMovementCameraShakeEnabled())
			{
				SetMovementCameraShakeState(EMovementCameraShakeState::TeleportArrive);
			}
		}
	}
}

#pragma region Utility

bool UAdvanceMovementComponent::TeleportDetection()
{
    bool bDebug = false;

	float CapsuleHalfHeight = CharacterCapsuleComponent()->GetScaledCapsuleHalfHeight();
	float CapsuleRadius = CharacterCapsuleComponent()->GetScaledCapsuleRadius();

    FVector CapsuleLocation = CharacterCapsuleComponent()->GetComponentLocation();
	FVector TraceStart = CapsuleLocation;
	FVector TraceEnd = TraceStart + (CharacterOwner->GetActorForwardVector() * Teleport->GetMaxDistance());


	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(CharacterOwner);
	FHitResult HitResult;
	bool bHit = GetWorld()->SweepSingleByChannel
	(
		HitResult,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
		QueryParams
	);


    if (bDebug)
    {
        FColor CapsuleColor = bHit ? FColor::Red : FColor::Green;

        DrawDebugCapsule
        (
            GetWorld(),
            TraceStart,
            CapsuleHalfHeight,
            CapsuleRadius,
            FQuat::Identity,
            CapsuleColor,
            true
        );
    }

    if (bHit)
    {
        return false;
    }
   
	Teleport->SetStartLocation(CapsuleLocation);
	Teleport->SetTargetLocation(CharacterOwner->GetActorForwardVector() * Teleport->GetMaxDistance());


    return true;
}

#pragma endregion

#pragma region Perform

void UAdvanceMovementComponent::PerformTeleportMovement()  
{ 
    if (Teleport->IsReachedTargetLocation())
    {
        return;
    }

    // Ensure valid teleport target location  
    FVector CurrentLocation = CharacterOwner->GetActorLocation();
    FVector StartLocation   = Teleport->GetStartLocation();
    FVector TargetLocation  = Teleport->GetTargetLocation();
    float TravelSpeed       = Teleport->GetTravelDistance();

    // Smoothly interpolate the character's position towards the target location  
    FVector NewLocation = FVector::ZeroVector;

    if (Teleport->IsInstant())
    {
        CharacterOwner->SetActorLocation(TargetLocation);
        Teleport->SetReachedTargetLocation(true);
    }
    else
    {
        NewLocation = FMath::VInterpTo(StartLocation, TargetLocation, GetWorld()->GetDeltaSeconds(), TravelSpeed);

        if (!CurrentLocation.Equals(TargetLocation, 0.01f))
        {
            CharacterOwner->SetActorLocation(NewLocation);
        }
        else
        {
            Teleport->SetReachedTargetLocation(true);
        }
    }
}

#pragma endregion

#pragma region Update

void UAdvanceMovementComponent::UpdateTeleportEnergy()
{
	CharacterData->CharacterAttribute.CharacterStat.ConsumeEnergy
	(
		Teleport->GetEnergyCost()   
	);
}

void UAdvanceMovementComponent::UpdateTeleportDuration()
{
	float DeltaSecond = GetWorld()->GetDeltaSeconds();
	float Duration = Teleport->GetDuration();
	float NewDuration = Duration + DeltaSecond;
	Teleport->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateTeleportTotalTime()
{
	float DeltaSecond   = GetWorld()->GetDeltaSeconds();
	float TotalTime     = Teleport->GetTotalTime();
	float NewTime       = TotalTime + DeltaSecond;
	Teleport->SetTotalTime(NewTime);
}

void UAdvanceMovementComponent::UpdateTeleportTravelDistance()
{
	FVector A                   = Teleport->GetStartLocation();
	FVector B                   = Teleport->GetEndLocation();
	float Distance              = FVector::Dist(A, B);
	float TravelDistance        = Teleport->GetTravelDistance();
	float NewTravelDistance     = TravelDistance + Distance;

	Teleport->SetTravelDistance(NewTravelDistance);
}

#pragma endregion

#pragma region Transition

void UAdvanceMovementComponent::TeleportToIdle()
{
	if (Teleport->TickDisabled())
	{
        return;
	}

	if (IsPlayer())
	{
        if (PlayerInputCache->MovementInputsInActive())
        {
            ExitTeleport();
            SetBasicMovement(IdleMovement);
            UE_LOG(LogTemp, Error, TEXT("TELEPORT TO IDLE"));
            return;
        }
	}
}

void UAdvanceMovementComponent::TeleportToFall()
{
	if (Teleport->TickDisabled())
	{
		return;
	}

	if (Teleport->IsComplete())
	{
		ExitTeleport();
		SetBasicMovement(FallMovement);
		UE_LOG(LogTemp, Error, TEXT("TELEPORT TO FALL"));
		return;
	}
}

void UAdvanceMovementComponent::TeleportToCrawl()
{
    if (Teleport->TickDisabled())
    {
        return;
    }

    if (CharacterData->CharacterAttribute.CharacterStat.GetHealth() <= 0)
    {
		ExitTeleport();
		SetBasicMovement(CrawlMovement);
		UE_LOG(LogTemp, Error, TEXT("TELEPORT TO FALL"));
		return;
    }
}

#pragma endregion

#pragma region Utility

#pragma endregion

#pragma endregion

#pragma endregion

#pragma region AdvanceMobilityState

EAdvanceMovementState UAdvanceMovementComponent::GetAdvanceMobility() const
{
    return AdvanceMobilityState;
}

void UAdvanceMovementComponent::SetAdvanceMobility(EAdvanceMovementState NewAdvanceMobility)
{
    // If the new state is the same as the current state, log a debug message and exit.
    if (AdvanceMobilityState == NewAdvanceMobility)
    {
#if DEV_DEBUG_MODE
        // Log a warning for attempting to set the same AdvanceMobilityState state.
        UE_LOG(LogTemp, Error, TEXT("Attempted to set the same AdvanceMobilityState state."));
#endif
        return;
    }

    // Update the AdvanceMobilityState state and reset other mobility states.
    AdvanceMobilityState = NewAdvanceMobility;
    BasicMovementState   = EBasicMovementState::Null;
    SpecialMobilityState = ESpecialMovementState::Null;

    SwitchAdvanceMobilityState(NewAdvanceMobility);
}

bool UAdvanceMovementComponent::IsAdvanceMobility(EAdvanceMovementState CheckAdvanceMobility) const
{
    // Check if the current AdvanceMobilityState state matches the given state
    return AdvanceMobilityState == CheckAdvanceMobility;
}

void UAdvanceMovementComponent::SwitchAdvanceMobilityState(EAdvanceMovementState InAdvanceMobility)
{
    switch (InAdvanceMobility)
    {
    case EAdvanceMovementState::Null:
#if DEV_DEBUG_MODE
        UE_LOG(LogTemp, Warning, TEXT("AdvanceMobilityState state set to Null. No advanced mobility actions will be executed. Ensure this is intentional."));
#endif
        break;
    case EAdvanceMovementState::Vault:
        EnterVault();
        break;

    case EAdvanceMovementState::Mantle:
        EnterMantle();
        break;

    case EAdvanceMovementState::Glide:
        EnterGlide();
        break;

    case EAdvanceMovementState::Swim:
        EnterSwim();
        break;

    case EAdvanceMovementState::Dive:
        EnterDive();
        break;

    case EAdvanceMovementState::Hover:
        EnterHover();
        break;

    case EAdvanceMovementState::Fly:
        EnterFly();
        break;

    default:
        break;
    }
}

#pragma region Vault

#pragma region Lifecycle

void UAdvanceMovementComponent::EnterVault()
{
    SetMovementState(VaultState);
    SetMovementMode(MOVE_Flying);
    Vault->SetState(EVaultState::ReadyToAttempt);

    if (Vault->IsReadyToAttempt())
    {
        GetController()->SetIgnoreMoveInput(true);
        GetController()->SetIgnoreLookInput(true);

        Vault->SetStartLocation(CharacterOwner->GetActorLocation());
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Vault"));
}

void UAdvanceMovementComponent::TickVaultMovement()
{
    if (Vault->TickDisabled())
    {
        return;
    }

    if (Vault->IsReadyToAttempt())
    {
        Vault->SetState(EVaultState::InProgress);
    }

    if (Vault->IsInProgress())
    {
        UpdateVaultDuration();
        PerformVaultMovement();


        if (IsPlayer())
        {
            UpdateVaultTotalTime();
            UpdateVaultTravelDistance();
        }
    }

}

void UAdvanceMovementComponent::ExitVault()
{
    Vault->SetTick(false);
    SetMovementMode(MOVE_Walking);

    if (Vault->IsInProgress())
    {
        Vault->SetState(EVaultState::Complete);
    }


    if (Vault->IsComplete())
    {
        UpdateVaultStamina();


        if (IsPlayer())
        {
            GetController()->SetIgnoreMoveInput(false);
            GetController()->SetIgnoreLookInput(false);
        }
    }
}

#pragma endregion

#pragma region Perform

void UAdvanceMovementComponent::PerformVaultMovement()
{

}

#pragma endregion

#pragma region Update

void UAdvanceMovementComponent::UpdateVaultStamina()
{
    CharacterData->CharacterAttribute.CharacterStat.ApplyStaminaCost
    (
        Vault->GetStaminaCost()
    );
}

void UAdvanceMovementComponent::UpdateVaultDuration()
{
    float DeltaSecond = GetWorld()->GetDeltaSeconds();
    float Duration = Run->GetDuration();
    float NewDuration = Duration + DeltaSecond;

    Vault->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateVaultTotalTime()
{
    float TotalTime = Vault->GetTotalTime();
    float DeltaSecond = GetWorld()->GetDeltaSeconds();
    float NewTime = TotalTime + DeltaSecond;

    Vault->SetTotalTime(NewTime);
}

void UAdvanceMovementComponent::UpdateVaultTravelDistance()
{
    FVector A = Vault->GetStartLocation();
    FVector B = Vault->GetEndLocation();

    float Distance = FVector::Dist(A, B);
    float TravelDistance = Vault->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    Vault->SetTravelDistance(NewTravelDistance);
}

#pragma endregion

#pragma region Utility 

bool UAdvanceMovementComponent::VaultCheck()
{
    if (VaultHeightDetection())
    {
        if (VaultWitdhDetection())
        {
            if (VaultCapsuleSizeHeightValidation())
            {
                UE_LOG(LogTemp, Error, TEXT("ValidVault Check"));
                return true;
            }
        }
    }
    return false;
}

bool UAdvanceMovementComponent::VaultHeightDetection()
{
    float CapsuleHeight = CharacterCapsuleComponent()->GetScaledCapsuleHalfHeight();

    FVector CapsuleLocation = CharacterCapsuleComponent()->GetComponentLocation();
    FVector CapsuleForward = CharacterCapsuleComponent()->GetForwardVector();
    FVector CapsuleUpward = CharacterCapsuleComponent()->GetUpVector();

    FVector CapsuleFloor = CapsuleLocation - (CapsuleUpward * CapsuleHeight);
    FVector CapsuleCeil = CapsuleFloor + (CapsuleUpward * ((CapsuleHeight * 2.0f) + 40.0f));
    FVector ForwardTarget = CapsuleCeil + (CapsuleForward * Vault->GetHeightForwardTraceDistance());

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);
    QueryParams.AddIgnoredComponent(CharacterCapsuleComponent());

    bool LastHit = false;
    FVector LastHitLocation = FVector::ZeroVector;

    for (float FloorZ = CapsuleFloor.Z; FloorZ < CapsuleCeil.Z; FloorZ += 1.0f)
    {
        float ForwardTraceDistance = Vault->GetHeightForwardTraceDistance();

        FVector Start = FVector(CapsuleLocation.X, CapsuleLocation.Y, FloorZ);
        FVector End = Start + (CapsuleForward * ForwardTraceDistance);
        FHitResult ForwardHit;

        bool bHit = GetWorld()->LineTraceSingleByChannel
        (
            ForwardHit,
            Start,
            End,
            ECC_Visibility,
            QueryParams
        );

        if (bHit)
        {
            LastHitLocation = ForwardHit.ImpactPoint;
            LastHit = true;
        }
        else
        {
            if (LastHit)
            {
                FVector UpdatedCapsuleFloor = CapsuleFloor;
                UpdatedCapsuleFloor.X = LastHitLocation.X;

                float Distance = FVector::Dist(LastHitLocation, UpdatedCapsuleFloor);
                float Height = FMath::Abs(LastHitLocation.Z - UpdatedCapsuleFloor.Z);

                Vault->SetHeightDistance(Height);
                LastHitLocation.Z += 3.0f;
                Vault->SetHeightLastImpactPoint(LastHitLocation);


                float MaximumHeight = Vault->GetMaximumHeight();
                if (Height <= MaximumHeight)
                {
                    if (Height > 200.0f)
                    {
                        Vault->SetVaultHeightType(EVaultHeightType::Climbable);
                    }
                    else if (Height > 160.0f)
                    {
                        Vault->SetVaultHeightType(EVaultHeightType::High);
                    }
                    else if (Height > 100.0f)
                    {
                        Vault->SetVaultHeightType(EVaultHeightType::Medium);
                    }
                    else if (Height > 50.0f)
                    {
                        Vault->SetVaultHeightType(EVaultHeightType::Low);
                    }
                    else if (Height > 0.0f)
                    {
                        Vault->SetVaultHeightType(EVaultHeightType::StepUp);
                    }
                    else
                    {
                        Vault->SetVaultHeightType(EVaultHeightType::None);
                    }
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

bool UAdvanceMovementComponent::VaultWitdhDetection()
{
    FVector CapsuleUpward = CharacterCapsuleComponent()->GetUpVector();
    FVector CapsuleForward = CharacterCapsuleComponent()->GetForwardVector();

    FVector StartLocation = Vault->GetHeightLastImpactPoint();
    FVector ForwardEndLocation = StartLocation + (CapsuleForward * 200.0f);

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);
    QueryParams.AddIgnoredComponent(CharacterCapsuleComponent());


    FHitResult DistanceHit;


    for (float Step = 0.0f; Step <= 200.0f; Step += 1.0f)
    {
        FVector CurrentStartLocation = StartLocation + (CapsuleForward * Step);
        FVector DownwardEndLocation = CurrentStartLocation - (CapsuleUpward * 10.0f);

        bool bDistanceHit =
            GetWorld()->LineTraceSingleByChannel
            (
                DistanceHit,
                CurrentStartLocation,
                DownwardEndLocation,
                ECC_Visibility,
                QueryParams
            );

        bool bDebug = false;

        bool bLastHit = false;

        if (bDistanceHit)
        {
            if (bDebug)
            {
                DrawDebugLine
                (
                    GetWorld(),
                    CurrentStartLocation,
                    DownwardEndLocation,
                    FColor::Cyan,
                    false,
                    10.0f,
                    0,
                    1.0f
                );
            }
            bLastHit = true;
        }
        else
        {
            if (bLastHit)
            {
                Vault->SetWidthLastImpactPoint(DistanceHit.ImpactPoint);

                float Distance = FVector::Dist(Vault->GetHeightLastImpactPoint(), Vault->GetWidthLastImpactPoint());
                Vault->SetWidthDistance(FMath::Abs(Distance));


                float MinimumDistance = Vault->GetMinimumDistance();
                float MaximumDistance = Vault->GetMaximumDistance();

                if (Distance <= MinimumDistance)
                {
                    return false;
                }
                else
                {
                    if (Distance >= MaximumDistance)
                    {
                        Vault->SetVaultWidthType(EVaultWidthType::Unreachable);
                    }
                    else if (Distance > 180.0f)
                    {
                        Vault->SetVaultWidthType(EVaultWidthType::Extended);
                    }
                    else if (Distance > 120.0f)
                    {
                        Vault->SetVaultWidthType(EVaultWidthType::Long);
                    }
                    else if (Distance > 50.0f)
                    {
                        Vault->SetVaultWidthType(EVaultWidthType::Medium);
                    }
                    else if (Distance > 0.0f)
                    {
                        Vault->SetVaultWidthType(EVaultWidthType::Short);
                    }
                    else
                    {
                        Vault->SetVaultWidthType(EVaultWidthType::Unreachable);
                    }
                }
            }

            if (bDebug)
            {
                DrawDebugLine
                (
                    GetWorld(),
                    CurrentStartLocation,
                    DownwardEndLocation,
                    FColor::Purple,
                    false,
                    10.0f,
                    0,
                    1.0f
                );
            }
        }
    }

    return true;
}

bool UAdvanceMovementComponent::VaultCapsuleSizeHeightValidation()
{
    float CapsuleHalfHeight = CharacterCapsuleComponent()->GetScaledCapsuleHalfHeight();
    float CapsuleRadius = CharacterCapsuleComponent()->GetScaledCapsuleRadius();

    FVector CapsuleForward = CharacterCapsuleComponent()->GetForwardVector();
    FVector CapsuleUpward = CharacterCapsuleComponent()->GetUpVector();

    FVector AdjustedHeightImpactPoint = Vault->GetHeightLastImpactPoint() + (CapsuleForward * CapsuleRadius);

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(CharacterOwner);
    CollisionParams.AddIgnoredComponent(CharacterCapsuleComponent());

    FHitResult HeightHit;

    struct FCapsuleInformation
    {
        FString Name;
        float CapsuleHeight;
        FColor DebugColor;
    };

    TArray<FCapsuleInformation> CapsuleInformations =
    {
        { TEXT("Prone"),    CapsuleHalfHeight / 2.0f,   FColor::Green },
        { TEXT("Crouch"),   CapsuleHalfHeight,          FColor::Yellow },
        { TEXT("Full"),     CapsuleHalfHeight * 2.0f,   FColor::Red },
    };

    // Track if even prone size is blocked
    bool LowHit = false;    //  Prone
    bool MidHit = false;    //  Crouch
    bool HighHit = false;    //  Full

    for (const FCapsuleInformation& CapsuleInformation : CapsuleInformations)
    {
        FVector StartLocation = AdjustedHeightImpactPoint;
        FVector EndLocation = StartLocation + (CapsuleUpward * CapsuleInformation.CapsuleHeight);

        bool bDebug = false;

        if (bDebug)
        {
            DrawDebugLine
            (
                GetWorld(),
                StartLocation,
                EndLocation,
                CapsuleInformation.DebugColor,
                true
            );
        }

        bool bHit = GetWorld()->LineTraceSingleByChannel(HeightHit, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

        if (bHit)
        {
            if (bDebug)
            {
                DrawDebugBox
                (
                    GetWorld(),
                    HeightHit.ImpactPoint,
                    FVector(10.0f, 10.0f, 10.0f),
                    FQuat::Identity,
                    CapsuleInformation.DebugColor,
                    true
                );
            }

            if (CapsuleInformation.Name == "Prone")
            {
                UE_LOG(LogTemp, Error, TEXT("LowHit"));
                LowHit = true;
            }
            else if (CapsuleInformation.Name == "Crouch")
            {
                UE_LOG(LogTemp, Error, TEXT("MidHit"));
                MidHit = true;
            }
            else if (CapsuleInformation.Name == "Full")
            {
                UE_LOG(LogTemp, Error, TEXT("FullHit"));
                HighHit = true;
            }
            break;
        }
    }

    if (LowHit)
    {
        return false;
    }

    return true;
}

#pragma endregion

#pragma endregion

#pragma region Mantle

#pragma region Lifecycle

void UAdvanceMovementComponent::EnterMantle()
{
    SetMovementState(MantleState);
    Mantle->SetState(EMantleState::ReadyToAttempt);
    if (Mantle->IsReadyToAttempt())
    {
        Velocity = FVector::ZeroVector;

        if (IsPlayer())
        {
            Mantle->SetStartLocation(CharacterOwner->GetActorLocation());
        }
    }

    UE_LOG(LogTemp, Error, TEXT("Enter Mantle"));
}

void UAdvanceMovementComponent::TickMantleMovement()
{
    if (Mantle->TickDisabled())
    {
        return;
    }

    if (Mantle->IsReadyToAttempt())
    {
        Mantle->SetState(EMantleState::InProgress);
    }

    if (Mantle->IsInProgress())
    {
        UpdateMantleDuration();
        UpdateMantleStamina();
        
        if (IsPlayer())
        {
            UpdateMantleTotalTime();
        }

        PerformMantleMovement();
    }
}

void UAdvanceMovementComponent::ExitMantle()
{
    if (Mantle->IsInProgress())
    {
        Mantle->SetState(EMantleState::Complete);
    }

    if (Mantle->IsComplete())
    {
        if (IsPlayer())
        {
            Mantle->SetEndLocation(CharacterOwner->GetActorLocation());
            UpdateMantleTravelDistance();
        }
    }
}

#pragma endregion

#pragma region Perform

void UAdvanceMovementComponent::PerformMantleMovement()
{
    if (IsPreviousMovementState(HangState))
    {
        float FirstTransitionDuration = 0.25f;
        float SecondTransitionDuration = 0.35f;

        if (Mantle->GetDuration() < FirstTransitionDuration)
        {
            float JumpZ = 800.0f;

            FVector JumpVelocity = FVector(0.0f, 0.0f, JumpZ);
            CharacterOwner->LaunchCharacter(JumpVelocity, true, true);
        }
        else if (Mantle->GetDuration() < SecondTransitionDuration)
        {
            FVector ForwardVector = CharacterCapsuleComponent()->GetForwardVector();
            FVector CurrentLocation = CharacterCapsuleComponent()->GetComponentLocation();
            FVector ForwardPosition = CurrentLocation + (ForwardVector * 250.0f);

            CharacterOwner->LaunchCharacter(ForwardPosition - CurrentLocation, true, true);
        }
    }
    else if (IsPreviousMovementState(VerticalWallRunState))
    {
        float FirstTransitionDuration = 0.25f;
        float SecondTransitionDuration = 0.35f;

        if (Mantle->GetDuration() < FirstTransitionDuration)
        {
            float JumpZ = 800.0f;

            FVector JumpVelocity = FVector(0.0f, 0.0f, JumpZ);
            CharacterOwner->LaunchCharacter(JumpVelocity, true, true);
        }
        else if (Mantle->GetDuration() < SecondTransitionDuration)
        {
            FVector ForwardVector = CharacterCapsuleComponent()->GetForwardVector();
            FVector CurrentLocation = CharacterCapsuleComponent()->GetComponentLocation();
            FVector ForwardPosition = CurrentLocation + (ForwardVector * 250.0f);

            CharacterOwner->LaunchCharacter(ForwardPosition - CurrentLocation, true, true);
        }
    }
    else if (IsPreviousMovementState(JumpState))
    {
        float UpTransitionDuration = 0.25f;
        float ForwardTransitionDuration = 0.35f;

        if (Mantle->GetDuration() < UpTransitionDuration)
        {
            float JumpZ = 800.0f;

            FVector JumpVelocity = FVector(0.0f, 0.0f, JumpZ);
            CharacterOwner->LaunchCharacter(JumpVelocity, true, true);
        }
        else if (Mantle->GetDuration() < ForwardTransitionDuration)
        {
            FVector ForwardVector = CharacterCapsuleComponent()->GetForwardVector();
            FVector CurrentLocation = CharacterCapsuleComponent()->GetComponentLocation();
            FVector ForwardPosition = CurrentLocation + (ForwardVector * 250.0f);

            CharacterOwner->LaunchCharacter(ForwardPosition - CurrentLocation, true, true);
        }
    }
    else
    {
		float PerformWallHeightTrace    = Mantle->GetWallHeight();
		float MaxHeight     = Mantle->GetMaximumHeight();

        float VelocityZ      = 0;
        float DurationPhase1 = 0;
		float DurationPhase2 = 0;

        UE_LOG(LogTemp, Error, TEXT("PerformWallHeightTrace: %f"), PerformWallHeightTrace);

        if (PerformWallHeightTrace < MaxHeight / 4)
        {
            UE_LOG(LogTemp, Error, TEXT("1"));
            UE_LOG(LogTemp, Error, TEXT("GroundDistance: %f"), GroundDistance());
            VelocityZ = 400.0f;
            DurationPhase1 = 0.15f;
            DurationPhase2 = 0.30f;

            if (GroundDistance() > 100.0f)
            {
                VelocityZ += 200.0f;
                DurationPhase1 += 0.10f;
                DurationPhase2 += 0.15f;
            }
        }
        else if (PerformWallHeightTrace < MaxHeight / 3)
        {
            UE_LOG(LogTemp, Error, TEXT("2"));
			VelocityZ = 500.f;
			DurationPhase1 = 0.20f;
			DurationPhase2 = 0.35f;
        }
		else if (PerformWallHeightTrace < MaxHeight / 2)
		{
            UE_LOG(LogTemp, Error, TEXT("3"));
			VelocityZ = 800.f;
			DurationPhase1 = 0.25f;
			DurationPhase2 = 0.35f;
		}
		else if (PerformWallHeightTrace <= MaxHeight )
		{
            UE_LOG(LogTemp, Error, TEXT("4"));
			VelocityZ = 1000.f;
			DurationPhase1 = 0.30f;
			DurationPhase2 = 0.45f;
		}

        // Check if the mantle duration is less than 0.5 seconds
        if (Mantle->GetDuration() < DurationPhase1)
        {
            FVector JumpVelocity = FVector(0.0f, 0.0f, VelocityZ);
            CharacterOwner->LaunchCharacter(JumpVelocity, true, true);
        }
        else if (Mantle->GetDuration() <= DurationPhase2)
        {
            FVector ForwardVector = CharacterCapsuleComponent()->GetForwardVector();
            FVector CurrentLocation = CharacterCapsuleComponent()->GetComponentLocation();
            FVector ForwardPosition = CurrentLocation + (ForwardVector * 250.0f);

            CharacterOwner->LaunchCharacter(ForwardPosition - CurrentLocation, true, true);
        }
    }

    if (Mantle->GetDuration() > 0.30f)
    {
        ExitMantle();
        SetBasicMovement(EBasicMovementState::Fall);
        UE_LOG(LogTemp, Error, TEXT("MANTLE TO FALL"));
        return;
    }
}

#pragma endregion

#pragma region Update

void UAdvanceMovementComponent::UpdateMantleStamina()
{
    CharacterData->CharacterAttribute.CharacterStat.ApplyStaminaCost
    (
        Mantle->GetStaminaCost()
    );
}

void UAdvanceMovementComponent::UpdateMantleDuration()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float Duration      = Mantle->GetDuration();
    float NewDuration   = Duration + DeltaSecond;

    Mantle->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateMantleTotalTime()
{
    float DeltaSecond   = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Mantle->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaSecond;

    Mantle->SetTotalTime(NewTotalTime);
}

void UAdvanceMovementComponent::UpdateMantleTravelDistance()
{
    FVector A = Mantle->GetStartLocation();
    FVector B = Mantle->GetEndLocation();

    float Distance = FVector::Dist(A, B);
    float TravelDistance = Mantle->GetTravelDistance();
    float NewTravelDistance = TravelDistance + Distance;

    Mantle->SetTravelDistance(NewTravelDistance);
}

#pragma endregion

#pragma region Utility

bool UAdvanceMovementComponent::MantleDetection()
{


    bool bDebug = false;

    TObjectPtr<UWorld> World = GetWorld(); 
    if (World == nullptr)
    {
        LOG_ERROR("MantleDetection: World is null!");
        return false;
    }


    float CapsuleRadius       = CharacterCapsuleComponent()->GetScaledCapsuleRadius();
    float CapsuleHalfHeight   = CharacterCapsuleComponent()->GetScaledCapsuleHalfHeight();

    FVector StartLocation           = CharacterCapsuleComponent()->GetComponentLocation();
    FVector ForwardVector           = CharacterCapsuleComponent()->GetForwardVector();
    FVector UpVector                = CharacterCapsuleComponent()->GetUpVector();

    float TraceDistance             = Mantle->GetTraceDistance();

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);

    if (IsCurrentMovementState(VerticalWallRunState))
    {
        // Step 1:
        FHitResult ForwardHit;

        FVector ForwardCapsuleStart = StartLocation;
        FVector ForwardCapsuleEnd   = ForwardCapsuleStart + (ForwardVector * TraceDistance);

        bool bCapsuleForwardHit = World->SweepSingleByChannel
        (
            ForwardHit,
            ForwardCapsuleStart,
            ForwardCapsuleEnd,
            FQuat::Identity,
            ECC_Visibility,
            FCollisionShape::MakeCapsule(CapsuleRadius * 0.9f, CapsuleHalfHeight * 0.9f),
            QueryParams
        );

        // Step 2: Line Trace from Capsule Center
        FHitResult CenterLineHit;
        const FVector CapsuleCenter = StartLocation;
        const FVector CenterLineEnd = CapsuleCenter + (ForwardVector * TraceDistance);

        bool bCenterHit = World->LineTraceSingleByChannel
        (
            CenterLineHit,
            CapsuleCenter,
            CenterLineEnd,
            ECC_Visibility,
            QueryParams
        );

        // Step 3: Line Trace from Head
        FHitResult HeadLineHit;
        const FVector HeadLocation  = StartLocation + FVector(0.0f, 0.0f, CapsuleHalfHeight);
        const FVector HeadLineEnd   = HeadLocation + (ForwardVector * TraceDistance);

        bool bHeadHit = World->LineTraceSingleByChannel
        (
            HeadLineHit,
            HeadLocation,
            HeadLineEnd,
            ECC_Visibility,
            QueryParams
        );

        if (bDebug)
        {
            DrawDebugCapsule(World, ForwardCapsuleStart, CapsuleHalfHeight * 0.8f, CapsuleRadius * 0.8f, FQuat::Identity, FColor::Green, false, 1.0f);
            DrawDebugLine(World, CapsuleCenter, CenterLineEnd, FColor::Red, false, 1.0f);
            DrawDebugLine(World, HeadLocation, HeadLineEnd, FColor::Blue, false, 1.0f);
        }

        bool ValidTraceHit = Mantle->GetValidTraceHit();

        if (ValidTraceHit && !bHeadHit)
        {
            if (bDebug)
            {
                UE_LOG(LogTemp, Error, TEXT("VerticalWallRun -> Mantle Detection Done!"));
            }

            // Reset TraceHit for next.
            Mantle->SetValidTraceHit(false);
            return true;
        }

        if (bCenterHit && bHeadHit)
        {
            Mantle->SetValidTraceHit(true);
        }
        else
        {
            Mantle->SetValidTraceHit(false);
        }
    }
    else if (IsCurrentMovementState(JumpState))
    {
        TraceDistance += 15.0f;
        FVector JumpForwardStart    = StartLocation;
        FVector JumpForwardEnd      = JumpForwardStart + (ForwardVector * TraceDistance);

        FHitResult JumpForwardHitResult;

        bool bJumpCapsuleForwardHit = World->LineTraceSingleByChannel
        (
            JumpForwardHitResult,
            JumpForwardStart,
            JumpForwardEnd,
            ECC_Visibility,
            QueryParams
        );

        if (bDebug)
        {
            DrawDebugLine
            (
                World,
                JumpForwardStart,
                JumpForwardEnd,
                bJumpCapsuleForwardHit ? FColor::Red : FColor::Green,
                true
            );
        }

        if (bJumpCapsuleForwardHit)
        {
            FVector JumpHeadForwardStart    = StartLocation + (UpVector * CapsuleHalfHeight);
            FVector JumpHeadForwardEnd      = JumpHeadForwardStart + (ForwardVector * TraceDistance * 1.5f);

            FHitResult JumpHeadHitResult;
            bool bJumpHeadHit = World->LineTraceSingleByChannel
            (
                JumpHeadHitResult,
                JumpHeadForwardStart,
                JumpHeadForwardEnd,
                ECC_Visibility,
                QueryParams
            );

            if (!bJumpHeadHit)
            {
                return true;
            }
        }
    }
    else if (IsCurrentMovementState(WallRunState))
    {
        TraceDistance += 15.0f;

        FVector WallRunCapsuleStart = StartLocation;
        FVector WallRunCapsuleEnd = StartLocation + (ForwardVector * TraceDistance);


        FHitResult WallRunMantleHitResult;
        bool bWallRunMantleHit = GetWorld()->SweepSingleByChannel
        (
            WallRunMantleHitResult,
            WallRunCapsuleStart,
            WallRunCapsuleEnd,
            FQuat::Identity,
            ECC_Visibility,
            FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight),
            QueryParams
        );

        if (bWallRunMantleHit)
        {
            FVector WallRunTopStart = StartLocation + (UpVector * CapsuleHalfHeight + 10.0f);
            FVector WallRunTopEnd = WallRunTopStart + (ForwardVector * TraceDistance);

            FHitResult WallRunLineTraceHitResult;
            bool bWallRunLineTraceHit = GetWorld()->LineTraceSingleByChannel
            (
                WallRunLineTraceHitResult,
                WallRunTopStart,
                WallRunTopEnd,
                ECC_Visibility,
                QueryParams
            );

            if (bWallRunLineTraceHit)
            {
                return false; 
            }

            return true;
        }
    }

    CapsuleHalfHeight   = CharacterCapsuleComponent()->GetScaledCapsuleHalfHeight() * 0.9f;
    CapsuleRadius       = CharacterCapsuleComponent()->GetScaledCapsuleRadius() * 0.5f;

    float ForwardDistance     = 15.0f;
    float MaxMantleHeight     = Mantle->GetMaximumHeight();

    ForwardStart            = CapsuleLocation + (ForwardVector * CapsuleRadius);
    ForwardEnd              = ForwardStart + (ForwardVector * ForwardDistance);

    FHitResult WallHit;
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(CharacterOwner);

    if (bDebug)
    {
        DrawDebugCapsule
        (
            GetWorld(),
            ForwardEnd,
            CapsuleHalfHeight,
            CapsuleRadius,
            FQuat::Identity,
            FColor::Cyan,
            false, 1.0f
        );

        DrawDebugLine
        (
            GetWorld(),
            ForwardStart, 
            ForwardEnd,
            FColor::Red,
            false, 
            1.0f,
            0,
            1.5f
        );
    }

    // Step 1: Forward check for wall
    if (GetWorld()->SweepSingleByChannel(WallHit, ForwardStart, ForwardEnd, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeCapsule(CapsuleRadius, CapsuleHalfHeight), QueryParams))
    {
        FVector WallImpact = WallHit.ImpactPoint;
        FVector WallNormal = WallHit.ImpactNormal;

        if (bDebug)
        {
            DrawDebugPoint(GetWorld(), WallImpact, 12.0f, FColor::Red, false, 2.0f);
            DrawDebugDirectionalArrow(GetWorld(), WallImpact, WallImpact + WallNormal * 50.0f, 10.0f, FColor::Red, false, 2.0f);
        }

        // Step 2: Find floor at base of wall
        FVector FloorStart = WallImpact - ForwardVector * 10.0f + UpVector * 10.0f;
        FVector FloorEnd = FloorStart - UpVector * 300.0f;

        FHitResult FloorHit;
        if (!GetWorld()->LineTraceSingleByChannel(FloorHit, FloorStart, FloorEnd, ECC_Visibility, QueryParams))
        {
            if (bDebug)
            {
                DrawDebugLine(GetWorld(), FloorStart, FloorEnd, FColor::Yellow, false, 2.0f);
            }
            return false;
        }

        float FloorZ = FloorHit.ImpactPoint.Z;

        if (bDebug)
        {
            DrawDebugPoint(GetWorld(), FloorHit.ImpactPoint, 12.0f, FColor::Green, false, 2.0f);
            DrawDebugLine(GetWorld(), FloorStart, FloorEnd, FColor::Green, false, 2.0f);
        }

        // Step 3: From slightly above floor, trace upward to find ledge
        FVector VerticalTraceStart = FloorHit.ImpactPoint + ForwardVector * 10.0f + FVector(0.0f, 0.0f, 5.0f);
        FVector VerticalTraceEnd = VerticalTraceStart + FVector(0.0f, 0.0f, MaxMantleHeight);

        FHitResult VerticalHit;
        float LedgeTopZ = VerticalTraceEnd.Z;

        // Loop upward in small steps until trace no longer hits
        const float StepSize = 2.0f;
        FVector StepTraceStart = VerticalTraceStart;

        while (StepTraceStart.Z < VerticalTraceEnd.Z)
        {
            FVector StepTraceEnd = StepTraceStart + ForwardVector * 10.0f;
            FHitResult StepHit;
            bool bHit = GetWorld()->LineTraceSingleByChannel(StepHit, StepTraceStart, StepTraceEnd, ECC_Visibility, QueryParams);

            if (bDebug)
            {
                DrawDebugLine(GetWorld(), StepTraceStart, StepTraceEnd, bHit ? FColor::Blue : FColor::White, false, 1.0f);
            }

            if (!bHit)
            {
                LedgeTopZ = StepTraceStart.Z;
                break;
            }

            StepTraceStart.Z += StepSize;
        }

        float TotalVerticalHeight = LedgeTopZ - FloorZ;

        Mantle->SetWallHeight(TotalVerticalHeight);

        if (bDebug)
        {
            FVector LedgeTopPoint = FVector(VerticalTraceStart.X, VerticalTraceStart.Y, LedgeTopZ);
            DrawDebugLine(GetWorld(), VerticalTraceStart, LedgeTopPoint, FColor::Purple, false, 2.0f);
            DrawDebugPoint(GetWorld(), LedgeTopPoint, 10.0f, FColor::Magenta, false, 2.0f);
        }

        return true;
    }

    return false;
}

#pragma endregion

#pragma endregion


#pragma region Glide

void UAdvanceMovementComponent::EnterGlide()
{
    SetMovementState(GlideState);
    Glide->SetState(EGlideState::ReadyToAttempt);

    if (Glide->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Glide->SetStartLocation(CharacterOwner->GetActorLocation());
        }
    }

    Velocity = FVector::ZeroVector;

    UE_LOG(LogTemp, Error, TEXT("Enter Glide"));
}

void UAdvanceMovementComponent::TickGlideMovement()
{
    if (Glide->TickDisabled())
    {
        return;
    }

    if (Glide->IsInProgress())
    {
        if (IsPlayer())
        {
            UpdateGlideDuration();
            UpdateGlideTotalTime();
        }

        PerformGlideMovement();
    }
}

void UAdvanceMovementComponent::ExitGlide()
{
    if (Glide->IsInProgress())
    {
        Glide->SetEndLocation(CharacterOwner->GetActorLocation());
        UpdateGlideTravelDistance();
    }
}


#pragma region Perform 

void UAdvanceMovementComponent::PerformGlideMovement()
{
    if (!IsValid(CharacterOwner) || !UpdatedComponent)
    {
        return;
    }

    // Get controller pitch and yaw (assuming glide direction is based on camera look direction)
    FRotator ControlRotation = CharacterOwner->GetControlRotation();
    float LookPitch = ControlRotation.Pitch;
    float LookYaw = ControlRotation.Yaw;

    // Clamp pitch to a reasonable range to prevent unnatural behavior
    LookPitch = FMath::ClampAngle(LookPitch, -89.9f, 89.9f);

    // Calculate glide forward direction from yaw only (horizontal movement)
    FVector GlideDirection = FRotationMatrix(FRotator(0.0f, LookYaw, 0.0f)).GetUnitAxis(EAxis::X);

    // Base glide speed
    float GlideSpeed = 1000.0f;

    // Apply pitch-based speed adjustment
    float PitchMultiplier = (LookPitch > 0.0f)
        ? FMath::Clamp(1.0f + LookPitch / 90.0f, 1.0f, 2.0f) // diving
        : 1.0f; // level or climbing

    float FinalSpeed = GlideSpeed * PitchMultiplier;

    // Combine forward movement and gravity
    FVector MovementDelta = GlideDirection * FinalSpeed * GetWorld()->GetDeltaSeconds();
    MovementDelta.Z += GetGravityZ() * 0.2f * GetWorld()->GetDeltaSeconds(); // gentle descent

    // Update velocity (optional if you're using AddImpulse elsewhere)
    Velocity = MovementDelta / GetWorld()->GetDeltaSeconds();

    // Apply movement
    FHitResult Hit;
    SafeMoveUpdatedComponent(MovementDelta, CharacterOwner->GetActorRotation(), true, Hit);

    // If we hit something, slide along surface
    if (Hit.IsValidBlockingHit())
    {
        SlideAlongSurface(MovementDelta, 1.0f - Hit.Time, Hit.Normal, Hit, true);
    }
}

#pragma endregion

#pragma region Update

void UAdvanceMovementComponent::UpdateGlideDuration()
{
    float DeltaTime   = GetWorld()->GetDeltaSeconds();
    float Duration = Glide->GetDuration();
    float NewDuration   = Duration + DeltaTime;
    Glide->SetDuration(NewDuration);
}

void UAdvanceMovementComponent::UpdateGlideTotalTime()
{
    float DeltaTime     = GetWorld()->GetDeltaSeconds();
    float TotalTime     = Glide->GetTotalTime();
    float NewTotalTime  = TotalTime + DeltaTime;

    Glide->SetTotalTime(NewTotalTime);
}

void UAdvanceMovementComponent::UpdateGlideTravelDistance()
{
    FVector A = Glide->GetStartLocation();
    FVector B = Glide->GetEndLocation();

    float Distance = FVector::Dist(A, B);
    float CurrentDistance = Glide->GetTravelDistance();

    Glide->SetTravelDistance(CurrentDistance + Distance);
}

#pragma endregion

#pragma endregion

#pragma region Swim

void UAdvanceMovementComponent::EnterSwim()
{
    SetMovementState(EMovementState::Swim);
    Swim->EnablePhysicsUpdate(true);
    Swim->bSwimming = true;

    UE_LOG(LogTemp, Error, TEXT("Enter Swim"));

}

void UAdvanceMovementComponent::TickSwimMovement()
{
    // Implementation for handling physics updates in Swim state
}

void UAdvanceMovementComponent::ExitSwim()
{
    Swim->EnablePhysicsUpdate(false);
    Swim->bSwimming = false;
}


#pragma endregion

#pragma region Dive

void UAdvanceMovementComponent::EnterDive()
{
    UE_LOG(LogTemp, Error, TEXT("Enter Dive"));

}

void UAdvanceMovementComponent::TickDiveMovement()
{
    // Implementation for handling physics updates in Dive state
}

void UAdvanceMovementComponent::ExitDive()
{

}

#pragma endregion

#pragma region Hover

void UAdvanceMovementComponent::EnterHover()
{
    SetMovementState(EMovementState::Hover);
    Hover->EnablePhysicsUpdate(true);
    Hover->bHovering = true;

    UE_LOG(LogTemp, Error, TEXT("Enter Hover"));
}

void UAdvanceMovementComponent::TickHoverMovement()
{
    // Implementation for handling physics updates in Hover state
}

void UAdvanceMovementComponent::ExitHover()
{
    Hover->EnablePhysicsUpdate(false);
    Hover->bHovering = false;
}

#pragma endregion

#pragma region Fly

void UAdvanceMovementComponent::EnterFly()
{
}

void UAdvanceMovementComponent::TickFlyMovement()
{

}

void UAdvanceMovementComponent::ExitFly()
{
  
}

#pragma endregion

#pragma region Grappling

void UAdvanceMovementComponent::EnterGrappling()
{
    SetMovementState(GrapplingState);
    Grappling->SetState(EGrapplingState::ReadyToAttempt);

    if (Grappling->IsReadyToAttempt())
    {
        if (IsPlayer())
        {
            Grappling->SetStartLocation(CharacterOwner->GetActorLocation());
        }
    }

    Velocity = FVector::ZeroVector;
    UE_LOG(LogTemp, Error, TEXT("Enter Grappling"));
}

void UAdvanceMovementComponent::TickGrapplingMovement()
{
    if (Grappling->TickDisabled())
    {
        return;
    }

    if (Grappling->IsReadyToAttempt())
    {
        Grappling->SetState(EGrapplingState::InProgress);
    }

    if (Grappling->IsInProgress())
    {

    }
}

void UAdvanceMovementComponent::ExitGrappling()
{

    //// Move towards the player
    //transform.position = Vector3.MoveTowards(transform.position, player.position, speed * Time.deltaTime);

    //// Optional: Rotate to look at the player
    //transform.LookAt(player);
    //// Move towards the player
    //transform.position = Vector3.MoveTowards(transform.position, player.position, speed * Time.deltaTime);

    //// Optional: Rotate to look at the player
    //transform.LookAt(player);

    //// Move towards the player
    //transform.position = Vector3.MoveTowards(transform.position, player.position, speed * Time.deltaTime);

    //// Optional: Rotate to look at the player
    //transform.LookAt(player);

}

#pragma endregion

#pragma endregion


#pragma region Configuration

#pragma region SystemCore

FSystemCore* UAdvanceMovementComponent::GetSystemCore()
{
    if (!SystemCore)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("SystemCore is null. Returning nullptr.");
        #endif
        return nullptr;
    }

    #if DEV_DEBUG_MODE
    LOG_INFO("SystemCore retrieved successfully.");
    #endif

    return SystemCore;
}


void UAdvanceMovementComponent::SetSystemCore(FSystemCore* InSystemCore)
{
    if (!InSystemCore)
    {
        #if DEV_DEBUG_MODE
        LOG_ERROR("Nullptr provided. SystemCore not set.");
        #endif
        return;
    }

    if (SystemCore)
    {
        #if DEV_DEBUG_MODE
        LOG_WARNING("SystemCore is already set. New assignment ignored.");
        #endif       
        return;
    }

    SystemCore = InSystemCore;

    #if DEV_DEBUG_MODE
    LOG_INFO("SystemCore set successfully.");
    #endif    


    SystemCore.
}


#pragma endregion

#pragma endregion
