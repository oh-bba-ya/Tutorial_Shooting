// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlight.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Bullet.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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

	// 메시 컴포넌트의 Static Mesh 항목에 큐브 파일을 할당한다.
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	// 만약, 큐브 파일을 로드하는데 성공했다면..
	if (cubeMesh.Succeeded()) {
		// 로드한 파일을 메시 컴포넌트의 static mesh 항목에 넣는다.
		meshComp->SetStaticMesh(cubeMesh.Object);
	}




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
	SetActorLocation(dir);


}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*
	* 기존 입력 방식 바인딩 해제
	// Horizontal Axis 입력에 함수를 연결한다.
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerFlight::Horizontal);


	// Vertical Axis 입력에 함수를 연결한다.
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::Vertical);


	// Fire Action 입력에 함수를 연결한다.
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerFlight::FireBullet);
	*/


	// 기존의 UInputComponent* 변수를 UEnhancedInputComponent* 로 변환한다.
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	// 함수 연결하기
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Triggered, this, &APlayerFlight::Horizontal);
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Completed, this, &APlayerFlight::Horizontal);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Triggered, this, &APlayerFlight::Vertical);
	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Completed, this, &APlayerFlight::Vertical);

	enhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Triggered, this, &APlayerFlight::FireBullet);

}


/*
* 기존 입력방식 함수 주석처리
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


void APlayerFlight::Horizontal(const FInputActionValue& value)
{
	h = value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("h : %.4f"), h);
	direction.Y = h;
}

void APlayerFlight::Vertical(const FInputActionValue& value)
{
	v = value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("v : %.4f"), v);
	direction.Z = v
}




// 마우스 왼쪽 버튼을 눌렀을 때 실행될 함수.
void APlayerFlight::FireBullet()
{
	
	// 생성 위치 : 플레이어 위치 기준으로 플레이어 위에서
	FVector spawnPosition = GetActorLocation() + GetActorUpVector() *90.0f;

	// 생성 방향 : 월드 축 기준이므로 pitch 방향이다 .(Roll , yaw 기준으로 말해야한다.)
	// 주의 사항 : pitch, yaw, roll 순이다. 에디터는 roll, pitch ,yaw 순이다.
	FRotator spawnRotation = FRotator(90.0f, 0, 0);

	// 어떤 상황에서든 생성시키기.
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// 총알을 생성한다.
	// 총알 블루프린트 변수
	GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation,param);

}
