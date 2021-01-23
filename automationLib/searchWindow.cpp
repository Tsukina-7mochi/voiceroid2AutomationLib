//searchWindow.cpp

#include "searchWindow.h"
#include <Windows.h>
#include <stdlib.h>
#include <string>

#define bfSize 512

static std::string searchClassName;
static std::string searchWindowName;
static HWND hWndResult = NULL;
static BOOL firstCallback = TRUE;

//process window handle
static BOOL callbackFunc(HWND hWnd) {
    if (firstCallback) {
        //first callback will called with parent window's handle
        firstCallback = FALSE;
        return FALSE;
    }

    char szClass[bfSize], szWinText[bfSize];

    GetWindowTextA(hWnd, szWinText, sizeof(szWinText) / sizeof(szWinText[0]));
    GetClassNameA(hWnd, szClass, sizeof(szClass) / sizeof(szClass[0]));

    std::string strWindowName = szWinText;
    std::string strClassName = szClass;

    //printf("WIN: %s\n", szWinText);
    //printf(" CLASS: %s\n", szClass);

    if (strWindowName.find(searchWindowName) == std::string::npos) return FALSE;
    if (strClassName.find(searchClassName) == std::string::npos) return FALSE;

    hWndResult = hWnd;

    return TRUE;
}

//search all window and callback
static BOOL enumetareWindows(HWND hWndParent, const char* className, const char* windowName) {
    if (callbackFunc(hWndParent) == TRUE) {
        return TRUE;
    }

    HWND hWndChild = FindWindowEx(hWndParent, NULL, NULL, NULL);
    if (hWndChild == NULL) {
        return FALSE;
    }

    do {
        if (enumetareWindows(hWndChild, className, windowName) == TRUE) {
            return TRUE;
        }
    } while ((hWndChild = FindWindowEx(hWndParent, hWndChild, NULL, NULL)) != NULL);

    return FALSE;
}

HWND searchWindow(const std::string className, const std::string windowName) {
    searchClassName = className;
    searchWindowName = windowName;
    firstCallback = TRUE;

    HWND hWndParent = GetDesktopWindow();
    enumetareWindows(hWndParent, searchClassName.c_str(), searchWindowName.c_str());

    return hWndResult;
}
