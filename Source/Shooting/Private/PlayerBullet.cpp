// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingGameModeBase.h"

APlayerBullet::APlayerBullet() {
	// �ڽ� ������Ʈ�� �ݸ��� �������� Bullet���� �����Ѵ�.
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
	// �浹�� ���͸� AEnemy Ŭ������ ��ȯ�غ���.
	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	// ���� ĳ������ ���������� �Ǿ AEnemy ������ ������ ���� �ִٸ�
	if (enemy != nullptr) {

		// ���� �ִ� ��ġ�� ���� ����Ʈ�� �����Ѵ�.
		FVector enemyLocation = enemy->GetActorLocation();
		FRotator enemyRotation = enemy->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_effect, enemyLocation, enemyRotation, true);

		// �浹�� ���͸� �����Ѵ�.
		enemy->Destroy();

		// ���� ����� ������ 1�� �߰��Ѵ�.
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);

		// gamemode�� �߰��ϴ� 2��° ���
		//AGameModeBase* gm = GetWorld()->GetAuthGameMode();

		AMyShootingGameModeBase* myGM = Cast<AMyShootingGameModeBase>(gm);




		myGM->AddScore(setPoint);
	}

	// �ڱ� �ڽ��� ����
	Destroy();
}