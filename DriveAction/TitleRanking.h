#pragma once
#include "UIManager.h"
#include "DxLib.h"
class NumUI;
class TitleRanking
{
public:
    TitleRanking();
    ~TitleRanking();
    
    void Draw()const;
private:
    void Draw(NumUI* ui,int score,VECTOR color)const;
    //���̃X�e�[�W�̒��ň�Ԃ����X�R�A
    NumUI* highUI;
    //2�Ԗڂɗǂ��X�R�A
    NumUI* secondUI;
    //3�Ԗڂɂ����X�R�A
    NumUI* thirdUI;
    //�P�̏���UI
    NumUI* highRankUI;
    //�Q�̏���UI
    NumUI* secondRankUI;
    //3�̏���UI
    NumUI* thirdRankUI;
    //�����L���O
    UIData rankUI;

    //��Ԃ����X�R�A�̐F
    const VECTOR firstColor = VGet(255, 215, 0);
    //������Ƃ����Ƃ��̐F
    const VECTOR thirdColor = VGet(196, 112, 34);
    //��Ԗڂɂ������̐F
    const VECTOR secondColor = VGet(192, 192, 192);

};