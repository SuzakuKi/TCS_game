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
    // Конструктор
    UPlatformMovementComponent();

    // Массив точек, по которым движется платформа
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")
    TArray<FVector> Points;

    // Индекс текущей точки
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")
    int32 CurrentPointIndex = 0;

    // Скорость движения платформы
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")
    float Speed = 500.0f;

    // Метод для получения индекса целевой точки
    UFUNCTION(BlueprintPure, Category = "Platform Movement")
    int32 GetTargetPointIndex() const;

    // Метод для проверки достижения целевой точки
    UFUNCTION(BlueprintPure, Category = "Platform Movement")
    bool IsReachedTargetPoint() const;

protected:
    // Вызывается при добавлении компонента к актеру
    virtual void BeginPlay() override;

    // Вызывается каждый кадр
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};