// Copyright MIET, Inc. All Rights Reserved.
#include "Public/MovingObject.h"

UMovingObject::UMovingObject()
{
}

// Конструктор
/*UMovingObject::UMovingObject(const TArray<FVector>& Points) : Points(Points) {
    PrimaryComponentTick.bCanEverTick = true;
}
UMovingObject::UMovingObject(const TArray<FVector>& Points, const int32& CurrentPointIndex, float Speed)
    : Points(Points), CurrentPointIndex(CurrentPointIndex), Speed(Speed)
{
    PrimaryComponentTick.bCanEverTick = true;
}*/



// Метод для получения индекса целевой точки
int32 UMovingObject::GetTargetPointIndex() const
{
    return (CurrentPointIndex + 1) % Points.Num();
}

// Метод для проверки достижения целевой точки
bool UMovingObject::IsReachedTargetPoint() const
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
void UMovingObject::BeginPlay() {
    Super::BeginPlay();

    if (!ensure(Points.Num() > 0)) return;
}

// Основной цикл обновления позиции
void UMovingObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (CurrentPointIndex >= Points.Num()) return;

    const auto TargetPosition = Points[CurrentPointIndex];
    const auto DistanceToTarget = GetOwner()->GetActorLocation().Distance(TargetPosition);

    if (DistanceToTarget <= 1.f) { // Если достигли целевой точки
        ++CurrentPointIndex;
        return;
    }

    // Интерполируем позицию
    const auto Direction = (TargetPosition - GetOwner()->GetActorLocation()).GetSafeNormal();
    GetOwner()->AddActorWorldOffset(Direction * Speed * DeltaTime);
}

