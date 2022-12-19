// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeTest.h"

#pragma warning (disable : 4458)			// C4458 경고 끄기

// 생성자 함수 : 처음 실행할 때 딱 한번만 실행된다.
// Sets default values
ACodeTest::ACodeTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodeTest::BeginPlay()
{
	Super::BeginPlay();
	
#pragma region 사칙연산 출력
	/*
	int32 result = Add(8, 4);
	UE_LOG(LogTemp, Warning, TEXT("덧셈의 결과는 : %d"), result);

	int32 result2 = Subtract(8, 4);
	UE_LOG(LogTemp, Warning, TEXT("뺄셈의 결과는 : %d"), result2);

	int32 result3 = Mult(8, 4);
	UE_LOG(LogTemp, Warning, TEXT("곱셈의 결과는 : %d"), result3);


	int32 result4 = Division(8, 4);
	UE_LOG(LogTemp, Warning, TEXT("나눗셈의 결과는 : %d"), result4);

	float result5 = fDivision(4, 8);
	UE_LOG(LogTemp, Warning, TEXT("f나눗셈의 결과는 : %0.1f"), result5);
	*/
#pragma endregion

#pragma region 조건문 출력
	/*
	if (nation >= "한국" && age >= 20 && age <40) {
		UE_LOG(LogTemp, Warning, TEXT("청년"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("청년아님"));
	}
	*/
#pragma endregion


#pragma region 풀네임출력
	/*
	FString result = StringAppender(firstName, secondName);
	UE_LOG(LogTemp, Warning, TEXT("이름의 결과는 : %s"), *result);
	*/
#pragma endregion


#pragma region Test 조건문 + 함수
	/*
	FString result = GetEvenOdd(10);
	UE_LOG(LogTemp, Warning, TEXT("입력하신 숫자는 : %s"), *result);
	*/
#pragma endregion



#pragma region 반복문
	//for (int32 i = 0; i < 10; i++) {
	//	UE_LOG(LogTemp, Warning, TEXT("%d : 안녕하세요"), i);
	//}
	//int32 num = 3;

	//int32 temp = num++;
	//UE_LOG(LogTemp, Warning, TEXT("temp : %d"), temp);


	//int32 num2 = 10;
	//temp = ++num2;
	//UE_LOG(LogTemp, Warning, TEXT("temp : %d"), temp);
	
#pragma endregion



#pragma region Test 반복문 구구단
	/*
	int32 result = 0;
	for (int32 i = 1; i < 10; i++) {
		result = 7 * i;
		UE_LOG(LogTemp, Warning, TEXT("7 * %d : = %d"), i, result);
	}
	

	
	for (int32 i = 2; i < 10; i++) {
		for (int32 j = 1; j < 10; j++) {
			UE_LOG(LogTemp, Warning, TEXT("%d * %d = %d"), i, j, i*j);
		}
		UE_LOG(LogTemp, Warning, TEXT("==============================="));
	}
	*/
#pragma endregion


#pragma region Test Off Warning
	int32 number = GetNum(10);
	UE_LOG(LogTemp, Warning, TEXT("지역변수 전역변수 name 중복 : %d"), number);
#pragma endregion
	
}

// Called every frame
void ACodeTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

/*
* 사칙연산
int32 ACodeTest::Add(int32 num1, int32 num2) {
	return num1 + num2;
}

int32 ACodeTest::Subtract(int32 num1, int32 num2) {
	return num1 - num2;
}

int32 ACodeTest::Mult(int32 num1, int32 num2) {
	return num1 * num2;
}

int32 ACodeTest::Division(int32 num1, int32 num2) {
	return num1 / num2;
}

float ACodeTest::fDivision(int32  num1, int32 num2) {
	return (float)num1 / num2;
}
*/



/*
// 풀네임 출력
FString ACodeTest::StringAppender(FString first, FString second) {
	return first + second;
}
*/

/*
* 짝수 홀수
FString ACodeTest::GetEvenOdd(int32 n) {
	if (n % 2 == 0) {
		return "Even";
	}
	else {
		return "Odd";
	}
}
*/



int32 ACodeTest::GetNum(int n) {
	int32 result = n;
	return result;
}
