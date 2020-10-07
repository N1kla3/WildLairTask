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
    ERewardType reward_type;

    UPROPERTY(EditAnywhere)
    int min_reward = 0;

    UPROPERTY(EditAnywhere)
    int max_reward = 0;

    UPROPERTY(EditAnywhere)
    FVector relative_location;
};

UCLASS()
class WILDLAIRS_API UDA_Rubble : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
    UStaticMesh* rubble_mesh;

    UPROPERTY(EditAnywhere)
    int health;

    UPROPERTY(EditAnywhere)
    float recovery_time;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AChest> chest_type;
    
    UPROPERTY(EditAnywhere)
    TArray<FChestProperties> chests;
};
