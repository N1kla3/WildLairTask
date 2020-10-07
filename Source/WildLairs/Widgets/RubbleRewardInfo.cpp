// Fill out your copyright notice in the Description page of Project Settings.


#include "RubbleRewardInfo.h"
#include "Internationalization/Text.h"
#include "Components/PanelWidget.h"
#include "Kismet/GameplayStatics.h"

void URubbleRewardInfo::SetWorldLocation(const FVector& Location)
{
    m_WorldSpawnLocation = Location;
    m_IsSetWorldLocation = true;
    FVector2D widget_screen;
    UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), m_WorldSpawnLocation, widget_screen, false);
    SetPositionInViewport(widget_screen);
}

void URubbleRewardInfo::SetOutputText(const FString& OutText)
{
    if (m_OutputText)
    {
        m_OutputText->SetText(FText::FromString(OutText));
    }
}

void URubbleRewardInfo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (m_IsSetWorldLocation)
    {
        m_WorldSpawnLocation.Z += 50.f * InDeltaTime;
        FVector2D widget_screen;
        UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), m_WorldSpawnLocation, widget_screen, false);
        SetPositionInViewport(widget_screen);
    }
}
