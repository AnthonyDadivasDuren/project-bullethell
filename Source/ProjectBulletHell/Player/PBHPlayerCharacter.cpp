#include "PBHPlayerCharacter.h"
#include "PBHPlayerState.h"
#include "../Abilities/PBHAbilitySystemComponent.h"
#include "../Abilities/PBHAttributeSet.h"
#include "../Abilities/PBHGameplayAbility.h"
#include "../Abilities/PBHGameplayTags.h"
#include "../ProjectBulletHell.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

APBHPlayerCharacter::APBHPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Placeholder movement defaults - these are the first numbers to tune
	// once the greybox arena is up. Kept in C++ constructor for now; move
	// to a data asset once we're actively iterating on feel so designers
	// (or you, later) aren't recompiling for every tweak.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2048.f;
	bUseControllerRotationYaw = false;
}

void APBHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
			else
			{
				UE_LOG(LogPBH, Warning, TEXT("APBHPlayerCharacter: DefaultMappingContext not set - no input will fire."));
			}
		}
	}
}

UAbilitySystemComponent* APBHPlayerCharacter::GetAbilitySystemComponent() const
{
	return CachedASC;
}

void APBHPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Server-side: PlayerState is valid by this point.
	InitAbilityActorInfo();
}

void APBHPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Client-side equivalent of the above.
	InitAbilityActorInfo();
}

void APBHPlayerCharacter::InitAbilityActorInfo()
{
	APBHPlayerState* PS = GetPlayerState<APBHPlayerState>();
	if (!PS)
	{
		return;
	}

	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	ASC->InitAbilityActorInfo(PS, this);
	CachedASC = Cast<UPBHAbilitySystemComponent>(ASC);

	// Only grant on the authority - GAS replicates granted abilities down.
	if (HasAuthority())
	{
		for (const TSubclassOf<UPBHGameplayAbility>& AbilityClass : StartingAbilities)
		{
			if (AbilityClass)
			{
				ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1, INDEX_NONE, this));
			}
		}
	}
}

void APBHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APBHPlayerCharacter::Input_Move);
		}
		if (LookAction)
		{
			EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &APBHPlayerCharacter::Input_Look);
		}
		if (DashAction)
		{
			EIC->BindAction(DashAction, ETriggerEvent::Started, this, &APBHPlayerCharacter::Input_Dash);
		}
		if (FireAction)
		{
			EIC->BindAction(FireAction, ETriggerEvent::Started, this, &APBHPlayerCharacter::Input_Fire);
			EIC->BindAction(FireAction, ETriggerEvent::Completed, this, &APBHPlayerCharacter::Input_FireReleased);
		}
	}
	else
	{
		UE_LOG(LogPBH, Error, TEXT("APBHPlayerCharacter: Expected an EnhancedInputComponent - check project input settings."));
	}
}

void APBHPlayerCharacter::Input_Move(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();
	if (!Controller)
	{
		return;
	}

	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDir, MoveInput.Y);
	AddMovementInput(RightDir, MoveInput.X);
}

void APBHPlayerCharacter::Input_Look(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void APBHPlayerCharacter::Input_Dash(const FInputActionValue& Value)
{
	if (CachedASC)
	{
		CachedASC->TryActivateAbilitiesByTag(PBHGameplayTags::Ability_Dash);
	}
}

void APBHPlayerCharacter::Input_Fire(const FInputActionValue& Value)
{
	if (CachedASC)
	{
		CachedASC->TryActivateAbilitiesByTag(PBHGameplayTags::Ability_Fire_Primary);
	}
}

void APBHPlayerCharacter::Input_FireReleased(const FInputActionValue& Value)
{
	// Full-auto fire abilities should self-terminate on release by checking
	// State.Firing / listening for input release inside the ability's task,
	// rather than us reaching in and cancelling by tag from here - keeps the
	// stop condition owned by the ability itself. Left as a hook for now.
}
