// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawningPool.h"
#include "Enemy.h"
#include "Components/ArrowComponent.h"

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
	
}

// Called every frame
void AEnemySpawningPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ����� �ð��� ������Ų��.
	currentTime += DeltaTime;


	// ����, ������ �ð��� spawnCool�� ������ �ð����� ũ�ų� ���ٸ�...
	if (currentTime >= spawnCool)
	{
		// ���ʹ� ��������Ʈ�� �����Ѵ�.
		// Arrow ������Ʈ�� ��ġ�� ȸ�� ���·� ���缭 �����Ѵ�.
		GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());

		// ������ �ð��� �ٽ� 0�ʷ� �ʱ�ȭ�Ѵ�.
		currentTime = 0;
	}


}
