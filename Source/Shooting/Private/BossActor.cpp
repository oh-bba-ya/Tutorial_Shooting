// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBullet.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABossActor::ABossActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(50, 300, 150));
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Boss"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0, 0, -150));
	meshComp->SetRelativeScale3D(FVector(1, 6, 3));

	
}

// Called when the game starts or when spawned
void ABossActor::BeginPlay()
{
	Super::BeginPlay();

	startPos = GetActorLocation();

	
}

// Called every frame
void ABossActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	// v = v0 + vt �� �̿��� �̵�
	// ���� ��ġ���� (0,0,200) ��ġ���� �̵��Ѵ�.
	float distance = (startPos - GetActorLocation()).Length();

	if (distance < 500) {
		SetActorLocation(GetActorLocation() + GetActorUpVector() * -1 * 200 * DeltaTime);
	}
	else {
		SetActorLocation(FVector(0, 0, 200));
	}
	*/


	// �������� ���
	speed += DeltaTime;
	speed = FMath::Clamp(speed, 0.0f, 1.0f);

	FVector result = FMath::Lerp(startPos, endPos,speed);
	SetActorLocation(result);



	if (currentTime > pattern_delay) {
		BossAttack1(15, 6);
		currentTime = 0;
	}
	else {
		currentTime += DeltaTime;
	}


}

// Called when the game starts or when spawned
void ABossActor::BossAttack1(float angle, int32 count)
{
	// angle 
	UE_LOG(LogTemp, Warning, TEXT("Boss Bullet Spawn"));


	// ���� ���� = 270 - (angle * (count -1) * 0.5f)
	float startAngle = 270 - (angle * (count - 1) * 0.5f);

	for (int32 i = 0; i < count; i++) {
		// �⺻ ��ǥ (0,rcos@, rsin@)
		// �������� ����� ���� ���� �Ѿ˵��� �Ÿ��� ��������.
		FVector bullet_base = FVector(0
			, 50 * FMath::Cos(FMath::DegreesToRadians(startAngle + angle * i))
			, 50 * FMath::Sin(FMath::DegreesToRadians(startAngle + angle * i)));



		AEnemyBullet* enemyActor = GetWorld()->SpawnActor<AEnemyBullet>(enemyBullet, 
			GetActorLocation() + bullet_base,
			FRotator(-90,0,0));

		//enemyActor->SetDirection(bullet_base.GetSafeNormal());


		// Up Vector ���� Bullet_base �������� ȸ�������� ���� ��������  ���� ����Ѵ�.
		// ù��° �Ķ���Ͱ� ����, 2��°�Ķ���Ͱ� �ٲܰ�
		FRotator rot = UKismetMathLibrary::MakeRotFromZX(enemyActor->GetActorUpVector(),bullet_base.GetSafeNormal());
	
		enemyActor->SetActorRotation(rot);
		
	}

}

