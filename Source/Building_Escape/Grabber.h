// Copyright GET IN GAME SAS

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	float Reach = 1000.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY ()
	UInputComponent* InputComponent = nullptr;
	
	UPROPERTY()
		UArrowComponent* PlayerViewPointArrow;

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();

	//Return the first actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Return the Line trace end
	FVector GetPlayerReach() const;

	//Get the player position in the world
	FVector GetPlayerWorldPosition() const;
	FVector GetLineTraceEnd() const;

};
