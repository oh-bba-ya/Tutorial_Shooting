// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "MyShootingGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UMainWidget::PrintCurrentScore()
{
	AMyShootingGameModeBase* myGM = Cast<AMyShootingGameModeBase>(UGameplayStatics::GetGameMode(this));
	
	if (myGM != nullptr) {

		// 현재 점수(정수) -> FText(문자열) 형태로 변환해서 curScore 텍스트 블록의 값으로 설정한다.
		curScore->SetText(FText::AsNumber(myGM->GetCurrentScore()));
		bestScore->SetText(FText::AsNumber(myGM->GetBestScore()));


		// scoreAnim 애니메이션을 실행한다.
		PlayAnimation(scoreAnim, 0, 1, EUMGSequencePlayMode::Forward);

	}
}
