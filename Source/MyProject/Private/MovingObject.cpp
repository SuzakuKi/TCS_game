// Copyright MIET, Inc. All Rights Reserved.
#include "Public/MovingObject.h"

UMovingObject::UMovingObject()
{
}

// �����������
/*UMovingObject::UMovingObject(const TArray<FVector>& Points) : Points(Points) {
    PrimaryComponentTick.bCanEverTick = true;
}
UMovingObject::UMovingObject(const TArray<FVector>& Points, const int32& CurrentPointIndex, float Speed)
    : Points(Points), CurrentPointIndex(CurrentPointIndex), Speed(Speed)
{
    PrimaryComponentTick.bCanEverTick = true;
}*/



// ����� ��� ��������� ������� ������� �����
int32 UMovingObject::GetTargetPointIndex() const
{
    return (CurrentPointIndex + 1) % Points.Num();
}

// ����� ��� �������� ���������� ������� �����
bool UMovingObject::IsReachedTargetPoint() const
{
    if (Points.Num() == 0)
    {
        return false;
    }

    FVector currentLocation = GetOwner()->GetActorLocation();
    FVector targetLocation = Points[GetTargetPointIndex()];

    float distance = FVector::Dist(currentLocation, targetLocation);
    float acceptanceRadius = 1.0f; // ������ �������

    return distance <= acceptanceRadius;
}

// ���������� ��� ���������� ���������� � ������
void UMovingObject::BeginPlay() {
    Super::BeginPlay();

    if (!ensure(Points.Num() > 0)) return;
}

// �������� ���� ���������� �������
void UMovingObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (CurrentPointIndex >= Points.Num()) return;

    const auto TargetPosition = Points[CurrentPointIndex];
    const auto DistanceToTarget = GetOwner()->GetActorLocation().Distance(TargetPosition);

    if (DistanceToTarget <= 1.f) { // ���� �������� ������� �����
        ++CurrentPointIndex;
        return;
    }

    // ������������� �������
    const auto Direction = (TargetPosition - GetOwner()->GetActorLocation()).GetSafeNormal();
    GetOwner()->AddActorWorldOffset(Direction * Speed * DeltaTime);
}

