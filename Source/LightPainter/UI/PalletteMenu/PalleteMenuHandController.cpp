// Fill out your copyright notice in the Description page of Project Settings.


#include "PalleteMenuHandController.h"


APalleteMenuHandController::APalleteMenuHandController()
{
	PalleteMenu = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaletteMenu"));
	PalleteMenu->SetupAttachment(GetRootComponent());
}

