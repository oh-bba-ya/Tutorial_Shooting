// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"         // Kismet : �𸮾�3���� ����ϴ� ���̺귯��
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMenuWidget::NativeConstruct()
{
	// OnColicked�� Delegate�̱� ������ AddDynamic�� �ؾ��Ѵ�.
	// Delegate�̹Ƿ� �ݵ�� ReSume�� UFUNCTION ��ũ�� �߰��ؾ��Ѵ�.
	btn_Resume->OnClicked.AddDynamic(this, &UMenuWidget::ResumeGame);
	btn_Restart->OnClicked.AddDynamic(this, &UMenuWidget::RestartGame);
	btn_Quit->OnClicked.AddDynamic(this, &UMenuWidget::Quit);
}

void UMenuWidget::ResumeGame() {

	// �ð� �ٽ� �帧
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	// ���콺 Ŀ�� OFF
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	// AddToViewport�� �ݴ� ��� , ���� ���Ӹ�忡�� ���������� �ű⼭ �ϴ°� �´µ�
	// ���⼭�� �����ϴ����� �߸𸣁ٴ�.
	// ���� �ڵ�� ���� Defprecated �Ǳ� ������ RemoveFromParent() �� ����غ���.
	this->RemoveFromViewport();

}

void UMenuWidget::RestartGame()
{
	// ������ �ٽ� �ε��Ѵ�.
	UGameplayStatics::OpenLevel(GetWorld(),TEXT("ShootingMap"));


	// ���� ������ �����Ѵ�.
	// RemoveFromViewport()�� Deprecated�Ǳ⿡ ���� �ڵ带 �������.
	this->RemoveFromParent();

}

void UMenuWidget::Quit()
{
	// �÷��̾� ���� ��������
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();

	// ���� �����Ѵ�.
	// true : �� �����ϰ� ���� ����
	// false : �÷��� ������ ���� ����
	UKismetSystemLibrary::QuitGame(GetWorld(),playerCon, EQuitPreference::Quit, true);
}
