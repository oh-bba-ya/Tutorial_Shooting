// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerFlight.h"
#include "MyShootingGameModeBase.h"
#include "EngineUtils.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50.0f));

	// Collsion presets�� Enemy ���������� ����
	boxComp->SetCollisionProfileName(TEXT("Enemy"));


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	meshComp->SetRelativeLocation(FVector(0, 0, -50));
	meshComp->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// ��÷�� �ؼ� �ϳ��� ���� ����, �� �ٸ� �ϳ��� �÷��̾� �������� �̵��ϰ� �ʹ�.
	// 1. ��÷�� �Ѵ�. Ȯ���� ������ �̿��ؼ� 70:30 ������ �Ѵ�.
	int32 drawNumber = FMath::RandRange(1, 100);

	// 2. ����, ���� ���� traceRate ���� ������...
	if (drawNumber <= traceRate)
	{
		// 2-1. �÷��̾� ���͸� ã�´�.

		// ���忡�� Ư���� ��ü�� ã�� ��� - 1
		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerFlight::StaticClass());

		// ���忡�� Ư���� ��ü�� ã�� ��� - 2

		for (TActorIterator<APlayerFlight> it(GetWorld()); it; ++it)
		{
			target = *it;
		}

		if (target != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("player"));
			float temp = target->moveSpeed;

			// 2-2. �÷��̾��� ��ġ - ���� ��ġ = �� ������ �����Ѵ�.
			FVector targetDir = target->GetActorLocation() - GetActorLocation();
			targetDir.Normalize();
			direction = targetDir;
		}

	}
	// 3. �׷��� ������...
	else
	{
		// 3-1. �������� ������ ���Ѵ�.
		direction = GetActorForwardVector();
	}

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);
	boxComp->SetGenerateOverlapEvents(true);
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

		// �÷��̾� ���� ����
		player->ReservationHitColor(0.2f);


	}
	else {
		//  �÷��̾ �ƴ� �ٸ� ���Ϳ� �浹�� �ڱ� �ڽ��� �����Ѵ�. 
		Destroy();
	}

}

