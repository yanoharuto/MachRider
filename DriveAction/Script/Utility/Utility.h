#pragma once 
#include <Windows.h>
#include <string>
#include <iostream>
//�֐��̃}�N��
//���S�ɃC���X�^���X���J�� 
#define SAFE_DELETE(p) {if(p){delete p; p=nullptr;}}

#define SAFE_STR_TO_F(f) static_cast<float>(atof(f.c_str()));

//�G���[�E�B���h�E
#define ERROR_MSG(str){MessageBox(NULL,TEXT(str),TEXT("Error"),MB_OK|MB_ICONERROR);}
//��ʉ��T�C�Y
#define SCREEN_WIDTH 1920
//��ʏc�T�C�Y
#define SCREEN_HEIGHT 1030
//1�o�C�g�ő�l
#define MAX1BYTEVALUE 255
//�f���^�^�C��
#define DELTATIME 0.016667f
//100
#define HUNDRED 100