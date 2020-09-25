// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "DrawDebugHelpers.h"
#include "WildLairs/WildLairsCharacter.h"


AChest::AChest()
{
	PrimaryActorTick.bCanEverTick = true;
	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChestMesh"));
	RootComponent = ChestMesh;
	OnActorBeginOverlap.AddDynamic(this, &AChest::OnOverlapBegin);
}

void AChest::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	AWildLairsCharacter* Unit = Cast<AWildLairsCharacter>(OtherActor);
	if(Unit && Unit->IsPawnControlled())
	{
		if(ChestType == ERewardType::Experience)
		{
			InfoWidgetInstance = CreateWidget<URubbleRewardInfo>(GetWorld(), RewardInfoWidget);
			InfoWidgetInstance->SetWorldLocation(GetActorLocation());
			InfoWidgetInstance->AddToViewport();
			InfoWidgetInstance->SetOutputText("Level-up");
			Unit->GetExp(Experience);
			UE_LOG(LogTemp, Warning, TEXT("Experience recieved: %s"), *OtherActor->GetName());
		}else if (ChestType == ERewardType::Gold)
		{
			const auto GoldAmount = FMath::RandRange(MinGold, MaxGold);
			InfoWidgetInstance = CreateWidget<URubbleRewardInfo>(GetWorld(), RewardInfoWidget);
			InfoWidgetInstance->SetWorldLocation(GetActorLocation());
			InfoWidgetInstance->AddToViewport();
			InfoWidgetInstance->SetOutputText(FString::Printf(TEXT("+%d"), GoldAmount));
			Unit->GetGold(GoldAmount);
			UE_LOG(LogTemp, Warning, TEXT("Gold recieved %s"), *OtherActor->GetName());
		}
		Destroy();
	}
}

void AChest::SetRewardValue(const ERewardType RewardType, const int Min, int Max = 0)
{
	if(Max < Min)Max = Min;
	ChestType = RewardType;
	if(RewardType == ERewardType::Experience)
	{
		Experience = Min;
	}else if(RewardType == ERewardType::Gold)
	{
		MinGold = Min;
        MaxGold = Max;
	}
}


// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}


