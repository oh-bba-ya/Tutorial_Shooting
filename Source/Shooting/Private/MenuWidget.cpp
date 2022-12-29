// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"         // Kismet : 언리얼3에서 사용하던 라이브러리
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeConstruct()
{
	// OnColicked도 Delegate이기 때문에 AddDynamic을 해야한다.
	// Delegate이므로 반드시 ReSume에 UFUNCTION 매크로 추가해야한다.
	btn_Resume->OnClicked.AddDynamic(this, &UMenuWidget::ResumeGame);
	btn_Restart->OnClicked.AddDynamic(this, &UMenuWidget::RestartGame);
	btn_Quit->OnClicked.AddDynamic(this, &UMenuWidget::Quit);
}

void UMenuWidget::ResumeGame() {

	// 시간 다시 흐름
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	// 마우스 커서 OFF
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	// AddToViewport의 반대 기능 , 원래 게임모드에서 생성했으니 거기서 하는게 맞는데
	// 여기서도 동작하는지는 잘모르곘다.
	// 다음 코드는 이제 Defprecated 되기 때문에 RemoveFromParent() 를 사용해보자.
	this->RemoveFromViewport();

}

void UMenuWidget::RestartGame()
{
	// 레벨을 다시 로드한다.
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("ShootingMap"));


	// 현재 위젯은 제거한다.
	// RemoveFromViewport()는 Deprecated되기에 다음 코드를 사용하자.
	this->RemoveFromParent();

}

void UMenuWidget::Quit()
{
	// 플레이어 정보 가져오기
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	// 앱을 종료한다.
	// true : 다 무시하고 강제 종료
	// false : 플랫폼 결정에 따른 종료
	UKismetSystemLibrary::QuitGame(GetWorld(),playerCon, EQuitPreference::Quit, true);
}
