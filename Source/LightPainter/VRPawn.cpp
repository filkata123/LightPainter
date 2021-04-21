// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Engine/World.h"




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

	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	if (Painting && Painting->Save())
	{
		CurrentSlotName = Painting->GetSlotName();
	}

	if (PaintBrushHandControllerClass != nullptr)
	{
		RightPaintBrushHandController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
		RightPaintBrushHandController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightPaintBrushHandController->SetOwner(this);

	}

	
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);

	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Released, this, &AVRPawn::Save);
	PlayerInputComponent->BindAction(TEXT("Load"), EInputEvent::IE_Released, this, &AVRPawn::Load);

}

void AVRPawn::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(CurrentSlotName);
	if (Painting)
	{
		Painting->SetState("Hello World");
		Painting->SerializeFromWorld(GetWorld());
		Painting->Save();
	}
}

void AVRPawn::Load()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(CurrentSlotName);
	if (Painting)
	{
		Painting->DeSerializeToWorld(GetWorld());
		UE_LOG(LogTemp, Warning, TEXT("Painting State %s"), *Painting->GetState());

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT FOUND"));
	}
}
