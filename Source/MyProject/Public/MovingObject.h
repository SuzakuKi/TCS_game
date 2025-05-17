// Copyright MIET, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "MovingObject.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UMovingObject : public UActorComponent
{
    GENERATED_BODY()

public:

    UMovingObject();
    //UMovingObject(const TArray<FVector>& Points);
    //UMovingObject(const TArray<FVector>& Points, const int32& CurrentPointIndex, float Speed);

    // ������ �����, �� ������� �������� ���������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Movement")
    TArray<FVector> Points;
    // ������ ������� �����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Movement")
    int CurrentPointIndex = 0;
    // �������� �������� ���������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Object Movement")
    float Speed = 500.0f;
    // ����� ��� ��������� ������� ������� �����
    UFUNCTION(BlueprintPure, Category = "Object Movement")
    int GetTargetPointIndex() const;
    // ����� ��� �������� ���������� ������� �����
    UFUNCTION(BlueprintPure, Category = "Object Movement")
    bool IsReachedTargetPoint() const;

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};