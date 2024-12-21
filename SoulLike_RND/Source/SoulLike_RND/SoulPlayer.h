// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SoulPlayer.generated.h"

UCLASS()
class SOULLIKE_RND_API ASoulPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoulPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void Initialize();

private:
	//================================FUNCTION======================================

	// 이동 함수 , Value라고 쓰는 이유는 읽기 편하기 위해 그리고 값이 -1,1 사이에 있기에
	void MoveForward(float Value);
	void MoveRight(float Value);

	// 점프 , 점프가 분리되어 있는 이유는 언리얼에서 bPressedJump라는 플래그 사용으로 점프의 시작과 중지관리도 있다..
	void StartJump();
	void StopJump();

	void Turn(float Value);
	void LookUp(float Value);

	//================================VAR===========================================

	UPROPERTY()
	class USpringArmComponent *MySpringArm;

	UPROPERTY()
	class UCameraComponent *MyCamera;

	UPROPERTY()
	class UMeshComponent *MyMesh;

	UPROPERTY(VisibleAnyWhere)
	FRotator CurrentRotation;

	bool bIsMoving;
};
