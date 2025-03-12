#pragma once

// 이준수, 손 동작에 따른 열거형 
UENUM(BlueprintType)
enum class EHandParts : uint8
{
    Neutral UMETA(DisplayName = "Neutral"),
    Gu UMETA(DisplayName = "Gu"),
    Katana UMETA(DisplayName = "Katana"),
    Hako UMETA(DisplayName = "Hako"),
    Taiken UMETA(DisplayName = "Taiken"),
    Bou UMETA(DisplayName = "Bou"),
    Shotgun UMETA(DisplayName = "Shotgun"),
    Gun UMETA(DisplayName = "Gun"),
    Tonfa UMETA(DisplayName = "Tonfa"),
    HandMax UMETA(DisplayName = "Hand Max"),
    HandMiddle UMETA(DisplayName = "Hand Middle"),
    HandMin UMETA(DisplayName = "Hand Min"),
    HandTabaco UMETA(DisplayName = "Hand Tabaco"),
    None UMETA(DisplayName = "None"),
};

UENUM()
enum class EBaseConfirmType : uint8
{
    Yes,
    No,
};

UENUM()
enum class EBaseValidType : uint8
{
    Valid,
    Invalid,
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    None = 0 UMETA(DisplayName = "None"),
    Brawler UMETA(DisplayName = "Brawler"),
    Katana UMETA(DisplayName = "Katana"),
    Gun UMETA(DisplayName = "Gun"),
    WildDancer UMETA(DisplayName = "WildDancer"),
};

UENUM()
enum class EBaseSuccessType : uint8
{
    Success,
    Failed,
};