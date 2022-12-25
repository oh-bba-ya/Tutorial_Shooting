// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PlayerFlight.generated.h"


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
	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UInputAction* ia_horizontal;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UInputAction* ia_vertical;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UInputAction* ia_fire;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
		class UInputMappingContext* imc_myMapping;


private:
	// �������Ʈ���� ȣ���ϱ�
	/*
	UFUNCTION(BlueprintCallable)
	void Horizontal(float value);

	UFUNCTION(BlueprintCallable)
	void Vertical(float value);

	UFUNCTION(BlueprintCallable)
	void FireBullet();		// action�� ��� parameter�� ������Ѵ�. , ��ȯ�� �������� void
	*/

	// EnhancedInput �Լ�
	UFUNCTION(BlueprintCallable)
		void Horizontal(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
		void Vertical(const FInputActionValue& value);

	UFUNCTION(BlueprintCallable)
		void FireBullet();




	float h;
	float v;

	FVector direction;

};
