// Fill out your copyright notice in the Description page of Project Settings.


#include "Rubble.h"
#include "../DA_Rubble.h"
#include "../MyDataAsset.h"
#include "WildLair.h"
#include "TimerManager.h"

// Sets default values
ARubble::ARubble()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Root;
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARubble::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(2);
	if(RubbleAsset)
	{
		Mesh->SetStaticMesh(RubbleAsset->RubbleMesh);
		StartTimerToRebuild();
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("No Asset Specified in : %s"), *GetName());
	}
}

void ARubble::Destroyed()
{
	for(auto ChestInfo : RubbleAsset->Chests)
	{
		FTransform SpawnTransform = GetTransform();
		SpawnTransform.SetLocation(SpawnTransform.GetLocation() + ChestInfo.RelativeLocation);
		auto Chest = GetWorld()->SpawnActorDeferred<AChest>(RubbleAsset->BP_Chest, SpawnTransform);
		Chest->SetRewardValue(ChestInfo.RewardType, ChestInfo.MinReward, ChestInfo.MaxReward);
		Chest->FinishSpawning(SpawnTransform);
	}
}

// Called every frame
void ARubble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARubble::SetSpawnLairAsset(UMyDataAsset* NewLairAsset)
{
	LairAsset = NewLairAsset;
}

void ARubble::SetRubbleAsset(UDA_Rubble* NewRubbleAsset)
{
	RubbleAsset = NewRubbleAsset;
}

void ARubble::StartTimerToRebuild()
{
	if(RubbleAsset)
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle,this, &ARubble::RebuildLair, RubbleAsset->RecoveryTime, true);
	}
}

void ARubble::RebuildLair()
{
	if(LairAsset)
	{	
		auto NewLair = GetWorld()->SpawnActorDeferred<AWildLair>(AWildLair::StaticClass(), GetTransform());
		NewLair->SetLairDataAsset(LairAsset);
		NewLair->FinishSpawning(GetTransform());
		Destroy();
	}else
		UE_LOG(LogTemp, Error, TEXT("No asset for lair rebuild specified: %s"), *GetName());
}

