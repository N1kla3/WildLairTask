// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Actors/Chest.h"

#include "DA_Rubble.generated.h"

/**
 * 
 */
USTRUCT()
struct FChestProperties
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere)
    ERewardType RewardType;

    UPROPERTY(EditAnywhere)
    int MinReward = 0;

    UPROPERTY(EditAnywhere)
    int MaxReward = 0;

    UPROPERTY(EditAnywhere)
    FVector RelativeLocation;
};

UCLASS()
class WILDLAIRS_API UDA_Rubble : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
    UStaticMesh* RubbleMesh;

    UPROPERTY(EditAnywhere)
    int Health;

    UPROPERTY(EditAnywhere)
    float RecoveryTime;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AChest> BP_Chest;
    
    UPROPERTY(EditAnywhere)
    TArray<FChestProperties> Chests;
};
