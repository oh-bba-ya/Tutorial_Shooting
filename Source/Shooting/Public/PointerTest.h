// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointerTest.generated.h"

UCLASS()
class SHOOTING_API APointerTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointerTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	int32 pt_number = 30;

	// 포인터 변수의 경우 UPROPERTY를 사용할 수 없다. 왜냐하면 리플렉션이 불가능 인스턴스가 될 수 없기에 클래스는 인스턴스가 되기에 쌉가능
	float* myAge;

	UPROPERTY(EditAnywhere)
	float realAge = 20;


};
