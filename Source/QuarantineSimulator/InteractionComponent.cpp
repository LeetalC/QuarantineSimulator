// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "InteractableComponent.h"
#include "InteractionComponent.h"


#define OUT

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("THE INTERACTION COMPONENT IS WORKING"));
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	InputComponent->BindAction("Interact", IE_Pressed, this, &UInteractionComponent::Interact);
	// ...
	
}

void UInteractionComponent::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("PRESSED"));
}


// Called every frame
void UInteractionComponent::TickComponent(
	float DeltaTime, 
	ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLoc;
	FRotator PlayerViewPointRot;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
	OUT PlayerViewPointLoc, 
	OUT PlayerViewPointRot);

	//UE_LOG(LogTemp, Warning, 
	//	TEXT("The Loc is: %s and the Rot is: %s"), 
	//	*PlayerViewPointLoc.ToString(), *PlayerViewPointRot.ToString());

	FString msg = FString::Printf(TEXT("The Loc is: %s and the Rot is: %s"),
		*PlayerViewPointLoc.ToString(), *PlayerViewPointRot.ToString());
	GEngine->AddOnScreenDebugMessage(1, 4.0f, FColor::Green, *msg);
	//------------------------------------------------------------------------------------------------------------------------------
	FVector LineTraceEnd = PlayerViewPointLoc + PlayerViewPointRot.Vector() * Reach;
	//DrawDebugLine(GetWorld(), PlayerViewPointLoc, LineTraceEnd, FColor::Red, false,0.f,0.f,5.0f );
	FHitResult Hit;

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLoc, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	


	//cases for interaction:
	//1. the interactable is the first one we have seen
	//2. the interactable that was seen last is the same as the interactable we're looking at
	//3. the interactable that was seen last is different from the one we're looking at
	//4. We are looking at nothing
	AActor* ActorThatWasHit = Hit.GetActor();
	if (ActorThatWasHit) 
	{
		//WE FOUND SOMETHING TO INTERACT WITH
		//UActorComponent* comp = ActorThatWasHit->FindComponentByClass(UInteractableComponent::StaticClass()); NOT USING THIS UNTIL I GET RID OF NEED FOR PHYSICS ACTOR

		if (PreviouslyHitActor!= ActorThatWasHit) 
		{
				FString hitMsg = FString::Printf(TEXT("The actor that was hit was %s"), *ActorThatWasHit->GetName());
				GEngine->AddOnScreenDebugMessage(2, 4.0f, FColor::Red, *hitMsg);
				UE_LOG(LogTemp, Error, TEXT("The actor that was hit was %s"), *ActorThatWasHit->GetName());
				PreviouslyHitActor = ActorThatWasHit;
		}
		LookingAtInteractable = true;
	}
	else 
	{
		//WE ARE LOOKING AT NOTHING 
		LookingAtInteractable = false;
		PreviouslyHitActor = nullptr;
		FString hitMsg = FString::Printf(TEXT("No Actor Detected"));
		GEngine->AddOnScreenDebugMessage(2, 4.0f, FColor::Orange, *hitMsg);
	}
	

	// ...
}

