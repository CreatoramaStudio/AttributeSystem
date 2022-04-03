#include "LogAttributeSystem.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(LogAttributeSystem);

void FLogAttributeSystem::ConsoleInfo(const FString& Description, const bool bShowOnScreen, const float Time)
{
	UE_LOG(LogAttributeSystem, Display, TEXT("%s"), *Description);

	if (bShowOnScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::White, Description);
	}
}

void FLogAttributeSystem::ConsoleWarning(const FString& Description, const bool bShowOnScreen, const float Time)
{
	UE_LOG(LogAttributeSystem, Warning, TEXT("%s"), *Description);

	if (bShowOnScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Yellow, Description);
	}
}

void FLogAttributeSystem::ConsoleError(const FString& Description, const bool bShowOnScreen, const float Time)
{
	UE_LOG(LogAttributeSystem, Error, TEXT("%s"), *Description);

	if (bShowOnScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Red, Description);
	}
}

void FLogAttributeSystem::VisLogString(const AActor* Actor, const FString& Description, const FColor Color)
{
	UE_VLOG(Actor, LogAttributeSystem, Log, TEXT("%s"), *Description);
}

void FLogAttributeSystem::VisLogLocation(const AActor* Actor, const FVector Location, const float Radius, const FString& Description, const FColor Color)
{
	UE_VLOG_LOCATION(Actor, LogAttributeSystem, Log, Location, Radius, Color, TEXT("%s"), *Description);
}

void FLogAttributeSystem::VisLogSegment(const AActor* Actor, const FVector Start, const FVector End, const float Thickness, const FString& Description, const FColor Color)
{
	UE_VLOG_SEGMENT_THICK(Actor, LogAttributeSystem, Log, Start, End, Color, Thickness, TEXT("%s"), *Description);
}

void FLogAttributeSystem::VisLogArrow(const AActor* Actor, const FVector Start, const FVector End, const FString& Description, const FColor Color)
{
	UE_VLOG_ARROW(Actor, LogAttributeSystem, Log, Start, End, Color, TEXT("%s"), *Description);
}
