// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class SHOOTING_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// 1. USphereComponent ����
	UPROPERTY(EditAnywhere, Category = TrapSettings)
		class USphereComponent* sphereComp;

	// 2. UStaticMesh ����
	UPROPERTY(EditAnywhere, Category = TrapSettings)
	class UStaticMeshComponent* meshComp;



	// 5. "InTrap" �Լ� ����
	UFUNCTION()
	void InTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION()
	void OutTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

	UPROPERTY(EditAnywhere, Category = TrapSettings)
	float currentTime = 0;

	UPROPERTY(EditAnywhere, Category = TrapSettings)
	float teleportTime = 3.0f;

	

};
