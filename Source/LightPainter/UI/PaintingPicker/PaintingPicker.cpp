// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPicker.h"


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

	Refresh();
	
}
void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
	CurrentPage = FMath::Clamp(CurrentPage + Offset, 0, (GetNumberOfPages() - 1));
	Refresh();
}


void APaintingPicker::RefreshSlots()
{
	if (!GetPaintingGrid()) return;

	GetPaintingGrid()->ClearPaintings();

	int32 StartOffset = CurrentPage * GetPaintingGrid()->GetNumberOfSlots();

	auto SlotNames = UPainterSaveGameIndex::Load()->GetSlotNames();

	for (int32 i = 0; i < GetPaintingGrid()->GetNumberOfSlots() && StartOffset + i < SlotNames.Num(); i++)
	{
		GetPaintingGrid()->AddPainting(i, SlotNames[StartOffset + i]);
	}

}

void APaintingPicker::RefreshDots()
{
	if (!GetPaintingGrid()) return;


	GetPaintingGrid()->ClearPaginationDots();
	for (int i = 0; i < GetNumberOfPages(); i++)
	{
		GetPaintingGrid()->AddPaginationDot(i == CurrentPage);
	}

}

void APaintingPicker::AddPainting()
{
	UPainterSaveGame::Create();

	Refresh();
}

void APaintingPicker::ToggleDeleteMode()
{
	if (!GetPaintingGrid()) return;

	//UPainterSaveGame::Delete("391BACF849DFE4F292BC18800AFA4368");
	GetPaintingGrid()->ClearPaintings();
	//Refresh();
}

int32 APaintingPicker::GetNumberOfPages() const
{
	if (!GetPaintingGrid()) return int32();
	int32 TotalNumberOfSlot = UPainterSaveGameIndex::Load()->GetSlotNames().Num();
	int32 SlotsPerPage = GetPaintingGrid()->GetNumberOfSlots();

	

	return FMath::DivideAndRoundUp(TotalNumberOfSlot, SlotsPerPage);
}



