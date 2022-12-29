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
	TSubclassOf<class UMainWidget> mainWidget;   // 블루프린트를 가져오고 싶을땐 TSubclassOf

	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UMenuWidget> menuWidget;   // 블루프린트를 가져오고 싶을땐 TSubclassOf


	void ShowMenu();






private:
	int32 currentScore = 0;

	int32 bestScore = 0;

	class UMainWidget* main_UI;

	class UMenuWidget* menu_UI;



	// 최고 점수를 파일로 저장한다. (절대경로)
	FString filePath = FString("D:/Myeongseok/Unreal_Engine/Shooting/Content/SaveScore/bestScore.txt");
		
	// 파일 경로 2번째 방법 (상대 경로)
	//FString filePath2 = FString("../../../Content/SaveScore/BestScore.txt");




	
};
