// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerFlight.generated.h"


// 1. �Ű������� ���� �Լ�
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FULTbomb);

// 2.  ���͸� ���ڷ� �Ѱܹ޴� ��������Ʈ �Լ� ����(FDirectionModifier)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDirectionModifier, FVector, newDir);



UCLASS()
class SHOOTING_API APlayerFlight : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerFlight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	float moveSpeed = 500;


	// ��� ����Ʈ Ŭ���� Ÿ���� ����ϱ� ���ؼ��� TSubclassOf<> ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	TSubclassOf<class ABullet> bulletFactory;



	// ������ Input Action, Mapping Context�� C++ ���� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		class UInputAction* ia_horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		class UInputAction* ia_vertical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = PlayerSettings)
		class UInputAction* ia_fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		class UInputAction* ia_boost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		class UInputAction* ia_ult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
		class UInputMappingContext* imc_myMapping;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	int32 bulletCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	int32 bulletSpacing = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	float bulletAngle = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	bool isFire = true;

	


	void ReservationHitColor(float time);

	void ChangeOriginColor();


	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class USoundBase* fireSound;

	
	FULTbomb playerBomb;

	FDirectionModifier OnSetDirection;


private:
	/*
	// ���� �Է� �Լ�
	// �������Ʈ���� ȣ���ϱ�
	UFUNCTION(BlueprintCallable)
	void Horizontal(float value);

	UFUNCTION(BlueprintCallable)
	void Vertical(float value);

	UFUNCTION(BlueprintCallable)
	void FireBullet();		// action�� ��� parameter�� ������Ѵ�. , ��ȯ�� �������� void

	*/

	void CheckEnemies();
	

	
	// EnhancedInput �Լ�
		void Horizontal(const FInputActionValue& value);
		void Vertical(const FInputActionValue& value);
		void FireBullet();
		void AddBullet();
		
		UFUNCTION()
		void ExplosionAll();

		UFUNCTION(BlueprintCallable)
			void AddBoost();

		UFUNCTION(BlueprintCallable)
			void RemoveBoost();

	
	float h;
	float v;

	FVector direction;
	FLinearColor initColor;				
	FTimerHandle colorTimer;
	UMaterialInstanceDynamic* dynamicMat;


};
