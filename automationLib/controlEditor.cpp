//talk.cpp

#include <uiautomation.h>
#include <propvarutil.h>
#include <stdio.h>
#include <atlstr.h>
#include "controlEditor.h"

// デバッグ用フラグ
// 外部から操作可能にするためstaticでない
bool ctrlEditDebug = false;

// UIAutomationを初期化
// @param
//   ppAutomation: IUIAutomationへのポインタ
// @returns
//   操作の成否
static HRESULT InitializeUIAutomation(IUIAutomation** ppAutomation)
{
    return CoCreateInstance(CLSID_CUIAutomation, NULL,
        CLSCTX_INPROC_SERVER, IID_IUIAutomation,
        reinterpret_cast<void**>(ppAutomation));
}

// COMを初期化
// @returns
//   操作の成否
HRESULT InitializeCOM(){
    return CoInitialize(NULL);
}

// debugが有効な場合に標準出力にログを出力
// @param
//   text: 出力する文字列
#define writeLog(text) (ctrlEditDebug ? printf("%s", (text)) : NULL)
// 改行を付与する
#define writeLogL(text) (ctrlEditDebug ? printf("%s\n", (text)) : NULL)
// "成功"と出力(改行を付与)
#define writeLogS() writeLogL("成功")
// "失敗"と出力(改行を付与)
#define writeLogF(reason) (ctrlEditDebug ? printf("失敗%s%s\n", (reason ? ": " : "") , (reason ? reason : "")) : NULL)


// テキストボックスに文字列を設定
// @param
//   message: 設定する文字列
//   hWnd   : VOICEROID2 Editorのウィンドウハンドル
CtrlEditResult SetText(LPCWSTR message, HWND hWnd) {
    IUIAutomation* automation;

    writeLogL("テキストボックスに文字列を設定します");

    // 初期化
    writeLog("UIAutomationを初期化...");
    if (InitializeUIAutomation(&automation) != S_OK || automation == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::init;
    }
    writeLogS();

    // ウィンドウハンドルから取得
    writeLog("VOICEROID2 Editorウィンドウの要素を取得...");
    IUIAutomationElement *window;
    if (automation->ElementFromHandle(hWnd, &window) != S_OK || window == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::elementFromHWnd;
    }
    writeLogS();

    // TextEditViewの取得
    writeLog("TextEditViewの要素を取得...");
    IUIAutomationCondition *customBoxCondition;
    IUIAutomationElement *customBox;
    VARIANT customBoxVariant;

    if (InitVariantFromString(L"c", &customBoxVariant) != S_OK) {
        writeLogF("Variantの生成に失敗");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30011, customBoxVariant, &customBoxCondition) != S_OK || customBoxCondition == nullptr) {
        writeLogF("Conditionの生成に失敗");
        return CtrlEditResult::createCondition;
    }
    if (window->FindFirst(TreeScope_Subtree, customBoxCondition, &customBox ) != S_OK || customBox == nullptr) {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // テキストエリアの取得・設定
    writeLog("TextEditの要素を取得...");
    IUIAutomationCondition *textAreaCondition;
    IUIAutomationElement *textArea;
    IUIAutomationLegacyIAccessiblePattern *textAreaPtrn;
    VARIANT textAreaVariant;

    if (InitVariantFromString(L"TextBox", &textAreaVariant) != S_OK) {
        writeLogF("Variantの生成に失敗");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30011, textAreaVariant, &textAreaCondition) != S_OK || textAreaCondition == nullptr) {
        writeLogF("Conditionの生成に失敗");
        return CtrlEditResult::createCondition;
    }
    if (customBox->FindFirst(TreeScope_Subtree, textAreaCondition, &textArea) != S_OK || textArea == nullptr) {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }
    if (textArea->GetCurrentPattern(10018, (IUnknown**)&textAreaPtrn) != S_OK || textAreaPtrn == nullptr){
        writeLogF("Patternの取得に失敗");
        return CtrlEditResult::getPattern;
    }
    if (textAreaPtrn->SetValue(message) != S_OK){
        writeLogF("テキストの設定に失敗");
        return CtrlEditResult::setValue;
    }
    if (textAreaPtrn->Select(1) != S_OK) {
        writeLogF("選択に失敗");
        return CtrlEditResult::selectElement;
    }
    writeLogS();

    writeLogL("正常終了");
    //free(automation);
    return CtrlEditResult::succeeded;
}

