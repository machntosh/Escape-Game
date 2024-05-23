// Copyright GET IN GAME SAS
#include "Grabber.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
	
	PlayerViewPointArrow = GetOwner()->FindComponentByClass<UArrowComponent>();
	if (!PlayerViewPointArrow)
	{
		UE_LOG(LogTemp, Error, TEXT("No player viewpoint arrow component found on %s!"), *GetOwner()->GetName());
		return;
	}

	UCameraComponent* Camera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	if (!Camera)
	{
		UE_LOG(LogTemp, Error, TEXT("No camera component found on %s!"), *GetOwner()->GetName());
		return;
	}

	PlayerViewPointArrow->SetWorldLocation(Camera->GetComponentLocation());
}
	

	
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If the Physiscs Handle is attached
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		//Move the object we are holding
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}

	DrawDebugLine
	(
		GetWorld(),
		GetLineTraceEnd(),
		GetPlayerReach(),
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);
	
}

void UGrabber::Grab()
{
	GetPlayerReach();

	FHitResult HitResult= GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

  //If we hit something then attach the physics handle
	if (ActorHit)
	{
		if (!PhysicsHandle) {return;}
		//Attach the PhysicsHandle
		PhysicsHandle->GrabComponentAtLocation(
		ComponentToGrab,
	    NAME_None,
		GetPlayerReach()); // GetPlayerReach is the refactored equivalent for LineTraceEnd initially defined in test and debug mode
	}

					
			
}

void UGrabber::Release()
{ 
	if (!PhysicsHandle) {return;}
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle()
{

	//Check for Physics Handle Component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle component Found on %s!"), *GetOwner()->GetName());
	}
	
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;

	// Ray-cast to a certain distance ( Reach )
	FCollisionQueryParams TraceParams(FName(TEXT("")),false,GetOwner());

		GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerReach(),
		GetPlayerWorldPosition(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
		);
		return Hit;
	
}

FVector UGrabber::GetPlayerReach() const
{
	
	 FVector PlayerViewPointLocation;
	 FRotator PlayerViewPointRotation;

	 // GetThePlayerViewPOint
	  GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		  OUT PlayerViewPointLocation,
		  OUT PlayerViewPointRotation
	 );

	//Draw a line from player showing the reach
	return  PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	
}

FVector UGrabber::GetPlayerWorldPosition() const
{
	//Get the player character's world locatiom
	ACharacter* PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (PlayerCharacter)
	{
		return PlayerCharacter->GetCapsuleComponent()->GetComponentLocation();
	}

	// GetThePLayerViewPOint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	//Draw a line from player showing the reach
	
    return PlayerViewPointLocation;
}

FVector UGrabber::GetLineTraceEnd() const
{
	// GetThePlayerViewPOint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetActorEyesViewPoint(OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);
	return  PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

}












//TODO Find a way to change the center of DefaultPawn From CameraViewPointLocation to aCustomLocation on DefaultPawn (ideally the RightHand)
//Bind an Input to trigger an AnimBP 
//Build Custom AnimBP ( Animate the RightHand and create a BlendSpace )


//Toolbox
//DrawDebugLine
/*
	GetWorld(),
	PlayerViewPointLocation,
	GetPLayerReach,
	FColor(0,255,0),
	false,
	0.f,
	0,
	5.f
);*/