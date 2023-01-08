// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyShootingGameModeBase.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �浹 ���� ����
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);

	// Box ������Ʈ extent size ����
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 0.25f));

	// �޽� ����
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));

	/*
	// �ڽ� ������Ʈ�� �ݸ��� �������� Bullet���� �����Ѵ�.
	boxComp->SetCollisionProfileName(TEXT("Bullet"));
	*/

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	// �ڽ� ������Ʈ�� �浹 ������ �̺�Ʈ�� BulletOverlap �Լ��� �����Ѵ�.
	//boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
	

	// 2�� �� ���� ����
	// SetLifeSpan(2.0f);

	// TimeManager�� �̿��� Destory ����
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &ABullet::DestroyMySelf, 2.0f, false);

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction = FVector(1, 0, 0);
	
	// ���� ���� �������� ��� �̵��ϰ� �ʹ�.
	// ForwardVector : �������ͷ� ��ȯ�ȴ�.
	direction = GetActorForwardVector();			// Locale ����, �� ������ ������ �����̴�. (World ���� �Լ��� ���� ������)


	// p = p0 + vt
	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
}

/*
void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
*/

void ABullet::DestroyMySelf()
{
	Destroy();
}

