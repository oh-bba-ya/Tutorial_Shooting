// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerFlight.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	// 3. USphereComponent로 루트 콜리전을 생성
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(sphereComp);
	
	sphereComp->SetSphereRadius(200);
	
	// 4. UStaticMesh를 루트의 자식 컴포넌트로 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);

	sphereComp->SetCollisionProfileName("TrapPreset");

}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("tRAP"));

	// 7.  Overlap 델리게이트 InTrap 함수를 연결
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATrap::InTrap);

	// Endoverlap 델리게이트에 outTrap 함수를 연결한다.
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &ATrap::OutTrap);
	
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 현재 누적 시간(Current Time)이.. 지정된 시간(Teleport Time)에 도달했다면..
	if (currentTime >= teleportTime) {
		// 랜덤 위치(벡터)를 설정한다.
		float y = FMath::RandRange(-300, 300);
		float z = FMath::RandRange(-300, 300);

		// 랜덤 위치(벡터)를 설정한다.
		FVector pos = { 0,y,z };

		// 랜덤 벡터를 받아보자 
		// -1 ~ 1 사이의 단위벡터로 받는다.
		FVector randVector = FMath::VRand() * 500.0f;
		randVector.X = 0;

		// 그 위치로 이동한다.
		SetActorLocation(pos);

		// 시간 초기화(Current Time)
		currentTime = 0;

	}
	else {
		currentTime += DeltaTime;
	}

}

// 6. "InTrap" 함수 선언
void ATrap::InTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);
	

	if (player != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player Collision"));
		player->isFire = false;
	}

}

void ATrap::OutTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// 만일 나가기 직전에 부딪힌 액터가 플레이어라면
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	if (player != nullptr) {
		// 플레이어의 canFire 변수의 값을 true로 변경한다.
		player->isFire = true;
	}
}
