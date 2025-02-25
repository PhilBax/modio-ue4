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

#include "Core/ModioTagOptionsUI.h"
#include "UI/BaseWidgets/ModioEditableTextBox.h"
#include "UI/BaseWidgets/ModioRichTextBlock.h"
#include "UI/BaseWidgets/ModioUserWidgetBase.h"
#include "UI/Commands/ModioCommonUICommands.h"
#include "UI/CommonComponents/ModioRichTextButton.h"
#include "UI/CommonComponents/ModioTagListWidgetBase.h"
#include "UI/Interfaces/IModioUIRefineSearchWidget.h"

#include "ModioRefineSearchDrawer.generated.h"

/**
* Class definition for the Modio refine search drawer which has search input
* and operation buttons
**/
UCLASS()
class MODIOUI_API UModioRefineSearchDrawer : public UModioUserWidgetBase,
											 public IModioUIRefineSearchWidget // IModioUIUserChangeReceiver
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioEditableTextBox* SearchInput;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioTagListWidgetBase* TagSelector;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextButton* ApplyButton;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widgets", meta = (BindWidget))
	UModioRichTextButton* ClearButton;

	UPROPERTY(BlueprintAssignable)
	FOnSearchSettingsChanged OnSettingsChanged;

	UPROPERTY(Transient)
	UModioTagOptionsUI* TagOptions;

	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void BuildCommandList(TSharedRef<FUICommandList> InCommandList) override;

	UFUNCTION()
	void OnClearClicked();
	UFUNCTION()
	void OnApplyClicked();

	void NextTagCategory();
	void PrevTagCategory();

	FString NativeGetSearchString() override;
	TArray<FString> NativeGetSelectedTagValues() override;
	void NativeRefreshTags() override;
	virtual FOnSearchSettingsChanged& NativeGetOnSettingsChangedDelegate();

	void OnTagOptionsReceived(FModioErrorCode ec, TOptional<FModioModTagOptions> Options);
};
