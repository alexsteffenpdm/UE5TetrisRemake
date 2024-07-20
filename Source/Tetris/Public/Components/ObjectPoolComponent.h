// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ObjectPoolComponentLog, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TETRIS_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectPoolComponent();

	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		meta = (
			ToolTip = "The class which the pool holds (child class of AActor)."
			)
	)
	TSubclassOf<AActor> ObjectClass;

	UPROPERTY(
		BlueprintReadWrite,
		EditAnywhere,
		meta = (
			ClampMin = "0",
			ToolTip = "Amount of objects to in the pool."
			)
	)
	int InitialPoolSize;

	UFUNCTION()
	void SetInitialPoolSize(int InPoolSize);

	UPROPERTY(VisibleInstanceOnly)
	TArray<AActor*> ObjectPool;

	UFUNCTION(BlueprintInternalUseOnly)
	AActor* SpawnNewActor();

	UFUNCTION()
	bool ObjectClassIsValid();

	UFUNCTION()
	void InitializePool();

	UFUNCTION()
	virtual void PartialSpawn();

	UFUNCTION()
	AActor* GetNextFreeObject();

	UFUNCTION()
	void ExpandObjectPool(float ExpansionPercentage);

private:
	void AddActorToPool();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
