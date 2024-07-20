// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ObjectPoolComponent.h"
#include "Utils/SuppressableLogging.h"
#include "Interfaces/ObjectPoolInterface.h"
#include "Actors/PooledActor.h"


DEFINE_LOG_CATEGORY(ObjectPoolComponentLog);


// Sets default values for this component's properties
UObjectPoolComponent::UObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	
	if (!ObjectClassIsValid())
	{
		SPM_ERROR_PRINTF(ObjectPoolComponentLog, true, "%s: ObjectClass is invalid! Triggering destructor.", *GetFName().ToString());
		this->DestroyComponent();
		return;
	}
	
}


// Called every frame
void UObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UObjectPoolComponent::SetInitialPoolSize(int InPoolSize)
{
	InitialPoolSize = InPoolSize;
	SPM_LOG_PRINTF(ObjectPoolComponentLog, true, "%s: Set InitialPoolSize to %d", *GetFName().ToString(), InitialPoolSize);
}

AActor* UObjectPoolComponent::SpawnNewActor()
{
	UWorld* World = this->GetWorld();
	if (World == nullptr)
		return nullptr;

	FActorSpawnParameters* SpawnParameters = new FActorSpawnParameters;
	SpawnParameters->SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedActor = World->SpawnActor<AActor>(ObjectClass, FVector::ZeroVector, FRotator::ZeroRotator, *SpawnParameters);
	if (IsValid(SpawnedActor))
		return SpawnedActor;

	return nullptr;
}

bool UObjectPoolComponent::ObjectClassIsValid()
{
	if (ObjectClass == nullptr)
	{
		SPM_ERROR_PRINTF(ObjectPoolComponentLog, false, "%s: ObjectClass property is not set!", *GetFName().ToString());
		return false;
	}

	AActor* SpawnedActor = SpawnNewActor();
	if (!IsValid(SpawnedActor)) {
		SPM_ERROR(ObjectPoolComponentLog, false, "Spawned actor is invalid!");
		return false;
	}

	FProperty* Property = SpawnedActor->GetClass()->FindPropertyByName("bInUse");
	FBoolProperty* RequiredProperty = CastField<FBoolProperty>(Property);
	if (!RequiredProperty) {
		SPM_ERROR(ObjectPoolComponentLog, false, "ObjectClass does not provide required property \"bInUse\" of type bool!");
		return false;
	}

	bool RequiredPropertyValue = RequiredProperty->GetPropertyValue(Property->ContainerPtrToValuePtr<void>(SpawnedActor));
	if (RequiredPropertyValue)
	{
		SPM_ERROR(ObjectPoolComponentLog, false, "ObjectClass provides required property  \"bInUse\" with unexpected value TRUE. Please set the default to FALSE.");
		return false;
	}
	// Destroy Dummy Actor as checks are valid.
	SpawnedActor->Destroy();
	return true;
}

void UObjectPoolComponent::InitializePool()
{
	for (int i = 0; i < InitialPoolSize; i++)
		AddActorToPool();
}

void UObjectPoolComponent::PartialSpawn()
{
	SPM_ERROR(ObjectPoolComponentLog, false, "Using not implemented default function! Child objects have to implement this function on their own.");
}

AActor* UObjectPoolComponent::GetNextFreeObject()
{
	for (AActor* ActorObject : ObjectPool)
		if (APooledActor* PooledActor = Cast<APooledActor>(ActorObject))
			if (!PooledActor->IsInUse())
				return ActorObject;

	return nullptr;
	
}

void UObjectPoolComponent::ExpandObjectPool(float ExpansionPercentage)
{
	int ExpansionAmount = int(ObjectPool.Num() * (1 + ExpansionPercentage));
	for (int i = 0; i < ExpansionAmount; i++)
		AddActorToPool();
}

void UObjectPoolComponent::AddActorToPool()
{
	AActor* SpawnedActor = SpawnNewActor();
	if (SpawnedActor == nullptr)
		return;

	ObjectPool.Add(SpawnedActor);
	SPM_LOG(ObjectPoolComponentLog, true, "Sucessfully added element to object pool.");
}
