#pragma once 
#include <Windows.h>
#include <string>
#include <iostream>
//関数のマクロ
//安全にインスタンスを開放 
#define SAFE_DELETE(p) {if(p){delete p; p=nullptr;}}
//文字列をfloat型に変更
#define SAFE_STR_TO_F(str) static_cast<float>(atof(str.c_str()));
//文字列をint型に変更
#define SAFE_STR_TO_I(str) static_cast<int>(atoi(str.c_str()));

//エラーウィンドウ
#define ERROR_MSG(str){MessageBox(NULL,TEXT(str),TEXT("Error"),MB_OK|MB_ICONERROR);}
//画面横サイズ
#define SCREEN_WIDTH 1920
//画面縦サイズ
#define SCREEN_HEIGHT 1030
//1バイト最大値
#define MAX1BYTEVALUE 255
//デルタタイム
#define DELTATIME 0.016667f
//100
#define HUNDRED 100