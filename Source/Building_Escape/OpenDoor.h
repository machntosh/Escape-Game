// Copyright GET IN GAME SAS

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void IsPressurePlateSet() const;

	//Tracks whether the sound has been played
	bool OpenDoorSound=false;
	bool CloseDoorSound=true;

private:

	float InitialYaw;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50.f;

	UPROPERTY(EditAnywhere)
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	float OpenAngle=90.f;

	float DoorLastOpened=0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed=0.8f;

	UPROPERTY(EditAnywhere)
		float DoorCloseSpeed=2.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate=nullptr;
	

	UPROPERTY(EditAnywhere)
		float NewTargetYaw = 0.f; // Aurait pu être supprimé et remplacé par InitialYaw ( déja présent dans le code) mais ca fonctionne qd meme avec cette variable :-)

	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;
};
