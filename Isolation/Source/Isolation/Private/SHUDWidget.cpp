// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerManager.h"
#include "Engine/World.h"
#include "SHUDWidget.h"

void USHUDWidget::ReceiveInput(FText MainText, FText DescriptionText)
{
	LocalMainText = MainText;
	LocalDescriptionText = DescriptionText;
	LocalTime = ReadTime(DescriptionText.ToString()) + 2.0f;
	
	if (TooltipVisible)
	{
		PlayAnimation(TooltipSlideOut);
		GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &USHUDWidget::ShowToolTip, 0.35f, false, 0.35f);
	}
	else
	{
		ShowToolTip();
	}
}

void USHUDWidget::ShowToolTip()
{
	TooltipTitle->SetText(this->LocalMainText);
	TooltipDescription->SetText(this->LocalDescriptionText);
	
	PlayAnimation(TooltipSlideIn);

	GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, this, &USHUDWidget::HideTooltip, LocalTime, false, LocalTime);

	TooltipVisible = true;
}

void USHUDWidget::HideTooltip()
{
	PlayAnimation(TooltipSlideOut);
	TooltipVisible = false;
}

float USHUDWidget::ReadTime(FString Text)
{
	return ((Text.Len()/4.7f)*60.0f)/250.0f;
}
