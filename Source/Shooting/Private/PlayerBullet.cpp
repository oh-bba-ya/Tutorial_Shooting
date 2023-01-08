// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingGameModeBase.h"

APlayerBullet::APlayerBullet() {
	// 박스 컴포넌트의 콜리전 프리셋을 Bullet으로 설정한다.
	boxComp->SetCollisionProfileName(TEXT("Bullet"));
}

// Called when the game starts or when spawned
void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnBulletOverlap);


}


void APlayerBullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 충돌한 액터를 AEnemy 클래스로 변환해본다.
	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	// 만일 캐스팅이 정상적으로 되어서 AEnemy 포인터 변수에 값이 있다면
	if (enemy != nullptr) {

		// 적이 있던 위치에 폭발 이펙트를 생성한다.
		FVector enemyLocation = enemy->GetActorLocation();
		FRotator enemyRotation = enemy->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, enemyLocation, enemyRotation, true);

		// 충돌할 액터를 제거한다.
		enemy->Destroy();

		// 게임 모드의 점수를 1점 추가한다.
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);

		// gamemode를 추가하는 2번째 방법
		//AGameModeBase* gm = GetWorld()->GetAuthGameMode();

		AMyShootingGameModeBase* myGM = Cast<AMyShootingGameModeBase>(gm);




		myGM->AddScore(setPoint);
	}

	// 자기 자신을 제거
	Destroy();
}