// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGridCard.h"
#include "../../Saving/PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UPaintingGridCard::SetPaintingName(FString PaintingName)
{
	PaintingNameGeneral = PaintingName;
	SlotName->SetText(FText::FromString(PaintingName));

	CardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{
	if (!DeleteMode)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Canvas", true, "SlotName=" + PaintingNameGeneral);
	}
	else
	{
		CardButton->SetIsEnabled(false);
		auto SmhSlot = UPainterSaveGame::Load(PaintingNameGeneral);
		SmhSlot->Delete();
	}

}

void UPaintingGridCard::ToggleDelete()
{
	DeleteMode = !DeleteMode;
}



