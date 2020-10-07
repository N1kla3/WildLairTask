// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WildLairs/Widgets/RubbleRewardInfo.h"

#include "Chest.generated.h"

struct FChestProperties;

UENUM()
enum class ERewardType
{
	Experience,
	Gold
};

UCLASS()
class WILDLAIRS_API AChest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();
	static AChest* SpawnChest(UWorld* World, const TSubclassOf<AChest> ChestType, FTransform RubbleTransform, FChestProperties ChestConfig);
	UFUNCTION()
    void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor );
	void SetRewardValue(const ERewardType RewardType, const int Min, int Max);

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_ChestMesh;
	UPROPERTY(EditAnywhere)
	ERewardType m_ChestType;
	UPROPERTY(EditAnywhere, Category="Reward")
	int m_MinGold;
	UPROPERTY(EditAnywhere, Category="Reward")
	int m_MaxGold;
	UPROPERTY(EditAnywhere, Category="Reward")
	int m_Experience;
	UPROPERTY(EditAnywhere)
	TSubclassOf<URubbleRewardInfo> m_RewardInfoWidget;
	UPROPERTY()
	URubbleRewardInfo* m_InfoWidgetInstance;


};
