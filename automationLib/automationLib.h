#pragma once

#include <Windows.h>


// ===== �����@�\ =====

// �e�L�X�g��ǂݏグ
// @param
//   message: �ǂݏグ��e�L�X�g
// @returns
//   ���s����
extern "C" __declspec(dllexport) int talk(LPCWSTR message);

// �ǂݏグ���~(��~�{�^��������)
// @returns
//   ���s����
extern "C" __declspec(dllexport) int stopTalk();


// ===== �ʋ@�\ =====

// �e�L�X�g��ݒ�
// @param
//   message: �ݒ肷��e�L�X�g
// @returns
//   ���s����
extern "C" __declspec(dllexport) int setTextView(LPCWSTR message);

// TextView�ɂ���{�^��������
// @param
//   text: �{�^���̃e�L�X�g
// @returns
//   ���s����
extern "C" __declspec(dllexport) int pushTextViewButton(LPCWSTR text);

// SleepModeOn�{�^��������
// @returns
//   ���s����
extern "C" __declspec(dllexport) int sleepMode();


// ===== �f�o�b�O =====

// �f�o�b�O��L����
extern "C" __declspec(dllexport) void enableDebug();

// �f�o�b�O�𖳌���
extern "C" __declspec(dllexport) void disableDebug();