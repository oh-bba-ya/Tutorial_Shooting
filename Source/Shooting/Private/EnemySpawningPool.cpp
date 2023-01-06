// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawningPool.h"
#include "Enemy.h"
#include "Components/ArrowComponent.h"
#include "MyShootingGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawningPool::AEnemySpawningPool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	rootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(rootScene);

	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Arrow"));
	spawnArrow->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemySpawningPool::BeginPlay()
{
	Super::BeginPlay();
	
	AGameModeBase* mode = UGameplayStatics::GetGameMode(this);
	gamemode = Cast<AMyShootingGameModeBase>(mode);
}

// Called every frame
void AEnemySpawningPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 경과된 시간을 누적시킨다.
	currentTime += DeltaTime;


	// 만일, 누적된 시간이 spawnCool에 지정한 시간보다 크거나 같다면...
	if (currentTime >= spawnCool)
	{
		if (isSpawn) {
			// 에너미 블루프린트를 생성한다.
			// Arrow 컴포넌트의 위치와 회전 상태로 맞춰서 생성한다.
			AEnemy* enemy = GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());

			gamemode->SaveEnemy(enemy);
		}


		// 누적된 시간을 다시 0초로 초기화한다.
		currentTime = 0;
	}




}

void AEnemySpawningPool::SetSpawn()
{
	isSpawn = !isSpawn;
}

