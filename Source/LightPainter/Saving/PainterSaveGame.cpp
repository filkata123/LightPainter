// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGame.h"

#include "Kismet/GameplayStatics.h"
#include "Misc/Guid.h"

#include "EngineUtils.h"
#include "PainterSaveGameIndex.h"
#include "HAL/FileManager.h"

#include "../Stroke.h"


UPainterSaveGame* UPainterSaveGame::Create()
{
	UPainterSaveGame* NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));

	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	if (!NewSaveGame->Save()) return nullptr;


	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	Index->AddSaveGame(NewSaveGame);
	Index->Save();

	return NewSaveGame;
	 
}

bool UPainterSaveGame::Save()
{
	
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame* UPainterSaveGame::Load(FString SlotName)
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{

	Strokes.Empty();
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		Strokes.Add(StrokeItr->SerializeToStruct());
	}

}


void UPainterSaveGame::DeSerializeToWorld(UWorld* World)
{
	ClearWorld(World);
	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::SpawnAndDeserializeFromStruct(World, StrokeState);
	}
}

void UPainterSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{

		StrokeItr->Destroy();
	}
}


void UPainterSaveGame::Delete()
{
	auto List = UPainterSaveGameIndex::Load();
	List->RemovePainting(SlotName);
	List->Save();

	UGameplayStatics::DeleteGameInSlot(SlotName, 0);

	IFileManager::Get().Delete(*GetImagePath(SlotName));
}

FString UPainterSaveGame::GetImagePath(const FString& UniqueIdentifier)
{
	FString ThumbnailDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Thumbs"));
	FString FileName = UniqueIdentifier + ".png";

	return FPaths::Combine(ThumbnailDir, FileName);
}