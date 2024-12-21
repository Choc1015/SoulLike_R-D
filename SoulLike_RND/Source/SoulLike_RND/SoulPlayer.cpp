// Fill out your copyright notice in the Description page of Project Settings.

#include "SoulPlayer.h"
#include "Components/CapsuleComponent.h"
#include "UtilityFunctions.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASoulPlayer::ASoulPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();
	bIsMoving = false;
}

// Called when the game starts or when spawned
void ASoulPlayer::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

// Called every frame
void ASoulPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentRotation = MyMesh->GetRelativeRotation();
}

// Called to bind functionality to input
void ASoulPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASoulPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASoulPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &ASoulPlayer::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASoulPlayer::LookUp);

	// IE_Pressed, IE_Released 로 눌르고 떼는걸 체크합니다.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASoulPlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASoulPlayer::StopJump);
}

#pragma region 초기화

void ASoulPlayer::Initialize()
{
	MySpringArm = UtilityFunctions::GetComponentByClass<USpringArmComponent>(this);
	MyCamera = UtilityFunctions::GetComponentByClass<UCameraComponent>(this);
	MyMesh = UtilityFunctions::GetComponentByClass<UMeshComponent>(this);
}

#pragma endregion

#pragma region 이동 구현

void ASoulPlayer::MoveForward(float Value)
{
	if (!bIsMoving)
		bIsMoving = Value != 0.0f;

	if (bIsMoving)
	{
		FRotator MeshRotation = MyMesh->GetComponentRotation();
		FRotator ForwardRotation(0, -90, 0);
		FRotator BackRotation(0, 90, 0);
		FRotator TargetRotation;

		if (Value > 0)
		{
			TargetRotation = ForwardRotation; // 전진 (0도)
		}
		else if (Value < 0)
		{
			TargetRotation = BackRotation; // 후진 (180도)
		}

		MyMesh->SetWorldRotation(FMath::RInterpTo(MeshRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f));

		// AddMovementInput character 기본 지급 함수 forward x축
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ASoulPlayer::MoveRight(float Value)
{
	if (!bIsMoving)
		bIsMoving = Value != 0.0f;

	if (bIsMoving)
	{
		FRotator MeshRotation = MyMesh->GetComponentRotation();
		FRotator RightRotation(0, 0, 0);
		FRotator LeftRotation(0, 180, 0);
		FRotator TargetRotation;

		// 캐릭터 회전 처리
		if (Value > 0)
		{
			TargetRotation = RightRotation; // 오른쪽 이동 (45도)
		}
		else if (Value < 0)
		{
			TargetRotation = LeftRotation; // 왼쪽 이동 (-45도)
		}

		MyMesh->SetWorldRotation(FMath::RInterpTo(MeshRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f));

		// AddMovementInput character 기본 지급 함수 right y축
		AddMovementInput(GetActorRightVector(), Value);
	}
}

#pragma endregion

#pragma region 점프 구현

void ASoulPlayer::StartJump()
{
	bPressedJump = true;
}

void ASoulPlayer::StopJump()
{
	bPressedJump = false;
}

#pragma endregion

#pragma region 마우스 회전

void ASoulPlayer::Turn(float Value)
{

	if (bIsMoving)
	{
		AddControllerYawInput(Value); // 좌우 회전
		if (MySpringArm)
		{
			MySpringArm->bUsePawnControlRotation = true;
			MySpringArm->bInheritYaw = true;
		}
	}
	else
	{
		// 정지 상태에서는 스프링 암만 회전
		if (MySpringArm)
		{
			MySpringArm->bUsePawnControlRotation = false;
			MySpringArm->bInheritYaw = false;

			FRotator NewRotation = MySpringArm->GetComponentRotation();
			NewRotation.Yaw += Value;
			MySpringArm->SetWorldRotation(NewRotation);
		}
	}
}

void ASoulPlayer::LookUp(float Value)
{
	if (MySpringArm)
	{
		AddControllerPitchInput(Value); // 상하 회전
		FRotator NewRotation = MySpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + Value, -80, 80);
		MySpringArm->SetWorldRotation(NewRotation);
	}
}

#pragma endregion