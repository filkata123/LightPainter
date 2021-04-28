// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPicker.h"
#include "PaintingGrid.h"

#include "../../Saving/PainterSaveGame.h"
#include "../../Saving/PainterSaveGameIndex.h"

#include "ActionBar.h"

// Sets default values
APaintingPicker::APaintingPicker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid->SetupAttachment(GetRootComponent());

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();

	UActionBar* ActionBardWidget = Cast<UActionBar>(ActionBar->GetUserWidgetObject());
	if (ActionBardWidget)
	{
		ActionBardWidget->SetParentPicker(this);
	}

	RefreshSlots();

	
}

void APaintingPicker::RefreshSlots()
{
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (!PaintingGridWidget) return;

	PaintingGridWidget->ClearPaintings();

	int32 Index = 0;
	for (FString Name : UPainterSaveGameIndex::Load()->GetSlotNames())
	{
		PaintingGridWidget->AddPainting(Index, Name);
		++Index;
	}

}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Create();

	RefreshSlots();
}

void APaintingPicker::ToggleDeleteMode()
{
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (!PaintingGridWidget) return;

	PaintingGridWidget->ClearPaintings();
}

