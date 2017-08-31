// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestRoom.h"
#include "OpenDoor.h"
#include <string>


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
	Owner = GetOwner();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	if(PressurePlate != nullptr)
	{	
		TArray<AActor*> OverlappingActors;
		PressurePlate->GetOverlappingActors(OverlappingActors);
		for(AActor* Actor:OverlappingActors)
		{
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			//UE_LOG(LogTemp, Warning, TEXT("Calculating mass"));
		}
    }
    //UE_LOG(LogTemp, Warning, TEXT("Total mass: %s"), *(FString::SanitizeFloat(TotalMass)));
    return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(PressurePlate != nullptr)
    {
        if(GetTotalMassOfActorsOnPlate() == TriggerMass)
		{
			OnOpen.Broadcast();			
		} else {
			OnClose.Broadcast();
		}
    }
	
	
}

