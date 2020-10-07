// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "DrawDebugHelpers.h"
#include "WildLairs/DA_Rubble.h"
#include "WildLairs/WildLairsCharacter.h"


AChest::AChest()
{
	PrimaryActorTick.bCanEverTick = true;
	m_ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestMesh"));
	RootComponent = m_ChestMesh;
	OnActorBeginOverlap.AddDynamic(this, &AChest::OnOverlapBegin);
}

AChest* AChest::SpawnChest(UWorld* World, const TSubclassOf<AChest> ChestType, FTransform RubbleTransform, FChestProperties ChestConfig)
{
	RubbleTransform.SetLocation(RubbleTransform.GetLocation() + ChestConfig.relative_location);
	auto chest = World->SpawnActorDeferred<AChest>(ChestType, RubbleTransform);
	chest->SetRewardValue(ChestConfig.reward_type, ChestConfig.min_reward, ChestConfig.max_reward);
	chest->FinishSpawning(RubbleTransform);
	return chest;
}

void AChest::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	AWildLairsCharacter* unit = Cast<AWildLairsCharacter>(OtherActor);
	if (unit && unit->IsPawnControlled())
	{
		m_InfoWidgetInstance = CreateWidget<URubbleRewardInfo>(GetWorld(), m_RewardInfoWidget);
     	m_InfoWidgetInstance->SetWorldLocation(GetActorLocation());
		if (m_ChestType == ERewardType::Experience)
		{
			m_InfoWidgetInstance->SetOutputText("Level-up");
			unit->GetExp(m_Experience);
			UE_LOG(LogTemp, Warning, TEXT("Experience recieved: %s"), *OtherActor->GetName());
		} else if (m_ChestType == ERewardType::Gold)
		{
			const auto GoldAmount = FMath::RandRange(m_MinGold, m_MaxGold);
			m_InfoWidgetInstance->SetOutputText(FString::Printf(TEXT("+%d"), GoldAmount));
			unit->GetGold(GoldAmount);
			UE_LOG(LogTemp, Warning, TEXT("Gold recieved %s"), *OtherActor->GetName());
		}
		m_InfoWidgetInstance->AddToViewport();
		Destroy();
	}
}

void AChest::SetRewardValue(const ERewardType RewardType, const int Min, int Max = 0)
{
	if (Max < Min)Max = Min;
	m_ChestType = RewardType;
	if (RewardType == ERewardType::Experience)
	{
		m_Experience = Min;
	} else if(RewardType == ERewardType::Gold)
	{
		m_MinGold = Min;
        m_MaxGold = Max;
	}
}

void AChest::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}


