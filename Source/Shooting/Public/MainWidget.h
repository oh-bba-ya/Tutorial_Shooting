// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

	
public:
	// meta = (BindWidget)를 해야 위젯의 텍스트 블록과 바인딩 된다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Scroe", meta = (BindWidget))
		class UTextBlock* curScore;

	UPROPERTY(EditAnywhere, Category = "MySetting|Score", meta = (BindWidget))
	class UTextBlock* bestScore;


	void PrintCurrentScore();


	
};
