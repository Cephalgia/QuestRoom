// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestRoom.h"
#include "OpenDoor.h"


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
	OpeningActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
    //FRotator Rotator = FRotator(0.0f, 90.0f, 0.0f);
    //Owner-> SetActorRotation(Rotator);
    OnOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
    FRotator Rotator = FRotator(0.0f, 0.0f, 0.0f);
    Owner-> SetActorRotation(Rotator);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(PressurePlate != nullptr)
    {
    	float TotalMass = 0.f;
        TArray<AActor*> OverlappingActors;
        PressurePlate->GetOverlappingActors(OverlappingActors);
        for(AActor* Actor:OverlappingActors)
        {
        	TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        	UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *(Actor->GetName()));
        }
        if(TotalMass >= 21)
		{
			OpenDoor();
			LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		}
		if(GetWorld()->GetTimeSeconds() - LastDoorOpenTime >= DoorCloseDelay)
		{
			CloseDoor();
		}
    }
	
	
}

