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
#include "UI/BaseWidgets/ModioOverlay.h"
#include "UI/BaseWidgets/ModioUserWidgetBase.h"
#include "UI/Interfaces/IModioUINotification.h"
#include "UI/Interfaces/IModioUINotificationController.h"
#include "UObject/UObjectGlobals.h"

#include "ModioNotificationController.generated.h"

/**
* Modio UI element that represents a central place to manage notifications
**/
UCLASS(Abstract, BlueprintType)
class MODIOUI_API UModioNotificationControllerBase : public UModioUserWidgetBase, public IModioUINotificationController
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	UFUNCTION()
	virtual void OnNotificationExpired(UWidget* Notification);

	virtual void NativeDisplayNotification(const TScriptInterface<class IModioUINotification>& Notification) override;
	virtual void NativeDisplayErrorNotification(const FModioNotificationParams& Params) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (MustImplement = "ModioUINotification"), Category = "Widgets")
	TSubclassOf<UWidget> ErrorNotificationClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	class UVerticalBox* NotificationList;
};
