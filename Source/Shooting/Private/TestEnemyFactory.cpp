// Fill out your copyright notice in the Description page of Project Settings.


#include "TestEnemyFactory.h"
#include "Components/ArrowComponent.h"
#include "TestEnemy.h"


// Sets default values
ATestEnemyFactory::ATestEnemyFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	


}

// Called when the game starts or when spawned
void ATestEnemyFactory::BeginPlay()
{
	Super::BeginPlay();

	

	
}

// Called every frame
void ATestEnemyFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	curTime += DeltaTime;
	if (curTime > spawnTime) {
		curTime = 0;
		GetWorld()->SpawnActor<ATestEnemy>(enemy, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());
	}

}

