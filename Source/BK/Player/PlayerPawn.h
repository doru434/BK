// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BK/Objects/Selectable.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"
UENUM(BlueprintType)
enum class SelectionState : uint8
{
	NothingSelected 	= 0 	UMETA(DisplayName="NothingSelected"),
	SingleSelection 	= 1 	UMETA(DisplayName="SingleSelection"),
	MultipleSelection 	= 2 	UMETA(DisplayName="MultipleSelection")
};
UCLASS()
class BK_API APlayerPawn : public APawn, public ISelectable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category =Enum)
	TEnumAsByte<SelectionState> ESelectionState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerPawn)
	class USceneComponent* SceneComponent;
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Player variable")
	float Height;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Player variable")
	FRotator Rotation;

	// Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);


	// Input variables
	FVector CurrentVelocity;
	float CameraSpeed = 5;
};
