#pragma once

#include <Windows.h>
extern "C" __declspec(dllexport) int talk(LPCWSTR message);
extern "C" __declspec(dllexport) int stopTalk();
extern "C" __declspec(dllexport) int setTextView(LPCWSTR message);
extern "C" __declspec(dllexport) int pushTextViewButton(LPCWSTR text);
extern "C" __declspec(dllexport) int sleepMode();
extern "C" __declspec(dllexport) void enableDebug();
extern "C" __declspec(dllexport) void disableDebug();