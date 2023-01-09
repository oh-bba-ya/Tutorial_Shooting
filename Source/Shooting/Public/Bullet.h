// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SHOOTING_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
	class UStaticMeshComponent* meshComp;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = BulletSettings)
	float moveSpeed = 1000.0f;

	/*
	UFUNCTION()
		void OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	*/
	UPROPERTY(EditDefaultsOnly, Category = BulletSettings)
	class UParticleSystem* explosion_effect;



	UPROPERTY(EditDefaultsOnly, Category = BulletSettings)
		int setPoint = 1;

	void SetDirection(FVector value);

private:
	FVector direction;

	FTimerHandle lifeTimer;


	// timerManager에서 사용할 함수 , 매개변수와 반환형이 없어야 한다.
	void DestroyMySelf();
};
