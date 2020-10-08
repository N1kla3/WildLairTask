// Fill out your copyright notice in the Description page of Project Settings.


#include "WildLair.h"

#include "Rubble.h"

AWildLair::AWildLair()
{
	PrimaryActorTick.bCanEverTick = true;
	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	m_BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = m_Root;
	m_BuildingMesh->SetupAttachment(RootComponent);

	OnDestroyed.AddDynamic(this, &AWildLair::OnDestroySpawnRubble);
}

void AWildLair::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5);
	if(m_LairAsset)
	{
		m_BuildingMesh->SetStaticMesh(m_LairAsset->lair_mesh);
	}else
		UE_LOG(LogTemp, Warning, TEXT("No asset specified in : %s"), *GetName());
}

void AWildLair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWildLair::SetLairDataAsset(UMyDataAsset* Asset)
{
	m_LairAsset = Asset;
}

void AWildLair::OnDestroySpawnRubble(AActor* DestroyedActor)
{
	if(m_LairAsset && m_LairAsset->is_include_rubble)
	{
		ARubble::SpawnRubble(GetWorld(), ARubble::StaticClass(), GetTransform(), m_LairAsset);
	}else
		UE_LOG(LogTemp, Error, TEXT("No lair asset specified in : %s"), *GetName());
}

