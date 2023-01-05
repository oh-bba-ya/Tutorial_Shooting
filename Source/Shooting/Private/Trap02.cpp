// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap02.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerFlight.h"

// Sets default values
ATrap02::ATrap02()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 3. USphereComponent로 루트 콜리전을 생성
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	//SetRootComponent(sComp);
	RootComponent = sphereComp;

	// 4. UStaticMesh를 루트의 자식 컴포넌트로 생성
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));


}

// Called when the game starts or when spawned
void ATrap02::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ATrap02::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void InTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	APlayerFlight* player = Cast<APlayerFlight>(OtherActor);

	if (player != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player Collision"));
		//player.isFire
	}
}

