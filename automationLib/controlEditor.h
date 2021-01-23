//talk.h

#pragma once

#include <uiautomation.h>
#include <propvarutil.h>
#include <stdio.h>

enum class CtrlEditResult : int {
	succeeded = 0,
	init,
	elementFromHWnd,
	createVariant,
	createCondition,
	getElement,
	getPattern,
	setValue,
	selectElement,
	pushButton,
	getLabel
};

extern bool ctrlEditDebug;

extern HRESULT InitializeCOM();
extern CtrlEditResult SetText(LPCWSTR message, HWND hWnd);
extern CtrlEditResult PushCButton(LPCWSTR buttonText, HWND hWnd);
CtrlEditResult PushSleepModeOnButton(HWND hWnd);
