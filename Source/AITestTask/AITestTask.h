// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogAiTest, Log, All);

inline void LogToConsoleAndScreen(const UObject* WorldContext, const FString& Message, const FColor Color = FColor::White,
                                  const float Duration = 5.0f)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color,
		                                 FString::Printf(TEXT("%s: %s"), *GetNameSafe(WorldContext), *Message));
	}
	UE_LOG(LogAiTest, Log, TEXT("%s: %s"), *GetNameSafe(WorldContext), *Message);
}
