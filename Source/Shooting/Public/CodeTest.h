// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointerTest.h"			// .h파일에서 .h 파일을 include 하게 될시 추후에 너무나 많은 클래스로 인해 중복이 많아진다. 그래서 전방 클래스라는 방법을 사용한다.
#include "CodeTest.generated.h"			// 반드시 외부 클래스 #include 시 generated.h 보다 위에 추가해야한다. 만약 밑이면 인식못함(언리얼 규칙)



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
	/*
	int32 result;

	int32 GetNum(int n);
	*/
#pragma endregion



#pragma region TArray TMap
	//UPROPERTY(EditAnywhere, Category = CodeVariable)
	//TArray<int32> ages;

	//UPROPERTY(EditAnywhere, Category = CodeVariable)
	//TMap<FString, float> distances;

#pragma endregion


#pragma region PointerActor

// 헤더파일을 포함하기 보다 class를 전방 선언함으로써 이런 클래스가 있다는것을 알려주고 사용한다.
UPROPERTY(EditAnywhere, Category = CodeVariable)
class APointerTest* pointerTest;	


// 여러개의 클래스를 바꾸고 싶을때
UPROPERTY(EditAnywhere, Category = CodeVariable)
TArray<class APointerTest*> pointerTestArray;

 
#pragma endregion



private:


};
