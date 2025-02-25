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

#include "Types/ModioCommonTypes.h"

#include "ModioUser.generated.h"


namespace Modio
{
	struct User;
}

/** 
* Object representing a mod.io user profile information
**/
USTRUCT(BlueprintType)
struct MODIO_API FModioUser
{
	GENERATED_BODY()

	FModioUser() = default;
	FModioUser(const Modio::User& User);

	/** 
	* User's unique ID
	**/
	UPROPERTY(BlueprintReadOnly,Category="User")
	FModioUserID UserId;

	/** 
	* Name chosen by the user 
	**/
	UPROPERTY(BlueprintReadOnly,Category="User")
	FString Username;

	/** 
	* Unix timestamp the last time the  user was online 
	**/
	UPROPERTY(BlueprintReadOnly,Category="User")
	FDateTime DateOnline;

	/** 
	* URL of the user's mod.io profile 
	**/
	UPROPERTY(BlueprintReadOnly,Category="User")
	FString ProfileUrl;
};

/**
* Struct wrapper for an optional ModioUser
**/
USTRUCT(BlueprintType)
struct MODIO_API FModioOptionalUser
{
	GENERATED_BODY()
	
	/**
	* Stored optional ModioUser
	**/
	TOptional<FModioUser> Internal;
};