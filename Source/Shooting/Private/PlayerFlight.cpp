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

	// ������ �̺�Ʈ�� �Ҵ�.
	boxComp->SetGenerateOverlapEvents(true);

	// �浹 ������ Query And Physics�� �����Ѵ�.
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Object Type�� 1�� ä�η�(Player)�� �����Ѵ�.
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel1);

	// ��� ä���� �浹 ���� �������� �����Ѵ�.
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Enemy�ʹ� �浹 �̺�Ʈ üũ(Quary)�� �Ѵ�.
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);




}

// Called when the game starts or when spawned
void APlayerFlight::BeginPlay()
{
	Super::BeginPlay();

	// �÷��̾� ��Ʈ�ѷ��� ĳ�����Ѵ�.
	APlayerController* playerCon = Cast<APlayerController>(GetController());

	// nullPtr üũ
	if (playerCon != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("ptr"));
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());
		
		if (subsys != nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("ptr2"));
			subsys->AddMappingContext(imc_myMapping, 0);
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Nullptr"));
	}

	// ���� ���� ���� �����Ѵ�
	UMaterialInterface* iMat = meshComp->GetMaterial(0);
	FHashedMaterialParameterInfo param = FHashedMaterialParameterInfo(TEXT("myColor"));		// TEXT : �̸��� ��� ������ ���׸��� ���� Ŭ�� �� Global Vector Parameter Values ���� ���ϴ°Ŵ�.
	
	// Material Interface���� ���� �Ķ���� ���� initColor ������ �����Ѵ�.
	iMat->GetVectorParameterValue(param, initColor);

	// ��� Ȯ��
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), initColor.R, initColor.G, initColor.B);


	// Material Interface�� �̿��ؼ� Material Instance Dynamic ��ü�� �����.
	dynamicMat = UMaterialInstanceDynamic::Create(iMat, this);

	if (dynamicMat != nullptr) {
		// ������ ���̳��� ���͸����� �޽ÿ� �����Ѵ�.
		meshComp->SetMaterial(0, dynamicMat);
	}


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
	// Sweep �Ķ���͸� ���� block ���� �������� �� �� �ִ�.
	SetActorLocation(dir,true);


}

// Called to bind functionality to input
void APlayerFlight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	// ������ UInputComponent* ������ UEnhancedInputComponent* �� ��ȯ�Ѵ�.
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	/*
	// EnhancedInput ���ε�
	// �Լ� �����ϱ�
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Triggered, this, &APlayerFlight::Horizontal);
	enhancedInputComponent->BindAction(ia_horizontal, ETriggerEvent::Completed, this, &APlayerFlight::Horizontal);

	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Triggered, this, &APlayerFlight::Vertical);
	enhancedInputComponent->BindAction(ia_vertical, ETriggerEvent::Completed, this, &APlayerFlight::Vertical);

	enhancedInputComponent->BindAction(ia_fire, ETriggerEvent::Triggered, this, &APlayerFlight::FireBullet);
	*/

	
	// ���� �Է� ��� ���ε�
	// Horizontal Axis �Է¿� �Լ��� �����Ѵ�.
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerFlight::Horizontal);


	// Vertical Axis �Է¿� �Լ��� �����Ѵ�.
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerFlight::Vertical);


	// Fire Action �Է¿� �Լ��� �����Ѵ�.
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerFlight::FireBullet);
	


}


void APlayerFlight::ReservationHitColor(float time)
{
	// 1. ������ Red ����� �����Ѵ�.
	dynamicMat->SetVectorParameterValue(TEXT("myColor"), (FVector4)FLinearColor::Red);

	// 2. ���� �������� �ǵ����� �Լ��� ���ε��� Ÿ�̸Ӹ� �����Ѵ�.


	// Timer�� ��� �Է°��� ���� ��ȯ���� ���� �Լ��� ���ε� �����ϴ�.
	GetWorld()->GetTimerManager().SetTimer(colorTimer, this, &APlayerFlight::ChangeOriginColor, time, false);
}


void APlayerFlight::ChangeOriginColor()
{

	// �������� �Ķ���Ϳ� �־����
	dynamicMat->SetVectorParameterValue(TEXT("myColor"), (FVector4)initColor);
}



// ���� �Է¹�� �Լ� �ּ�ó��
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


/*
// EnhancedInput �Է� �Լ�.
void APlayerFlight::Horizontal(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("hori"));
	h = value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("h : %.4f"), h);
	direction.Y = h;
}

void APlayerFlight::Vertical(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("ver"));
	v = value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("v : %.4f"), v);
	direction.Z = v;
}
*/




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

	// �Ѿ� �߻� ȿ������ �����Ѵ�.
	UGameplayStatics::PlaySound2D(this, fireSound);



}


