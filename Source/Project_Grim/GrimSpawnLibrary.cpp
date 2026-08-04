#include "GrimSpawnLibrary.h"

int32 UGrimSpawnLibrary::ChooseWeightedEnemyType(
	const TArray<double>& SpawnWeights,
	const TArray<int32>& AliveCounts,
	const TArray<int32>& TypeCaps)
{
	const int32 EntryCount = FMath::Min(
		SpawnWeights.Num(),
		FMath::Min(AliveCounts.Num(), TypeCaps.Num())
	);

	if (EntryCount <= 0)
	{
		return INDEX_NONE;
	}

	double TotalWeight = 0.0;
	int32 LastEligibleIndex = INDEX_NONE;

	// Calculate the total weight of every enemy that can currently spawn.
	for (int32 Index = 0; Index < EntryCount; ++Index)
	{
		const double Weight = SpawnWeights[Index];
		const bool bCanSpawn =
			Weight > 0.0 &&
			AliveCounts[Index] < TypeCaps[Index];

		if (bCanSpawn)
		{
			TotalWeight += Weight;
			LastEligibleIndex = Index;
		}
	}

	if (TotalWeight <= 0.0)
	{
		return INDEX_NONE;
	}

	const double RandomRoll =
		static_cast<double>(FMath::FRand()) * TotalWeight;

	double RunningWeight = 0.0;

	// Find which enemy's weighted range contains the random roll.
	for (int32 Index = 0; Index < EntryCount; ++Index)
	{
		const double Weight = SpawnWeights[Index];
		const bool bCanSpawn =
			Weight > 0.0 &&
			AliveCounts[Index] < TypeCaps[Index];

		if (!bCanSpawn)
		{
			continue;
		}

		RunningWeight += Weight;

		if (RandomRoll < RunningWeight)
		{
			return Index;
		}
	}

	// Handles extremely unlikely floating-point edge cases.
	return LastEligibleIndex;
}