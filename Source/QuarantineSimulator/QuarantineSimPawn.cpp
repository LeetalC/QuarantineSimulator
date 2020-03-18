// Fill out your copyright notice in the Description page of Project Settings.


#include "QuarantineSimPawn.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AQuarantineSimPawn::AQuarantineSimPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovementComponent");

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>("PawnMesh");

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("PawnSpringArm");
	SpringArm->SetupAttachment(PawnMesh);
	SpringArm->bHiddenInGame = false;
	SpringArm->TargetArmLength = 150.f;


	PawnCamera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	PawnCamera->SetupAttachment(SpringArm);
	PawnCamera->bHiddenInGame = false;

	SetRootComponent(PawnMesh);

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void AQuarantineSimPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuarantineSimPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQuarantineSimPawn::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);


	InputComponent->BindAxis("MoveForward", this, &AQuarantineSimPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AQuarantineSimPawn::MoveRight);

	InputComponent->BindAxis("Turn", this, &AQuarantineSimPawn::AddControllerYawInput);
	InputComponent->BindAxis("Lookup", this, &AQuarantineSimPawn::AddControllerPitchInput);

}

void AQuarantineSimPawn::MoveForward(float InInput)
{
	AddMovementInput(GetActorForwardVector(), InInput);
}

void AQuarantineSimPawn::MoveRight(float InInput)
{

	AddMovementInput(GetActorRightVector(), InInput);
}

void AQuarantineSimPawn::Turn(float InInput)
{
	AddControllerYawInput(InInput);
}

void AQuarantineSimPawn::LookUp(float InInput)
{
	AddControllerPitchInput(InInput);
}



