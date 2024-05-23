// Copyright GET IN GAME SAS

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CubePosition.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UCubePosition : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCubePosition();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float InitialPosition;
	float CurrentPOsition;
	float TargetPosition;

		
};
