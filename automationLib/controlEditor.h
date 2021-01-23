//talk.h

#pragma once

#include <uiautomation.h>
#include <propvarutil.h>
#include <stdio.h>

// 実行結果
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

// デバッグが有効かどうか
extern bool ctrlEditDebug;



// COMを初期化
// @returns
//   操作の成否
extern HRESULT InitializeCOM();

// テキストボックスに文字列を設定
// @param
//   message: 設定する文字列
//   hWnd   : VOICEROID2 Editorのウィンドウハンドル
extern CtrlEditResult SetText(LPCWSTR message, HWND hWnd);

// カスタム #c 内の指定した名前のテキストが子要素に存在するボタンを押下
// @param
//   message: ボタンの文字列
//   hWnd   : VOICEROID2 Editorのウィンドウハンドル
extern CtrlEditResult PushCButton(LPCWSTR buttonText, HWND hWnd);

// Sleep Mode をOnにする
// @param
//   hWnd     : VOICEROID2 Editorのウィンドウハンドル
CtrlEditResult PushSleepModeOnButton(HWND hWnd);
