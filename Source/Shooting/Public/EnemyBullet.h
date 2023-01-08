// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "EnemyBullet.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTING_API AEnemyBullet : public ABullet
{
	GENERATED_BODY()
	
public:
	AEnemyBullet();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
