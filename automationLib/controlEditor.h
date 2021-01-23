//talk.h

#pragma once

#include <uiautomation.h>
#include <propvarutil.h>
#include <stdio.h>

// ���s����
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

// �f�o�b�O���L�����ǂ���
extern bool ctrlEditDebug;



// COM��������
// @returns
//   ����̐���
extern HRESULT InitializeCOM();

// �e�L�X�g�{�b�N�X�ɕ������ݒ�
// @param
//   message: �ݒ肷�镶����
//   hWnd   : VOICEROID2 Editor�̃E�B���h�E�n���h��
extern CtrlEditResult SetText(LPCWSTR message, HWND hWnd);

// �J�X�^�� #c ���̎w�肵�����O�̃e�L�X�g���q�v�f�ɑ��݂���{�^��������
// @param
//   message: �{�^���̕�����
//   hWnd   : VOICEROID2 Editor�̃E�B���h�E�n���h��
extern CtrlEditResult PushCButton(LPCWSTR buttonText, HWND hWnd);

// Sleep Mode ��On�ɂ���
// @param
//   hWnd     : VOICEROID2 Editor�̃E�B���h�E�n���h��
CtrlEditResult PushSleepModeOnButton(HWND hWnd);
