// Copyright GET IN GAME SAS


#include "CubePosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UCubePosition::UCubePosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCubePosition::BeginPlay()
{
	Super::BeginPlay();
	InitialPosition = GetOwner()->GetActorLocation().Y;
	CurrentPOsition = InitialPosition;
	TargetPosition = InitialPosition - 100;

	
}


// Called every frame
void UCubePosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		UE_LOG(LogTemp, Error, TEXT("%s)"), *GetOwner()->GetActorLocation().ToString());
		UE_LOG(LogTemp, Error, TEXT("Position is : %f)"), GetOwner()->GetActorLocation().Y);


		CurrentPOsition = FMath::FInterpTo(CurrentPOsition, TargetPosition, DeltaTime, 0.5);
		FVector CubeYTranslation = GetOwner()->GetActorLocation();
		CubeYTranslation.Y = CurrentPOsition;
		GetOwner()->SetActorLocation(CubeYTranslation);

}

