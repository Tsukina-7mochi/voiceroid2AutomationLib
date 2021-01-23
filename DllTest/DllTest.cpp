#include <stdio.h>
#include "automationLib.h"

int main(){
	enableDebug();

	//printf("stopTalk: %s\n", (stopTalk() == 0 ? "成功" : "失敗"));
	printf("talk: %s\n", (talk(L"テストです。") == 0 ? "成功" : "失敗"));
	//printf("再生時間の計測: %s\n", (pushTextViewButton(L"再生時間") == 0 ? "成功" : "失敗"));
	//printf("sleepMode: %s\n", (sleepMode() == 0 ? "成功" : "失敗"));

	return 0;
}