// Fill out your copyright notice in the Description page of Project Settings.


#include "WildLair.h"

#include "Rubble.h"

// Sets default values
AWildLair::AWildLair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = Root;
	BuildingMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWildLair::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5);
	if(LairAsset)
	{
		BuildingMesh->SetStaticMesh(LairAsset->LairMesh);
	}else
		UE_LOG(LogTemp, Warning, TEXT("No asset specified in : %s"), *GetName());
}

// Called every frame
void AWildLair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWildLair::SetLairDataAsset(UMyDataAsset* Asset)
{
	LairAsset = Asset;
}

void AWildLair::Destroyed()
{
	if(LairAsset && LairAsset->IsIncludeRubble)
	{
		auto Rubble = GetWorld()->SpawnActorDeferred<ARubble>(ARubble::StaticClass(), GetTransform());
		Rubble->SetRubbleAsset(LairAsset->RubbleAsset);
		Rubble->SetSpawnLairAsset(LairAsset);
		Rubble->FinishSpawning(GetTransform());
	}else
		UE_LOG(LogTemp, Error, TEXT("No lair asset specified in : %s"), *GetName());
}

