// Copyright MIET, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "PlatformMovementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLATFORM_API UPlatformMovementComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // �����������
    UPlatformMovementComponent();

    // ������ �����, �� ������� �������� ���������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")
    TArray<FVector> Points;

    // ������ ������� �����
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")
    int32 CurrentPointIndex = 0;

    // �������� �������� ���������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")
    float Speed = 500.0f;

    // ����� ��� ��������� ������� ������� �����
    UFUNCTION(BlueprintPure, Category = "Platform Movement")
    int32 GetTargetPointIndex() const;

    // ����� ��� �������� ���������� ������� �����
    UFUNCTION(BlueprintPure, Category = "Platform Movement")
    bool IsReachedTargetPoint() const;

protected:
    // ���������� ��� ���������� ���������� � ������
    virtual void BeginPlay() override;

    // ���������� ������ ����
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};