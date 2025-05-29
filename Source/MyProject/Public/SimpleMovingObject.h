// Copyright MIET, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleMovingObject.generated.h"

UCLASS()
class MYPROJECT_API ASimpleMovingObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleMovingObject();

	// Массив точек, по которым движется объект
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	TArray<FVector> Points;

	// Текущая целевая точка пути
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int CurrentPointIndex = 0;

	// Скорость движения объекта
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 500.0f;

	// Методы интерфейса передвижения
	UFUNCTION(BlueprintCallable, Category = "Movement")
	int GetNextPointIndex() const;

	//UFUNCTION(BlueprintPure, Category = "Movement")
	//bool HasReachedTargetPoint() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveToNextPoint(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	const int GetDistance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	const float AcceptanceRadius = 1.0f; // Допустимый радиус погрешности
	float distanceToTarget;
	FVector nextPoint;
	FVector direction;

};
