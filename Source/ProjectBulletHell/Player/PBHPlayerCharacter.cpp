#include "PBHPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PBHPlayerState.h"
#include "../Abilities/PBHAbilitySystemComponent.h"
#include "../Abilities/PBHGameplayAbility.h"
#include "../Abilities/PBHAttributeSet.h"


APBHPlayerCharacter::APBHPlayerCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 30.0f, 30.0f);
	CameraBoom->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

void APBHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!DefaultMappingContext) { return; }
	
	APlayerController* PC = Cast<APlayerController>(GetController()); 
	
	if (!PC) { return; }
	
	ULocalPlayer* LocalPlayer = PC->GetLocalPlayer();
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	
	if (!Subsystem) { return; }
	
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	
}

void APBHPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EIC) { return; }

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
	
	if (JumpAction)
	{
		EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}

	if (FireAction)
	{
		EIC->BindAction(FireAction, ETriggerEvent::Started, this, &APBHPlayerCharacter::Input_Fire);
		EIC->BindAction(FireAction, ETriggerEvent::Completed, this, &APBHPlayerCharacter::Input_FireReleased);
	}
}


UAbilitySystemComponent* APBHPlayerCharacter::GetAbilitySystemComponent() const
{
	return CachedASC;
}

void APBHPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void APBHPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
}

void APBHPlayerCharacter::InitAbilityActorInfo()
{
	APBHPlayerState* PS = GetPlayerState<APBHPlayerState>();
	if (!PS) { return; }
	
	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	if (!ASC) { return; }
	
	ASC->InitAbilityActorInfo(PS, this);
	CachedASC = Cast<UPBHAbilitySystemComponent>(ASC);
	
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
	
	GetWorldTimerManager().SetTimer(DashRegenTimerHandle, this, &APBHPlayerCharacter::RegenDashCharge, DashRegenInterval, true);
}

void APBHPlayerCharacter::Input_Move(const FInputActionValue& Value)
{
	if (!Controller) { return; }

	const FVector2D MoveInput = Value.Get<FVector2D>();

	const FRotator YawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MoveInput.Y);
	AddMovementInput(RightDirection, MoveInput.X);
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
		CachedASC->ActivateAbilityByTag(FGameplayTag::RequestGameplayTag(FName("Ability.Dash")));
		UE_LOG(LogTemp, Warning, TEXT("Dash Activated"));
	}

}

void APBHPlayerCharacter::Input_Jump(const FInputActionValue& Value)
{
	// works with built-in  will build custom later on
}

void APBHPlayerCharacter::Input_Fire(const FInputActionValue& Value)
{
}

void APBHPlayerCharacter::Input_FireReleased(const FInputActionValue& Value)
{
}

void APBHPlayerCharacter::RegenDashCharge()
{
	if (!CachedASC) { return; }

	UPBHAttributeSet* AttributeSet = const_cast<UPBHAttributeSet*>(CachedASC->GetSet<UPBHAttributeSet>());
	if (!AttributeSet) { return; }

	AttributeSet->SetDashCharges(FMath::Min(AttributeSet->GetDashCharges() + 1.0f, AttributeSet->GetMaxDashCharges()));
}

void APBHPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
