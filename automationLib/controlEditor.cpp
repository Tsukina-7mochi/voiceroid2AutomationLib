//talk.cpp

#include <uiautomation.h>
#include <propvarutil.h>
#include <stdio.h>
#include <atlstr.h>
#include "controlEditor.h"

// �f�o�b�O�p�t���O
// �O�����瑀��\�ɂ��邽��static�łȂ�
bool ctrlEditDebug = false;

// UIAutomation��������
// @param
//   ppAutomation: IUIAutomation�ւ̃|�C���^
// @returns
//   ����̐���
static HRESULT InitializeUIAutomation(IUIAutomation** ppAutomation)
{
    return CoCreateInstance(CLSID_CUIAutomation, NULL,
        CLSCTX_INPROC_SERVER, IID_IUIAutomation,
        reinterpret_cast<void**>(ppAutomation));
}

// COM��������
// @returns
//   ����̐���
HRESULT InitializeCOM(){
    return CoInitialize(NULL);
}

// debug���L���ȏꍇ�ɕW���o�͂Ƀ��O���o��
// @param
//   text: �o�͂��镶����
#define writeLog(text) (ctrlEditDebug ? printf("%s", (text)) : NULL)
// ���s��t�^����
#define writeLogL(text) (ctrlEditDebug ? printf("%s\n", (text)) : NULL)
// "����"�Əo��(���s��t�^)
#define writeLogS() writeLogL("����")
// "���s"�Əo��(���s��t�^)
#define writeLogF(reason) (ctrlEditDebug ? printf("���s%s%s\n", (reason ? ": " : "") , (reason ? reason : "")) : NULL)


// �e�L�X�g�{�b�N�X�ɕ������ݒ�
// @param
//   message: �ݒ肷�镶����
//   hWnd   : VOICEROID2 Editor�̃E�B���h�E�n���h��
CtrlEditResult SetText(LPCWSTR message, HWND hWnd) {
    IUIAutomation* automation;

    writeLogL("�e�L�X�g�{�b�N�X�ɕ������ݒ肵�܂�");

    // ������
    writeLog("UIAutomation��������...");
    if (InitializeUIAutomation(&automation) != S_OK || automation == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::init;
    }
    writeLogS();

    // �E�B���h�E�n���h������擾
    writeLog("VOICEROID2 Editor�E�B���h�E�̗v�f���擾...");
    IUIAutomationElement *window;
    if (automation->ElementFromHandle(hWnd, &window) != S_OK || window == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::elementFromHWnd;
    }
    writeLogS();

    // TextEditView�̎擾
    writeLog("TextEditView�̗v�f���擾...");
    IUIAutomationCondition *customBoxCondition;
    IUIAutomationElement *customBox;
    VARIANT customBoxVariant;

    if (InitVariantFromString(L"c", &customBoxVariant) != S_OK) {
        writeLogF("Variant�̐����Ɏ��s");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30011, customBoxVariant, &customBoxCondition) != S_OK || customBoxCondition == nullptr) {
        writeLogF("Condition�̐����Ɏ��s");
        return CtrlEditResult::createCondition;
    }
    if (window->FindFirst(TreeScope_Subtree, customBoxCondition, &customBox ) != S_OK || customBox == nullptr) {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // �e�L�X�g�G���A�̎擾�E�ݒ�
    writeLog("TextEdit�̗v�f���擾...");
    IUIAutomationCondition *textAreaCondition;
    IUIAutomationElement *textArea;
    IUIAutomationLegacyIAccessiblePattern *textAreaPtrn;
    VARIANT textAreaVariant;

    if (InitVariantFromString(L"TextBox", &textAreaVariant) != S_OK) {
        writeLogF("Variant�̐����Ɏ��s");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30011, textAreaVariant, &textAreaCondition) != S_OK || textAreaCondition == nullptr) {
        writeLogF("Condition�̐����Ɏ��s");
        return CtrlEditResult::createCondition;
    }
    if (customBox->FindFirst(TreeScope_Subtree, textAreaCondition, &textArea) != S_OK || textArea == nullptr) {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    if (textArea->GetCurrentPattern(10018, (IUnknown**)&textAreaPtrn) != S_OK || textAreaPtrn == nullptr){
        writeLogF("Pattern�̎擾�Ɏ��s");
        return CtrlEditResult::getPattern;
    }
    if (textAreaPtrn->SetValue(message) != S_OK){
        writeLogF("�e�L�X�g�̐ݒ�Ɏ��s");
        return CtrlEditResult::setValue;
    }
    if (textAreaPtrn->Select(1) != S_OK) {
        writeLogF("�I���Ɏ��s");
        return CtrlEditResult::selectElement;
    }
    writeLogS();

    writeLogL("����I��");
    //free(automation);
    return CtrlEditResult::succeeded;
}

