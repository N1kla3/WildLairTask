// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DA_Rubble.h"
#include "Engine/DataAsset.h"

#include "MyDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WILDLAIRS_API UMyDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* lair_mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int health;

	UPROPERTY(EditAnywhere, Category="RubbleMechanic")
	bool is_include_rubble;

	UPROPERTY(EditAnywhere, Category="RubbleMechanic")
	UDA_Rubble* rubble_asset;
};
