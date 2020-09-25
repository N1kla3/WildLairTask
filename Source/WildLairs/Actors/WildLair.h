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
	// Sets default values for this actor's properties
	AWildLair();
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BuildingMesh;

	UPROPERTY(EditAnywhere)
	UMyDataAsset* LairAsset;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLairDataAsset(UMyDataAsset* Asset);
};
