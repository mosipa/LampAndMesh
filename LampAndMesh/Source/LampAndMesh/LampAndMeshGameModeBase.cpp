// Fill out your copyright notice in the Description page of Project Settings.

#include "LampAndMeshGameModeBase.h"
#include "MyPawn.h"

ALampAndMeshGameModeBase::ALampAndMeshGameModeBase()
{
	DefaultPawnClass = AMyPawn::StaticClass();
}