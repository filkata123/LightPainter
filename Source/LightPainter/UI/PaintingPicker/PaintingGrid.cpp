// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting(int32 PaintingIndex, FString PaintingName)
{
	if (!PaintingGrid) return;
	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
	if (!NewWidget) return;

	NewWidget->SetPaintingName(PaintingName);

	USizeBox* CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(PaintingIndex));
	if (!CardContainer) return;

	CardContainer->AddChild(NewWidget);
}	

void UPaintingGrid::ClearPaintings()
{
	if (!PaintingGrid) return;
	TArray <UWidget*> WidgetList = PaintingGrid->GetAllChildren();

	for (UWidget* Widget : WidgetList)
	{
		(Cast<USizeBox>(Widget))->ClearChildren();
	}


}

void UPaintingGrid::AddPaginationDot(bool Active)
{
	if (!PaginationDots) return;

	auto Dot = CreateWidget<UPaginationDot>(GetWorld(), PaginationDotClass);
	if (!Dot) return;


	UHorizontalBoxSlot* BoxSlot = PaginationDots->AddChildToHorizontalBox(Dot);
	BoxSlot->SetPadding(FMargin(PagginationDotPadding, 0));

	Dot->SetActive(Active);
	
}

void UPaintingGrid::ClearPaginationDots()
{
	if (!PaginationDots) return;
	PaginationDots->ClearChildren();

}

int32 UPaintingGrid::GetNumberOfSlots() const
{
	return PaintingGrid->GetChildrenCount();
}
