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
	ARubble();
	static ARubble* SpawnRubble(UWorld* World, TSubclassOf<ARubble> RubbleType, const FTransform& LairTransform, UMyDataAsset* LairAsset);

	virtual void Tick(float DeltaTime) override;
	void SetSpawnLairAsset(UMyDataAsset* NewLairAsset);
	void SetRubbleAsset(UDA_Rubble* NewRubbleAsset);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
    void RebuildLair();
	UFUNCTION()
	void OnDestroyAnimation(AActor* DestroyedActor);
	UFUNCTION()
    void OnDestroyStuff(AActor* DestroyedActor);
	UFUNCTION()
    void OnDestroy(AActor* DestroyedActor);
	
	void StartTimerToRebuild();

	UPROPERTY()
	USceneComponent* m_Root;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_Mesh;
	UPROPERTY(EditAnywhere)
	UMyDataAsset* m_LairAsset;
	UPROPERTY(EditAnywhere)
	UDA_Rubble* m_RubbleAsset;

	bool bNoRecovery = true;

};
