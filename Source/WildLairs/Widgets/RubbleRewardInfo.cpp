// Fill out your copyright notice in the Description page of Project Settings.


#include "RubbleRewardInfo.h"
#include "Internationalization/Text.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"

void URubbleRewardInfo::SetWorldLocation(const FVector& Location)
{
    WorldSpawnLocation = Location;
    IsSetWorldLocation = true;
}

void URubbleRewardInfo::SetOutputText(const FString OutText)
{
    if(OutputText)
    {
        OutputText->SetText(FText::FromString(OutText));
    }
}

void URubbleRewardInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (IsSetWorldLocation)
    {
        WorldSpawnLocation.Z += 50.f * InDeltaTime;
        FVector2D WidgetScreen;
        UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), WorldSpawnLocation, WidgetScreen, false);
        SetPositionInViewport(WidgetScreen);
    }
}
