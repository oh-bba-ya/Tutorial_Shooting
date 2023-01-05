// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerFlight.h"
#include "Enemy.h"


// Sets default values
AShieldActor::AShieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("box collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50, 150, 50));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(1.0f, 1.0f, 1.0f));

	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AShieldActor::BeginPlay()
{
	Super::BeginPlay();
	

	// 충돌시 실행할 함수 바인딩
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AShieldActor::ShieldOverlapped);

}

// Called every frame
void AShieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator rot = FRotator(0, 0, 1);
	SetActorRotation(GetActorRotation() + rot);

}

void AShieldActor::ResetAttach()
{
	// 붙여놨던 부모를 해제한다.
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void AShieldActor::ShieldOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	// 부딪힌 대상이 플레이어 라면
	if (player != nullptr) {
		// 플레이어에게 부착
		this->AttachToActor(player, FAttachmentTransformRules::KeepRelativeTransform);

		FTimerHandle snapTimer;
		GetWorld()->GetTimerManager().SetTimer(snapTimer, this, &AShieldActor::ResetAttach, 2.0f, false);
	
	}	
	
	// 부딪힌 대상이 에너미라면
	if (enemy != nullptr) {
		// 충돌한 에너미를 파괴한다.
		enemy->Destroy();
		
	}

	
}

