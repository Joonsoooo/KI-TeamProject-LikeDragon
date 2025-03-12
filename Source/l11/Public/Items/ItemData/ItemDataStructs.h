#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"
//정찬희
//아이템 등급
UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	OneStar UMETA(DisplayName = "One"),
	TwoStar UMETA(DisplayName = "Two"),
	ThreeStar UMETA(DisplayName = "Three"),
	FourStar UMETA(DisplayName = "Four"),
	FiveStar UMETA(DisplayName = "Five"),
	SixStar UMETA(DisplayName = "Six"),
	SevenStar UMETA(DisplayName = "Seven"),
	EightStar UMETA(DisplayName = "Eight"),
	NineStar UMETA(DisplayName = "Nine"),
	TenStar UMETA(DisplayName = "Ten")
};
//정찬희
//소비아이템인지 아닌지
UENUM(BlueprintType)
enum class EItemType : uint8
{
	ConsumeItem UMETA(DisplayName = "ConsumeItem"),
	NoneConsumeItem UMETA(DisplayName = "NoneConsumeItem")

};
//정찬희
//아이템 스텟
USTRUCT(BlueprintType)
struct FItemStatus
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere  , blueprintReadWrite)
	float RestorationAmount = 0.f;

	UPROPERTY(EditAnywhere , blueprintReadWrite)
	float SellValue = 0.0f;


};
//정찬희
//아이템 이름 , 설명
USTRUCT(BlueprintType)
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere , blueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere , blueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere , blueprintReadWrite)
	FText InteractionText;

	UPROPERTY(EditAnywhere , blueprintReadWrite)
	FText UsageText;
};

USTRUCT(BlueprintType)
struct FItemNumericData
{
	GENERATED_USTRUCT_BODY()

	int32 MaxStackSize;
	bool bIsStackable;
	
};
//정찬희
//아이템 이미지
USTRUCT(BlueprintType)
struct FItemAssetData 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere , blueprintReadWrite)
	UTexture2D* Icon = nullptr;
	

};

USTRUCT(BlueprintType)
struct FItemQuantity
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere , blueprintReadWrite)
	int32 MaxQuantity = 0;

	UPROPERTY(EditAnywhere   , blueprintReadWrite)
	bool bIsMaxQuantity = false;
	
};

//정찬희
//데이터테이블 형식 설정
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere   , BlueprintReadWrite , category = "ItemData")
	FName ItemID;
	
	UPROPERTY(EditAnywhere ,BlueprintReadWrite ,category = "ItemData")
	EItemType ItemType= EItemType::ConsumeItem;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite , category = "ItemData")
	EItemQuality ItemQuality = EItemQuality::OneStar;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite, category = "ItemData")
	FItemStatus ItemStatus;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite , category = "ItemData")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite , category = "ItemData")
	FItemNumericData ItemNumericData;
	
	UPROPERTY(EditAnywhere ,BlueprintReadWrite, category = "ItemData")
	FItemAssetData ItemAssetData;
	
	UPROPERTY(EditAnywhere ,BlueprintReadWrite, category = "ItemData")
	FItemQuantity ItemQuantity;

	

};
