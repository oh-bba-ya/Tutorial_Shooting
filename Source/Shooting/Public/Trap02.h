// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap02.generated.h"

UCLASS()
class SHOOTING_API ATrap02 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap02();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 1. USphereComponent 識情
	UPROPERTY(EditAnywhere, Category = TrapSettings)
	class USphereComponent* sphereComp;

	// 2. UStaticMesh 識情
	UPROPERTY(EditAnywhere, Category = TrapSettings)
	class UStaticMeshComponent* meshComp;



	// 5. "InTrap" 敗呪 識情


	void InTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
