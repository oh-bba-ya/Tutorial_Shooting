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

	// Collsion presets을 Enemy 프리셋으로 변경
	boxComp->SetCollisionProfileName(TEXT("Enemy"));


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	meshComp->SetRelativeLocation(FVector(0, 0, -50));
	meshComp->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// 추첨을 해서 하나는 정면 방향, 또 다른 하나는 플레이어 방향으로 이동하고 싶다.
	// 1. 추첨을 한다. 확률은 변수를 이용해서 70:30 비율로 한다.
	int32 drawNumber = FMath::RandRange(1, 100);

	// 2. 만일, 뽑은 값이 traceRate 보다 작으면...
	if (drawNumber <= traceRate)
	{
		// 2-1. 플레이어 액터를 찾는다.

		// 월드에서 특정한 객체를 찾는 방법 - 1
		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerFlight::StaticClass());

		// 월드에서 특정한 객체를 찾는 방법 - 2

		for (TActorIterator<APlayerFlight> it(GetWorld()); it; ++it)
		{
			target = *it;
		}

		if (target != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("player"));
			float temp = target->moveSpeed;

			// 2-2. 플레이어의 위치 - 나의 위치 = 갈 방향을 설정한다.
			FVector targetDir = target->GetActorLocation() - GetActorLocation();
			targetDir.Normalize();
			direction = targetDir;
		}

	}
	// 3. 그렇지 않으면...
	else
	{
		// 3-1. 정면으로 방향을 정한다.
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

		// 플레이어 색상 변경
		player->ReservationHitColor(0.2f);


	}
	else {
		//  플레이어가 아닌 다른 액터와 충돌시 자기 자신을 제거한다. 
		Destroy();
	}

}

