// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShootingGameModeBase.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"

void AMyShootingGameModeBase::BeginPlay()
{
	// 위젯 블루프린트를 생성한다.
	main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	if (main_UI != nullptr) {
		// 생성된 위젯을 뷰 포트에 그린다.
		main_UI->AddToViewport();

		// 최고 점수를 파일에서 읽어온다.
		FString scoreText;

		FFileHelper::LoadFileToString(scoreText, *filePath);

		bool isLoadSuccess = FFileHelper::LoadFileToString(scoreText, *filePath);
		/*
		if (isLoadSuccess) {
			UE_LOG(LogTemp, Warning, TEXT("Success"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Failed"));
		}
		*/

		//UE_LOG(LogTemp, Warning, TEXT("%s"), isLoadSuccess ? TEXT("Success") : TEXT("Failed"));

		// 읽어온 값을 bestScore 변수에 넣는다.
		// string to int 의 경우  FCString 타입을 넣는다.
		bestScore = FCString::Atoi(*scoreText);

		//UE_LOG(LogTemp, Warning, TEXT("%d"),bestScore);

		//현재 점수를 위젯의 curScore 텍스트 블로에 반영한다.
		main_UI->PrintCurrentScore();

	}
	FString testPath = FPaths::ProjectContentDir()+TEXT("SaveScore/SaveScore.txt");

	UE_LOG(LogTemp, Warning, TEXT("test path: %s"), *testPath);

	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Emerald, TEXT("LogTest"), true);

}

void AMyShootingGameModeBase::AddScore(int32 point)
{
	currentScore += point;

	if (currentScore > bestScore) {
		bestScore = currentScore;

		// 문자열을 전달할때 ' * '를 써야한다. -> 포인터 아님 FString가서 * 보면 오퍼레이터로 구현되어 있음
		bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(bestScore),*filePath);
		
		UE_LOG(LogTemp, Warning, TEXT("%s"), isSaved ? TEXT("True") : TEXT("False"));
	}

	// 현재 점수를 위젯의 curScore 텍스트 블록에 반영한다.
	if (main_UI != nullptr) {
		main_UI->PrintCurrentScore();
	}

}

void AMyShootingGameModeBase::ShowMenu()
{
	// 메뉴 위젯을 화면에 표시한다.
	menu_UI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

	if (menu_UI != nullptr) {
		menu_UI->AddToViewport();
	}

	// 게임을 일시정지 상태로 만든다.
	// 1. 직접 게임의 시간 흐름을 0으로 만든다.
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);

	// 2. 일시정지 함수 호출
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	// 마우스 커서 나타내기
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

}
