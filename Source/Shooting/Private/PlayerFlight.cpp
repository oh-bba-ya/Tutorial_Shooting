// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlight.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Bullet.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"
#include "EngineUtils.h"
#include "MyShootingGameModeBase.h"


// Sets default values
APlayerFlight::APlayerFlight()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 충돌 박스 컴포넌트를 생성한다.
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	// 생성된 충돌 박스 컴포넌트를 루트 컴포넌트로 설정한다.
	SetRootComponent(boxComp);

	// 생성된 충돌 박스 size를 변경한다.
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComp->SetBoxExtent(boxSize);


	// 스태틱 메쉬 컴포넌트 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	// 루트 컴포넌트의 자식 컴포넌트로 설정
	meshComp->SetupAttachment(RootComponent);

	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 메시 컴포넌트의 Static Mesh 항목에 큐브 파일을 할당한다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	// 만약, 큐브 파일을 로드하는데 성공했다면..
	if (cubeMesh.Succeeded()) {
		// 로드한 파일을 메시 컴포넌트의 static mesh 항목에 넣는다.
		meshComp->SetStaticMesh(cubeMesh.Object);
	}

	// 오버랩 이벤트를 켠다.
	boxComp->SetGenerateOverlapEvents(true);

	// 충돌 응답을 Query And Physics로 설정한다.
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Object Type을 1번 채널로(Player)로 설정한다.
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel1);

	// 모든 채널을 충돌 응답 없음으로 설정한다.
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Enemy와는 충돌 이벤트 체크(Quary)를 한다.
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);




}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();



	// 플레이어 컨트롤러를 캐스팅한다.
	APlayerController* playerCon = Cast<APlayerController>(GetController());

	// nullPtr 체크
	if (playerCon != nullptr) {
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());
		
		if (subsys != nullptr) {
			subsys->AddMappingContext(imc_myMapping, 0);
		}
	}
	else {
		
	}

	// 현재 색상 값을 저장한다
	UMaterialInterface* iMat = meshComp->GetMaterial(0);
	FHashedMaterialParameterInfo param = FHashedMaterialParameterInfo(TEXT("myColor"));		// TEXT : 이름의 경우 생성한 메테리얼 더블 클릭 후 Global Vector Parameter Values 값을 말하는거다.
	
	// Material Interface에서 벡터 파라미터 값을 initColor 변수에 저장한다.
	iMat->GetVectorParameterValue(param, initColor);



	// Material Interface를 이용해서 Material Instance Dynamic 개체를 만든다.
	dynamicMat = UMaterialInstanceDynamic::Create(iMat, this);

	if (dynamicMat != nullptr) {
		// 생성한 다이나믹 메터리얼을 메시에 설정한다.
		meshComp->SetMaterial(0, dynamicMat);
	}


}

// Called every frame
void APlayerFlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// 사용자가 입력한 방향대로 이동하고 싶다.
	// P = P0 + VT
	
	direction.Normalize();			// 방향 단위벡터로 바꾸기

	// FVector dir = GetActorLocation() +  direction.Normalize() * moveSpeed * DeltaTime;
    // 위의 코드가 동작하지 않는 이유는 direction.Normalize()의 경우 반환 값이 없기 때문에 moveSpeed와 계산이 안된다.
    // 때문에 위에서 먼저 direction을 단위벡터로 변경한 다음 moveSpeed와 변경해줘야한다.

	// p = p0 + vt
	FVector dir = GetActorLocation() +  direction * moveSpeed * DeltaTime;
	// Sweep 파라미터를 통해 block 적용 움직임을 할 수 있다.
	SetActorLocation(dir,true);


}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// 기존의 UInputComponent* 변수를 UEnhancedInputComponent* 로 변환한다.
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	
	// EnhancedInput 바인딩
	// 함수 연결하기
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Triggered, this, &APlayerFlight::Horizontal);
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Completed, this, &APlayerFlight::Horizontal);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Triggered, this, &APlayerFlight::Vertical);
	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Completed, this, &APlayerFlight::Vertical);

	enhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Triggered, this, &APlayerFlight::FireBullet);

	enhancedInputComponent->BindAction(ia_ult, ETriggerEvent::Triggered, this, &APlayerFlight::ExplosionAll);

	// Started 파라미터를 설정하여 버튼 클릭 시작히 함수가 동작하도록 했다.
	enhancedInputComponent->BindAction(ia_boost, ETriggerEvent::Started, this, &APlayerFlight::AddBoost);
	
	// Completed 파라미터 설정을 통해 키버튼에서 손가락을 떼는 순간 함수가 동작 되도록 했다.
	enhancedInputComponent->BindAction(ia_boost, ETriggerEvent::Completed, this, &APlayerFlight::RemoveBoost);
	

	/*
	// 기존 입력 방식 바인딩
	// Horizontal Axis 입력에 함수를 연결한다.
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerFlight::Horizontal);


	// Vertical Axis 입력에 함수를 연결한다.
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::Vertical);


	// Fire Action 입력에 함수를 연결한다.
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerFlight::FireBullet);

	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &APlayerFlight::AddBoost);

	PlayerInputComponent->BindAction("Boost", IE_Released, this, &APlayerFlight::RemoveBoost);

	
	// Boost
	*/


}





