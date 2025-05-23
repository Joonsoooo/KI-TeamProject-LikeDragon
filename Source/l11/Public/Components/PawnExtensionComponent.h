// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class L11_API UPawnExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	//김동휘, T는 제너릭 타입 T는 인스턴스를 생성할때 구체적인 타입이 정해진다, (T가 APawn의 자식 클래스라면 캐스팅이 가능)
	template<class T>
	T* GetOwningPawn() const
	{
		//김동휘, 컴파일에서 에러가 발생하면 해당 텍스트표시 T에 파라미터는 APawn에서 파생되어야 한다.
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter get GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template<class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter get GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}

	AController* GetOwningController() const
	{
		return GetOwningController<AController>();
	}
};
