// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WildLairs/Widgets/RubbleRewardInfo.h"

#include "Rubble.generated.h"

class AWildLair;
class UMyDataAsset;
class UDA_Rubble;

UCLASS()
class WILDLAIRS_API ARubble : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARubble();
private:
	UPROPERTY()
	USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	UMyDataAsset* LairAsset;
	UPROPERTY(EditAnywhere)
	UDA_Rubble* RubbleAsset;
	
	void StartTimerToRebuild();
	
	UFUNCTION()
    void RebuildLair();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpawnLairAsset(UMyDataAsset* NewLairAsset);
	void SetRubbleAsset(UDA_Rubble* NewRubbleAsset);
};
