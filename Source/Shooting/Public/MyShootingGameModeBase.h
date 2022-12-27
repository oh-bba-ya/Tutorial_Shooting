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


	void AddScore(int32 point);


	UPROPERTY(EditAnywhere, Category = MyDefaultSetting)
	TSubclassOf<class UMainWidget> mainWidget;   // 블루프린트를 가져오고 싶을땐 TSubclassOf

	class UMainWidget* main_UI;

private:
	int32 currentScore = 0;




	
};
