// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RubbleRewardInfo.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class WILDLAIRS_API URubbleRewardInfo : public UUserWidget
{
	GENERATED_BODY()
public:
    void SetWorldLocation(const FVector& Location);
    void SetOutputText(const FString OutText);
protected:
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
private:
    FString InfoText;
    FVector WorldSpawnLocation;
    UPROPERTY(meta = (BindWidget))
    UTextBlock* OutputText;
    bool IsSetWorldLocation = false;
};
