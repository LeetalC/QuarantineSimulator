// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QuarantineSimCharacter.generated.h"

UCLASS()
class QUARANTINESIMULATOR_API AQuarantineSimCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuarantineSimCharacter();

	UPROPERTY(EditAnywhere)
		class UCameraComponent* CharacterCamera;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* CameraSpringArm;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	void StartCrouching();
	void EndCrouching();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
