// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShootingGameModeBase.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"

void AMyShootingGameModeBase::BeginPlay()
{
	// ���� �������Ʈ�� �����Ѵ�.
	main_UI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	if (main_UI != nullptr) {
		// ������ ������ �� ��Ʈ�� �׸���.
		main_UI->AddToViewport();

		// �ְ� ������ ���Ͽ��� �о�´�.
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

		// �о�� ���� bestScore ������ �ִ´�.
		// string to int �� ���  FCString Ÿ���� �ִ´�.
		bestScore = FCString::Atoi(*scoreText);

		//UE_LOG(LogTemp, Warning, TEXT("%d"),bestScore);

		//���� ������ ������ curScore �ؽ�Ʈ ��ο� �ݿ��Ѵ�.
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

		// ���ڿ��� �����Ҷ� ' * '�� ����Ѵ�. -> ������ �ƴ� FString���� * ���� ���۷����ͷ� �����Ǿ� ����
		bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(bestScore),*filePath);
		
		UE_LOG(LogTemp, Warning, TEXT("%s"), isSaved ? TEXT("True") : TEXT("False"));
	}

	// ���� ������ ������ curScore �ؽ�Ʈ ��Ͽ� �ݿ��Ѵ�.
	if (main_UI != nullptr) {
		main_UI->PrintCurrentScore();
	}

}

void AMyShootingGameModeBase::ShowMenu()
{
	// �޴� ������ ȭ�鿡 ǥ���Ѵ�.
	menu_UI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

	if (menu_UI != nullptr) {
		menu_UI->AddToViewport();
	}

	// ������ �Ͻ����� ���·� �����.
	// 1. ���� ������ �ð� �帧�� 0���� �����.
	//UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);

	// 2. �Ͻ����� �Լ� ȣ��
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	// ���콺 Ŀ�� ��Ÿ����
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

}
