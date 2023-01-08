// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerFlight.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingGameModeBase.h"

AEnemyBullet::AEnemyBullet() {

	boxComp->SetCollisionProfileName(TEXT("Enemy"));

}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnBulletOverlap);


}


void AEnemyBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 충돌한 대상 액터를 APlayerPawn 클래스로 변환을 시도
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	// 만일, 캐스팅 성공
	if (player != nullptr)
	{
		//부딪힌 대상(플레이어) 액터 제거
		player->Destroy();

		// 메뉴 위젯을 생성하는 함수를 실행한다.
		AMyShootingGameModeBase* gm = Cast<AMyShootingGameModeBase>(GetWorld()->GetAuthGameMode());

		if (gm != nullptr) {
			gm->ShowMenu();
		}


		Destroy();
	}
}