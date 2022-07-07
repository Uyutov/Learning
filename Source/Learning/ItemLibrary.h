// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemLibrary.generated.h"

UENUM()
enum class EArmorType : uint8
{

	NONE UMETA(DisplayName = "No armor type"),
	TORSO UMETA(DisplayName = "Armor on cheast"),
	LEGS UMETA(DisplayName = "Armor on legs"),
	HEAD UMETA(DisplayName = "Helmet"),
	FOOT UMETA(DisplayName = "Boots"),
	PLUS UMETA(DisplayName = "Test")

};

UENUM()
enum class EItemType : uint8
{

	NONE UMETA(DisplayName = "No item type"),
	ITEM UMETA(DisplayName = "Simple item"),
	ARMOR UMETA(DisplayName = "Item with armor type"),
	CONSUMABLE UMETA(DisplayName = "Consumable type of item")

};

UENUM()
enum class EItemsVariety : uint8
{

	NONE UMETA(DisplayName = "Missn item"),
	COIN UMETA(DisplayName = "Coin"),
	APPLE UMETA(DisplayName = "Apple"),
	LEATHER_BOOTS UMETA(DisplayName = "LeatherBoots")

};

UCLASS(BlueprintType)
class UItemInformation : public UObject
{

	GENERATED_BODY()

public:

	UPROPERTY()
		EItemType ItemType = EItemType::ITEM;
	UPROPERTY(EditAnywhere)
		EItemsVariety ItemVariation;
	UPROPERTY(EditAnywhere)
		int32 Coast;
	UPROPERTY(EditAnywhere)
		int32 Ammount;
	UPROPERTY(EditAnywhere)
		int32 MaxAmmount;
	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		float Weight;
	UPROPERTY(EditAnywhere)
		UTexture2D* Image;
	UPROPERTY(EditAnywhere)
		UStaticMesh* Mesh;
	
	UFUNCTION()
		virtual void Copy(UItemInformation* OtherItem);
	UFUNCTION()
		virtual UItemInformation* CreateDeepCopy();
};

UCLASS(BlueprintType)
class UArmorInfo : public UItemInformation
{

	GENERATED_BODY()

public:

	UArmorInfo();
	
	UPROPERTY(EditAnywhere)
		int32 Armor;
	UPROPERTY(EditAnywhere)
		EArmorType ArmorType;

	virtual void Copy(UItemInformation* OtherItem) override;
	virtual UItemInformation* CreateDeepCopy() override;
};

UCLASS(BlueprintType)
class UConsumablesInfo : public UItemInformation
{

	GENERATED_BODY()

public:

	UConsumablesInfo();
	
	UPROPERTY(EditAnywhere)
		float Duration;
	UPROPERTY(EditAnywhere)
		float Rate;
	
	virtual void Copy(UItemInformation* OtherItem) override;
	virtual UItemInformation* CreateDeepCopy() override;

};

USTRUCT(BlueprintType)
struct FArmorInfoStruct
{

	GENERATED_USTRUCT_BODY()

		FArmorInfoStruct()
	{
		ItemType = EItemType::ARMOR;
	}

	UPROPERTY()
		EItemType ItemType;
	UPROPERTY(EditAnywhere)
		EItemsVariety ItemVariation;
	UPROPERTY(EditAnywhere)
		int32 Coast;
	UPROPERTY(EditAnywhere)
		int32 Ammount;
	UPROPERTY(EditAnywhere)
		int32 MaxAmmount;
	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		float Weight;
	UPROPERTY(EditAnywhere)
		UTexture2D* Image;
	UPROPERTY(EditAnywhere)
		UStaticMesh* Mesh;
	// Exclusive to armor info
	UPROPERTY(EditAnywhere)
		int32 Armor;
	UPROPERTY(EditAnywhere)
		EArmorType ArmorType;


};

USTRUCT(BlueprintType)
struct FConsumablesInfoStruct
{

	GENERATED_USTRUCT_BODY()

		FConsumablesInfoStruct()
	{
		ItemType = EItemType::CONSUMABLE;
	}

	UPROPERTY(EditAnywhere)
		EItemType ItemType;
	UPROPERTY(EditAnywhere)
		EItemsVariety ItemVariation;
	UPROPERTY(EditAnywhere)
		int32 Coast;
	UPROPERTY(EditAnywhere)
		int32 Ammount;
	UPROPERTY(EditAnywhere)
		int32 MaxAmmount;
	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		float Weight;
	UPROPERTY(EditAnywhere)
		UTexture2D* Image;
	UPROPERTY(EditAnywhere)
		UStaticMesh* Mesh;
	// Exclusive to consumables info
	UPROPERTY(EditAnywhere)
		float Duration;
	UPROPERTY(EditAnywhere)
		float Rate;

};

USTRUCT(BlueprintType)
struct FItemInfoStruct
{

	GENERATED_USTRUCT_BODY()

		FItemInfoStruct()
	{
		ItemType = EItemType::ITEM;
	}

	UPROPERTY()
		EItemType ItemType;
	UPROPERTY(EditAnywhere)
		EItemsVariety ItemVariation;
	UPROPERTY(EditAnywhere)
		int32 Coast;
	UPROPERTY(EditAnywhere)
		int32 Ammount;
	UPROPERTY(EditAnywhere)
		int32 MaxAmmount;
	UPROPERTY(EditAnywhere)
		FString Name;
	UPROPERTY(EditAnywhere)
		float Weight;
	UPROPERTY(EditAnywhere)
		UTexture2D* Image;
	UPROPERTY(EditAnywhere)
		UStaticMesh* Mesh;
	
};

DECLARE_MULTICAST_DELEGATE_OneParam(ChangeAllItems, TArray<FItemInfoStruct>)
UCLASS()
class LEARNING_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FItemInfoStruct> ItemInfoArray;
	
	ChangeAllItems ChangeAll;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

};

DECLARE_MULTICAST_DELEGATE_OneParam(ChangeAllArmor, TArray<FArmorInfoStruct>)
UCLASS()
class LEARNING_API UArmorDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FArmorInfoStruct> ArmorInfoArray;
	
	ChangeAllArmor ChangeAll;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};

DECLARE_MULTICAST_DELEGATE_OneParam(ChangeAllConsumables, TArray<FConsumablesInfoStruct>)
UCLASS()
class LEARNING_API UConsumablesDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FConsumablesInfoStruct> ConsumableInfoArray;

	ChangeAllConsumables ChangeAll;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};