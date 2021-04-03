// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGame.h"

#include "Kismet/GameplayStatics.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	USaveGame* NewGame = UGameplayStatics::CreateSaveGameObject(StaticClass());
	return Cast<UPainterSaveGame>(NewGame);
	 
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("test"), 0);
}