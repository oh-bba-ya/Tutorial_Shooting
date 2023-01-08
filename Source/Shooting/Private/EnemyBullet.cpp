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
	// �浹�� ��� ���͸� APlayerPawn Ŭ������ ��ȯ�� �õ�
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	// ����, ĳ���� ����
	if (player != nullptr)
	{
		//�ε��� ���(�÷��̾�) ���� ����
		player->Destroy();

		// �޴� ������ �����ϴ� �Լ��� �����Ѵ�.
		AMyShootingGameModeBase* gm = Cast<AMyShootingGameModeBase>(GetWorld()->GetAuthGameMode());

		if (gm != nullptr) {
			gm->ShowMenu();
		}


		Destroy();
	}
}