// Copyright GET IN GAME SAS


#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"



#define OUT
// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw; //TargetYaw = TargetYaw + InitialYaw;

	 IsPressurePlateSet();

	 FindAudioComponent();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors()>MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		
		DoorLastOpened= GetWorld()->GetTimeSeconds();
	}
	else {
		 if (GetWorld()->GetTimeSeconds()-DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);	
		}	
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	
	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSound = false;
	if (!AudioComponent) { return; }
	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}

}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, NewTargetYaw, DeltaTime * DoorCloseSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSound = false;
	if (!AudioComponent){return;} //protecs from crashing the game if no audio component is found
	if (!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}
	

}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 50.f;
	//find all overlapping actors
	TArray<AActor*>OverlappingActors;

	if (!PressurePlate){return TotalMass;} //Remember This line protects the code from returning a nullptr

	PressurePlate->GetOverlappingActors(OverlappingActors);

	//Add up their masses
	for(AActor* Actor:OverlappingActors)
	{
		TotalMass+= Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass(); //TotalMass = 
		
	}


	return TotalMass;
}

void UOpenDoor::FindAudioComponent() 
{
	AudioComponent = GetOwner()->FindComponentByClass <UAudioComponent> ();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio component !"), *GetOwner()->GetName());
	}
}

void UOpenDoor::IsPressurePlateSet() const
{
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the OpenDoor component on it, but no PressurePlate set!"), *GetOwner()->GetName());

	}
}




