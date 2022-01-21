// Fill out your copyright notice in the Description page of Project Settings.


#include "Pingaman_Gamemode.h"
#include "GameFramework/Actor.h"

APingaman_Gamemode::APingaman_Gamemode()
{
	PrimaryActorTick.bCanEverTick = true;
}
//We want overide begin play
void APingaman_Gamemode::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle UnusedHandle;

	GetWorldTimerManager().SetTimer(UnusedHandle, this, &APingaman_Gamemode::SpawnPlayerRecharge, FMath::RandRange(1, 3), true);

	
}

void APingaman_Gamemode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

	//Create a random spawn points x and y 
void APingaman_Gamemode::SpawnPlayerRecharge()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);

	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
		//Get World Spawns actor
		GetWorld()->SpawnActor(PlayerRecharge, &SpawnPosition, &SpawnRotation);

}


