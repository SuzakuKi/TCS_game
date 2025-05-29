// Copyright MIET, Inc. All Rights Reserved.

#include "SimpleMovingObject.h"

// Called when the game starts or when spawned
void ASimpleMovingObject::BeginPlay()
{
	Super::BeginPlay();
	// create init states
	if (Points.IsEmpty())
	{
		return;
	}
	nextPoint = Points[GetNextPointIndex()];
	distanceToTarget = FVector::Distance(GetActorLocation(), nextPoint);
	direction = (nextPoint - GetActorLocation()).GetSafeNormal();
}

// Called every frame
void ASimpleMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//MoveToNextPoint(DeltaSeconds);
}


ASimpleMovingObject::ASimpleMovingObject()
{
	PrimaryActorTick.bCanEverTick = true;

}

int ASimpleMovingObject::GetNextPointIndex() const
{
	return (CurrentPointIndex + 1) % Points.Num();
}


/*bool ASimpleMovingObject::HasReachedTargetPoint() const
{
	if (Points.IsEmpty())
	{
		return false;
	}

	FVector currentLocation = GetActorLocation();
	FVector targetLocation = Points[GetNextPointIndex()];

	return  FVector::Dist(currentLocation, targetLocation)>AcceptanceRadius; // Допустимый радиус погрешности;//FVector::DistSquared(currentLocation, targetLocation) <= AcceptanceRadius * AcceptanceRadius;
}*/

void ASimpleMovingObject::MoveToNextPoint(float DeltaSeconds)
{
	if (distanceToTarget <= Speed * DeltaSeconds) // меньше скачка
	{
		SetActorLocation(nextPoint); // Двигаемся точно в точку
		CurrentPointIndex++;
		UE_LOG(LogTemp, Warning, TEXT("point reached"));
		nextPoint = Points[GetNextPointIndex()];
		direction = (nextPoint - GetActorLocation()).GetSafeNormal();
		distanceToTarget = FVector::Distance(GetActorLocation(), nextPoint);
		return;
	}
	// Перемещаем объект ближе к цели
	AddActorWorldOffset(direction* Speed* DeltaSeconds);
	//UE_LOG(LogTemp, Warning, TEXT("Move %n"), distanceToTarget);
	distanceToTarget -= Speed * DeltaSeconds;
	return;
}
const int ASimpleMovingObject::GetDistance()
{
	//UE_LOG(LogTemp, Warning, TEXT("Move %n"), distanceToTarget);
	return distanceToTarget;
}
