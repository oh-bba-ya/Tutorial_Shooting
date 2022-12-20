// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeTest.h"
#include "PointerTest.h"			//.cpp  파일에서는 외부 헤더파일을 #include 한다.

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
	//int32 number = GetNum(10);
	//UE_LOG(LogTemp, Warning, TEXT("지역변수 전역변수 name 중복 : %d"), number);
#pragma endregion



#pragma region TArray TMap

	
// 	for (int32 i = 0; i < ages.Num(); i++) {
// 		UE_LOG(LogTemp, Warning, TEXT("%d"), ages[i])
// 	}

	//for (auto dist : distances) {			// auto = TPair<FString, float> 자료형이다 .
	//	UE_LOG(LogTemp, Warning, TEXT("%s : %f"), *dist.Key, dist.Value);
	//}




#pragma endregion


#pragma region PointerActor
/*
* 포인터 기초
// 깊은 복사 (Deep Copy)
// int32 number1 = 10;
// int32 copyNum = number1;
// number1 = 30;

// UE_LOG(LogTemp, Warning, TEXT("Number : %d / CopyNumber :  %d"), number1, copyNum);


// 얕은 복사 (Shallow copy)
int32 number1 = 10;
int32* copyNum = &number1;
number1 = 30;

UE_LOG(LogTemp, Warning, TEXT("Number : %d / CopyNumber :  %d"), number1, *copyNum);

 // %p : 포인터가 가리키는 주소 출력
// %p : 본인의 주소를 출력하기 위해0서는 &변수명 을 통해 출력한다.
UE_LOG(LogTemp, Warning, TEXT("Number : %d , %p / CopyNumber :  %p"), number1, &number1, copyNum);
*/

// 다른 cpp 클래스 참조
pointerTest->pt_number = 50;			// 포인터 변수를 참조하기 위해서는 ' -> ' 를 사용해야한다. ' . ' dot 사용 ㄴㄴ


int32 num = 1;


// 여러 클래스
for (APointerTest* pt : pointerTestArray) {
	num++;
	pt->pt_number += num;
}


// 다른 클래스 포인터 변수 참조 *(참조클래스명->변수이름)
// 가끔 에러가 발생할 때 있다. 그 이유는 CodeTest의 BeginPlay() / PointerTest의 beginPlay() 중 
// PointerTest의 BeginPlay()가 실행되어야 포인터가 메모리 할당되는데 다른 사람 컴퓨터는 CodeTest의 BeginPlay()가 실행되서 크래쉬가 발생한다.
// 이를 해결하기 위해 lifecycle을 알면 생성자가 먼저 실행되므로 먼저 실행되어야 하는것은 생성자에 넣어줘야된다.
// 또는 방어코드를 해준다. 조건문을 통해 ptr != nullptr이 아닐경우에만 실행되도록
*(pointerTest->myAge) = 50.0f;

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


/*
* Test
int32 ACodeTest::GetNum(int n) {
	int32 result = n;
	return result;
}
*/