void APlayerFlight::ReservationHitColor(float time)
{
	// 1. 색상을 Red 색깔로 변경한다.
	dynamicMat->SetVectorParameterValue(TEXT("myColor"), (FVector4)FLinearColor::Red);

	// 2. 원래 색상으로 되돌리는 함수를 바인딩한 타이머를 예약한다.


	// Timer의 경우 입력값이 없고 반환형이 없는 함수만 바인딩 가능하다.
	GetWorld()->GetTimerManager().SetTimer(colorTimer, this, &APlayerFlight::ChangeOriginColor, time, false);
}


void APlayerFlight::ChangeOriginColor()
{

	// 변수명을 파라미터에 넣어야함
	dynamicMat->SetVectorParameterValue(TEXT("myColor"), (FVector4)initColor);
}


/*
// 기존 입력방식 함수 주석처리
// 좌우 입력이 있을 때 실행될 함수
void APlayerFlight::Horizontal(float value) {
	h = value;
	//UE_LOG(LogTemp, Warning, TEXT("h : %.4f"), h);
	direction.Y = h;
}

// 상하 입력이 있을 때 실행될 함수
void APlayerFlight::Vertical(float value) {
	v = value;
	direction.Z = v;
	//UE_LOG(LogTemp, Warning, TEXT("v : %.4f"), v);
}
*/


// EnhancedInput 입력 함수.
void APlayerFlight::Horizontal(const FInputActionValue& value)
{
	//UE_LOG(LogTemp, Warning, TEXT("hori"));
	h = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("h : %.4f"), h);
	direction.Y = h;
}

void APlayerFlight::Vertical(const FInputActionValue& value)
{
	//UE_LOG(LogTemp, Warning, TEXT("ver"));
	v = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("v : %.4f"), v);
	direction.Z = v;
}





// 마우스 왼쪽 버튼을 눌렀을 때 실행될 함수.
void APlayerFlight::FireBullet()
{
	if (isFire) {
		AddBullet();
	}



	// 총알 발사 효과음을 실행한다.
	UGameplayStatics::PlaySound2D(this, fireSound);

}

void APlayerFlight::AddBullet()
{
	// 생성 위치 : 플레이어 위치 기준으로 플레이어 위에서
	FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 90.0f;
	
	
	// 발사 간격
	float interval = 0.5f * (bulletCount -1) * bulletSpacing;

	// 각도 (왼쪽 기준이기 때문에 -0.5f를 적용)
	float offset = -0.5f * (bulletCount - 1) * bulletAngle;

	FRotator rot = FRotator(0,offset,0);


	// 생성 방향 : 월드 축 기준이므로 pitch 방향이다 .(Roll , yaw 기준으로 말해야한다.)
	// 주의 사항 : pitch, yaw, roll 순이다. 에디터는 roll, pitch ,yaw 순이다.
	FRotator spawnRotation = FRotator(90.0f, 0, 0);


	// 어떤 상황에서든 생성시키기.
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 기준점 설정
	spawnPosition = FVector(spawnPosition.X, spawnPosition.Y - interval, spawnPosition.Z);



	for (int i = 0; i < bulletCount; i++) {
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation, param);

		// 기준점에서부터 오른쪽으로 간격만큼 더해준다.
		spawnPosition = FVector(spawnPosition.X, spawnPosition.Y + bulletSpacing, spawnPosition.Z);

		// 생성된 총알(Bullet)을 bulletAngle 만큼 일정하게 회전시킨다.
		bullet->AddActorLocalRotation(rot);
		offset += bulletAngle;
		rot = FRotator(0, offset, 0);

	}

}


// 궁극기 폭탄 함수
void APlayerFlight::ExplosionAll()
{


	/*
	// 1. TActorIteraotr 사용
	for (TActorIterator<AEnemy> it(GetWorld()); it; ++it) {
		it->DestroyMySelf();
		it->Destroy();
	}
	*/

	/*
	// 2. 배열 사용
	AGameModeBase* mode = UGameplayStatics::GetGameMode(this);
	AMyShootingGameModeBase* myGameMode = Cast<AMyShootingGameModeBase>(mode);

	myGameMode->RemoveEnemy();
	*/

	// 3. Delegate 실행한다.
	//playerBomb.Broadcast();   // 플레이어를 추적하는 Enemy 삭제
	OnSetDirection.Broadcast(FVector(0,1,0)); // 플레이어를 추적하는 Enemy 방향 바꾸기

}

void APlayerFlight::AddBoost()
{
	moveSpeed *= 2;


}

void APlayerFlight::RemoveBoost()
{
	// moveSpeed /= 2;
	moveSpeed *= 0.5f;			// 나눗셈 연산보다 곱셈 연산량이 더 적다.
}

