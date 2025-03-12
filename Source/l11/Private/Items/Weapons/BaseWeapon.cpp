// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Utilities/BaseDebugHelper.h"
#include "Utilities/BaseFunctionLibrary.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment((RootComponent));
	WeaponCollisionBox->SetBoxExtent(FVector(20.0f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//김동휘, Overlap Connect, 이준수, OnComponentBeginOverlap 는 델리게이트 변수임 
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

void ABaseWeapon::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//김동휘, GetInstigator 이벤트를 발생시킨 포인터 누가 데미지를 입혔는가 T 클래스 반환 (주체대상)
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forget to Assign an instigator as the owning pawn of the weapon: %s"), *GetName());

	/*if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (WeaponOwningPawn != HitPawn)
		{
			Debug::Print(GetName() + TEXT(" Begin overlap with ") + HitPawn->GetName(), FColor::Green);
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
	}*/
	
	//김동휘, 피아식별 부분 변경
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UBaseFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			//Debug::Print(GetName() + TEXT(" Begin overlap with ") + HitPawn->GetName(), FColor::Green);
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
			OnCollisionBoxHitLinetrace(OtherActor);
		}
	}
}



void ABaseWeapon::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//김동휘, GetInstigator 이벤트를 발생시킨 포인터 누가 데미지를 입혔는가 T 클래스 반환 (주체대상)
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forget to Assign an instigator as the owning pawn of the weapon: %s"), *GetName());

	/*if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (WeaponOwningPawn != HitPawn)
		{
			Debug::Print(GetName() + TEXT(" End overlap with ") + HitPawn->GetName(), FColor::Green);
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}*/
	
	//김동휘, 피아식별 부분 변경
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UBaseFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			//Debug::Print(GetName() + TEXT(" End overlap with ") + HitPawn->GetName(), FColor::Green);
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void ABaseWeapon::OnCollisionBoxHitLinetrace(AActor* OtherActor)
{
	// 박스 시작과 끝 위치
	FVector Start = WeaponCollisionBox->GetComponentLocation(); // 박스 시작 위치 (월드 좌표)
	FVector End = Start + WeaponCollisionBox->GetForwardVector() * 10.0f; // 박스를 전진시킨 끝 위치

	// 박스의 크기
	FVector BoxExtent = WeaponCollisionBox->GetScaledBoxExtent(); // 스케일 포함

	// 박스의 로컬 회전
	FRotator BoxRotation = WeaponCollisionBox->GetComponentRotation();

	// 충돌 검사
	TArray<FHitResult> HitResults;
	TSet<AActor*> UniqueActors; // 중복 제거용 TSet
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // 자기 자신 무시

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		BoxRotation.Quaternion(), // 박스의 회전
		ECC_Pawn,                 // 충돌 채널
		FCollisionShape::MakeBox(BoxExtent), // 박스 크기
		QueryParams
	);

	// 디버그 박스 시각화
	//DrawDebugBox(GetWorld(), Start, BoxExtent, BoxRotation.Quaternion(), FColor::Blue, false, 2.0f);
	//DrawDebugBox(GetWorld(), End, BoxExtent, BoxRotation.Quaternion(), FColor::Green, false, 2.0f);

	// 충돌 결과 처리
	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("bHit: SweepMulti detected hits."));

		for (const FHitResult& HitResult : HitResults)
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor && !UniqueActors.Contains(HitActor))
			{
				UniqueActors.Add(HitActor); // 중복 제거

				// 디버그 충돌 지점 표시
				//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 12, FColor::Red, false, 2.0f);

				// 액터 처리
				//UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitActor->GetName());

				// Delegate 실행
				OnTargetHitResult.ExecuteIfBound(HitResult);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("bHit: No hits detected."));
	}
}



