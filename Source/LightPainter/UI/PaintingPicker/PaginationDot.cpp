// Fill out your copyright notice in the Description page of Project Settings.


#include "PaginationDot.h"


void UPaginationDot::SetActive(bool Active)
{
	if (!DotImage) return;

	DotImage->SetOpacity(Active ? 1 : DisabledOpacity);
}
