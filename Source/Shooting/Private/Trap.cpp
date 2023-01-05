// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerFlight.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	// 3. USphereComponent�� ��Ʈ �ݸ����� ����
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(sphereComp);
	
	sphereComp->SetSphereRadius(200);
	
	// 4. UStaticMesh�� ��Ʈ�� �ڽ� ������Ʈ�� ����
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);

	sphereComp->SetCollisionProfileName("TrapPreset");

}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("tRAP"));

	// 7.  Overlap ��������Ʈ InTrap �Լ��� ����
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATrap::InTrap);

	// Endoverlap ��������Ʈ�� outTrap �Լ��� �����Ѵ�.
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &ATrap::OutTrap);
	
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���� ���� �ð�(Current Time)��.. ������ �ð�(Teleport Time)�� �����ߴٸ�..
	if (currentTime >= teleportTime) {
		// ���� ��ġ(����)�� �����Ѵ�.
		float y = FMath::RandRange(-300, 300);
		float z = FMath::RandRange(-300, 300);

		// ���� ��ġ(����)�� �����Ѵ�.
		FVector pos = { 0,y,z };

		// ���� ���͸� �޾ƺ��� 
		// -1 ~ 1 ������ �������ͷ� �޴´�.
		FVector randVector = FMath::VRand() * 500.0f;
		randVector.X = 0;

		// �� ��ġ�� �̵��Ѵ�.
		SetActorLocation(pos);

		// �ð� �ʱ�ȭ(Current Time)
		currentTime = 0;

	}
	else {
		currentTime += DeltaTime;
	}

}

// 6. "InTrap" �Լ� ����
void ATrap::InTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);
	

	if (player != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player Collision"));
		player->isFire = false;
	}

}

void ATrap::OutTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// ���� ������ ������ �ε��� ���Ͱ� �÷��̾���
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	if (player != nullptr) {
		// �÷��̾��� canFire ������ ���� true�� �����Ѵ�.
		player->isFire = true;
	}
}
