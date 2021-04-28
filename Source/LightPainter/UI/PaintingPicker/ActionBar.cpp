// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBar.h"

bool UActionBar::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!AddButton) return false;
	AddButton->OnClicked.AddDynamic(this, &UActionBar::AddButtonClicked);

	if (!DeleteButton) return false;
	DeleteButton->OnClicked.AddDynamic(this, &UActionBar::DeleteButtonClicked);

	return true;

}

void UActionBar::AddButtonClicked()
{
	if (ParentPicker) ParentPicker->AddPainting();
}

void UActionBar::DeleteButtonClicked()
{
	if (ParentPicker) ParentPicker->ToggleDeleteMode();
}

