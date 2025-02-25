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

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/ModioCommonTypes.h"
#include "Types/ModioCreateModFileParams.h"
#include "Types/ModioCreateModParams.h"

#include "ModioCreateModLibrary.generated.h"

/**
 *
 */
UCLASS()
class MODIO_API UModioCreateModLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod Params")
	static void SetInitialVisibility(UPARAM(ref) FModioCreateModParams& In, bool InitialVisibility);

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod Params")
	static void SetDescription(UPARAM(ref) FModioCreateModParams& In, FString Description);

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod Params")
	static void SetHomepageURL(UPARAM(ref) FModioCreateModParams& In, FString HomepageURL);

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod Params")
	static void SetMetadataBlob(UPARAM(ref) FModioCreateModParams& In, FString MetadataBlob);

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod Params")
	static void SetTags(UPARAM(ref) FModioCreateModParams& In, UPARAM(ref) TArray<FString>& Tags);

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod File Params")
	static void SetVersionString(UPARAM(ref) FModioCreateModFileParams& In, FString Version);

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod File Params")
	static void SetChangelogString(UPARAM(ref) FModioCreateModFileParams& In, FString Changelog);

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod File Params")
	static void SetMarkAsActiveRelease(UPARAM(ref) FModioCreateModFileParams& In, bool bMarkAsActiveRelease);

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod File Params")
	static void SetModFileMetadataBlob(UPARAM(ref) FModioCreateModFileParams& In, FString MetadataBlob);

	UFUNCTION(BlueprintCallable, Category = "mod.io|Create Mod File Params")
	static void SetModfilePlatforms(UPARAM(ref) FModioCreateModFileParams& In,
							 UPARAM(ref) TArray<EModioModfilePlatform>& Platforms);
};
