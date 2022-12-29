// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyShootingGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API AMyShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentScore() {return currentScore;}

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetBestScore() { return bestScore; }


	void AddScore(int32 point);


	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UMainWidget> mainWidget;   // �������Ʈ�� �������� ������ TSubclassOf

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UMenuWidget> menuWidget;   // �������Ʈ�� �������� ������ TSubclassOf


	void ShowMenu();






private:
	int32 currentScore = 0;

	int32 bestScore = 0;

	class UMainWidget* main_UI;

	class UMenuWidget* menu_UI;



	// �ְ� ������ ���Ϸ� �����Ѵ�. (������)
	FString filePath = FString("D:/Myeongseok/Unreal_Engine/Shooting/Content/SaveScore/bestScore.txt");
		
	// ���� ��� 2��° ��� (��� ���)
	//FString filePath2 = FString("../../../Content/SaveScore/BestScore.txt");




	
};
