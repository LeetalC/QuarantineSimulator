// Fill out your copyright notice in the Description page of Project Settings.


#include "QuarantineSimCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "InteractionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AQuarantineSimCharacter::AQuarantineSimCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	CameraSpringArm->SetupAttachment(RootComponent);
	CharacterCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	CharacterCamera->SetupAttachment(CameraSpringArm);

	Interactor = CreateDefaultSubobject<UInteractionComponent>("Grabber");
	//NOTE: I had to manually enable use pawn controller movement, should put that in code
	//NOTE: Set Cancrouch in bp_character in nav mesh


}

// Called when the game starts or when spawned
void AQuarantineSimCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuarantineSimCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQuarantineSimCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AQuarantineSimCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AQuarantineSimCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AQuarantineSimCharacter::StartCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AQuarantineSimCharacter::EndCrouching);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);



}

void AQuarantineSimCharacter::MoveForward(float Value)
{
	FRotator PlayerRotation = GetControlRotation();
	PlayerRotation.Pitch = 0;

	FVector MovementDirection = FRotationMatrix(PlayerRotation).GetScaledAxis(EAxis::X);
	AddMovementInput(MovementDirection, Value);
}

void AQuarantineSimCharacter::MoveRight(float Value)
{
	FRotator PlayerRotation = GetControlRotation();
	PlayerRotation.Pitch = 0;

	FVector MovementDirection = FRotationMatrix(PlayerRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(MovementDirection, Value);
}

//My Crouch functions
void AQuarantineSimCharacter::StartCrouching()
{
	Crouch();

}

void AQuarantineSimCharacter::EndCrouching()
{
	UnCrouch();
}

