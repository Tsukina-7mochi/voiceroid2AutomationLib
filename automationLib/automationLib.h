#pragma once

#include <Windows.h>


// ===== 統合機能 =====

// テキストを読み上げ
// @param
//   message: 読み上げるテキスト
// @returns
//   実行結果
extern "C" __declspec(dllexport) int talk(LPCWSTR message);

// 読み上げを停止(停止ボタンを押下)
// @returns
//   実行結果
extern "C" __declspec(dllexport) int stopTalk();


// ===== 個別機能 =====

// テキストを設定
// @param
//   message: 設定するテキスト
// @returns
//   実行結果
extern "C" __declspec(dllexport) int setTextView(LPCWSTR message);

// TextViewにあるボタンを押下
// @param
//   text: ボタンのテキスト
// @returns
//   実行結果
extern "C" __declspec(dllexport) int pushTextViewButton(LPCWSTR text);

// SleepModeOnボタンを押下
// @returns
//   実行結果
extern "C" __declspec(dllexport) int sleepMode();


// ===== デバッグ =====

// デバッグを有効化
extern "C" __declspec(dllexport) void enableDebug();

// デバッグを無効化
extern "C" __declspec(dllexport) void disableDebug();