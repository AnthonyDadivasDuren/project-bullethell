#pragma once

#include "CoreMinimal.h"
#include "ProjectBulletHell/Core/PBHCharacterBase.h"
#include "PBHPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PROJECTBULLETHELL_API APBHPlayerCharacter : public APBHCharacterBase
{
	GENERATED_BODY()

public:
	APBHPlayerCharacter();

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;
	
	// --- Enhanced Input ---
	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputAction> DashAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputAction> JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "PBH|Input")
	TObjectPtr<UInputAction> FireAction;
	
	
	
	void Input_Move(const FInputActionValue& Value);
	void Input_Look(const FInputActionValue& Value);
	void Input_Dash(const FInputActionValue& Value);
	void Input_Jump(const FInputActionValue& Value); // works with built in  will build custom later on
	void Input_Fire(const FInputActionValue& Value);
	void Input_FireReleased(const FInputActionValue& Value);
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PBH|Camera", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PBH|Camera", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

};
