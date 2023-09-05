#include "DxLib.h"
#include "TimerUI.h"
#include "Utility.h"
#include "Timer.h"
#include "UIManager.h"
#include "NumUI.h"

/// <summary>
/// �c�莞�Ԃ̃Z�b�g�Ɛ����摜�̓ǂݍ���
/// </summary>
/// <param name="setTimer">�c�莞�ԃ^�C�}�[</param>
TimerUI::TimerUI(std::weak_ptr<Timer> setTimer)
{
    timer = setTimer;
    frameUI = UIManager::CreateUIData(timerFrame);
    pointUI = UIManager::CreateUIData(point);
    numUI = new NumUI(timeNum);
    //�^�C�}�[�̘g�̉��ʒu
    frameX = frameUI.x + numUI->GetNumWidthSize() * 2;
}
/// <summary>
/// �^�C�}�[�̃��b�N����
/// </summary>
TimerUI::~TimerUI()
{
    timer.reset();
}
/// <summary>
/// �^�C�}�[�̎c�莞�Ԃ�`��
/// </summary>
void TimerUI::Draw()
{
    //�^�C�}�[�̘g��`��@�����ɂ��邽�߂�
    DrawRotaGraph( frameX , frameUI.y, frameUI.size, 0, frameUI.dataHandle[0], true);
    //�c�莞�Ԃ̕`��
    float limit = timer.lock()->GetRemainingTime();
    numUI->Draw(limit);
}