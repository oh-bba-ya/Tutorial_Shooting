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

	// 충돌 영역 생성
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);

	// Box 컴포넌트 extent size 설정
	boxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 0.25f));

	// 메쉬 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0, 0, -50.0f));

	/*
	// 박스 컴포넌트의 콜리전 프리셋을 Bullet으로 설정한다.
	boxComp->SetCollisionProfileName(TEXT("Bullet"));
	*/

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	// 박스 컴포넌트의 충돌 오버랩 이벤트에 BulletOverlap 함수를 연결한다.
	//boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);
	

	// 2초 후 액터 제거
	// SetLifeSpan(2.0f);

	// TimeManager를 이용한 Destory 적용
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &ABullet::DestroyMySelf, 2.0f, false);

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//direction = FVector(1, 0, 0);
	
	// 나의 정면 방향으로 계속 이동하고 싶다.
	// ForwardVector : 단위벡터로 반환된다.
	direction = GetActorForwardVector();			// Locale 기준, 즉 액터의 기준의 정면이다. (World 기준 함수는 따로 존재함)


	// p = p0 + vt
	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
}

/*
void ABullet::OnBulletOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
*/

void ABullet::DestroyMySelf()
{
	Destroy();
}

