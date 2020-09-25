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
	UStaticMesh* LairMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Health;

	UPROPERTY(EditAnywhere, Category="RubbleMechanic")
	bool IsIncludeRubble;

	UPROPERTY(EditAnywhere, Category="RubbleMechanic")
	UDA_Rubble* RubbleAsset;
};
