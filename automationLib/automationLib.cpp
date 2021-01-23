//automationCpp.cpp

#include <uiautomation.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "searchWindow.h"
#include "controlEditor.h"
#include "automationLib.h"

typedef BOOL(*LPFNENUMERATEWINDOWCALLBACK)(HWND hWnd);

// DLLのエントリーポイント
// 読み込み時にCOMを初期化
int WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason){
    case DLL_PROCESS_ATTACH:
        //COM初期化
        if (InitializeCOM() != S_OK) {
            return FALSE;
        }
        break;
    default:
        break;
    }

    return TRUE;
}

// VOICEROID2 Editorのウィンドウハンドルを取得
// @returns
//   VOICEROID2 Editorのウィンドウハンドル
//   見つからない場合はNULL
HWND getVoiceroidEditorWindow() {
    HWND hWnd;
    std::string className = "VoiceroidEditor.exe";
    std::string windowName = "VOICEROID2";
    std::string windowName2 = "VOICEROID2*";

    hWnd = searchWindow(className, windowName);
    if (hWnd == NULL) {
        hWnd = searchWindow(className, windowName2);
        if (hWnd == NULL) {
            return NULL;
        }
    }

    return hWnd;
}

// ===== 統合機能 =====

// テキストを読み上げ
// @param
//   message: 読み上げるテキスト
// @returns
//   実行結果
int talk(LPCWSTR message) {
    CtrlEditResult result;
    HWND hWnd = getVoiceroidEditorWindow();
    if (hWnd == NULL) return -1;

    // テキストを設定
    result = SetText(message, hWnd);
    if (result != CtrlEditResult::succeeded) return static_cast<int>(result);

    // 先頭ボタンを押す
    result = PushCButton(L"先頭", hWnd);
    if (result != CtrlEditResult::succeeded) return static_cast<int>(result);

    // 再生ボタンを押す
    result = PushCButton(L"再生", hWnd);
    if (result != CtrlEditResult::succeeded) return static_cast<int>(result);

    return 0;
}

// 読み上げを停止(停止ボタンを押下)
// @returns
//   実行結果
int stopTalk() {
    CtrlEditResult result;
    HWND hWnd = getVoiceroidEditorWindow();
    if (hWnd == NULL) return -1;

    // 停止ボタンを押す
    result = PushCButton(L"停止", hWnd);
    if (result != CtrlEditResult::succeeded) return static_cast<int>(result);

    return 0;
}

// ===== 個別機能 =====

// テキストを設定
// @param
//   message: 設定するテキスト
// @returns
//   実行結果
int setTextView(LPCWSTR message) {
    CtrlEditResult result;
    HWND hWnd = getVoiceroidEditorWindow();
    if (hWnd == NULL) return -1;

    // テキストを設定
    result = SetText(message, hWnd);
    if (result != CtrlEditResult::succeeded) return static_cast<int>(result);

    return 0;
}

// TextViewにあるボタンを押下
// @param
//   text: ボタンのテキスト
// @returns
//   実行結果
int pushTextViewButton(LPCWSTR text) {
    CtrlEditResult result;
    HWND hWnd = getVoiceroidEditorWindow();
    if (hWnd == NULL) return -1;

    // ボタンを押す
    result = PushCButton(text, hWnd);
    if (result != CtrlEditResult::succeeded) return static_cast<int>(result);

    return 0;
}

// SleepModeOnボタンを押下
// @returns
//   実行結果
int sleepMode() {
    CtrlEditResult result;
    HWND hWnd = getVoiceroidEditorWindow();
    if (hWnd == NULL) return -1;

    // ボタンを押す
    result = PushSleepModeOnButton(hWnd);
    if (result != CtrlEditResult::succeeded) return static_cast<int>(result);

    return 0;
}


// ===== デバッグ =====

// デバッグを有効化
void enableDebug() {
    ctrlEditDebug = true;
}

// デバッグを無効化
void disableDebug() {
    ctrlEditDebug = true;
}