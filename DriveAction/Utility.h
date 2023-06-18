#pragma once 
#include <Windows.h>

//関数のマクロ
//安全にインスタンスを開放 
#define SAFE_DELETE(p) {if(p){delete p; p=nullptr;}}

#define SAFE_UNIQUE_DELETE(uniPtr) {if(uniPtr){ uniPtr.reset(); uniPtr=nullptr;}}

//エラーウィンドウ
#define ERROR_MSG(str){MessageBox(NULL,TEXT(str),TEXT("Error"),MB_OK|MB_ICONERROR);}

#define SCREEN_WIDTH 1920

#define SCREEN_HEIGHT 1030

#define MAX1BYTEVALUE 255

#define UI_SCREEN_WIDTH 96

#define UI_SCREEN_HEIGHT 51.5

#define DELTATIME 0.016667f

#define HUNDRED 100