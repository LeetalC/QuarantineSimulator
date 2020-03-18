// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "QuarantineSimPawn.generated.h"

UCLASS()
class QUARANTINESIMULATOR_API AQuarantineSimPawn : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	AQuarantineSimPawn();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* PawnMesh;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
		class UFloatingPawnMovement* MovementComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
		void MoveForward(float InInput);

	UFUNCTION()
		void MoveRight(float InInput);

	UFUNCTION()
		void Turn(float InInput);

	UFUNCTION()
		void LookUp(float InInput);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
