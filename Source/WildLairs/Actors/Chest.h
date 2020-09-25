// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WildLairs/Widgets/RubbleRewardInfo.h"

#include "Chest.generated.h"

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
	
	UFUNCTION()
    void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor );
	void SetRewardValue(const ERewardType RewardType, const int Min, int Max);
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ChestMesh;
	UPROPERTY(EditAnywhere)
	ERewardType ChestType;
	UPROPERTY(EditAnywhere, Category="Reward")
	int MinGold;
	UPROPERTY(EditAnywhere, Category="Reward")
	int MaxGold;
	UPROPERTY(EditAnywhere, Category="Reward")
	int Experience;
	UPROPERTY(EditAnywhere)
	TSubclassOf<URubbleRewardInfo> RewardInfoWidget;
	UPROPERTY()
	URubbleRewardInfo* InfoWidgetInstance;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
