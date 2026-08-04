#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GrimSpawnLibrary.generated.h"

UCLASS()
class PROJECT_GRIM_API UGrimSpawnLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		Category = "Grim|Spawning",
		meta = (DisplayName = "Choose Weighted Enemy Type")
	)
	static int32 ChooseWeightedEnemyType(
		const TArray<double>& SpawnWeights,
		const TArray<int32>& AliveCounts,
		const TArray<int32>& TypeCaps
	);
};