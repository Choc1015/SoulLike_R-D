// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SOULLIKE_RND_API UtilityFunctions
{
public:
	UtilityFunctions();
	~UtilityFunctions();



// 템플릿 함수 정의
template <typename T>
static T *GetComponentByClass(UObject *Object)
{
    if (!Object)
    {
        UE_LOG(LogTemp, Warning, TEXT("오브젝트가 존재하지 않습니다! Null"));
        return nullptr;
    }

    // AActor인지 확인 후, 컴포넌트 검색하기.
    AActor *Actor = Cast<AActor>(Object);

    if (Actor)
    {
        T *Component = Actor->FindComponentByClass<T>();
        FString ComponentName = Component->GetName();
        if (Component)
        {
            UE_LOG(LogTemp, Log, TEXT("%s found: %s"), *ComponentName, *ComponentName);
            return Component;

        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("%s not found!"), *ComponentName);
        }

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("이 오브젝트는 액터가 아닙니다!"));
    }

    return nullptr;
}

};
