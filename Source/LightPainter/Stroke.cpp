// Fill out your copyright notice in the Description page of Project Settings.


#include "Stroke.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
AStroke::AStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

}

void AStroke::Update(FVector CursorLocation)
{
	USplineMeshComponent* Spline = CreateSplineMesh();

	FVector StartPosition = GetActorTransform().InverseTransformPosition(CursorLocation);
	FVector EndPosition = GetActorTransform().InverseTransformPosition(PreviousCursorLocation);

	if (PreviousCursorLocation == FVector(0, 0, 0))
	{
		Spline->SetStartAndEnd(StartPosition, FVector(0, 0, 0), StartPosition, FVector(0, 0, 0));
	}
	else
	{
		Spline->SetStartAndEnd(StartPosition, FVector(0, 0, 0), EndPosition, FVector(0, 0, 0));
	}

	PreviousCursorLocation = CursorLocation;
}


USplineMeshComponent* AStroke::CreateSplineMesh()
{
	USplineMeshComponent* NewSpline = NewObject<USplineMeshComponent>(this);

	NewSpline->SetMobility(EComponentMobility::Movable);
	NewSpline->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	NewSpline->SetStaticMesh(SplineMesh);
	NewSpline->SetMaterial(0, SplineMaterial);
	NewSpline->RegisterComponent();

	return NewSpline;
}

