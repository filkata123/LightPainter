// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Engine/World.h"
#include "PaintingGameMode.h"
#include "EngineUtils.h"
#include "UI/PaintingPicker/PaintingPicker.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

}
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();


	if (RightHandControllerClass != nullptr)
	{
		RightHandController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
		RightHandController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandController->SetOwner(this);
		RightHandController->SetHand(EControllerHand::Right);

	}

	if (LeftHandControllerClass != nullptr)
	{
		LeftHandController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
		LeftHandController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		LeftHandController->SetOwner(this);
		LeftHandController->SetHand(EControllerHand::Left);

	}

	
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);

	PlayerInputComponent->BindAxis(TEXT("PaginateRight_X"),this, &AVRPawn::PaginateRightAxisInput);
}


void AVRPawn::PaginateRightAxisInput(float AxisValue)
{
	int32 PaginationOffset = 0;
	PaginationOffset += AxisValue > PaginationThumbstickThreshold ? 1 : 0;
	PaginationOffset += AxisValue < -PaginationThumbstickThreshold ? -1 : 0;

	if (PaginationOffset != LastPagnationOffSet && PaginationOffset != 0)
	{
		UpdateCurrentPage(PaginationOffset);
	}
	LastPagnationOffSet = PaginationOffset;

}

void AVRPawn::UpdateCurrentPage(int32 Offset)
{
	for (TActorIterator<APaintingPicker> PaintingPickerItr(GetWorld()); PaintingPickerItr; ++PaintingPickerItr)
	{
		PaintingPickerItr->UpdateCurrentPage(Offset);
	}
}

