// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../HandControllerBase.h"
#include "Components/WidgetComponent.h"

#include "PalleteMenuHandController.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API APalleteMenuHandController : public AHandControllerBase
{
	GENERATED_BODY()

public:
	APalleteMenuHandController();

private:
	// Components
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PalleteMenu;
	
};
