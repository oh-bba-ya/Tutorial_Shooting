// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "MyShootingGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UMainWidget::PrintCurrentScore()
{
	AMyShootingGameModeBase* myGM = Cast<AMyShootingGameModeBase>(UGameplayStatics::GetGameMode(this));
	
	if (myGM != nullptr) {

		// ���� ����(����) -> FText(���ڿ�) ���·� ��ȯ�ؼ� curScore �ؽ�Ʈ ����� ������ �����Ѵ�.
		curScore->SetText(FText::AsNumber(myGM->GetCurrentScore()));
		bestScore->SetText(FText::AsNumber(myGM->GetBestScore()));
	}
}
