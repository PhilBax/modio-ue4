﻿/*
 *  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
 *
 *  This file is part of the mod.io UE4 Plugin.
 *
 *  Distributed under the MIT License. (See accompanying file LICENSE or
 *   view online at <https://github.com/modio/modio-ue4/blob/main/LICENSE>)
 *
 */

#pragma once

#include "Interfaces/IModioMenuBackgroundProvider.h"

#include "ModioMenuDefaultBackgroundProvider.generated.h"

UCLASS()
class MODIOUI_API UModioMenuDefaultBackgroundProvider : public UObject, public IModioMenuBackgroundProvider
{
	GENERATED_BODY()

protected:
	UMaterialInterface* NativeGetBackgroundMaterial();

private:
	UMaterialInterface* BackgroundMaterial;
};
