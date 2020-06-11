// Fill out your copyright notice in the Description page of Project Settings.


#include "QuarantineSimCharacter.h"
#include "Components/InputComponent.h"
#include "InteractionComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"


// Sets default values
AQuarantineSimCharacter::AQuarantineSimCharacter()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;	//chick from the video said to do this, not sure why

	//removing the spring arm cause i dont think i need it?
	//CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//CameraSpringArm->SetupAttachment(RootComponent);

	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CharacterCamera->AttachTo(RootComponent);	//doing this instead of the below
	CharacterCamera->SetRelativeLocation(FVector(0, 0, 170));
	//CharacterCamera->SetupAttachment(CameraSpringArm);

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

	PlayerInputComponent->BindAxis("Turn", this, &AQuarantineSimCharacter::MyTurn);
	PlayerInputComponent->BindAxis("LookUp", this, &AQuarantineSimCharacter::MyLookUp);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AQuarantineSimCharacter::StartCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AQuarantineSimCharacter::EndCrouching);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);



}

void AQuarantineSimCharacter::MoveForward(float Value)
{
	if (Value)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
	/*FRotator PlayerRotation = GetControlRotation();
	PlayerRotation.Pitch = 0;

	FVector MovementDirection = FRotationMatrix(PlayerRotation).GetScaledAxis(EAxis::X);
	AddMovementInput(MovementDirection, Value);*/
}

void AQuarantineSimCharacter::MoveRight(float Value)
{
	/*FRotator PlayerRotation = GetControlRotation();
	PlayerRotation.Pitch = 0;

	FVector MovementDirection = FRotationMatrix(PlayerRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(MovementDirection, Value);*/
	if (Value)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AQuarantineSimCharacter::MyTurn(float Value)
{
	if (Value)
	{
		AddActorLocalRotation(FRotator(0, Value, 0));
	}
}
void AQuarantineSimCharacter::MyLookUp(float Value)
{
	if (Value)
	{
		float temp = CharacterCamera->GetComponentRotation().Pitch + Value;

		if (temp < 65.0f && temp > -65.0f)
		{
			CharacterCamera->AddLocalRotation(FRotator(Value, 0, 0));
		}
	}
}
//My Crouch functions
void AQuarantineSimCharacter::StartCrouching()
{
	Crouch();
	CharacterCamera->SetRelativeLocation(FVector(0,0,10));

}

void AQuarantineSimCharacter::EndCrouching()
{
	UnCrouch();
	CharacterCamera->SetRelativeLocation(FVector(0, 0, 170));
}

