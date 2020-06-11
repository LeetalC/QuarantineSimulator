// Fill out your copyright notice in the Description page of Project Settings.

#include "QuarantineSimGameMode.h"
#include "QuarantineSimCharacter.h"



AQuarantineSimGameMode::AQuarantineSimGameMode()
{
	DefaultPawnClass = AQuarantineSimCharacter::StaticClass();

}

