// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/ObjectPoolInterface.h"
#include "PooledActor.generated.h"

UCLASS(config=Game)
class TETRIS_API APooledActor : public AActor, public IObjectPoolInterface
{
	
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APooledActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetInUse(bool bStatus) override;

	virtual void Reset() override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "PooledActor|Properties")
	bool bInUse = false;

	UPROPERTY(VisibleAnywhere, Category = "PooledActor|Properties")
	int AssociatedPhase = -1;
public:

	UFUNCTION()
	FORCEINLINE bool IsInUse() const { return bInUse; }

	UFUNCTION()
	FORCEINLINE int GetAssociatedPhase() const { return AssociatedPhase; }

	UFUNCTION()
	FORCEINLINE void SetAssociatedPhase(int InPhase) { AssociatedPhase = InPhase; }

};
