/*
 *  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
 *
 *  This file is part of the mod.io UE4 Plugin.
 *
 *  Distributed under the MIT License. (See accompanying file LICENSE or
 *   view online at <https://github.com/modio/modio-ue4/blob/main/LICENSE>)
 *
 */

#pragma once

#include "Types/ModioFileMetadata.h"
#include "Types/ModioMetadata.h"
#include "Types/ModioModStats.h"
#include "Types/ModioModTag.h"
#include "Types/ModioURLList.h"
#include "Types/ModioUser.h"

#include "ModioModInfo.generated.h"

namespace Modio
{
	struct ModInfo;
}

/**
* Enumeration that represent mature content for the mod to create
**/
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EModioMaturityFlags : uint8
{
	/** No maturity **/
	None,

	/** Content contains alcohol references **/
	Alcohol = 1,

	/** Content contains drug references **/
	Drugs = 2,

	/** Content contains violence references **/
	Violence = 4,

	/** Content contains sexual references **/
	Explicit = 8
};

/** 
* Full mod profile including current release information, media links, and stats 
**/
USTRUCT(BlueprintType)
struct MODIO_API FModioModInfo
{
	GENERATED_BODY()

	/** @brief Unique Mod ID */
	UPROPERTY(BlueprintReadOnly, Category = "ModInfo")
	FModioModID ModId;

	/** @brief Name of the mod */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Profile")
	FString ProfileName;

	/** @brief Summary of the mod */
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	FString ProfileSummary;

	/** @brief Detailed description in HTML format */
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	FString ProfileDescription;

	/** @brief Detailed description in plaintext */
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	FString ProfileDescriptionPlaintext;

	/** @brief URL to the mod profile */
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	FString ProfileURL;

	/** @brief Information on the user who submitted the mod */
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	FModioUser ProfileSubmittedBy;

	/** @brief Unix timestamp of the date the mod was registered */
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	FDateTime ProfileDateAdded;

	/** @brief Unix timestamp of the date the mod was updated */
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	FDateTime ProfileDateUpdated;

	/** @brief Unix timestamp of the date the mod was marked live */
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	FDateTime ProfileDateLive;

	/**
	 * @brief Flags for maturity options
	 * Maturity options flagged by the mod developer, this is only relevant if the parent game allows mods to
	 * be labeled as mature.
	 **/
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	EModioMaturityFlags ProfileMaturityOption;

	/** @brief Is the mod marked as visible? */
	UPROPERTY(BlueprintReadOnly, Category = "Profile")
	bool bVisible;

	/**
	* Stored property to the metadata string
	**/
	UPROPERTY(BlueprintReadOnly, Category = "Metadata")
	FString MetadataBlob;

	/** @brief Information about the mod's most recent public release */
	UPROPERTY(BlueprintReadOnly, Category = "File")
	FModioFileMetadata FileInfo;

	/** @brief Arbitrary key-value metadata set for this mod */
	UPROPERTY(BlueprintReadOnly, Category = "Metadata")
	TArray<FModioMetadata> MetadataKvp;

	/** @brief Tags this mod has set */
	UPROPERTY(BlueprintReadOnly, Category = "Metadata")
	TArray<FModioModTag> Tags;

	/** @brief Number of images in the mod's media gallery */
	UPROPERTY(BlueprintReadOnly, Category = "Media")
	int32 NumGalleryImages;

	/** @brief List of youtube links provided by the creator of the mod */
	UPROPERTY(BlueprintReadOnly, Category = "Media")
	FModioYoutubeURLList YoutubeURLs;

	/** @brief List of sketchfab links provided by the creator of the mod */
	UPROPERTY(BlueprintReadOnly, Category = "Media")
	FModioSketchfabURLList SketchfabURLs;

	/** @brief Stats and rating information for the mod */
	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	FModioModStats Stats;

	friend struct FModioModInfo ToUnreal(const struct Modio::ModInfo& In);
};

/**
* Strong type struct to store an optional ModInfo parameter
**/
USTRUCT(BlueprintType)
struct MODIO_API FModioOptionalModInfo
{
	GENERATED_BODY()
	/**
	* Stored property to an optional ModInfo
	**/
	TOptional<FModioModInfo> Internal;
};
