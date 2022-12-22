// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlight.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Bullet.h"

// Sets default values
APlayerFlight::APlayerFlight()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �浹 �ڽ� ������Ʈ�� �����Ѵ�.
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	// ������ �浹 �ڽ� ������Ʈ�� ��Ʈ ������Ʈ�� �����Ѵ�.
	SetRootComponent(boxComp);

	// ������ �浹 �ڽ� size�� �����Ѵ�.
	FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
	boxComp->SetBoxExtent(boxSize);


	// ����ƽ �޽� ������Ʈ ����
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	// ��Ʈ ������Ʈ�� �ڽ� ������Ʈ�� ����
	meshComp->SetupAttachment(RootComponent);

	// �޽� ������Ʈ�� Static Mesh �׸� ť�� ������ �Ҵ��Ѵ�.
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	// ����, ť�� ������ �ε��ϴµ� �����ߴٸ�..
	if (cubeMesh.Succeeded()) {
		// �ε��� ������ �޽� ������Ʈ�� static mesh �׸� �ִ´�.
		meshComp->SetStaticMesh(cubeMesh.Object);
	}




}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerFlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// ����ڰ� �Է��� ������ �̵��ϰ� �ʹ�.
	// P = P0 + VT
	
	direction.Normalize();			// ���� �������ͷ� �ٲٱ�

	// FVector dir = GetActorLocation() +  direction.Normalize() * moveSpeed * DeltaTime;
    // ���� �ڵ尡 �������� �ʴ� ������ direction.Normalize()�� ��� ��ȯ ���� ���� ������ moveSpeed�� ����� �ȵȴ�.
    // ������ ������ ���� direction�� �������ͷ� ������ ���� moveSpeed�� ����������Ѵ�.

	// p = p0 + vt
	FVector dir = GetActorLocation() +  direction * moveSpeed * DeltaTime;
	SetActorLocation(dir);


}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Horizontal Axis �Է¿� �Լ��� �����Ѵ�.
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerFlight::Horizontal);


	// Vertical Axis �Է¿� �Լ��� �����Ѵ�.
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::Vertical);


	// Fire Action �Է¿� �Լ��� �����Ѵ�.
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerFlight::FireBullet);



}


// �¿� �Է��� ���� �� ����� �Լ�
void APlayerFlight::Horizontal(float value) {
	h = value;
	//UE_LOG(LogTemp, Warning, TEXT("h : %.4f"), h);
	direction.Y = h;
}


// ���� �Է��� ���� �� ����� �Լ�
void APlayerFlight::Vertical(float value) {
	v = value;
	direction.Z = v;
	//UE_LOG(LogTemp, Warning, TEXT("v : %.4f"), v);
}

// ���콺 ���� ��ư�� ������ �� ����� �Լ�.
void APlayerFlight::FireBullet()
{
	
	// ���� ��ġ : �÷��̾� ��ġ �������� �÷��̾� ������
	FVector spawnPosition = GetActorLocation() + GetActorUpVector() *90.0f;

	// ���� ���� : ���� �� �����̹Ƿ� pitch �����̴� .(Roll , yaw �������� ���ؾ��Ѵ�.)
	// ���� ���� : pitch, yaw, roll ���̴�. �����ʹ� roll, pitch ,yaw ���̴�.
	FRotator spawnRotation = FRotator(90.0f, 0, 0);

	// � ��Ȳ������ ������Ű��.
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// �Ѿ��� �����Ѵ�.
	// �Ѿ� �������Ʈ ����
	GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotation,param);

}
