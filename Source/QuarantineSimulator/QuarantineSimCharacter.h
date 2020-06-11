// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QuarantineSimCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()

class QUARANTINESIMULATOR_API AQuarantineSimCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuarantineSimCharacter();

	UPROPERTY(EditAnywhere, Category = Camera)
		UCameraComponent* CharacterCamera;

	UPROPERTY(EditAnywhere, Category = Camera)
		USpringArmComponent* CameraSpringArm;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UInteractionComponent* Interactor;

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void MyTurn(float Value);

	UFUNCTION()
		void MyLookUp(float Value);


	void StartCrouching();
	void EndCrouching();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
