// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WildLairs/MyDataAsset.h"

#include "WildLair.generated.h"

UCLASS()
class WILDLAIRS_API AWildLair : public AActor
{
	GENERATED_BODY()
	
public:	
	AWildLair();
	
	virtual void Tick(float DeltaTime) override;
	void SetLairDataAsset(UMyDataAsset* Asset);

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* m_Root;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* m_BuildingMesh;
	UPROPERTY(EditAnywhere)
	UMyDataAsset* m_LairAsset;

};
