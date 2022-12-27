// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"
#include "Components/BoxComponent.h"
#include "PlayerFlight.h"

// Sets default values
AKillZone::AKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(50.0f, 2000.0f, 50.0f));
	boxComp->SetCollisionProfileName((TEXT("KillZonePreset")));
	
}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	// 오버랩 이벤트 활성화
	boxComp->SetGenerateOverlapEvents(true);

	// 오버랩 이벤트 델리게이트에 오버랩 함수를 연결한다.
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AKillZone::OnOverlap);
	
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillZone::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	// 플레이어를 제외한 부딪힌 모든 대상을 제거한다.
	// 캐스팅을 통해 부딪힌 대상을 판단할 수 있다.
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	// 플레이어가 부딪힌다면 Cast가 되서 nullPtr이 아니게된다.
	if (player != nullptr) {

	}
	else {
		// 플레이어가 아닌 다른 모든 물체 삭제
		OtherActor->Destroy();
	}
}