// カスタム #c 内の指定した名前のテキストが子要素に存在するボタンを押下
// @param
//   message: ボタンの文字列
//   hWnd   : VOICEROID2 Editorのウィンドウハンドル
CtrlEditResult PushCButton(LPCWSTR buttonText, HWND hWnd) {
    IUIAutomation* automation;

    writeLogL("カスタム#c内のボタンを押下します");

    // 初期化
    writeLog("UIAutomationを初期化...");
    if (InitializeUIAutomation(&automation) != S_OK || automation == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::init;
    }
    writeLogS();

    // ウィンドウハンドルから取得
    writeLog("VOICEROID2 Editorウィンドウの要素を取得...");
    IUIAutomationElement* window;
    if (automation->ElementFromHandle(hWnd, &window) != S_OK || window == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::elementFromHWnd;
    }
    writeLogS();

    // TextEditViewの取得
    writeLog("TextEditViewの要素を取得...");
    IUIAutomationCondition* customBoxCondition;
    IUIAutomationElement* customBox;
    VARIANT customBoxVariant;

    if (InitVariantFromString(L"c", &customBoxVariant) != S_OK) {
        writeLogF("Variantの生成に失敗");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30011, customBoxVariant, &customBoxCondition) != S_OK || customBoxCondition == nullptr) {
        writeLogF("Conditionの生成に失敗");
        return CtrlEditResult::createCondition;
    }
    if (window->FindFirst(TreeScope_Subtree, customBoxCondition, &customBox) != S_OK || customBox == nullptr) {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // ボタンの取得・押下
    writeLog("ボタンを押下...");
    IUIAutomationCondition* buttonCondition;
    IUIAutomationElementArray* buttonArray;
    IUIAutomationLegacyIAccessiblePattern* buttonPtrn;
    VARIANT buttonVariant;

    if (InitVariantFromString(L"Button", &buttonVariant) != S_OK) {
        writeLogF("Variantの生成に失敗");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30012, buttonVariant, &buttonCondition) != S_OK || buttonCondition == nullptr) {
        writeLogF("Conditionの生成に失敗");
        return CtrlEditResult::createCondition;
    }
    if (customBox->FindAll(TreeScope_Descendants, buttonCondition, &buttonArray) != S_OK || buttonArray == nullptr) {
        writeLogF("ボタンリストの検索に失敗");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // 各ボタンをチェック
    bool buttonFound = false;
    int arrayLength = 0;
    buttonArray->get_Length(&arrayLength);

    for (int i = 0; i < arrayLength; i++) {
        // ボタンの子要素を取得
        IUIAutomationElement* button;
        IUIAutomationCondition* childCondition;
        IUIAutomationElementArray* children;
        VARIANT childVariant;
        buttonArray->GetElement(i, &button);

        if (InitVariantFromString(L"TextBlock", &childVariant) != S_OK) {
            writeLogF("Variantの生成に失敗");
            return CtrlEditResult::createVariant;
        }
        if (automation->CreatePropertyCondition(30012, childVariant, &childCondition) != S_OK || childCondition == nullptr) {
            writeLogF("Conditionの生成に失敗");
            return CtrlEditResult::createCondition;
        }
        if (button->FindAll(TreeScope_Descendants, childCondition, &children) != S_OK || children == nullptr) {
            writeLogF("ボタン子要素リストの検索に失敗");
            return CtrlEditResult::getElement;
        }

        int childrenLength = 0;
        children->get_Length(&childrenLength);

        for (int j = 0; j < childrenLength; j++) {
            IUIAutomationElement* child;
            children->GetElement(j, &child);
            BSTR childName;

            if (child == nullptr || child->get_CurrentName(&childName) != S_OK || childName == nullptr) {
                writeLogF("ボタンテキストの取得に失敗\n");
                return CtrlEditResult::getLabel;
            }

            CComBSTR name(childName);
            if (name == buttonText) {
                // ボタンを押す
                buttonFound = true;
                if (button->GetCurrentPattern(10018, (IUnknown**)&buttonPtrn) != S_OK || buttonPtrn == nullptr) {
                    writeLogF("Patternの取得に失敗");
                    return CtrlEditResult::getPattern;
                }

                if (buttonPtrn->DoDefaultAction() != S_OK) {
                    writeLogF("押下に失敗");
                    return CtrlEditResult::pushButton;
                }
            };

            SysFreeString(childName);
            SysFreeString(name);

            if (buttonFound) break;
        }
    }

    if (!buttonFound) {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    writeLogL("正常終了");
    //free(automation);
    return CtrlEditResult::succeeded;
}

// Sleep Mode をOnにする
// @param
//   hWnd     : VOICEROID2 Editorのウィンドウハンドル
CtrlEditResult PushSleepModeOnButton(HWND hWnd) {
    IUIAutomation* automation;

    writeLogL("カスタム#c内のボタンを押下します");

    // 初期化
    writeLog("UIAutomationを初期化...");
    if (InitializeUIAutomation(&automation) != S_OK || automation == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::init;
    }
    writeLogS();

    // ウィンドウハンドルから取得
    writeLog("VOICEROID2 Editorウィンドウの要素を取得...");
    IUIAutomationElement* window;
    if (automation->ElementFromHandle(hWnd, &window) != S_OK || window == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::elementFromHWnd;
    }
    writeLogS();

    // CharacterViewの取得
    writeLog("Character Viewの要素を取得...");
    IUIAutomationCondition* customBoxCondition;
    IUIAutomationElement* customBox;
    VARIANT customBoxVariant;

    if (InitVariantFromString(L"d", &customBoxVariant) != S_OK) {
        writeLogF("Variantの生成に失敗");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30011, customBoxVariant, &customBoxCondition) != S_OK || customBoxCondition == nullptr) {
        writeLogF("Conditionの生成に失敗");
        return CtrlEditResult::createCondition;
    }
    if (window->FindFirst(TreeScope_Subtree, customBoxCondition, &customBox) != S_OK || customBox == nullptr) {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // Sleep Mode Onボタンの取得・押下
    writeLog("Sleep Mode Onボタンを押下...");
    IUIAutomationCondition* sleepButtonCondition;
    IUIAutomationElement* sleepButton;
    IUIAutomationLegacyIAccessiblePattern* sleepButtonPtrn;
    VARIANT sleepButtonVariant;

    if (InitVariantFromString(L"Button", &sleepButtonVariant) != S_OK) {
        writeLogF("Variantの生成に失敗");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30012, sleepButtonVariant, &sleepButtonCondition) != S_OK || sleepButtonCondition == nullptr) {
        writeLogF("Conditionの生成に失敗");
        return CtrlEditResult::createCondition;
    }
    if (customBox->FindFirst(TreeScope_Descendants, sleepButtonCondition, &sleepButton) != S_OK || sleepButton == nullptr) {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }
    if (sleepButton->GetCurrentPattern(10018, (IUnknown**)&sleepButtonPtrn) != S_OK || sleepButtonPtrn == nullptr) {
        writeLogF("Patternの取得に失敗");
        return CtrlEditResult::getPattern;
    }
    if (sleepButtonPtrn->DoDefaultAction() != S_OK) {
        writeLogF("押下に失敗");
        return CtrlEditResult::pushButton;
    }
    writeLogS();

    // 「スリープモードの設定」ウィンドウの取得
    writeLog("「スリープモードの設定」ウィンドウの要素を取得...");
    IUIAutomationCondition* configWindowCondition;
    IUIAutomationElement* configWindow;
    VARIANT configWindowVariant;

    if (InitVariantFromString(L"Window", &configWindowVariant) != S_OK) {
        writeLogF("Variantの生成に失敗");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30012, configWindowVariant, &configWindowCondition) != S_OK || configWindowCondition == nullptr) {
        writeLogF("Conditionの生成に失敗");
        return CtrlEditResult::createCondition;
    }
    if (window->FindFirst(TreeScope_Descendants, configWindowCondition, &configWindow) != S_OK || configWindow == nullptr) {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }
    BSTR winName;
    if (configWindow->get_CurrentName(&winName) != S_OK || winName == nullptr) {
        writeLogF("ウィンドウタイトルの取得に失敗\n");
        return CtrlEditResult::getLabel;
    }
    CComBSTR winName_(winName);
    if (winName_ != L"スリープモードの設定") {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // OKボタンの取得・押下
    writeLog("OKボタンを押下...");
    IUIAutomationCondition* okButtonCondition;
    IUIAutomationElementArray* okButtonArray;
    IUIAutomationLegacyIAccessiblePattern* okButtonPtrn;
    VARIANT okButtonVariant;

    if (InitVariantFromString(L"Button", &okButtonVariant) != S_OK) {
        writeLogF("Variantの生成に失敗");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30012, okButtonVariant, &okButtonCondition) != S_OK || okButtonCondition == nullptr) {
        writeLogF("Conditionの生成に失敗");
        return CtrlEditResult::createCondition;
    }
    if (configWindow->FindAll(TreeScope_Descendants, okButtonCondition, &okButtonArray) != S_OK || okButtonArray == nullptr) {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }

    BOOL buttonFound = false;
    int arrayLength = 0;
    okButtonArray->get_Length(&arrayLength);

    for (int i = 0; i < arrayLength; i++) {
        IUIAutomationElement* button;
        okButtonArray->GetElement(i, &button);
        BSTR buttonName;

        if (button == nullptr || button->get_CurrentName(&buttonName) != S_OK || buttonName == nullptr) {
            writeLogF("ボタンテキストの取得に失敗\n");
            return CtrlEditResult::getLabel;
        }

        CComBSTR name(buttonName);
        if(name == L"OK"){
            // ボタンを押す
            buttonFound = true;
            if (button->GetCurrentPattern(10018, (IUnknown**)&okButtonPtrn) != S_OK || okButtonPtrn == nullptr) {
                writeLogF("Patternの取得に失敗");
                return CtrlEditResult::getPattern;
            }

            if (okButtonPtrn->DoDefaultAction() != S_OK) {
                writeLogF("押下に失敗");
                return CtrlEditResult::pushButton;
            }
        }
    }
    
    if (!buttonFound) {
        writeLogF("検索に失敗");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    writeLogL("正常終了");
    //free(automation);
    return CtrlEditResult::succeeded;
}
