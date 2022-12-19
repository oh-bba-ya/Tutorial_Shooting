// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeTest.generated.h"

UCLASS()
class SHOOTING_API ACodeTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region 변수 선언, 매크로 적용
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MacroNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MacroNumber2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=CodeVariable)
	int32 MacroNumber3;



	// 정수형 변수 number 를 선언한다.
	int32 number;

	int32 number2;



	// 실수형 변수 fnumber 를 선언한다.
	float fnumber1 = 3.14f;
	float fnumber2 = 10.0f;

	// 문자열 변수 name 을 선언한다.
	FString name;

	FString name2 = FString(TEXT("곽명석"));   // 한글로 출력하기 위해 TEXT로 감싸야한다.

	// 논리형 변수 isStudent
	bool isStudent;
	bool isTeacher = true;



	int32 Add(int32 num1, int32 num2);
	int32 Subtract(int32 num1, int32 num2);
	int32 Mult(int32 num1, int32 num2);
	int32 Division(int32 num1, int32 num2);
	float fDivision(int32 num1, int32 num2);
	*/
#pragma endregion


#pragma region 풀네임출력

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Condition)
	int32 age = 42;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Condition)
	FString nation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Condition)
	FString firstName = "kwak";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Condition)
	FString secondName = "Myeongseok";


	UFUNCTION(BlueprintCallable)
	FString StringAppender(FString first, FString second);

	*/
#pragma endregion



#pragma region Test 조건문 + 함수
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Condition)
	int32 checker;

	UFUNCTION(BlueprintCallable)
	FString GetEvenOdd(int32 n);
	*/

#pragma endregion


#pragma region Off Warning
	int32 result;

	int32 GetNum(int n);
#pragma endregion




private:


};
