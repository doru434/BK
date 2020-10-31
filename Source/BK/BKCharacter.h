// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BKCharacter.generated.h"

UCLASS(Blueprintable)
class ABKCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABKCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;


private:


};

