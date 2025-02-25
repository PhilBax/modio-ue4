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

#include "Components/Widget.h"
#include "Delegates/Delegate.h"
#include "IModioModInfoUIDetails.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/ModioErrorCode.h"
#include "UObject/Interface.h"

#include "IModioUINotification.generated.h"

/**
* Strong type struct to store the notification parameters
**/
USTRUCT(BlueprintType)
struct MODIOUI_API FModioNotificationParams
{
	GENERATED_BODY()

	/**
	* Key-value pair dictionary typedef to give format to the notification
	**/
	FFormatNamedArguments FormatArgs;

	/**
	* Key-value pair dictionary to store the name and format of the notification
	**/
	TMap<FName, FText> NamedTextFormats;

	/**
	* Error code stored in the notification
	**/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Notification")
	FModioErrorCode ErrorCode;

	/**
	* Stored reference UObject
	**/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Notification")
	UObject* NotificationContextObject = nullptr;

	/**
	* How long the notification shoud be visible
	**/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Notification")
	float Duration = 1;
};

/**
* Class factory to create notification parameters with different parameters
**/
UCLASS(BlueprintType)
class UModioNotificationParamsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Create a notification parameters instance using an error code and text labels
	* @param StatusCode The modio error code to store
	* @param SuccessText The string to display when a successful result happen
	* @param ErrorText The string to display when an error occur
	* @return FModioNotificationParams instance
	**/
	UFUNCTION(BlueprintCallable, Category = "ModioNotificationParams")
	static FModioNotificationParams CreateErrorNotificationParams(FModioErrorCode StatusCode, const FText& SuccessText,
																  const FText& ErrorText);
	/**
	* Create a notification parameters instance using an error code and a mod info details
	* @param StatusCode The modio error code to store
	* @param ModInfo A class interface related to ModInfoUIDetails
	* @return FModioNotificationParams instance
	**/
	UFUNCTION(BlueprintCallable, Category = "ModioNotificationParams")
	static FModioNotificationParams CreateRatingNotification(FModioErrorCode StatusCode,
															 const TScriptInterface<IModioModInfoUIDetails>& ModInfo);
	
	/**
	* Create a notification parameters instance using an error code
	* @param StatusCode The modio error code to store
	* @return FModioNotificationParams instance
	**/
	UFUNCTION(BlueprintCallable, Category = "ModioNotificationParams")
	static FModioNotificationParams CreateSubscriptionNotification(FModioErrorCode StatusCode);

	/**
	* Add format text to the notification parameter
	* @param NotificationParams Base class to add the format
	* @param Name The assigned format name
	* @param Text The value of the format 
	* @return Updated ModioNotificationParams instance 
	**/
	UFUNCTION(BlueprintCallable, Category = "ModioNotificationParams")
	static FModioNotificationParams& AddFormatText(UPARAM(ref) FModioNotificationParams& NotificationParams,
												   const FName& Name, const FText& Text)
	{
		NotificationParams.NamedTextFormats.Add(Name, Text);
		return NotificationParams;
	}
	
	/**
	* Add text argument to the notification parameter
	* @param NotificationParams Base class to add a new argument
	* @param Name The assigned name
	* @param Text The value associated to the name above
	* @return Updated ModioNotificationParams instance 
	**/
	UFUNCTION(BlueprintCallable, Category = "ModioNotificationParams")
	static FModioNotificationParams& SetTextArg(UPARAM(ref) FModioNotificationParams& NotificationParams,
												const FString& Name, const FText& Text)
	{
		NotificationParams.FormatArgs.Add(Name, Text);
		return NotificationParams;
	}

	/**
	* Add string argument to the notification parameter
	* @param NotificationParams Base class to add the string
	* @param Name The assigned name
	* @param Value The value associated to the name above
	* @return Updated ModioNotificationParams instance 
	**/
	UFUNCTION(BlueprintCallable, Category = "ModioNotificationParams")
	static FModioNotificationParams& SetStringArg(UPARAM(ref) FModioNotificationParams& NotificationParams,
												  const FString& Name, const FString& Value)
	{
		NotificationParams.FormatArgs.Add(Name, FText::FromString(Value));
		return NotificationParams;
	}	

	/**
	* Add float argument to the notification parameter
	* @param NotificationParams Base class to add the float value
	* @param Name The assigned name
	* @param Value The float value associated to the name above
	* @return Updated ModioNotificationParams instance 
	**/
	UFUNCTION(BlueprintCallable, Category = "ModioNotificationParams")
	static FModioNotificationParams& SetFloatArg(UPARAM(ref) FModioNotificationParams& NotificationParams,
												 const FString& Name, float Value)
	{
		NotificationParams.FormatArgs.Add(Name, Value);
		return NotificationParams;
	}
	
	/**
	* Add integer argument to the notification parameter
	* @param NotificationParams Base class to add the integer value
	* @param Name The assigned name
	* @param Value The integer value associated to the name above
	* @return Updated ModioNotificationParams instance 
	**/
	UFUNCTION(BlueprintCallable, Category = "ModioNotificationParams")
	static FModioNotificationParams& SetIntegerArg(UPARAM(ref) FModioNotificationParams& NotificationParams,
												   const FString& Name, int32 Value)
	{
		NotificationParams.FormatArgs.Add(Name, Value);
		return NotificationParams;
	}
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnNotificationExpired, UWidget*, NotificationWidget);

/**
* Modio UI interface that defines a notification, subclass of UInterface
**/
UINTERFACE(BlueprintType)
class MODIOUI_API UModioUINotification : public UInterface
{
	GENERATED_BODY()
};

/**
* Modio UI interface that defines a notification, subclass of IInterface
**/
class MODIOUI_API IModioUINotification : public IInterface
{
	GENERATED_BODY()
protected:
	bool bRoutedDisplayNotification = false;

	virtual void NativeOnDisplay() {};
	virtual void NativeConfigure(const FModioNotificationParams& Params) {};
	virtual void NativeSetNotificationExpireHandler(const FOnNotificationExpired& InDelegate) {};
	virtual UWidget* NativeGetAsWidget()
	{
		return nullptr;
	}

public:
	/**
	* Stored widget reference in the notification
	**/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IModioUINotification")
	UWidget* GetAsWidget();

	// GetAsWidget_Implementation
	UWidget* GetAsWidget_Implementation()
	{
		return NativeGetAsWidget();
	}

	/**
	* Modify the parameters to the notification instance
	* @param Params Notification parameters to update
	**/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IModioUINotification")
	void Configure(const FModioNotificationParams& Params);

	// Configure_Implementation
	void Configure_Implementation(const FModioNotificationParams& Params)
	{
		NativeConfigure(Params);
	}

	/**
	* Present the notification at the next possible frame
	**/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IModioUINotification")
	void Display();

	// Display_Implementation
	void Display_Implementation()
	{
		NativeOnDisplay();
	}

	/**
	* Update the delegate which will receive state changes to the notification
	**/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "IModioUINotification")
	void SetNotificationExpireHandler(const FOnNotificationExpired& InDelegate);

	// SetNotificationExpireHandler_Implementation
	void SetNotificationExpireHandler_Implementation(const FOnNotificationExpired& InDelegate)
	{
		NativeSetNotificationExpireHandler(InDelegate);
	}
};