// �J�X�^�� #c ���̎w�肵�����O�̃e�L�X�g���q�v�f�ɑ��݂���{�^��������
// @param
//   message: �{�^���̕�����
//   hWnd   : VOICEROID2 Editor�̃E�B���h�E�n���h��
CtrlEditResult PushCButton(LPCWSTR buttonText, HWND hWnd) {
    IUIAutomation* automation;

    writeLogL("�J�X�^��#c���̃{�^�����������܂�");

    // ������
    writeLog("UIAutomation��������...");
    if (InitializeUIAutomation(&automation) != S_OK || automation == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::init;
    }
    writeLogS();

    // �E�B���h�E�n���h������擾
    writeLog("VOICEROID2 Editor�E�B���h�E�̗v�f���擾...");
    IUIAutomationElement* window;
    if (automation->ElementFromHandle(hWnd, &window) != S_OK || window == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::elementFromHWnd;
    }
    writeLogS();

    // TextEditView�̎擾
    writeLog("TextEditView�̗v�f���擾...");
    IUIAutomationCondition* customBoxCondition;
    IUIAutomationElement* customBox;
    VARIANT customBoxVariant;

    if (InitVariantFromString(L"c", &customBoxVariant) != S_OK) {
        writeLogF("Variant�̐����Ɏ��s");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30011, customBoxVariant, &customBoxCondition) != S_OK || customBoxCondition == nullptr) {
        writeLogF("Condition�̐����Ɏ��s");
        return CtrlEditResult::createCondition;
    }
    if (window->FindFirst(TreeScope_Subtree, customBoxCondition, &customBox) != S_OK || customBox == nullptr) {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // �{�^���̎擾�E����
    writeLog("�{�^��������...");
    IUIAutomationCondition* buttonCondition;
    IUIAutomationElementArray* buttonArray;
    IUIAutomationLegacyIAccessiblePattern* buttonPtrn;
    VARIANT buttonVariant;

    if (InitVariantFromString(L"Button", &buttonVariant) != S_OK) {
        writeLogF("Variant�̐����Ɏ��s");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30012, buttonVariant, &buttonCondition) != S_OK || buttonCondition == nullptr) {
        writeLogF("Condition�̐����Ɏ��s");
        return CtrlEditResult::createCondition;
    }
    if (customBox->FindAll(TreeScope_Descendants, buttonCondition, &buttonArray) != S_OK || buttonArray == nullptr) {
        writeLogF("�{�^�����X�g�̌����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // �e�{�^�����`�F�b�N
    bool buttonFound = false;
    int arrayLength = 0;
    buttonArray->get_Length(&arrayLength);

    for (int i = 0; i < arrayLength; i++) {
        // �{�^���̎q�v�f���擾
        IUIAutomationElement* button;
        IUIAutomationCondition* childCondition;
        IUIAutomationElementArray* children;
        VARIANT childVariant;
        buttonArray->GetElement(i, &button);

        if (InitVariantFromString(L"TextBlock", &childVariant) != S_OK) {
            writeLogF("Variant�̐����Ɏ��s");
            return CtrlEditResult::createVariant;
        }
        if (automation->CreatePropertyCondition(30012, childVariant, &childCondition) != S_OK || childCondition == nullptr) {
            writeLogF("Condition�̐����Ɏ��s");
            return CtrlEditResult::createCondition;
        }
        if (button->FindAll(TreeScope_Descendants, childCondition, &children) != S_OK || children == nullptr) {
            writeLogF("�{�^���q�v�f���X�g�̌����Ɏ��s");
            return CtrlEditResult::getElement;
        }

        int childrenLength = 0;
        children->get_Length(&childrenLength);

        for (int j = 0; j < childrenLength; j++) {
            IUIAutomationElement* child;
            children->GetElement(j, &child);
            BSTR childName;

            if (child == nullptr || child->get_CurrentName(&childName) != S_OK || childName == nullptr) {
                writeLogF("�{�^���e�L�X�g�̎擾�Ɏ��s\n");
                return CtrlEditResult::getLabel;
            }

            CComBSTR name(childName);
            if (name == buttonText) {
                // �{�^��������
                buttonFound = true;
                if (button->GetCurrentPattern(10018, (IUnknown**)&buttonPtrn) != S_OK || buttonPtrn == nullptr) {
                    writeLogF("Pattern�̎擾�Ɏ��s");
                    return CtrlEditResult::getPattern;
                }

                if (buttonPtrn->DoDefaultAction() != S_OK) {
                    writeLogF("�����Ɏ��s");
                    return CtrlEditResult::pushButton;
                }
            };

            SysFreeString(childName);
            SysFreeString(name);

            if (buttonFound) break;
        }
    }

    if (!buttonFound) {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    writeLogL("����I��");
    //free(automation);
    return CtrlEditResult::succeeded;
}

// Sleep Mode ��On�ɂ���
// @param
//   hWnd     : VOICEROID2 Editor�̃E�B���h�E�n���h��
CtrlEditResult PushSleepModeOnButton(HWND hWnd) {
    IUIAutomation* automation;

    writeLogL("�J�X�^��#c���̃{�^�����������܂�");

    // ������
    writeLog("UIAutomation��������...");
    if (InitializeUIAutomation(&automation) != S_OK || automation == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::init;
    }
    writeLogS();

    // �E�B���h�E�n���h������擾
    writeLog("VOICEROID2 Editor�E�B���h�E�̗v�f���擾...");
    IUIAutomationElement* window;
    if (automation->ElementFromHandle(hWnd, &window) != S_OK || window == nullptr) {
        writeLogF(NULL);
        return CtrlEditResult::elementFromHWnd;
    }
    writeLogS();

    // CharacterView�̎擾
    writeLog("Character View�̗v�f���擾...");
    IUIAutomationCondition* customBoxCondition;
    IUIAutomationElement* customBox;
    VARIANT customBoxVariant;

    if (InitVariantFromString(L"d", &customBoxVariant) != S_OK) {
        writeLogF("Variant�̐����Ɏ��s");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30011, customBoxVariant, &customBoxCondition) != S_OK || customBoxCondition == nullptr) {
        writeLogF("Condition�̐����Ɏ��s");
        return CtrlEditResult::createCondition;
    }
    if (window->FindFirst(TreeScope_Subtree, customBoxCondition, &customBox) != S_OK || customBox == nullptr) {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // Sleep Mode On�{�^���̎擾�E����
    writeLog("Sleep Mode On�{�^��������...");
    IUIAutomationCondition* sleepButtonCondition;
    IUIAutomationElement* sleepButton;
    IUIAutomationLegacyIAccessiblePattern* sleepButtonPtrn;
    VARIANT sleepButtonVariant;

    if (InitVariantFromString(L"Button", &sleepButtonVariant) != S_OK) {
        writeLogF("Variant�̐����Ɏ��s");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30012, sleepButtonVariant, &sleepButtonCondition) != S_OK || sleepButtonCondition == nullptr) {
        writeLogF("Condition�̐����Ɏ��s");
        return CtrlEditResult::createCondition;
    }
    if (customBox->FindFirst(TreeScope_Descendants, sleepButtonCondition, &sleepButton) != S_OK || sleepButton == nullptr) {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    if (sleepButton->GetCurrentPattern(10018, (IUnknown**)&sleepButtonPtrn) != S_OK || sleepButtonPtrn == nullptr) {
        writeLogF("Pattern�̎擾�Ɏ��s");
        return CtrlEditResult::getPattern;
    }
    if (sleepButtonPtrn->DoDefaultAction() != S_OK) {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::pushButton;
    }
    writeLogS();

    // �u�X���[�v���[�h�̐ݒ�v�E�B���h�E�̎擾
    writeLog("�u�X���[�v���[�h�̐ݒ�v�E�B���h�E�̗v�f���擾...");
    IUIAutomationCondition* configWindowCondition;
    IUIAutomationElement* configWindow;
    VARIANT configWindowVariant;

    if (InitVariantFromString(L"Window", &configWindowVariant) != S_OK) {
        writeLogF("Variant�̐����Ɏ��s");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30012, configWindowVariant, &configWindowCondition) != S_OK || configWindowCondition == nullptr) {
        writeLogF("Condition�̐����Ɏ��s");
        return CtrlEditResult::createCondition;
    }
    if (window->FindFirst(TreeScope_Descendants, configWindowCondition, &configWindow) != S_OK || configWindow == nullptr) {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    BSTR winName;
    if (configWindow->get_CurrentName(&winName) != S_OK || winName == nullptr) {
        writeLogF("�E�B���h�E�^�C�g���̎擾�Ɏ��s\n");
        return CtrlEditResult::getLabel;
    }
    CComBSTR winName_(winName);
    if (winName_ != L"�X���[�v���[�h�̐ݒ�") {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    // OK�{�^���̎擾�E����
    writeLog("OK�{�^��������...");
    IUIAutomationCondition* okButtonCondition;
    IUIAutomationElementArray* okButtonArray;
    IUIAutomationLegacyIAccessiblePattern* okButtonPtrn;
    VARIANT okButtonVariant;

    if (InitVariantFromString(L"Button", &okButtonVariant) != S_OK) {
        writeLogF("Variant�̐����Ɏ��s");
        return CtrlEditResult::createVariant;
    }
    if (automation->CreatePropertyCondition(30012, okButtonVariant, &okButtonCondition) != S_OK || okButtonCondition == nullptr) {
        writeLogF("Condition�̐����Ɏ��s");
        return CtrlEditResult::createCondition;
    }
    if (configWindow->FindAll(TreeScope_Descendants, okButtonCondition, &okButtonArray) != S_OK || okButtonArray == nullptr) {
        writeLogF("�����Ɏ��s");
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
            writeLogF("�{�^���e�L�X�g�̎擾�Ɏ��s\n");
            return CtrlEditResult::getLabel;
        }

        CComBSTR name(buttonName);
        if(name == L"OK"){
            // �{�^��������
            buttonFound = true;
            if (button->GetCurrentPattern(10018, (IUnknown**)&okButtonPtrn) != S_OK || okButtonPtrn == nullptr) {
                writeLogF("Pattern�̎擾�Ɏ��s");
                return CtrlEditResult::getPattern;
            }

            if (okButtonPtrn->DoDefaultAction() != S_OK) {
                writeLogF("�����Ɏ��s");
                return CtrlEditResult::pushButton;
            }
        }
    }
    
    if (!buttonFound) {
        writeLogF("�����Ɏ��s");
        return CtrlEditResult::getElement;
    }
    writeLogS();

    writeLogL("����I��");
    //free(automation);
    return CtrlEditResult::succeeded;
}
