// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShootingGameModeBase.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "BossActor.h"
#include "EnemySpawningPool.h"
#include "EngineUtils.h"

void AMyShootingGameModeBase::BeginPlay()
{
	//Super::BeginPlay();

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


	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Emerald, TEXT("LogTest"), true);

}

void AMyShootingGameModeBase::AddScore(int32 point)
{
	currentScore += point;

	if (currentScore > bestScore) {
		bestScore = currentScore;

		// 문자열을 전달할때 ' * '를 써야한다. -> 포인터 아님 FString가서 * 보면 오퍼레이터로 구현되어 있음
		bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(bestScore),*filePath);
		
	}

	// 만일, 현재 점수가 30점 이상이면
	if (currentScore >= 30) {
		if (!isSpawn) {
			isSpawn = true;

			// 4초 뒤에 보스를 생성한다.
			FTimerHandle spawnHandle;
			GetWorld()->GetTimerManager().SetTimer(spawnHandle, this, &AMyShootingGameModeBase::SpawnBoss, 4, false);

			// 모든 스폰을 중단한다.
			StopAllSpawn();
		}

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

void AMyShootingGameModeBase::SaveEnemy(AEnemy* enemy)
{
	enemies.Add(enemy);
}

void AMyShootingGameModeBase::RemoveEnemy()
{

	// 배열이 비어있는지 검사. 
	// 배열이 비어있을때 Destory() 함수를 호출하게 되면 크래쉬 발생
	if (enemies.IsEmpty()) {
		return;
	}

	// enemy 배열이 비어 있지 않다면 다음 반복문 실행
	// Num() : 배열의 크기
	for (int32 i = 0; i < enemies.Num(); i++) {
		enemies[i]->DestroyMySelf();
		enemies[i]->Destroy();
		this->AddScore(1);
		
	}

	// 배열 비우기 : 삭제한 액터들 배열에서 삭제
	enemies.Empty();
}

void AMyShootingGameModeBase::SpawnBoss()
{
	GetWorld()->SpawnActor<ABossActor>(bossActor, FVector(0, 0, 700), FRotator::ZeroRotator);


}

void AMyShootingGameModeBase::StopAllSpawn()
{
	for (TActorIterator<AEnemySpawningPool> pool(GetWorld()); pool; ++pool) {
		pool->SetSpawn();
	}

}