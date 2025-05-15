// Copyright MIET, Inc. All Rights Reserved.
#include "PlatformMovementComponent.h"

// Конструктор
UPlatformMovementComponent::UPlatformMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Метод для получения индекса целевой точки
int32 UPlatformMovementComponent::GetTargetPointIndex() const
{
    return (CurrentPointIndex + 1) % Points.Num();
}

// Метод для проверки достижения целевой точки
bool UPlatformMovementComponent::IsReachedTargetPoint() const
{
    if (Points.Num() == 0)
    {
        return false;
    }

    FVector currentLocation = GetOwner()->GetActorLocation();
    FVector targetLocation = Points[GetTargetPointIndex()];

    float distance = FVector::Dist(currentLocation, targetLocation);
    float acceptanceRadius = 1.0f; // Радиус допуска

    return distance <= acceptanceRadius;
}

// Вызывается при добавлении компонента к актеру
void UPathFollowerComponent::BeginPlay() {
    Super::BeginPlay();

    if (!ensure(PathPoints.Num() > 0)) return;
}

// Основной цикл обновления позиции
void UPathFollowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (CurrentIndex >= PathPoints.Num()) return;

    const auto TargetPosition = PathPoints[CurrentIndex];
    const auto DistanceToTarget = GetOwner()->GetActorLocation().Distance(TargetPosition);

    if (DistanceToTarget <= 1.f) { // Если достигли целевой точки
        ++CurrentIndex;
        return;
    }

    // Интерполируем позицию
    const auto Direction = (TargetPosition - GetOwner()->GetActorLocation()).GetSafeNormal();
    GetOwner()->AddActorWorldOffset(Direction * Speed * DeltaTime);
}