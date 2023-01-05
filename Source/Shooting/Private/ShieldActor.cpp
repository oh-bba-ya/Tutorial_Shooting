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
	

	// �浹�� ������ �Լ� ���ε�
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
	// �ٿ����� �θ� �����Ѵ�.
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void AShieldActor::ShieldOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	// �ε��� ����� �÷��̾� ���
	if (player != nullptr) {
		// �÷��̾�� ����
		this->AttachToActor(player, FAttachmentTransformRules::KeepRelativeTransform);

		FTimerHandle snapTimer;
		GetWorld()->GetTimerManager().SetTimer(snapTimer, this, &AShieldActor::ResetAttach, 2.0f, false);
	
	}	
	
	// �ε��� ����� ���ʹ̶��
	if (enemy != nullptr) {
		// �浹�� ���ʹ̸� �ı��Ѵ�.
		enemy->Destroy();
		
	}

	
}

