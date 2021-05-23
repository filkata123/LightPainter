// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGridCard.h"
#include "Kismet/GameplayStatics.h"

void UPaintingGridCard::SetPaintingName(FString PaintingName)
{
	PaintingNameGeneral = PaintingName;
	SlotName->SetText(FText::FromString(PaintingName));

	CardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Canvas", true, "SlotName=" + PaintingNameGeneral);
}



