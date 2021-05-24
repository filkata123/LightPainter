// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGame.generated.h"

USTRUCT()
struct FStrokeState
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<class AStroke> Class;

	UPROPERTY()
	TArray<FVector> ControlPoints;
};

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UPainterSaveGame* Create();
	bool Save();
	void Delete();
	static UPainterSaveGame* Load(FString SlotName);

	void SetState(FString NewState) { State = NewState;}
	FString GetState() const { return State; }

	void SerializeFromWorld(UWorld* World);
	void DeSerializeToWorld(UWorld* World);

	FString GetSlotName() const { return SlotName; }

	static FString GetImagePath(const FString& UniqueIdentifier);

private:
	void ClearWorld(UWorld *World);
	
	//	State
	UPROPERTY()
	FString State;

	UPROPERTY()
	FString SlotName;

	UPROPERTY()
	TArray<FStrokeState> Strokes;

};
