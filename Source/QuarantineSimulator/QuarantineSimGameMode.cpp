// Fill out your copyright notice in the Description page of Project Settings.


#include "QuarantineSimCharacter.h"
#include "QuarantineSimGameMode.h"


AQuarantineSimGameMode::AQuarantineSimGameMode()
{
	DefaultPawnClass = AQuarantineSimCharacter::StaticClass();

}

