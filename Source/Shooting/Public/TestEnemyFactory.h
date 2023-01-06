// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestEnemyFactory.generated.h"

UCLASS()
class SHOOTING_API ATestEnemyFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestEnemyFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ATestEnemy> enemy;




	UPROPERTY(EditAnywhere)
	class UArrowComponent* spawnArrow;

	float curTime;

	float spawnTime = 3.f;
	



};