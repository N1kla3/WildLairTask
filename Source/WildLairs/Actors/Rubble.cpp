// Fill out your copyright notice in the Description page of Project Settings.


#include "Rubble.h"
#include "../DA_Rubble.h"
#include "../MyDataAsset.h"
#include "WildLair.h"
#include "TimerManager.h"

ARubble::ARubble()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = m_Root;
	m_Mesh->SetupAttachment(RootComponent);
	
	OnDestroyed.AddDynamic(this, &ARubble::OnDestroy);
	OnDestroyed.AddDynamic(this, &ARubble::OnDestroyAnimation);
	OnDestroyed.AddDynamic(this, &ARubble::OnDestroyStuff);
}

ARubble* ARubble::SpawnRubble(UWorld* World, TSubclassOf<ARubble> RubbleType, const FTransform& LairTransform,
                              UMyDataAsset* LairAsset)
{
	auto rubble = World->SpawnActorDeferred<ARubble>(RubbleType, LairTransform);
	rubble->SetRubbleAsset(LairAsset->rubble_asset);
	rubble->SetSpawnLairAsset(LairAsset);
	rubble->FinishSpawning(LairTransform);
	return rubble;
}

// Called when the game starts or when spawned
void ARubble::BeginPlay()
{
	Super::BeginPlay();
	//FOR DEBUG
	SetLifeSpan(2);
	if (m_RubbleAsset)
	{
		m_Mesh->SetStaticMesh(m_RubbleAsset->rubble_mesh);
		StartTimerToRebuild();
	} else
	{
		UE_LOG(LogTemp, Error, TEXT("No Asset Specified in : %s"), *GetName());
	}
}

// Called every frame
void ARubble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARubble::SetSpawnLairAsset(UMyDataAsset* NewLairAsset)
{
	m_LairAsset = NewLairAsset;
}

void ARubble::SetRubbleAsset(UDA_Rubble* NewRubbleAsset)
{
	m_RubbleAsset = NewRubbleAsset;
}

void ARubble::StartTimerToRebuild()
{
	if (m_RubbleAsset)
	{
		FTimerHandle timer_handle;
		GetWorldTimerManager().SetTimer(timer_handle,this, &ARubble::RebuildLair, m_RubbleAsset->recovery_time, true);
	}
}

void ARubble::RebuildLair()
{
	if (m_LairAsset)
	{	
		auto new_lair = GetWorld()->SpawnActorDeferred<AWildLair>(AWildLair::StaticClass(), GetTransform());
		new_lair->SetLairDataAsset(m_LairAsset);
		new_lair->FinishSpawning(GetTransform());
		bNoRecovery = false;
		Destroy();
	} else
		UE_LOG(LogTemp, Error, TEXT("No asset for lair rebuild specified: %s"), *GetName());
}

void ARubble::OnDestroyAnimation(AActor* DestroyedActor)
{
	//TODO: animation on destroy
}

void ARubble::OnDestroyStuff(AActor* DestroyedActor)
{
	//TODO: some stuff on destoy
}

void ARubble::OnDestroy(AActor* DestroyedActor)
{
	if (bNoRecovery)
	{
		for (auto ChestInfo : m_RubbleAsset->chests)
		{
			AChest::SpawnChest(GetWorld(), m_RubbleAsset->chest_type, GetTransform(), ChestInfo);
		}
	}
}

